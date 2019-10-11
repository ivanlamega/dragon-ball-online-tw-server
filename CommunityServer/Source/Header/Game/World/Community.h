#ifndef __COMMUNITY_H
#define __COMMUNITY_H

#include <Singleton.h>
#include <Util\Util.h>

#include <set>
#include <list>
#include <deque>
#include <mutex>
#include <functional>
#include <vector>
#include <unordered_map>
#include <cassert>

#define DBO_MOVE_DIR_TO_FLOAT(n) \
	(n / (float) 10000.0)
#define DBO_MOVE_FLOAT_TO_DIR(n) \
	(n * (int16) 10000.0)

WORD byte_to_opcode(unsigned char val);
float dbo_move_pos_to_float(INT32 n); // thanks sangawku
INT32 dbo_move_float_to_pos(float n); // thanks luizoe

enum ShutdownMask
{
	SHUTDOWN_MASK_RESTART = 1,
	SHUTDOWN_MASK_IDLE = 2,
};

enum ShutdownExitCode
{
	SHUTDOWN_EXIT_CODE = 0,
	ERROR_EXIT_CODE = 1,
	RESTART_EXIT_CODE = 2,
};

class CommunitySession;
/// The Community
class Community
{
public:
	static volatile uint32 m_worldLoopCounter;

	Community();
	~Community();
	bool Shenlong = false;
	static void StopNow(uint8 exitcode) { m_stopEvent = true; m_ExitCode = exitcode; }
	static bool IsStopped() { return m_stopEvent; }
	void Update(uint32 diff);
	void UpdateSessions(uint32 diff);
	void AddSession_(CommunitySession* s);
	CommunitySession* FindSession(uint32 id) const;
	bool RemoveSession(uint32 id);

	uint32 GetActiveSessionCount() const { return m_sessions.size(); }
	uint32 GetPlayerAmountLimit() const { return m_playerLimit >= 0 ? m_playerLimit : 0; }

	uint32	AcquireSerialId();
	uint32	AcquireItemSerialId();

	void	SendToAll(char* data, size_t size);

	//	GM COMMAND
//	void			SendAnnounce(std::string message);
protected:

private:
	static volatile bool m_stopEvent;
	static uint8 m_ExitCode;
	int32 m_playerLimit;

	typedef std::unordered_map<uint32, CommunitySession*> SessionMap;
	SessionMap m_sessions;
	uint32 m_maxActiveSessionCount;
	uint32 m_maxQueuedSessionCount;

	std::mutex m_sessionAddQueueLock;
	std::deque<CommunitySession*> m_sessionAddQueue;
	// Player Queue
	typedef std::list<CommunitySession*> Queue;
	Queue m_QueuedSessions;
};

extern uint32 realmID;

#define sCommunity AKCore::Singleton<Community>::Instance()
#endif
/// @}
