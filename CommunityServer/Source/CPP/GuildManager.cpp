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


//Show Guild INFO TO ALL OTHER PLAYERS
void CommunitySession::LoadGuildInfotoOtherPlayers() {

	sql::ResultSet* query = sDB.executes("select * from characters where CharacterID = %d;", _player->GetCharacterID());
	int GuildID = 0;


	if (query->getInt("GuildID") > GuildID)
	{
		GuildID = query->getInt("GuildID");

		query = sDB.executes("select * from guilds where GuildID = %d;", GuildID);

		std::string guildname = query->getString("GuildName");
		std::wstring wguildname = std::wstring(guildname.begin(), guildname.end());
		const wchar_t* wsguildname = wguildname.c_str();

		sGU_GUILD_NAME_CHANGED_NFY res2;

		res2.wPacketSize = sizeof(sGU_GUILD_NAME_CHANGED_NFY) - 2;
		res2.wOpCode = GU_GUILD_NAME_CHANGED_NFY;
		res2.hSubject = _player->GetHandle();
		wcscpy_s(res2.wszGuildName, MAX_SIZE_GUILD_NAME_IN_UNICODE + 1, wsguildname);

		sCommunity.SendToAll((char*)&res2, sizeof(sGU_GUILD_NAME_CHANGED_NFY));
	   
		delete query;
	}

}

//SHOW GUILD DATA TO ALL GUILD PLAYERS
void CommunitySession::LoadGuildInfotoPlayer() {

	int result = sDB.GetGuildID(_player->GetCharacterID());

	if (result > 0) {

		//GET GUILD DATA
		sTU_GUILD_INFO req;

		// GUILD INFORMATIONS
		sTU_GUILD_INFO res;
		res.wOpCode = TU_GUILD_INFO;
		sql::ResultSet* GuildInfo = sDB.executes("select * from Guilds where GuildID = %d;", result);

		if (!GuildInfo) return;
		if (GuildInfo && GuildInfo->rowsCount() == 0) return;

		res.guildId = GuildInfo->getInt("GuildID");
		wcscpy_s(res.wszName, 16 + 1, s2ws(GuildInfo->getString("GuildName")).c_str());
		res.wAligniament = 27760;
		res.guildMaster = GuildInfo->getInt("GuildMaster");

		res.guildSecondMaster[0] = INVALID_TBLIDX; 
		if (GuildInfo->getInt("GuildSecondMaster")> 0) res.guildSecondMaster[0] = GuildInfo->getInt("GuildSecondMaster");
		res.guildSecondMaster[1] = INVALID_TBLIDX;
		res.guildSecondMaster[2] = INVALID_TBLIDX;
		res.guildSecondMaster[3] = INVALID_TBLIDX;

		res.dwGuildReputation = 5000;//1 here is 0 in game i dont know why
		res.dwMaxGuildPointEver = 5000;
		res.wAligniament2[0] = 11385;
		res.wAligniament2[1] = 29287;
		res.qwGuildFunctionFlag = GuildInfo->getInt("GuildFunctions");
		res.timeToDisband = 0;
		//Mark set Guild Logo we not need set When Create Guild
		res.sMark.byMarkMain = -1;
		res.sMark.byMarkMainColor = -1;
		res.sMark.byMarkInColor = -1;
		res.sMark.byMarkInLine = -1;
		res.sMark.byMarkOutColor = -1;
		res.sMark.byMarkOutLine = -1;

		wcscpy_s(res.awchName, 16 + 1, s2ws(GuildInfo->getString("GuildName")).c_str());
		wcscpy_s(res.awchNotice, 256 + 1, s2ws(GuildInfo->getString("GuildNotice")).c_str());
		res.wAligniament3 = 13625;
		//sDogi set GuildLogo on Guild Doji
		res.sDogi.guildId = -1;
		res.sDogi.byType = -1;
		res.sDogi.byGuildColor = -1;
		res.sDogi.byDojoColor = -1;

		res.wAligniament4[0] = 48;
		res.wAligniament4[1] = 41;
		res.wAligniament4[2] = 0;
		res.wAligniament4[3] = -2;
		res.wAligniament4[4] = 0;


		res.wPacketSize = sizeof(sTU_GUILD_INFO) - 2;

		SendPacket((char*)&res, sizeof(sTU_GUILD_INFO));

		//set guild name 
		_player->GuildName = GuildInfo->getString("GuildName");

		//Load Guild members
		LoadGuildMembers();
		
		//Show Guild Info to players arround you
		//GU_LoadGuildINFO();
	}


}

