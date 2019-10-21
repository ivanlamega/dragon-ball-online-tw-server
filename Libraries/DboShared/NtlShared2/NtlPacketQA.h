#pragma once

#include "NtlPacketCommon.h"
#include "NtlCSArchitecture.h"

enum eOPCODE_QA
{
	QA_OPCODE_BEGIN = 1500,

	QA_HEARTBEAT = QA_OPCODE_BEGIN,
	QA_LOGIN_RES,
	QA_CHARACTER_EXIT,

	QA_OPCODE_DUMMY,
	QA_OPCODE_END = QA_OPCODE_DUMMY - 1
};


//------------------------------------------------------------------
//
//------------------------------------------------------------------
const char * NtlGetPacketName_QA(WORD wOpCode);
//------------------------------------------------------------------


#pragma pack(push,1)

//------------------------------------------------------------------
BEGIN_PROTOCOL(QA_HEARTBEAT)
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(QA_LOGIN_RES)
	WORD				wResultCode;
	WCHAR				awchUserId[NTL_MAX_SIZE_USERID_UNICODE + 1];
	//BYTE				abyAuthKey[NTL_MAX_SIZE_AUTH_KEY];
	ACCOUNTID			accountId;
	SERVERFARMID		lastServerFarmId;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(QA_CHARACTER_EXIT)
	ACCOUNTID			accountId;
END_PROTOCOL()
//------------------------------------------------------------------

#pragma pack()