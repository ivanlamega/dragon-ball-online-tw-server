#ifndef __SOCKET_H_
#define __SOCKET_H_

#include <memory>
#include <string>
#include <mutex>
#include <functional>

#include <asio.hpp>
#include <PacketBuffer.h>

class Socket
{
private:
	static const int BufferTimeout = 50;

	enum class WriteState
	{
		Idle,
		Buffering,
		Sending,
	};

	enum class ReadState
	{
		Idle,
		Reading
	};

	WriteState m_writeState;
	ReadState m_readState;

	boost::asio::ip::tcp::socket m_socket;

	std::function<void(Socket *)> m_closeHandler;

	std::unique_ptr<PacketBuffer> m_inBuffer;
	std::unique_ptr<PacketBuffer> m_outBuffer;
	std::unique_ptr<PacketBuffer> m_secondaryOutBuffer;

	std::mutex m_mutex;
	boost::asio::deadline_timer m_outBufferFlushTimer;

	void StartAsyncRead();
	void OnRead(const boost::system::error_code &error, size_t length);

	void StartWriteFlushTimer();
	void OnWriteComplete(const boost::system::error_code &error, size_t length);
	void FlushOut();

	void OnError(const boost::system::error_code &error);

protected:
	const std::string m_address;
	const std::string m_remoteEndpoint;

	virtual bool ProcessIncomingData() = 0;
	virtual void OnConnectionDone() = 0;
	virtual void OnClosed() = 0;

	const uint8 *InPeak() const { return &m_inBuffer->m_buffer[m_inBuffer->m_readPosition]; }

	size_t ReadLengthRemaining() const { return m_inBuffer->ReadLengthRemaining(); }

	void ForceFlushOut();

public:
	Socket(boost::asio::io_service &service, std::function<void(Socket *)> closeHandler);
	virtual ~Socket() { assert(Deletable()); }

	virtual bool Open();
	void Close();

	bool IsClosed() const { return !m_socket.is_open(); }
	virtual bool Deletable() const { return IsClosed(); }

	bool Read(char *buffer, int length);
	void ReadSkip(int length) { m_inBuffer->Read(nullptr, length); }

	void Write(const char *buffer, int length);

	boost::asio::ip::tcp::socket &GetAsioSocket() { return m_socket; }

	const std::string &GetRemoteEndpoint() const { return m_remoteEndpoint; }
	const std::string &GetRemoteAddress() const { return m_address; }
};
#endif /* !__SOCKET_H_ */