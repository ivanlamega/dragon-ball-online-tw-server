#ifndef __GUILD_H
#define __GUILD_H

#pragma once

#include <Packet\Community\PacketTU.h>
#include <Packet\Community\PacketUT.h>
#include "CommunitySession.h"

class Player;
class GuildManager
{
public:
	GuildManager();
	~GuildManager();
	
	struct Guild_Member {

		CHARACTERID		charId;
		WCHAR			wszMemberName[MAX_SIZE_CHAR_NAME_UNICODE + 1];
		BYTE			byRace;
		BYTE			byClass;
		BYTE			byLevel;
		DWORD			dwReputation;
		bool			bIsOnline;
		BYTE			unk[2];
		DWORD			WORLDID;
		DWORD			MAPID;
	};


	DWORD				GetGuild() { return guildId; }
	Guild_Member		*GetGuildMembers() { return members; }

	void				AddNewMembertoGUild();
	void				RemoveMemberfromGUild();


	
	
	//Guild Members
	Guild_Member    members[50];


		
	DWORD           guildId;
	WCHAR           wszName[16 + 1];
	WORD			wAligniament;
	DWORD           guildMaster;
	DWORD           guildSecondMaster[4];
	DWORD           dwGuildReputation;
	DWORD           dwMaxGuildPointEver;
	DWORD64         qwGuildFunctionFlag;
	DBOTIME         timeToDisband;
	sDBO_GUILD_MARK sMark;
	WORD            wAligniament2[2];
	WCHAR           awchName[MAX_SIZE_CHAR_NAME_UNICODE + 1];
	WCHAR           awchNotice[MAX_LENGTH_OF_GUILD_NOTICE_UNICODE + 1];
	sDBO_DOGI_DATA  sDogi;

private:

};

#endif