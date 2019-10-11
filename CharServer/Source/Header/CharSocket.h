#ifndef _CHARSOCKET_H
#define _CHARSOCKET_H

#include <Socket.h>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <functional>
#include <Packet.h>
#include <TableAll.h>
#include <Singleton.h>

class CharSocket : public Socket
{
public:
	CharSocket(boost::asio::io_service &service, std::function<void(Socket *)> closeHandler);
	bool _ProcessCharPacket(Packet& packet, WORD wOpCode);
	// Packet Management
	bool GetLoginRequest(Packet &packet);
	bool GetCharacterServerList(Packet &packet, bool one);
	bool GetCharacterLoad(Packet &packet);
	int AddCharacters(sPC_SUMMARY data);
	bool GetCreateCharactersRequest(Packet &packet);
	bool GetCharactersDeleteRequest(Packet &packet);
	void SendCharacterList();
	bool SendCharacterExit(Packet &packet);
	bool SendCancelCharacterDeleteRequest(Packet &packet);
	bool SendCharSelect(Packet &packet);
	bool SendConnectWaitCheck(Packet& packet);
	bool SendCharacterRename(Packet& packet);
	bool HaveToSendOneServer();
private:
	virtual bool ProcessIncomingData() override;
	virtual void OnConnectionDone() override;
	virtual void OnClosed() override;

	int AccountID;
	int ServerID;
	char username[MAX_SIZE_USERID_UNICODE + 1];
	bool isGameMaster;
};
#endif