void CommunitySession::LoadGuildMembers() {

	int result = sDB.GetGuildID(_player->GetCharacterID());
	if (!result) return;

	sql::ResultSet* GuildInfo = sDB.executes("select * from Guilds where GuildID = %d;", result);
	if (!GuildInfo) return;

	//Getting all Guild Members Info
	sql::ResultSet * GuildMembers = sDB.executes("SELECT * from guilds JOIN characters on characters.GuildID = guilds.GuildID WHERE guilds.GuildID = %d", GuildInfo->getInt("GuildID"));

	if (GuildMembers == NULL)
		return;
	if (GuildMembers->rowsCount() <= 0)
	{
		delete GuildMembers;
		return;
	}

	BYTE GuildMembersCount = GuildMembers->rowsCount();

	// Need Load Guild Member By GuildID and send 1 packet for player
	sTU_GUILD_MEMBER_INFO res2;
	res2.wOpCode = TU_GUILD_MEMBER_INFO;
	res2.wPacketSize = sizeof(sTU_GUILD_MEMBER_INFO) - 2;

	for (int i = 0; i < GuildMembersCount; i++)
	{

		//if blacked or offline dont send
		if (GuildMembers->getInt("CharacterID") == _player->GetCharacterID())
		{
			res2.guildMemberInfo.charId = GuildMembers->getInt("CharacterID");;
			wcscpy_s(res2.guildMemberInfo.wszMemberName, 16 + 1, charToWChar(GuildMembers->getString("Name").c_str()));

			res2.guildMemberInfo.byRace = GuildMembers->getInt("RaceID");
			res2.guildMemberInfo.byClass = GuildMembers->getInt("ClassID");
			res2.guildMemberInfo.byLevel = GuildMembers->getInt("CurrentLevel");
			res2.guildMemberInfo.bIsOnline = true;
			res2.guildMemberInfo.WORLDID = 1;
			res2.guildMemberInfo.MAPID = 200107100; //4294967295 Need fix map ids
			res2.guildMemberInfo.unk[0] = 0;
			res2.guildMemberInfo.unk[1] = 0;
			res2.guildMemberInfo.dwReputation = GuildMembers->getInt("Reputation");;


			SendPacket((char*)&res2, sizeof(sTU_GUILD_MEMBER_INFO));
		}
		else if (sCommunity.FindSession(GuildMembers->getInt("CharacterID"))) {

			int Hhandle = GuildMembers->getInt("GSHandle");

			res2.guildMemberInfo.charId = GuildMembers->getInt("CharacterID");;
			wcscpy_s(res2.guildMemberInfo.wszMemberName, 16 + 1, charToWChar(GuildMembers->getString("Name").c_str()));

			res2.guildMemberInfo.byRace = GuildMembers->getInt("RaceID");
			res2.guildMemberInfo.byClass = GuildMembers->getInt("ClassID");
			res2.guildMemberInfo.byLevel = GuildMembers->getInt("CurrentLevel");
			res2.guildMemberInfo.bIsOnline = true;
			res2.guildMemberInfo.WORLDID = 1;
			res2.guildMemberInfo.MAPID = 200107100; //4294967295 Need fix map ids
			res2.guildMemberInfo.unk[0] = 0;
			res2.guildMemberInfo.unk[1] = 0;
			res2.guildMemberInfo.dwReputation = GuildMembers->getInt("Reputation");;

			SendPacket((char*)&res2, sizeof(sTU_GUILD_MEMBER_INFO));

			//send the packet to player online
			Player* plr = static_cast<Player*>(sCommunity.FindSession(GuildMembers->getInt("CharacterID"))->_player);
			NotifyguildiesAfterLoginOn(plr);

		}
		//Offline
		else {

			int Hhandle = GuildMembers->getInt("GSHandle");

			res2.guildMemberInfo.charId = GuildMembers->getInt("CharacterID");;
			wcscpy_s(res2.guildMemberInfo.wszMemberName, 16 + 1, charToWChar(GuildMembers->getString("Name").c_str()));

			res2.guildMemberInfo.byRace = GuildMembers->getInt("RaceID");
			res2.guildMemberInfo.byClass = GuildMembers->getInt("ClassID");
			res2.guildMemberInfo.byLevel = GuildMembers->getInt("CurrentLevel");
			res2.guildMemberInfo.bIsOnline = false;
			res2.guildMemberInfo.WORLDID = 1;
			res2.guildMemberInfo.MAPID = 200107100; //4294967295 Need fix map ids
			res2.guildMemberInfo.unk[0] = 0;
			res2.guildMemberInfo.unk[1] = 0;
			res2.guildMemberInfo.dwReputation = GuildMembers->getInt("Reputation");;

			SendPacket((char*)&res2, sizeof(sTU_GUILD_MEMBER_INFO));
		}

		GuildMembers->next();
	}

}

