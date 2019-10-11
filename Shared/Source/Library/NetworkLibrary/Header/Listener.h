#ifndef __LISTENER_H_
#define __LISTENER_H_

#include <memory>
#include <thread>
#include <vector>

#include <asio.hpp>

#include <Listener.h>
#include <NetworkThread.h>
#include <Logger.h>

template <typename SocketType>
class Listener
{
private:
	boost::asio::io_service m_service;
	boost::asio::ip::tcp::acceptor m_acceptor;
	std::thread m_acceptorThread;
	std::vector<std::unique_ptr<NetworkThread<SocketType>>> m_workerThreads;

	void BeginAccept();
	void OnAccept(NetworkThread<SocketType> *worker, SocketType *socket, const boost::system::error_code &ec);

	const int SleepInterval = 100;
	NetworkThread<SocketType> *SelectWorker() const
	{
		int minIndex = 0;
		size_t minSize = m_workerThreads[minIndex]->Size();

		for (size_t i = 1; i < m_workerThreads.size(); ++i)
		{
			const size_t size = m_workerThreads[i]->Size();

			if (size < minSize)
			{
				minSize = size;
				minIndex = (int)i;
			}
		}
		return m_workerThreads[minIndex].get();
	}
public:
	Listener(int port, int workerThreads);
	~Listener();
};

template <typename SocketType>
Listener<SocketType>::Listener(int port, int workerThreads) : m_acceptor(m_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port))
{
	sLog.outDebug("Listener will be initiate at port: %d and at %d workerThread", m_acceptor.local_endpoint().port(), workerThreads);
	m_workerThreads.reserve(workerThreads);
	for (int i = 0; i < workerThreads; ++i)
		m_workerThreads.push_back(std::unique_ptr<NetworkThread<SocketType>>(new NetworkThread<SocketType>));
	BeginAccept();
	m_acceptorThread = std::thread([this]() { this->m_service.run(); });
}
template <typename SocketType>
Listener<SocketType>::~Listener()
{
	m_service.stop();
	m_acceptor.close();
	m_acceptorThread.join();
}
template <typename SocketType>
void Listener<SocketType>::BeginAccept()
{
	NetworkThread<SocketType> *worker = SelectWorker();
	SocketType *socket = worker->CreateSocket();
	m_acceptor.async_accept(socket->GetAsioSocket(), [this, worker, socket](const boost::system::error_code &ec) { this->OnAccept(worker, socket, ec); });
}
template <typename SocketType>
void Listener<SocketType>::OnAccept(NetworkThread<SocketType> *worker, SocketType *socket, const boost::system::error_code &ec)
{
	// an error has occurred
	if (ec)
	{
		std::cout << ec << std::endl;
		worker->RemoveSocket(socket);
	}
	else
	{
		socket->Open();
	}
	BeginAccept();
}
#endif	__LISTENER_H_