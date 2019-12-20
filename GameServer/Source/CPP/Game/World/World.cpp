#include "World.h"
#include <WorldSession.h>
#include <Game\Maps\MapManager.h>
#include <mysqlconn_wrapper.h>
#include <XmlParser2/XmlParser2.h>
#include <Logger.h>

#include <algorithm>
#include <mutex>
#include <cstdarg>

#define DEFAULT_PLAYER_LIMIT 100

volatile bool World::m_stopEvent = false;
volatile uint32 World::m_worldLoopCounter = 0;
uint8 World::m_ExitCode = SHUTDOWN_EXIT_CODE;

static HOBJECT m_uiSerialId = 5;
static HOBJECT m_iSerialId = 1000000;
static HOBJECT m_iHandleObjectOffset = 100000;

WORD byte_to_opcode(unsigned char val)
{
	return (WORD)((WORD)&val);
}
INT32 dbo_move_float_to_pos(float in_f)
{
	int in_i = in_f * 100;
	
	bool negative = in_i < 0;
	if (negative) in_i *= -1;
	
	int ret;
	unsigned char *in_p = (unsigned char *)&in_i;
	unsigned char *ret_p = (unsigned char *)&ret;
	ret_p[0] = in_p[2];
	ret_p[1] = in_p[3];
	ret_p[2] = in_p[0];
	ret_p[3] = in_p[1];
	
	if (negative) ret_p[0] |= 0x80; // apply the sign bit
	
	return ret;
	
}
float dbo_move_pos_to_float(INT32 n)
{
	float f;
	unsigned char *p = (unsigned char *)&n;
	if (htonl(47) == 47) // BIG ENDIAN
	{
		sLog.outError("BIG ENDIAN EXPECTED");
	}
	else
	{
		f = static_cast<float>((p[1] << 24) + ((p[0] & 0x7f) << 16) + (p[3] << 8) + (p[2]));
		((char *)&f)[3] |= (p[0] & 0x80);	/* first byte sign bit for a float */
		f /= 100.0;
	}
	return f;
}
uint32 World::AcquireSerialId(void)
{
	if (m_uiSerialId++)
	{
		if (m_uiSerialId == 0xffffffff)//INVALID_SERIAL_ID)
			m_uiSerialId = 0;
	}

	return m_uiSerialId;
}

uint32 World::AcquireItemSerialId(void)
{
	if (m_iSerialId++)
	{
		if (m_iSerialId == 0xffffffff)//INVALID_SERIAL_ID)
			m_iSerialId = 0;
	}

	return m_iSerialId;
}

World::World()
{
	m_playerLimit = DEFAULT_PLAYER_LIMIT;
}
World::~World()
{
}
void World::SendToAll(char* data, size_t size)
{
	for (SessionMap::iterator itr = m_sessions.begin(); itr != m_sessions.end(); itr++)
	{
		WorldSession* pSession = itr->second;

		if (pSession != NULL)
		{
			pSession->SendPacket(data, size);
		}
	}
}
void World::Update(uint32 diff)
{
	/// <li> Handle session updates
	UpdateSessions(diff);

	/// <li> Update maps
	sMapMgr.Update(diff);

	/// </ul>
	///- Move all creatures with "delayed move" and remove and delete all objects with "delayed remove"
	sMapMgr.RemoveAllObjectsInRemoveList();
}
void handle_eptr(std::exception_ptr eptr) // passing by value is ok
{
	try {
		if (eptr) {
			std::rethrow_exception(eptr);
		}
	}
	catch (const std::exception& e) {
		std::cout << "Caught exception \"" << e.what() << "\"\n";
	}
}
void World::UpdateSessions(uint32 /*diff*/)
{
	std::exception_ptr eptr;
	///- Add new sessions
	{
		std::lock_guard<std::mutex> guard(m_sessionAddQueueLock);

		for (auto const &session : m_sessionAddQueue)
		{
			AddSession_(session);
		}

		m_sessionAddQueue.clear();
	}

	///- Then send an update signal to remaining ones
	for (SessionMap::iterator itr = m_sessions.begin(); itr != m_sessions.end(); )
	{
		///- and remove not active sessions from the list
		WorldSession* pSession = itr->second;
		// if WorldSession::Update fails, it means that the session should be destroyed
		if (!pSession->Update())
		{

			sLog.outError("Session must be destroyed");
			//Decress Player Pupulation
			uint32 Sessions = GetActiveSessionCount();
			uint32 pLimit = GetPlayerAmountLimit();
			if (Sessions > 0){ Sessions -= 1; }
			sLog.outDetail("Server Population (%d). Max Population (%d).", Sessions, pLimit);
			try {
				sDB.SetGameServerState(sXmlParser.GetInt("Server", "ID"), sXmlParser.GetInt("Server", "ChannelID"), eDBO_SERVER_STATUS::DBO_SERVER_STATUS_UP, Sessions);
				sql::ResultSet* result = sDB.executes("UPDATE account SET AccountStatus = 0 WHERE AccountStatus = 2;");
				if (result != NULL)
					delete result;
			}
			catch(...){
				eptr = std::current_exception();
			}
			handle_eptr(eptr);

			itr = m_sessions.erase(itr);
			if (pSession != NULL)
				delete pSession;
		}
		else
			++itr;
	}
}
/// Remove a given session
bool World::RemoveSession(uint32 id)
{
	///- Find the session if it already exist and kick the user, but we can't delete session at this moment to prevent iterator invalidation
	SessionMap::const_iterator itr = m_sessions.find(id);

	if (itr != m_sessions.end() && itr->second)
	{
		itr->second->KickPlayer();
	}
	return true;
}
/// Find a session by its id
WorldSession* World::FindSession(uint32 id) const
{
	SessionMap::const_iterator itr = m_sessions.find(id);

	if (itr != m_sessions.end())
		return itr->second;// also can return nullptr for kicked session
	else
		return nullptr;
}
void World::AddSession_(WorldSession* s)
{
	assert(s != NULL);

	if (!RemoveSession(s->GetAccountId()))
	{
		sLog.outError("World::AddSession_ kicking player");
		s->KickPlayer();
		delete s; // session not added yet in session list, so not listed in queue
		return;
	}
	// decrease session counts only at not reconnection case
	bool decrease_session = true;
	// if session already exist, prepare to it deleting at next world update
	// NOTE - KickPlayer() should be called on "old" in RemoveSession()
	{
		SessionMap::const_iterator old = m_sessions.find(s->GetAccountId());

		if (old != m_sessions.end())
		{
			decrease_session = false;
		}
	}
	m_sessions[s->GetAccountId()] = s;

	uint32 Sessions = GetActiveSessionCount();
	uint32 pLimit = GetPlayerAmountLimit();

	if (decrease_session)
		--Sessions;

	if (pLimit > 0 && Sessions >= pLimit && s->GetSecurity() == AccountTypes::PLAYER)
	{
		// send player hard logout
		sLog.outError("Send player hard logout, limit of player reach");
		return;
	}
	// Updates the population
	if (pLimit > 0)
	{
		sLog.outDetail("Server Population (%d).", GetActiveSessionCount());
		sDB.SetGameServerState(sXmlParser.GetInt("Server", "ID"), sXmlParser.GetInt("Server", "ChannelID"), eDBO_SERVER_STATUS::DBO_SERVER_STATUS_UP, GetActiveSessionCount());
	}
}