//Load Guild Info from Ppl in the World
void CommunitySession::SendGuildInfotoPlayer(Player * plr) {


	sql::ResultSet* query = sDB.executes("select * from characters where CharacterID = %d;", _player->GetCharacterID());
	int GuildID = 0;


	if (query->getInt("GuildID") > GuildID)
	{
		GuildID = query->getInt("GuildID");

		query = sDB.executes("select * from guilds where GuildID = %d;", GuildID);

		std::string guildname = query->getString("GuildName");
		std::wstring wguildname = std::wstring(guildname.begin(), guildname.end());
		const wchar_t* wsguildname = wguildname.c_str();

		sGU_GUILD_NAME_CHANGED_NFY res2;

		res2.wPacketSize = sizeof(sGU_GUILD_NAME_CHANGED_NFY) - 2;
		res2.wOpCode = GU_GUILD_NAME_CHANGED_NFY;
		res2.hSubject = _player->GetHandle();
		wcscpy_s(res2.wszGuildName, MAX_SIZE_GUILD_NAME_IN_UNICODE + 1, wsguildname);

		plr->SendPacket((char*)&res2, sizeof(sGU_GUILD_NAME_CHANGED_NFY));

		delete query;
	}
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


	//Getting all Guild Members Info & Send to them all new Notice

	sql::ResultSet* GuildInfo = sDB.executes("select * from Guilds where GuildID = %d;", guildId);
	if (!GuildInfo) return;


	sql::ResultSet * GuildMembers = sDB.executes("SELECT * from guilds JOIN characters on characters.GuildID = guilds.GuildID WHERE guilds.GuildID = %d", GuildInfo->getInt("GuildID"));

	if (GuildMembers == NULL) return;
	if (GuildMembers->rowsCount() <= 0)
	{
		delete GuildMembers;
		return;
	}

	BYTE GuildMembersCount = GuildMembers->rowsCount();

	for (int i = 0; i < GuildMembersCount; i++)
	{
		//if blacked or offline dont send
		if (GuildMembers->getInt("CharacterID") == _player->GetCharacterID()) {
			SendPacket((char*)&res, sizeof(sTU_GUILD_CHANGE_NOTICE_NFY));
		}
		else if (sCommunity.FindSession(GuildMembers->getInt("CharacterID"))) {

			//send the packet to player online
			Player* plr = static_cast<Player*>(sCommunity.FindSession(GuildMembers->getInt("CharacterID"))->_player);
			plr->SendPacket((char*)&res, sizeof(sTU_GUILD_CHANGE_NOTICE_NFY));

		}
		//Offline
		else {

		}

		GuildMembers->next();
	}

	

	

}
	
