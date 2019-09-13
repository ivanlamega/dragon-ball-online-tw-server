#include <string>
#include <memory>
#include <vector>
#include <functional>

#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <boost/lexical_cast.hpp>

#include <Socket.h>
#include <Logger.h>
#include <Packet.h>

PACKETHEADER header;

Socket::Socket(boost::asio::io_service &service, std::function<void(Socket *)> closeHandler)
	: m_socket(service), m_address("0.0.0.0"), m_outBufferFlushTimer(service),
	m_closeHandler(closeHandler), m_writeState(WriteState::Idle), m_readState(ReadState::Idle) 
{
	
}

bool Socket::Open()
{
	try
	{
		const_cast<std::string &>(m_address) = m_socket.remote_endpoint().address().to_string();
		const_cast<std::string &>(m_remoteEndpoint) = boost::lexical_cast<std::string>(m_socket.remote_endpoint());
	}
	catch (boost::system::error_code& error)
	{
		sLog.outError("Socket::Open() failed to get remote address.  Error: %s", error.message().c_str());
		return false;
	}

	m_outBuffer.reset(new PacketBuffer);
	m_secondaryOutBuffer.reset(new PacketBuffer);
	m_inBuffer.reset(new PacketBuffer);

	StartAsyncRead();
	OnConnectionDone();
	return true;
}

void Socket::Close()
{
	OnClosed();
	assert(!IsClosed());
	boost::system::error_code ec;
	m_socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ec);
	m_socket.close();

	if (m_closeHandler)
		m_closeHandler(this);
	ReadSkip(ReadLengthRemaining());
}

void Socket::StartAsyncRead()
{
	if (IsClosed())
	{
		m_readState = ReadState::Idle;
		return;
	}
	m_readState = ReadState::Reading;

	m_socket.async_read_some(boost::asio::buffer(&m_inBuffer->m_buffer[m_inBuffer->m_writePosition], m_inBuffer->m_buffer.size() - m_inBuffer->m_writePosition),
		[this](const boost::system::error_code &error, size_t length) { this->OnRead(error, length); });
}

void Socket::OnRead(const boost::system::error_code &error, size_t length)
{
	if (error)
	{
		m_readState = ReadState::Idle;
		OnError(error);
		return;
	}
	if (IsClosed())
	{
		m_readState = ReadState::Idle;
		return;
	}
	m_inBuffer->m_writePosition += length;
	const size_t available = m_socket.available();
	if (available > 0 && (length + available) > m_inBuffer->m_buffer.size())
	{
		m_inBuffer->m_buffer.resize(m_inBuffer->m_buffer.size() + available);
		StartAsyncRead();
		return;
	}
	while (m_inBuffer->m_readPosition < m_inBuffer->m_writePosition)
	{
		if (ProcessIncomingData() == false)
		{
			if (errno == EBADMSG)
			{
				const size_t bytesRemaining = m_inBuffer->m_writePosition - m_inBuffer->m_readPosition;
				if (m_inBuffer->m_readPosition >= bytesRemaining)
					memcpy(&m_inBuffer->m_buffer[0], &m_inBuffer->m_buffer[m_inBuffer->m_readPosition], bytesRemaining);
				else
				{
					std::vector<uint8> temporaryBuffer(m_inBuffer->m_buffer.size());
					memcpy(&temporaryBuffer[0], &m_inBuffer->m_buffer[m_inBuffer->m_readPosition], bytesRemaining);
					m_inBuffer->m_buffer = std::move(temporaryBuffer);
				}
				m_inBuffer->m_readPosition = 0;
				m_inBuffer->m_writePosition = bytesRemaining;
				StartAsyncRead();
			}
			else
				Close();
			return;
		}
	}
	m_inBuffer->m_writePosition = m_inBuffer->m_readPosition = 0;
	StartAsyncRead();
}

