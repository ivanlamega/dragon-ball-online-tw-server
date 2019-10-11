#pragma once

#include <Define.h>
#include <Opcodes.h>
#include <SharedDef.h>
#include <SharedType.h>

struct sUC_LOGIN_REQ
{
	ACCOUNTID		accountId;
	BYTE			abyAuthKey[MAX_SIZE_USERID_UNICODE];
	SERVERFARMID	serverID;
};
struct sUC_CHARACTER_LOAD_REQ
{
	ACCOUNTID		accountId;
	SERVERFARMID	serverFarmId;
};
struct sUC_CHARACTER_ADD_REQ
{
	WCHAR			awchCharName[MAX_SIZE_CHAR_NAME_UNICODE + 1];
	//DWORD			dwCodePage; //bug
	BYTE			byRace;
	BYTE			byClass;
	BYTE			byGender;
	BYTE			byFace;
	BYTE			byHair;
	BYTE			byHairColor;
	BYTE			bySkinColor;
	BYTE			byBlood;
	DWORD			unknown;
};
struct sUC_CHARACTER_DEL_REQ
{
	CHARACTERID		charId;
};
struct sUC_CHARACTER_DEL_CANCEL_REQ
{
	CHARACTERID		charId;
	/* PACKET DEBBUGING */
	/*
	[0] : [64] // here character id 4octets
	[1] : [0]
	[2] : [0]
	[3] : [0]
	[4] : [113] // ?? 2 octets
	[5] : [0]
	[6] : [100] // ?? 2 octets
	[7] : [0]
	[8] : [113] // ?? 2 octets
	[9] : [0]
	[10] : [122] // ?? 2 octets
	[11] : [0]
	[12] : [100] // ?? 2 octets
	[13] : [0]
	[14] : [113] // ?? 2 octets
	[15] : [0]
	*/
};
struct sUC_CHARACTER_EXIT_REQ
{
	bool			bIsGameMove;
};
struct sUC_CHARACTER_SELECT_REQ
{
	CHARACTERID		charId;
	BYTE		    byServerChannelIndex;
};
struct sUC_CHARACTER_RENAME_REQ
{
	CHARACTERID		charId;
	//DWORD			dwCodePage;
	WCHAR			awchCharName[MAX_SIZE_CHAR_NAME_UNICODE + 1];
};