void CommunitySession::GuildInviteResponse(Packet& packet) {

	sUT_GUILD_RESPONSE_INVITATION * req = (sUT_GUILD_RESPONSE_INVITATION*)packet.GetPacketBuffer();

	switch (req->byResponse) {
	case (eINVITATION_RESPONSE::INVITATION_RESPONSE_ACCEPT):
	{
		sTU_GUILD_RESPONSE_INVITATION_RES res;
		res.wOpCode = TU_GUILD_RESPONSE_INVITATION_RES;
		res.wResultCode = GAME_SUCCESS;
		res.wPacketSize = sizeof(sTU_GUILD_RESPONSE_INVITATION_RES) - 2;
		//send Packet
		SendPacket((char*)&res, sizeof(sTU_GUILD_RESPONSE_INVITATION_RES));

		//send new data to all guild memebers
		int result = sDB.GetGuildID(_player->GetCharacterID());
		if (!result) return;

		sql::ResultSet* GuildInfo = sDB.executes("select * from Guilds where GuildID = %d;", result);
		if (!GuildInfo) return;

		//Getting all Guild Members Info
		sql::ResultSet * GuildMembers = sDB.executes("SELECT * from guilds JOIN characters on characters.GuildID = guilds.GuildID WHERE guilds.GuildID = %d", GuildInfo->getInt("GuildID"));

		if (GuildMembers == NULL)
			return;
		if (GuildMembers->rowsCount() <= 0)
		{
			delete GuildMembers;
			return;
		}

		BYTE GuildMembersCount = GuildMembers->rowsCount();

		// load my info
		sTU_GUILD_MEMBER_INFO Myinfo;
		Myinfo.wOpCode = TU_GUILD_MEMBER_INFO;
		Myinfo.wPacketSize = sizeof(sTU_GUILD_MEMBER_INFO) - 2;
		Myinfo.guildMemberInfo.charId = _player->GetCharacterID();
		wcscpy_s(Myinfo.guildMemberInfo.wszMemberName, 16 + 1, charToWChar(_player->GetName().c_str()));

		Myinfo.guildMemberInfo.byRace = _player->GetAttributesManager()->PlayerRaceID;
		Myinfo.guildMemberInfo.byClass = _player->GetAttributesManager()->PlayerClassID;
		Myinfo.guildMemberInfo.byLevel = _player->GetPcProfile()->byLevel;
		Myinfo.guildMemberInfo.bIsOnline = true;
		Myinfo.guildMemberInfo.WORLDID = 1;
		Myinfo.guildMemberInfo.MAPID = 200107100; //4294967295 Need fix map ids
		Myinfo.guildMemberInfo.unk[0] = 0;
		Myinfo.guildMemberInfo.unk[1] = 0;
		Myinfo.guildMemberInfo.dwReputation = 0;

		for (int i = 0; i < GuildMembersCount; i++)
		{
			//if blacked or offline dont send
			if (GuildMembers->getInt("CharacterID") == _player->GetCharacterID()) {}
			else if (sCommunity.FindSession(GuildMembers->getInt("CharacterID"))) {

				//send the packet to player online
				Player* plr = static_cast<Player*>(sCommunity.FindSession(GuildMembers->getInt("CharacterID"))->_player);
				plr->SendPacket((char*)&Myinfo, sizeof(sTU_GUILD_MEMBER_INFO));
			}
			//Offline
			else {	}
			GuildMembers->next();
		}

		//SHOW GUILD & MEMBERS
		LoadGuildInfotoPlayer();
		LoadGuildInfotoOtherPlayers();

		break;
	}
	case (eINVITATION_RESPONSE::INVITATION_RESPONSE_DECLINE):
	{
		sTU_GUILD_RESPONSE_INVITATION_RES res;
		res.wOpCode = TU_GUILD_RESPONSE_INVITATION_RES;
		res.wResultCode = GAME_FAIL;
		res.wPacketSize = sizeof(sTU_GUILD_RESPONSE_INVITATION_RES) - 2;
		//send Packet
		SendPacket((char*)&res, sizeof(sTU_GUILD_RESPONSE_INVITATION_RES));

		if (sDB.executes("UPDATE `characters` SET `GuildID` = '%d' WHERE `CharacterID` = '%d';", 0, _player->GetCharacterID())) return;

		break;
	}
	case (eINVITATION_RESPONSE::INVITATION_RESPONSE_EXPIRE):
	{
		sTU_GUILD_RESPONSE_INVITATION_RES res;
		res.wOpCode = TU_GUILD_RESPONSE_INVITATION_RES;
		res.wResultCode = ResultCodes::GAME_FAIL;
		res.wPacketSize = sizeof(sTU_GUILD_RESPONSE_INVITATION_RES) - 2;
		//send Packet
		SendPacket((char*)&res, sizeof(sTU_GUILD_RESPONSE_INVITATION_RES));

		if (sDB.executes("UPDATE `characters` SET `GuildID` = '%d' WHERE `CharacterID` = '%d';", 0, _player->GetCharacterID())) return;


		break;
	}
	default:
	{
		if (sDB.executes("UPDATE `characters` SET `GuildID` = '%d' WHERE `CharacterID` = '%d';", 0, _player->GetCharacterID())) return;
		break;
	}

	}

}