void Socket::OnError(const boost::system::error_code &error)
{
	if (error != boost::asio::error::eof &&
		error != boost::asio::error::operation_aborted)
		sLog.outError("Socket::OnError.  %s.  Connection closed.", error.message().c_str());

	if (!IsClosed())
		Close();
}

bool Socket::Read(char *buffer, int length)
{
	if (ReadLengthRemaining() < length)
		return false;
	m_inBuffer->Read(buffer, length);
	return true;
}

void Socket::Write(const char *buffer, int length)
{
	std::lock_guard<std::mutex> guard(m_mutex);
	switch (m_writeState)
	{
	case WriteState::Idle:
	{
		m_outBuffer->Write(buffer, length);
		StartWriteFlushTimer();
		break;
	}
	case WriteState::Buffering:
	{
		m_outBuffer->Write(buffer, length);
		break;
	}
	case WriteState::Sending:
	{
		m_secondaryOutBuffer->Write(buffer, length);
		break;
	}
	default:
		assert(false);
	}
}

void Socket::StartWriteFlushTimer()
{
	if (m_writeState == WriteState::Buffering)
		return;
	if (IsClosed())
	{
		m_writeState = WriteState::Idle;
		return;
	}
	m_writeState = WriteState::Buffering;
	m_outBufferFlushTimer.expires_from_now(boost::posix_time::milliseconds(BufferTimeout));
	m_outBufferFlushTimer.async_wait([this](const boost::system::error_code &error) { this->FlushOut(); });
}

void Socket::FlushOut()
{
	if (IsClosed())
	{
		m_writeState = WriteState::Idle;
		return;
	}
	std::lock_guard<std::mutex> guard(m_mutex);
	assert(m_writeState == WriteState::Buffering);
	m_writeState = WriteState::Sending;
	m_socket.async_write_some(boost::asio::buffer(m_outBuffer->m_buffer, m_outBuffer->m_writePosition),
		[this](const boost::system::error_code &error, size_t length) { this->OnWriteComplete(error, length); });
}
void Socket::ForceFlushOut()
{
	m_outBufferFlushTimer.cancel();
}

void Socket::OnWriteComplete(const boost::system::error_code &error, size_t length)
{
	if (error)
	{
		OnError(error);
		return;
	}
	if (IsClosed())
	{
		m_writeState = WriteState::Idle;
		return;
	}
	std::lock_guard<std::mutex> guard(m_mutex);
	assert(m_writeState == WriteState::Sending);
	assert(length <= m_outBuffer->m_writePosition);
	if (length < m_outBuffer->m_writePosition)
	{
		std::copy(&m_outBuffer->m_buffer[length], &m_outBuffer->m_buffer[m_outBuffer->m_writePosition], m_outBuffer->m_buffer.begin());
		m_outBuffer->m_writePosition -= length;
	}
	else
		m_outBuffer->m_writePosition = 0;

	if (m_secondaryOutBuffer->m_writePosition > 0)
	{
		if (m_outBuffer->m_buffer.size() < (m_outBuffer->m_writePosition + m_secondaryOutBuffer->m_writePosition))
			m_outBuffer->m_buffer.resize(m_outBuffer->m_writePosition + m_secondaryOutBuffer->m_writePosition);

		std::copy(&m_secondaryOutBuffer->m_buffer[0], &m_secondaryOutBuffer->m_buffer[m_secondaryOutBuffer->m_writePosition], &m_outBuffer->m_buffer[m_outBuffer->m_writePosition]);

		m_outBuffer->m_writePosition += m_secondaryOutBuffer->m_writePosition;
		m_secondaryOutBuffer->m_writePosition = 0;
	}
	if (m_outBuffer->m_writePosition > 0)
		m_socket.async_write_some(boost::asio::buffer(m_outBuffer->m_buffer, m_outBuffer->m_writePosition),
			[this](const boost::system::error_code &error, size_t length) { this->OnWriteComplete(error, length); });
	else
		m_writeState = WriteState::Idle;
}