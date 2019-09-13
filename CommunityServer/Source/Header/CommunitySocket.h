#ifndef _COMMUNITYSOCKET_H
#define _COMMUNITYSOCKET_H

#pragma once

#include <Socket.h>
#include <chrono>
#include <functional>
#include <Packet.h>

class CommunitySession;

class CommunitySocket : public Socket
{
public:
	CommunitySocket(boost::asio::io_service &service, std::function<void(Socket *)> closeHandler);
	void ClearSession() { m_session = nullptr; }
private:
	bool HandleAuthSession(Packet& packet);
private:
	virtual bool ProcessIncomingData() override;
	virtual void OnConnectionDone() override;
	virtual void OnClosed() override;

	CommunitySession *m_session;
	bool m_sessionFinalized;

	PACKETHEADER m_existingHeader;
	bool m_useExistingHeader;
};
#endif