void CommunitySession::NotifyguildiesAfterLoginOn(Player* plr) {

	sTU_GUILD_MEMBER_ONLINE_NFY res3;
	res3.wOpCode = TU_GUILD_MEMBER_ONLINE_NFY;
	res3.wPacketSize = sizeof(sTU_GUILD_MEMBER_ONLINE_NFY) - 2;
	res3.memberCharId = _player->GetCharacterID();
	res3.newMapNameTblidx = 200107100;
	plr->SendPacket((char*)&res3, sizeof(sTU_GUILD_MEMBER_ONLINE_NFY));

}

void CommunitySession::NotifyguildiesAfterLoginOff() {

	int result = sDB.GetGuildID(_player->GetCharacterID());
	if (!result) return;

	sql::ResultSet* GuildInfo = sDB.executes("select * from Guilds where GuildID = %d;", result);
	if (!GuildInfo) return;

	//Getting all Guild Members Info
	sql::ResultSet * GuildMembers = sDB.executes("SELECT * from guilds JOIN characters on characters.GuildID = guilds.GuildID WHERE guilds.GuildID = %d", GuildInfo->getInt("GuildID"));

	if (GuildMembers == NULL)
		return;
	if (GuildMembers->rowsCount() <= 0)
	{
		delete GuildMembers;
		return;
	}

	BYTE GuildMembersCount = GuildMembers->rowsCount();

	for (int i = 0; i < GuildMembersCount; i++)
	{

		//if blacked or offline dont send
		if (GuildMembers->getInt("CharacterID") == _player->GetCharacterID()){}
		else if (sCommunity.FindSession(GuildMembers->getInt("CharacterID"))) {

			//send the packet to player online
			Player* plr = static_cast<Player*>(sCommunity.FindSession(GuildMembers->getInt("CharacterID"))->_player);

			sTU_GUILD_MEMBER_OFFLINE_NFY res3;
			res3.wOpCode = TU_GUILD_MEMBER_OFFLINE_NFY;
			res3.wPacketSize = sizeof(sTU_GUILD_MEMBER_OFFLINE_NFY) - 2;
			res3.memberCharId = _player->GetCharacterID();
			plr->SendPacket((char*)&res3, sizeof(sTU_GUILD_MEMBER_OFFLINE_NFY));

		}
		//Offline
		else {
		
		}

		GuildMembers->next();
	}

}

//in dev
void CommunitySession::GUILD_APPOINT_SECOND_MASTER(Packet& packet) {

	sGU_SYSTEM_DISPLAY_TEXT sNotice;

	sNotice.wOpCode = GU_SYSTEM_DISPLAY_TEXT;
	sNotice.wPacketSize = sizeof(sGU_SYSTEM_DISPLAY_TEXT) - 2;

	sNotice.byDisplayType = eSERVER_TEXT_TYPE::SERVER_TEXT_SYSNOTICE;
	wcscpy_s(sNotice.awchMessage, BUDOKAI_MAX_NOTICE_LENGTH + 1, (L"Function In developpement..."));
	wcscpy_s(sNotice.awGMChar, MAX_SIZE_CHAR_NAME_UNICODE, (L" GM "));
	sNotice.wMessageLengthInUnicode = (WORD)wcslen(sNotice.awchMessage);

	_player->SendPacket((char*)&sNotice, sizeof(sGU_SYSTEM_DISPLAY_TEXT));
}

