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
	GAME_MASTER = 1
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
	
	/* Guild Manager */ /* DBO-MELIODAS 23-07-2019 */
	void SendGuildDisband(Packet packet); // Salir de la Guild
	void SendGuildInvitationResponse(Packet packet); // Invitar Guild 
	void SendGuildLeave(Packet packet); // TEST 
	void SendGuildKickOut(Packet packet); // Sacar a un miembro? ver 
	void SendAppointSecondMaster(Packet packet); // pasar a Segundo master
	void SendDismissSecondMaster(Packet packet); // Sacar al segundo master
	void SendChangeGuildMaster(Packet packet); // Cambiar de Master en la Guild
	void SendChangeNotice(Packet packet); // Cambiar la noticia de la guild

	// Friend Manager
	void SendFriendAdd(Packet packet);
	void SendFriendDelete(Packet packet);
	void SendFriendMove(Packet packet);
	void SendFriendBlackAdd(Packet packet);
	void SendFriendBlackDelete(Packet packet);
	void SendFriendListInfomation();
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
