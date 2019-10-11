#ifndef __COMMUNITYSESSION_H
#define __COMMUNITYSESSION_H

#include <Define.h>

#include <SharedDef.h>
#include <SharedType.h>

#include <deque>
#include <mutex>
#include <memory>

enum AccountTypes
{
	PLAYER = 0,
	GAME_MASTER
};
class Packet;
class CommunitySocket;
class Player;
enum eCHARSTATE;
struct sITEM_PROFILE;

class CommunitySession
{
public:
	CommunitySession(uint32 id, CommunitySocket* sock, AccountTypes sec);
	~CommunitySession();

	void			SendPacket(char* packet, size_t size);

	AccountTypes	GetSecurity() const { return _security; }
	uint32			GetAccountId() const { return _accountId; }
	void			SetSecurity(AccountTypes security) { _security = security; }
	const			std::string &GetRemoteAddress() const;
	void			QueuePacket(std::unique_ptr<Packet> new_packet);
	bool			Update();
	void			LogoutPlayer(bool save);
	void			KickPlayer();
	bool			CreatePlayer(CHARACTERID id);
	// PACKET
	void			PacketParser(Packet& packet);
	// PACKET PROCESS

	/*     Chat Manager    */
	void SendLocalChat(Packet packet);
	void SendShoutChat(Packet packet);
	void SendTradeChat(Packet packet);
	void SendLFGChat(Packet packet);

	//Cash Shop Manager
	void SendHlsSlotMachineInfo(Packet packet);
	void SendHlsSlotMachineExtract(Packet packet);
	void SendHlsSlotMachineWinnerInfo(Packet packet);

private:
	CommunitySocket * const m_Socket;                       // socket pointer is owned by the network thread which created 
	AccountTypes	_security;
	uint32			_accountId;
	std::wstring     _charName;
	std::mutex		m_recvQueueLock;
	std::deque<std::unique_ptr<Packet>> m_recvQueue;

	bool			requestToLogout;
	/*	 PLAYER INFO	*/
	Player*			_player;


	/*		END			*/
};
#endif
/// @}