void CommunitySession::GUILD_CHANGE_GUILD_MASTER(Packet& packet) {
	sGU_SYSTEM_DISPLAY_TEXT sNotice;

	sNotice.wOpCode = GU_SYSTEM_DISPLAY_TEXT;
	sNotice.wPacketSize = sizeof(sGU_SYSTEM_DISPLAY_TEXT) - 2;

	sNotice.byDisplayType = eSERVER_TEXT_TYPE::SERVER_TEXT_SYSNOTICE;
	wcscpy_s(sNotice.awchMessage, BUDOKAI_MAX_NOTICE_LENGTH + 1, (L"Function In developpement..."));
	wcscpy_s(sNotice.awGMChar, MAX_SIZE_CHAR_NAME_UNICODE, (L" GM "));
	sNotice.wMessageLengthInUnicode = (WORD)wcslen(sNotice.awchMessage);

	_player->SendPacket((char*)&sNotice, sizeof(sGU_SYSTEM_DISPLAY_TEXT));

}

void CommunitySession::GUILD_KICK_OUT(Packet& packet) {
	sGU_SYSTEM_DISPLAY_TEXT sNotice;

	sNotice.wOpCode = GU_SYSTEM_DISPLAY_TEXT;
	sNotice.wPacketSize = sizeof(sGU_SYSTEM_DISPLAY_TEXT) - 2;

	sNotice.byDisplayType = eSERVER_TEXT_TYPE::SERVER_TEXT_SYSNOTICE;
	wcscpy_s(sNotice.awchMessage, BUDOKAI_MAX_NOTICE_LENGTH + 1, (L"Function In developpement..."));
	wcscpy_s(sNotice.awGMChar, MAX_SIZE_CHAR_NAME_UNICODE, (L" GM "));
	sNotice.wMessageLengthInUnicode = (WORD)wcslen(sNotice.awchMessage);

	_player->SendPacket((char*)&sNotice, sizeof(sGU_SYSTEM_DISPLAY_TEXT));

}

void CommunitySession::LeaveGuild(Packet& packet) {

	sUT_GUILD_LEAVE_REQ * req = (sUT_GUILD_LEAVE_REQ*)packet.GetPacketBuffer();

	//Leave Guild Successfully
	sTU_GUILD_LEAVE_RES res1;
	res1.wPacketSize = sizeof(sTU_GUILD_LEAVE_RES) - 2;
	res1.wOpCode = TU_GUILD_LEAVE_RES;
	res1.wResultCode = ResultCodes::GAME_FAIL;//COMMUNITY_GUILD_LEAVE;

	SendPacket((char*)&res1, sizeof(sTU_GUILD_LEAVE_RES));
	//sCommunity.SendToAll((char*)&res1, sizeof(sTU_GUILD_LEAVE_RES));

	sGU_SYSTEM_DISPLAY_TEXT sNotice;

	sNotice.wOpCode = GU_SYSTEM_DISPLAY_TEXT;
	sNotice.wPacketSize = sizeof(sGU_SYSTEM_DISPLAY_TEXT) - 2;

	sNotice.byDisplayType = eSERVER_TEXT_TYPE::SERVER_TEXT_SYSNOTICE;
	wcscpy_s(sNotice.awchMessage, BUDOKAI_MAX_NOTICE_LENGTH + 1, (L"Function In developpement..."));
	wcscpy_s(sNotice.awGMChar, MAX_SIZE_CHAR_NAME_UNICODE, (L" GM "));
	sNotice.wMessageLengthInUnicode = (WORD)wcslen(sNotice.awchMessage);

	_player->SendPacket((char*)&sNotice, sizeof(sGU_SYSTEM_DISPLAY_TEXT));

}