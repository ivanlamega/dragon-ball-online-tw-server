#ifndef DEFINE_H
#define DEFINE_H

#pragma once

#if !defined(_WIN32_WINNT)
#define _WIN32_WINNT 0x0501 	
#elif (_WIN32_WINNT < 0x0501)
#undef _WIN32_WINNT
#define _WIN32_WINNT 0x0501
#endif

#include <Windows.h>
#include <stdlib.h>
#include <cstdint>
#include <mutex>
#include <map>
#include <assert.h>

#  define ATTR_NORETURN

#define STRINGIZE(a) #a
#define WPError(CONDITION) \
if (!(CONDITION)) \
{ \
    printf("%s:%i: Error: Assertion in %s failed: %s", \
        __FILE__, __LINE__, __FUNCTION__, STRINGIZE(CONDITION)); \
    assert(STRINGIZE(CONDITION) && 0); \
}

typedef std::int64_t int64;
typedef int int32;
typedef std::int16_t int16;
typedef std::int8_t int8;
typedef std::uint64_t uint64;
typedef unsigned int uint32;
typedef std::uint16_t uint16;
#define uint8 unsigned char

#  pragma warning( disable : 4328)
#  pragma warning( disable : 4819)
#  pragma warning( disable : 4503)
#  pragma warning( disable : 4099)
#  pragma warning( disable : 4305)
#  pragma warning( disable : 4129)
#  pragma warning( disable : 4309)
#  pragma warning( disable : 4251)
#  pragma warning( disable : 4006)
#  pragma warning( disable : 4267 )                         // conversion from 'size_t' to 'int', possible loss of data
#  pragma warning( disable : 4786 )                         // identifier was truncated to '255' characters in the debug information

//------------------------------------------------------------------
enum eDBO_SERVER_STATUS
{
	DBO_SERVER_STATUS_UP = 0,
	DBO_SERVER_STATUS_DOWN,
	DBO_SERVER_STATUS_LOCKED
};

struct sPACKETHEADER
{
	sPACKETHEADER(BYTE wGivenOpCode) :
		wOpCode(wGivenOpCode) {}
	WORD		wPacketSize;
	//BYTE		bEncrypt;
	WORD		wOpCode;
	//BYTE		byChecksum;
};
//------------------------------------------------------------------
//------------------------------------------------------------------
//
//------------------------------------------------------------------
#define BEGIN_PROTOCOL(opcode)						\
struct s##opcode :									\
	public sPACKETHEADER							\
{													\
	s##opcode() :									\
		sPACKETHEADER(opcode)						\
	{												\
	}

#define END_PROTOCOL()	};
/*#define BEGIN_PROTOCOL(opcode)						\
struct s##opcode 									\
{													\
s##opcode()										\
{												\
}
#define END_PROTOCOL()	};*/
//------------------------------------------------------------------
//------------------------------------------------------------------
//
//------------------------------------------------------------------
#define BEGIN_PROTOCOL_IDENTITY( opcode, identity )	\
typedef s##identity s##opcode						\

#define END_PROTOCOL_IDENTITY()	;
//------------------------------------------------------------------


//------------------------------------------------------------------
#define DECLARE_PACKET_NAME( opcode )	{ #opcode }
//------------------------------------------------------------------
#endif DEFINE_H