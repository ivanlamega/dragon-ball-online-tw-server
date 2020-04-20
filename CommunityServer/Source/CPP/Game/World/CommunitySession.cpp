#include <CommunitySocket.h>
#include <Define.h>
#include <Logger.h>
#include <Opcodes.h>
#include <Packet.h>
#include "CommunitySession.h"
#include <Game\Object\Player.h>
#include <Community.h>
#include <Packet\Community\PacketTU.h>
#include <Packet\Community\PacketUT.h>
#include <mysqlconn_wrapper.h>

#include <mutex>
#include <deque>
#include <memory>

//----------------------------------------
//	World Session Constructor, init all session info
//----------------------------------------
CommunitySession::CommunitySession(uint32 id, CommunitySocket* sock, AccountTypes sec) :
	m_Socket(sock), _security(sec), _accountId(id), requestToLogout(false), _player(nullptr)
{
	m_recvQueue.clear();
}
//----------------------------------------
//	World Session destructor, Logout player and close socket
//----------------------------------------
CommunitySession::~CommunitySession()
{
	///- unload player if not unloaded
	if (_player)
	{
		LogoutPlayer(true);
	}
	m_Socket->ClearSession();
}
//----------------------------------------
//	Called when game need to access the world, create the player and fill info from DB
//----------------------------------------
bool CommunitySession::CreatePlayer(CHARACTERID id)
{
	_player = new Player(this);

	if (!_player->Create(id)) // character create failed
	{
		sLog.outError("Failed to create player with charid: %d, from accountid: %d", id, GetAccountId());
		delete _player;
		_player = nullptr;
		return false;
	}

	_player->accID = GetAccountId();

	//Load Friend List Info On load into memory
	_player->LoadFriendList(_player->accID, _player->friendlist);
	

	return true;
}
//----------------------------------------
//	Get IP from client
//----------------------------------------
const std::string &CommunitySession::GetRemoteAddress() const
{
	return m_Socket->GetRemoteAddress();
}
//----------------------------------------
//	Send packet to our game
//----------------------------------------
void CommunitySession::SendPacket(char* packet, size_t size)
{
	if (m_Socket->IsClosed())
		return;
	m_Socket->Write(packet, size);
}
//----------------------------------------
//	Queue a packet to process, for now it not works, some packet aren't added...
//----------------------------------------
void CommunitySession::QueuePacket(std::unique_ptr<Packet> new_packet)
{
	std::lock_guard<std::mutex> guard(m_recvQueueLock);
	m_recvQueue.push_back(std::move(new_packet));
}
//----------------------------------------
//	Update the session, trigger by World Tick()
//----------------------------------------
bool CommunitySession::Update()
{
		
	try {
		std::lock_guard<std::mutex> guard(m_recvQueueLock);
		///- Retrieve packets from the receive queue and call the appropriate handlers
		/// not process packets if socket already closed
		while (m_Socket && !m_Socket->IsClosed() && !m_recvQueue.empty())
		{
			auto const packet = std::move(m_recvQueue.front());
			m_recvQueue.pop_front();
			PacketParser(*packet);
			packet->Destroy();
		}
		// check if we are safe to proceed with logout
		// logout procedure should happen only in World::UpdateSessions() method!!!
		if (requestToLogout == true || m_Socket->IsClosed() == true)
		{
			LogoutPlayer(true);
			return false;
		}
	}
	catch (std::logic_error&)
	{
		sLog.outError("[Exception Caught in Update Process]");
	}
	return true;
}
//----------------------------------------
//	Logout the player and save if asked
//----------------------------------------
void CommunitySession::LogoutPlayer(bool save)
{

	//Logging off
	NotifyOtherPlayersFriendList_onLogoff();
	NotifyguildiesAfterLoginOff();

	
	// if the player has just logged out, there is no need to do anything here
	if (_player)
	{
		// update population realm.

		// save player
		if (save)
			sLog.outDebug("We Don't Save the player on the community Server");
		///- Remove the player from the world
		// the player may not be in the world when logging out
		// e.g if he got disconnected during a transfer to another map
		// calls to GetMap in this case may cause crashes
		if (_player->IsInWorld())
		{
			Map* _map = _player->GetMap();
			_map->Remove(_player, true);
		}
		else
		{
			_player->CleanupsBeforeDelete();
			Map::DeleteFromWorld(_player); 
		}
		if (_player->isMovingToCharServer == false)
			sDB.UpdateAccountOnline(_player->accID, 0); // SET OUR USER OFFLINE IN DB
		sql::ResultSet* result1 = sDB.executes("UPDATE characters SET IsOnline = 0 WHERE CharacterID = '%d';", _player->charid);
		if (result1 != NULL)
			delete result1;		
		sql::ResultSet* result2 = sDB.executes("UPDATE characters SET GSHandle = 0 WHERE CharacterID = '%d';", _player->charid);
		if (result2 != NULL)
			delete result2;
		_player = nullptr;  // deleted in Remove/DeleteFromWorld call
	}
}
/// Kick a player out of the World
void CommunitySession::KickPlayer()
{
	if (!m_Socket->IsClosed())
		m_Socket->Close();
}

void CommunitySession::Updatefriendlist() {



}

