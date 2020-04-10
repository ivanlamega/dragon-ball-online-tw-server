#include <Logger.h>
#include <stdio.h>
#include <cstdio>
#include <Opcodes.h>
#include <Encryptation.h>
#include <mysqlconn_wrapper.h>
#include <XmlParser.h>
#include <Packet\Community\PacketUT.h>
#include <Packet\Community\PacketTU.h>
#include <Packet\Game\PacketUG.h>
#include <Packet\Game\PacketGU.h>
#include <Packet.h>
#include "CommunitySession.h"
#include "Community.h"
#include <Game\Maps\MapManager.h>
#include "NtlStringHandler.h"
#include <Game\Object\Player.h>
#include <vector>
#include <string>
#include <cstring>
#include <cwchar>
#include <cassert>
#include<NtlGuild.h>


//SHOW GUILD DATA TO ALL GUILD PLAYERS
void CommunitySession::TU_LoadGuildINFO() {

	//GET GUILD DATA
	sTU_GUILD_INFO req;

	int result = sDB.GetGuildID(_player->GetCharacterID());

	if (result > 0) {

		sLog.outDebug("GUILD INFO RETRIEVED : Guild ID %d \n", result);


		// GUILD INFORMATIONS
		sTU_GUILD_INFO res;
		res.wPacketSize = sizeof(sTU_GUILD_INFO) - 2;
		res.wOpCode = TU_GUILD_INFO;
		sql::ResultSet* query = sDB.executes("select * from Guilds where GuildID = %d;", result);

		res.guildId = query->getInt("GuildID");
		res.guildMaster = _player->GetHandle();//query->getInt("GuildMaster");
		res.wAligniament = -1;
		res.guildSecondMaster[0] = INVALID_TBLIDX;
		res.guildSecondMaster[1] = INVALID_TBLIDX;
		res.guildSecondMaster[2] = INVALID_TBLIDX;
		res.guildSecondMaster[3] = INVALID_TBLIDX;

		wcscpy_s(res.wszName, 16 + 1, s2ws(query->getString("GuildName")).c_str());
		wcscpy_s(res.awchName, 16 + 1, s2ws(query->getString("GuildMasterName")).c_str());
		res.dwGuildReputation = 5000; //1 here is 0 in game i dont know why
		res.dwMaxGuildPointEver = 5000;
		res.qwGuildFunctionFlag = -1;//(DWORD64)1 << eDBO_GUILD_FUNCTION::DBO_GUILD_FUNCTION_CAN_SET_EMBLEM; //Need discover how set the bitflag

		sLog.outDebug("FLAG NOW IS : %d", res.qwGuildFunctionFlag);


		//If this has a value not 0, GuildNotice will change and be forced to disband msg
		res.timeToDisband = 0;

		res.unk1 = 0;
		res.DojiColor = -1;
		
		//unknown
		res.unk[0] = 0;
		res.unk[1] = 0;
		res.unk[2] = 0;
		res.unk[3] = 0;
		res.unk[4] = 0;
		res.unk[5] = 0;
		res.unk[6] = 0;

		//Somehow this works better to get correct Data
		std::wstring notice = s2ws(query->getString("GuildNotice"));
		wcscpy_s(res.awchNotice, 256 + 1, notice.c_str());

		//Mark set Guild Logo we not need set When Create Guild
		res.sMark.byMarkMain = 8;
		res.sMark.byMarkMainColor = 2;
		res.sMark.byMarkInColor = 5;
		res.sMark.byMarkInLine = 10;
		res.sMark.byMarkOutColor = 9;
		res.sMark.byMarkOutLine = 10;
		//sDogi set GuildLogo on Guild Doji
		res.sDogi.guildId = -1;
		res.sDogi.byType = -1;
		res.sDogi.byGuildColor = -1;
		res.sDogi.byDojoColor = -1;



		SendPacket((char*)&res, sizeof(sTU_GUILD_INFO));

		sLog.outDebug("sTU_GUILD_INFO sent  im HERE");


		// Need Load Guild Member By GuildID and send 1 packet for player
		sTU_GUILD_MEMBER_INFO res2;


		res2.wOpCode = TU_GUILD_MEMBER_INFO;
		res2.wPacketSize = sizeof(sTU_GUILD_MEMBER_INFO) - 2;

		res2.guildMemberInfo.charId = _player->GetHandle();
		wcscpy_s(res2.guildMemberInfo.wszMemberName, 16 + 1, _player->GetPcProfile()->awchName);

		res2.guildMemberInfo.byRace = _player->GetAttributesManager()->PlayerRaceID;
		res2.guildMemberInfo.byClass = _player->GetAttributesManager()->PlayerClassID;
		res2.guildMemberInfo.byLevel = _player->GetPcProfile()->byLevel;
		res2.guildMemberInfo.bIsOnline = false;

		res2.guildMemberInfo.unk[0] = 0;
		res2.guildMemberInfo.unk[1] = 0;
		res2.guildMemberInfo.dwReputation = 100;

		res2.guildMemberInfo.WORLDID = 1;
		res2.guildMemberInfo.MAPID = 1; //4294967295 Need fix map ids


		SendPacket((char*)&res2, sizeof(sTU_GUILD_MEMBER_INFO));
		sLog.outDebug("sTU_GUILD_MEMBER_INFO sent");


	}

	GU_LoadGuildINFO();
}


