#include "StdAfx.h"
#include "NtlPacketQA.h"

const char * s_packetName_QA[] =
{
	DECLARE_PACKET_NAME(QA_HEARTBEAT),
	DECLARE_PACKET_NAME(QA_LOGIN_RES),
	DECLARE_PACKET_NAME(QA_CHARACTER_EXIT),
};


//------------------------------------------------------------------
//
//------------------------------------------------------------------
const char * NtlGetPacketName_QA(WORD wOpCode)
{
	if (wOpCode < WORD(QA_OPCODE_BEGIN))
	{
		return "NOT DEFINED PACKET NAME : OPCODE LOW";
	}

	if (wOpCode > WORD(QA_OPCODE_END))
	{
		return "NOT DEFINED PACKET NAME : OPCODE HIGH";
	}

	int nIndex = wOpCode - WORD(QA_OPCODE_BEGIN);
	if (nIndex >= _countof(s_packetName_QA))
	{
		return "OPCODE BUFFER OVERFLOW";
	}

	return s_packetName_QA[nIndex];
}