#ifndef PACKETCU__H
# define PACKETCU__H

#include <Define.h>
#include <SharedDef.h>
#include <SharedType.h>
#include <Opcodes.h>
#include <TableAll.h>

#pragma once

#pragma pack(1)

struct sDBO_GAME_SERVER_FARM_INFO
{
	sDBO_GAME_SERVER_FARM_INFO() :
		serverFarmId(INVALID_SERVERFARMID),
		byServerStatus(DBO_SERVER_STATUS_DOWN),
		dwMaxLoad(0),
		dwLoad(0)
	{
		::ZeroMemory(wszGameServerFarmName, sizeof(wszGameServerFarmName));
	};
	SERVERFARMID serverFarmId;
	WCHAR wszGameServerFarmName[MAX_SIZE_SERVER_FARM_NAME_UNICODE + 1];
	BYTE byServerStatus;
	DWORD dwMaxLoad;
	DWORD dwLoad;
	uint16_t unknown;
};
struct sDBO_GAME_SERVER_CHANNEL_INFO
{
	sDBO_GAME_SERVER_CHANNEL_INFO() :
		serverFarmId(INVALID_SERVERFARMID),
		byServerChannelIndex(INVALID_SLOTID),
		bIsVisible(true),
		byServerStatus(DBO_SERVER_STATUS_DOWN),
		dwMaxLoad(0),
		dwLoad(0)
	{
	};
	SERVERFARMID serverFarmId;
	BYTE byServerChannelIndex;
	bool bIsVisible;
	BYTE byServerStatus;
	DWORD dwMaxLoad;
	DWORD dwLoad;
	bool is_pvpdb;
	char unknown[106];
};
//------------------------------------------------------------------
BEGIN_PROTOCOL(CU_LOGIN_RES)
WORD			wResultCode;
SERVERFARMID	lastServerFarmId;
DWORD			dwRaceAllowedFlag;
BYTE			LastChannelID;
BYTE		    unk[3];
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(CU_CHARACTER_SERVERLIST_ONE_RES)
WORD wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(CU_CHARACTER_SERVERLIST_RES)
WORD wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(CU_SERVER_FARM_INFO)
sDBO_GAME_SERVER_FARM_INFO		serverFarmInfo;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(CU_SERVER_CHANNEL_INFO)
BYTE	byCount;
sDBO_GAME_SERVER_CHANNEL_INFO		serverChannelInfo[MAX_SERVER_CHANNEL_COUNT_IN_SERVER_FARM];
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(CU_CHARACTER_INFO)
sDELETE_WAIT_CHARACTER_INFO asDelData[MAX_COUNT_USER_CHAR_SLOT];
BYTE			byCount;
sPC_SUMMARY		sPcData[MAX_COUNT_USER_CHAR_SLOT]; // Maximum of Character is 8 (Temporary)	
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(CU_CHARACTER_LOAD_RES)
WORD	wResultCode;
BYTE	ServerID;
BYTE	OpenCharSlots;
BYTE	VipCharSlot;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(CU_CHARACTER_ADD_RES)
WORD			wResultCode;
sPC_SUMMARY		sPcDataSummary;
BYTE			unknown;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(CU_CHARACTER_DEL_RES)
WORD			wResultCode;
CHARACTERID		charId;
//sDBO_TIME		tDeleteDate;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(CU_CHARACTER_DEL_NFY)
CHARACTERID		charId;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(CU_CHARACTER_EXIT_RES)
WORD	wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(CU_CHARACTER_DEL_CANCEL_RES)
WORD			wResultCode;
CHARACTERID		charId;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(CU_CHARACTER_SELECT_RES)
WORD			wResultCode;
CHARACTERID		charId;
BYTE			abyAuthKey[MAX_SIZE_AUTH_KEY];
char			szGameServerIP[MAX_LENGTH_OF_IP + 1];
WORD			wGameServerPortForClient;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(CU_CONNECT_WAIT_CHECK_RES)
WORD				wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(CU_CONNECT_WAIT_COUNT_NFY)
DWORD				dwCountWaiting;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(CU_CHARACTER_RENAME_RES)
CHARACTERID			charId;
WORD				wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
#pragma pack()

#endif // !PACKETCU__H