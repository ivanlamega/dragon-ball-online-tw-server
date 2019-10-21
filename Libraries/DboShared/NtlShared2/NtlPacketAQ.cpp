#include "StdAfx.h"
#include "NtlPacketAQ.h"

const char * s_packetName_AQ[] =
{
	DECLARE_PACKET_NAME(AQ_HEARTBEAT),
	DECLARE_PACKET_NAME(AQ_LOGIN_REQ),
};


//------------------------------------------------------------------
//
//------------------------------------------------------------------
const char * NtlGetPacketName_AQ(WORD wOpCode)
{
	if (wOpCode < WORD(AQ_OPCODE_BEGIN))
	{
		return "NOT DEFINED PACKET NAME : OPCODE LOW";
	}

	if (wOpCode > WORD(AQ_OPCODE_END))
	{
		return "NOT DEFINED PACKET NAME : OPCODE HIGH";
	}

	int nIndex = wOpCode - WORD(AQ_OPCODE_BEGIN);
	if (nIndex >= _countof(s_packetName_AQ))
	{
		return "OPCODE BUFFER OVERFLOW";
	}

	return s_packetName_AQ[nIndex];
}