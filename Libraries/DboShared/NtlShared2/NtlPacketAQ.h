#pragma once

#include "NtlPacketCommon.h"
#include "NtlCSArchitecture.h"

enum eOPCODE_AQ
{
	AQ_OPCODE_BEGIN = 200,

	AQ_HEARTBEAT = AQ_OPCODE_BEGIN,
	AQ_LOGIN_REQ,
	
	AQ_OPCODE_DUMMY,
	AQ_OPCODE_END = AQ_OPCODE_DUMMY - 1
};


//------------------------------------------------------------------
//
//------------------------------------------------------------------
const char * NtlGetPacketName_AQ(WORD wOpCode);
//------------------------------------------------------------------


#pragma pack(push,1)

//------------------------------------------------------------------
BEGIN_PROTOCOL(AQ_HEARTBEAT)
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(AQ_LOGIN_REQ)
	WCHAR		awchUserId[NTL_MAX_SIZE_USERID_UNICODE + 1];
	WCHAR		awchPasswd[NTL_MAX_SIZE_USERPW_UNICODE + 1];
	BYTE		abyMacAddress[DBO_MAX_ADAPTER_ADDRESS_LENGTH];
END_PROTOCOL()
//------------------------------------------------------------------

#pragma pack()