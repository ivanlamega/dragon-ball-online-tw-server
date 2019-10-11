#ifndef _AUTHSOCKET_H
#define _AUTHSOCKET_H

#include <SharedDef.h>
#include <Socket.h>
#include <boost/asio.hpp>
#include <functional>
#include <Packet.h>

class AuthSocket : public Socket
{
public:
	AuthSocket(boost::asio::io_service &service, std::function<void(Socket *)> closeHandler);
	bool _HandleOnLogin(Packet& packet);
	bool _ProcessLoginPacket(Packet& packet);
private:
	virtual bool ProcessIncomingData() override;
	virtual void OnConnectionDone() override;
	virtual void OnClosed() override;
};
#endif