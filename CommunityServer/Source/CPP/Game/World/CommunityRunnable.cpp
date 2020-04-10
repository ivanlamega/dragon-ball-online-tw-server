#include <Community.h>
#include <Timer.h>
#include <CommunityRunnable.h>
#include <mysqlconn_wrapper.h>
//#include "ObjectAccessor.h"

#define WORLD_SLEEP_CONST 100
extern int m_ServiceStatus;

/// Heartbeat for the World
void CommunityRunnable::run()
{

	//sWorld.InitResultQueue();

	uint32 realCurrTime = 0;
	uint32 realPrevTime = CommunityTimer::tick();

	uint32 prevSleepTime = 0;         // used for balanced full tick time length near WORLD_SLEEP_CONST

									 ///- While we have not World::m_stopEvent, update the world
	time_t pingDatabase = 0;		 // ping database to keep alive connection

	while (!Community::IsStopped())
	{

		++Community::m_worldLoopCounter;
		realCurrTime = CommunityTimer::getMSTime();

		uint32 diff = CommunityTimer::tick();

		sCommunity.Update(diff);
		realPrevTime = realCurrTime;

		// diff (D0) include time of previous sleep (d0) + tick time (t0)
		// we want that next d1 + t1 == WORLD_SLEEP_CONST
		// we can't know next t1 and then can use (t0 + d1) == WORLD_SLEEP_CONST requirement
		// d1 = WORLD_SLEEP_CONST - t0 = WORLD_SLEEP_CONST - (D0 - d0) = WORLD_SLEEP_CONST + d0 - D0
		if (diff <= WORLD_SLEEP_CONST + prevSleepTime)
		{
			prevSleepTime = WORLD_SLEEP_CONST + prevSleepTime - diff;
			AKCore::Thread::Sleep(prevSleepTime);
		}
		else
			prevSleepTime = 0;
		pingDatabase += 1;
		if (pingDatabase >= 3000)
		{
			sDB.Ping();
			pingDatabase = 0;
		}

	}
	//sWorld.CleanupsBeforeStop();
}