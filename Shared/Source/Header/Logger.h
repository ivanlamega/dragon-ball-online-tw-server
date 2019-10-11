#pragma once

#include <iostream>
#include <stdarg.h>
#include <ConsoleColor.h>
#include <mutex>
#include <shared_mutex>
#include <memory>
#include <Singleton.h>

#  define ATTR_PRINTF(F,V)
class Packet;

enum LogLevel
{
	LOG_LVL_MINIMAL = 0, // unconditional and errors
	LOG_LVL_BASIC = 1,
	LOG_LVL_DETAIL = 2,
	LOG_LVL_DEBUG = 3
};
class Log
{
public:
	void outString();                                   // any log level
	void outString(const char* str, ...)      ATTR_PRINTF(2, 3);
	// any log level
	void outError(const char* err, ...)       ATTR_PRINTF(2, 3);
	// log level >= 1
	void outBasic(const char* str, ...)       ATTR_PRINTF(2, 3);
	// log level >= 2
	void outDetail(const char* str, ...)      ATTR_PRINTF(2, 3);
	// log level >= 3
	void outDebug(const char* str, ...)       ATTR_PRINTF(2, 3);
	// log to file
	void outFile(const char* str, ...)       ATTR_PRINTF(2, 3);

	void outTime();
	void outPacketDebugger(Packet* paquet);
	void outPacketFile(Packet * pPacket);
	void outDebugToFile(BYTE* data, int size, WORD opcode);
	void SetLogLevel(int _level);
private:
	LogLevel logLevel;
};

// Logger singleton
#define sLog AKCore::Singleton<Log>::Instance()