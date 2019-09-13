#pragma once

#include <SharedDef.h>
#include <SharedType.h>
#include <Opcodes.h>

//------------------------------------------------------------------
#pragma pack(1)
struct sSERVER_INFO
{
	char		szCharacterServerIP[MAX_LENGTH_OF_IP + 1];
	WORD		wCharacterServerPortForClient;
	DWORD		dwLoad;
	WORD		unknow;
};
//------------------------------------------------------------------
BEGIN_PROTOCOL(AU_HEARTBEAT)
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(AU_LOGIN_RES)
WORD				wResultCode;
WCHAR				awchUserId[MAX_SIZE_CHAR_NAME_UNICODE + 1];
BYTE				abyAuthKey[MAX_SIZE_AUTH_KEY];
ACCOUNTID			AccountID;
BYTE				lastServerID;
SERVERFARMID		lastChannelID;
DWORD				dev;
BYTE				byServerInfoCount;

sSERVER_INFO		CharServerInfo[DBO_MAX_CHARACTER_SERVER_COUNT];
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(AU_COMMERCIAL_SETTING_NFY)
BYTE unk[3];
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(AU_LOGIN_DISCONNECT_RES)
END_PROTOCOL()
#pragma pack()
