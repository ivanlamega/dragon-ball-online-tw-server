#include <GameSocket.h>
#include <Define.h>
#include <Logger.h>
#include <Opcodes.h>
#include <Packet.h>
#include "WorldSession.h"
#include <Game\Object\Player.h>
#include <World.h>
#include <Packet\Game\PacketGU.h>
#include <Packet\Game\PacketUG.h>
#include <mysqlconn_wrapper.h>

#include <mutex>
#include <deque>
#include <memory>

//----------------------------------------
//	World Session Constructor, init all session info
//----------------------------------------
WorldSession::WorldSession(uint32 id, GameSocket* sock, AccountTypes sec) :
	m_Socket(sock), _security(sec), _accountId(id), requestToLogout(false), _player(nullptr)
{
	m_recvQueue.clear();
}
//----------------------------------------
//	World Session destructor, Logout player and close socket
//----------------------------------------
WorldSession::~WorldSession()
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
bool WorldSession::CreatePlayer(CHARACTERID id)
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
	sDB.UpdateAccountOnline(GetAccountId(), 2); // SET OUR USER ONLINE IN DB
	return true;
}
//----------------------------------------
//	Get IP from client
//----------------------------------------
const std::string &WorldSession::GetRemoteAddress() const
{
	return m_Socket->GetRemoteAddress();
}
//----------------------------------------
//	Send packet to our game
//----------------------------------------
void WorldSession::SendPacket(char* packet, size_t size)
{
	if (m_Socket->IsClosed())
		return;
	m_Socket->Write(packet, size);
}
//----------------------------------------
//	Queue a packet to process, for now it not works, some packet aren't added...
//----------------------------------------
void WorldSession::QueuePacket(std::unique_ptr<Packet> new_packet)
{
	std::lock_guard<std::mutex> guard(m_recvQueueLock);
	m_recvQueue.push_back(std::move(new_packet));
}
//----------------------------------------
//	Update the session, trigger by World Tick()
//----------------------------------------
bool WorldSession::Update()
{

	
	try
	{
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
		return true;
	}
	catch (std::logic_error&)
	{
			sLog.outError("[exception caught] in update thread\n");
	}

	


}
//----------------------------------------
//	Logout the player and save if asked
//----------------------------------------
void WorldSession::LogoutPlayer(bool save)
{
	// if the player has just logged out, there is no need to do anything here
	if (_player)
	{
		// update population realm.

		// save player
		if (save)
			_player->SavePlayer();

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
		_player = nullptr;  // deleted in Remove/DeleteFromWorld call
	}
}
/// Kick a player out of the World
void WorldSession::KickPlayer()
{
	if (!m_Socket->IsClosed())
		m_Socket->Close();
}