//Load Guild Info from Ppl in the World
void CommunitySession::LoadGuildDataAroundYou() {

	sLog.outDebug("Players in the WORLD COUNT : %d", _player->GetHandle());
	/*
	for (auto it = _player->objList.begin(); it != _player->objList.end();)
	{


		if (it->second != NULL)
		{
			if (it->second->GetTypeId() == OBJTYPE_PC)
			{
				Player* plr = static_cast<Player*>(it->second);
				if (plr->IsInWorld() == true && plr->GetSession() != NULL)
				{
					sql::ResultSet* query = sDB.executes("select * from characters where CharacterID = %d;", plr->GetCharacterID());
					int GuildID = 0;


					if (query->getInt("GuildID") > GuildID)
					{
						GuildID = query->getInt("GuildID");

						query = sDB.executes("select * from guilds where GuildID = %d;", GuildID);

						sLog.outDebug("Player ID : %d and GUILD ID %d \n", plr->GetCharacterID(), GuildID);

						std::string guildname = query->getString("GuildName");
						std::wstring wguildname = std::wstring(guildname.begin(), guildname.end());
						const wchar_t* wsguildname = wguildname.c_str();

						sGU_GUILD_NAME_CHANGED_NFY res2;

						res2.wPacketSize = sizeof(sGU_GUILD_NAME_CHANGED_NFY) - 2;
						res2.wOpCode = GU_GUILD_NAME_CHANGED_NFY;
						res2.hSubject = plr->GetHandle();
						wcscpy_s(res2.wszGuildName, MAX_SIZE_GUILD_NAME_IN_UNICODE + 1, wsguildname);

						SendPacket((char*)&res2, sizeof(sGU_GUILD_NAME_CHANGED_NFY));

						sLog.outDebug("GU_GUILD_NAME_CHANGED_NFY SENT");


						delete query;
					}
				}
				delete plr;
			}
		}
		it++;
	}*/
}

//Show Guild INFO TO OTHER PLAYERS ???
void CommunitySession::GU_LoadGuildINFO() {

	sql::ResultSet* query = sDB.executes("select * from characters where CharacterID = %d;", _player->GetCharacterID());
	int GuildID = 0;


	if (query->getInt("GuildID") > GuildID)
	{
		GuildID = query->getInt("GuildID");

		query = sDB.executes("select * from guilds where GuildID = %d;", GuildID);

		sLog.outDebug("Player ID : %d and GUILD ID %d \n", _player->GetCharacterID(), GuildID);

		std::string guildname = query->getString("GuildName");
		std::wstring wguildname = std::wstring(guildname.begin(), guildname.end());
		const wchar_t* wsguildname = wguildname.c_str();

		sGU_GUILD_NAME_CHANGED_NFY res2;

		res2.wPacketSize = sizeof(sGU_GUILD_NAME_CHANGED_NFY) - 2;
		res2.wOpCode = GU_GUILD_NAME_CHANGED_NFY;
		res2.hSubject = _player->GetHandle();
		wcscpy_s(res2.wszGuildName, MAX_SIZE_GUILD_NAME_IN_UNICODE + 1, wsguildname);

		sCommunity.SendToAll((char*)&res2, sizeof(sGU_GUILD_NAME_CHANGED_NFY));

		sLog.outDebug("GU_GUILD_NAME_CHANGED_NFY SENT");


		delete query;
	}

}

void CommunitySession::LeaveGuild(Packet& packet) {

	sUT_GUILD_LEAVE_REQ * req = (sUT_GUILD_LEAVE_REQ*)packet.GetPacketBuffer();

	//Leave Guild Successfully
	sTU_GUILD_LEAVE_RES res1;
	res1.wPacketSize = sizeof(sTU_GUILD_LEAVE_RES) - 2;
	res1.wOpCode = TU_GUILD_LEAVE_RES;
	res1.wResultCode = ResultCodes::CHAT_SUCCESS;//COMMUNITY_GUILD_LEAVE;
	
	SendPacket((char*)&res1, sizeof(sTU_GUILD_LEAVE_RES));
	sCommunity.SendToAll((char*)&res1, sizeof(sTU_GUILD_LEAVE_RES));
	
}


void CommunitySession::UpdateGuildNotice(Packet& packet) {

	sUT_GUILD_CHANGE_NOTICE_REQ * req = (sUT_GUILD_CHANGE_NOTICE_REQ*)packet.GetPacketBuffer();

	//Leave Guild Successfully
	sTU_GUILD_CHANGE_NOTICE_NFY res;
	sTU_GUILD_CHANGE_NOTICE_RES res1;

	res1.wPacketSize = sizeof(sTU_GUILD_CHANGE_NOTICE_RES) - 2;
	res1.wOpCode = TU_GUILD_CHANGE_NOTICE_RES;
	res1.wResultCode = ResultCodes::CHAT_SUCCESS;//COMMUNITY_GUILD_LEAVE;
	//send Packet
	SendPacket((char*)&res1, sizeof(sTU_GUILD_CHANGE_NOTICE_RES));

	//Update Database 
	int guildId = sDB.GetGuildID(_player->GetCharacterID());
	char notice[256+1];
	wcstombs(notice, req->awchNotice, 256+1);
	sql::ResultSet* query = sDB.executes("UPDATE guilds SET GuildNotice = '%s' WHERE GuildID = %d;", notice ,guildId );

	wcscpy_s(res.awchNotice, 256 + 1, req->awchNotice);
	wcscpy_s(res.awchCharName, 16 + 1, _player->GetPcProfile()->awchName);
	res.wNoticeLengthInUnicode = wcslen(res.awchNotice);
	res.wOpCode = TU_GUILD_CHANGE_NOTICE_NFY;
	res.wPacketSize = sizeof(sTU_GUILD_CHANGE_NOTICE_NFY) - 2;
	//send Packets
	SendPacket((char*)&res, sizeof(sTU_GUILD_CHANGE_NOTICE_NFY));

	

	

}