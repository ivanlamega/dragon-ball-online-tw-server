#include <Game\World\WorldSession.h>
#include <Game\World\World.h>
#include <Packet\Game\PacketGU.h>
#include <Packet\Game\PacketUG.h>
#include <Packet\Community\PacketUT.h>
#include <Packet\Community\PacketTU.h>
#include <Game\Object\Player.h>
#include <Game\Maps\MapManager.h>
#include <Game\Maps\Map.h>
#include <mysqlconn_wrapper.h>
#include <Logger.h>
#include <World.h>
#include <XmlParser2/XmlParser2.h>


//Create GUILD from NPC
void WorldSession::CreateNewGuild(Packet& packet)
{

	//Cast Packet
	sUG_GUILD_CREATE_REQ * req = (sUG_GUILD_CREATE_REQ*)packet.GetPacketBuffer();

	//Preparing Guild Creation Packet
	sGU_GUILD_CREATE_RES res;
	res.wOpCode = GU_GUILD_CREATE_RES;

	int result = sDB.CreateGuild(WC2MB(req->wszGuildName), _player->GetCharacterID());
	
	switch (result) {

	case GAME_SUCCESS:
	{
		
	    // CREATE Guild Creation packet
		sTU_GUILD_CREATED_NFY res2;
		res2.wOpCode = TU_GUILD_CREATED_NFY;
		res2.wPacketSize = sizeof(sTU_GUILD_CREATED_NFY) - 2;
		memcpy(res2.wszGuildName, req->wszGuildName, sizeof(wchar_t)* MAX_SIZE_GUILD_NAME_IN_UNICODE);
		SendPacket((char*)&res2, sizeof(sTU_GUILD_CREATED_NFY));


		//Send Result Packet SUCCESS
		res.wResultCode = GAME_SUCCESS;
		res.wPacketSize = sizeof(sGU_GUILD_CREATE_RES) - 2;
		SendPacket((char*)&res, sizeof(sGU_GUILD_CREATE_RES));

		//Show Guild Info After creation using TU PACKETS 
		LoadGuildInfotoPlayer();

		break;
	}	
	case GAME_GUILD_SAME_GUILD_NAME_EXIST:
	{
		//Send Result Packet SUCCESS
		res.wResultCode = ResultCodes::GAME_GUILD_SAME_GUILD_NAME_EXIST;
		res.wPacketSize = sizeof(sGU_GUILD_CREATE_RES) - 2;
		SendPacket((char*)&res, sizeof(sGU_GUILD_CREATE_RES));

		break;
	}
	default:
	{
		//Send Result Packet Fail
		res.wResultCode = ResultCodes::GAME_FAIL;
		res.wPacketSize = sizeof(sGU_GUILD_CREATE_RES) - 2;
		SendPacket((char*)&res, sizeof(sGU_GUILD_CREATE_RES));
		break;
	}

	}

	
}


//Show Guild INFO TO ALL OTHER PLAYERS
void WorldSession::LoadGuildInfotoOtherPlayers() {

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

		sWorld.SendToAll((char*)&res2, sizeof(sGU_GUILD_NAME_CHANGED_NFY));

		delete query;
	}

}

//SHOW GUILD DATA TO ALL GUILD PLAYERS
void WorldSession::LoadGuildInfotoPlayer() {

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
		if (GuildInfo->getInt("GuildSecondMaster") > 0) res.guildSecondMaster[0] = GuildInfo->getInt("GuildSecondMaster");
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

void WorldSession::LoadGuildMembers() {

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
		else if (sWorld.FindSession(GuildMembers->getInt("CharacterID"))) {

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
			Player* plr = static_cast<Player*>(sWorld.FindSession(GuildMembers->getInt("CharacterID"))->_player);
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


//Invite Player in the world to Guild
void WorldSession::InvitePlayertoGuild(Packet& packet) {

	//Cast Packet
	sUG_GUILD_INVITE_REQ * req = (sUG_GUILD_INVITE_REQ*)packet.GetPacketBuffer();

	//Cast Player need to be tested
	Player* PlayerInfo = static_cast<Player*>(_player->GetFromList(req->hTarget));

	sLog.outDebug("Target : %d , Name : %s", req->hTarget, PlayerInfo->GetName());

	//Prepare response Packet
	sGU_GUILD_INVITE_RES res;
	memset(&res, 0, sizeof(sGU_GUILD_INVITE_RES));
	res.wOpCode = GU_GUILD_INVITE_RES;
	res.wResultCode = ResultCodes::GAME_SUCCESS;
	res.wPacketSize = sizeof(sGU_GUILD_INVITE_RES) - 2;
	wcscpy_s(res.wszTargetName, 16 + 1, PlayerInfo->GetPcProfile()->awchName);
	SendPacket((char*)&res, sizeof(sGU_GUILD_INVITE_RES));

	
	int result = sDB.GetGuildID(_player->GetCharacterID());
	if (!result) return;

	sql::ResultSet* GuildInfo = sDB.executes("select * from Guilds where GuildID = %d;", result);
	if (!GuildInfo) return;
	
	if (sDB.executes("UPDATE `characters` SET `GuildID` = '%d' WHERE `CharacterID` = '%d';", result, PlayerInfo->GetCharacterID())) return;


	sTU_GUILD_INVITED_NFY res2;
	memset(&res2, 0, sizeof(sTU_GUILD_INVITED_NFY));
	res2.wOpCode = TU_GUILD_INVITED_NFY;
	res2.wPacketSize = sizeof(sTU_GUILD_INVITED_NFY) - 2;
	wcscpy_s(res2.wszGuildName, 32 + 1, s2ws(GuildInfo->getString("GuildName")).c_str());
	PlayerInfo->SendPacket((char*)&res2, sizeof(sTU_GUILD_INVITED_NFY));

}


void WorldSession::NotifyguildiesAfterLoginOn(Player* plr) {

	sTU_GUILD_MEMBER_ONLINE_NFY res3;
	res3.wOpCode = TU_GUILD_MEMBER_ONLINE_NFY;
	res3.wPacketSize = sizeof(sTU_GUILD_MEMBER_ONLINE_NFY) - 2;
	res3.memberCharId = _player->GetCharacterID();
	res3.newMapNameTblidx = 200107100;
	plr->SendPacket((char*)&res3, sizeof(sTU_GUILD_MEMBER_ONLINE_NFY));

}


//in dev 

void WorldSession::GUILD_GIVE_ZENNY(Packet& packet) {

	sGU_GUILD_GIVE_ZENNY_RES res;
	res.wOpCode = GU_GUILD_GIVE_ZENNY_RES;
	res.wResultCode = GAME_SUCCESS;
	res.wPacketSize = sizeof(sGU_GUILD_GIVE_ZENNY_RES) - 2;

	_player->SendPacket((char*)&res, sizeof(sGU_GUILD_GIVE_ZENNY_RES));

	sGU_SYSTEM_DISPLAY_TEXT sNotice;

	sNotice.wOpCode = GU_SYSTEM_DISPLAY_TEXT;
	sNotice.wPacketSize = sizeof(sGU_SYSTEM_DISPLAY_TEXT) - 2;

	sNotice.byDisplayType = eSERVER_TEXT_TYPE::SERVER_TEXT_SYSNOTICE;
	wcscpy_s(sNotice.awchMessage, BUDOKAI_MAX_NOTICE_LENGTH + 1, (L"Function In developpement..."));
	wcscpy_s(sNotice.awGMChar, MAX_SIZE_CHAR_NAME_UNICODE, (L" GM "));
	sNotice.wMessageLengthInUnicode = (WORD)wcslen(sNotice.awchMessage);

	_player->SendPacket((char*)&sNotice, sizeof(sGU_SYSTEM_DISPLAY_TEXT));
}


void WorldSession::GUILD_FUNCTION_ADD_REQ(Packet& packet) {


	sGU_GUILD_FUNCTION_ADD_RES res;
	res.wOpCode = GU_GUILD_FUNCTION_ADD_RES;
	res.wResultCode = GAME_SUCCESS;
	res.wPacketSize = sizeof(sGU_GUILD_FUNCTION_ADD_RES) - 2;

	_player->SendPacket((char*)&res, sizeof(sGU_GUILD_FUNCTION_ADD_RES));

	sGU_SYSTEM_DISPLAY_TEXT sNotice;

	sNotice.wOpCode = GU_SYSTEM_DISPLAY_TEXT;
	sNotice.wPacketSize = sizeof(sGU_SYSTEM_DISPLAY_TEXT) - 2;

	sNotice.byDisplayType = eSERVER_TEXT_TYPE::SERVER_TEXT_SYSNOTICE;
	wcscpy_s(sNotice.awchMessage, BUDOKAI_MAX_NOTICE_LENGTH + 1, (L"Function In developpement..."));
	wcscpy_s(sNotice.awGMChar, MAX_SIZE_CHAR_NAME_UNICODE, (L" GM "));
	sNotice.wMessageLengthInUnicode = (WORD)wcslen(sNotice.awchMessage);

	_player->SendPacket((char*)&sNotice, sizeof(sGU_SYSTEM_DISPLAY_TEXT));
}


void WorldSession::GUILD_CREATE_MARK_REQ(Packet& packet) {

	sGU_GUILD_CREATE_MARK_RES res;
	res.wOpCode = GU_GUILD_CREATE_MARK_RES;
	res.wResultCode = GAME_SUCCESS;
	res.wPacketSize = sizeof(sGU_GUILD_CREATE_MARK_RES) - 2;

	_player->SendPacket((char*)&res, sizeof(sGU_GUILD_CREATE_MARK_RES));

	sGU_SYSTEM_DISPLAY_TEXT sNotice;

	sNotice.wOpCode = GU_SYSTEM_DISPLAY_TEXT;
	sNotice.wPacketSize = sizeof(sGU_SYSTEM_DISPLAY_TEXT) - 2;

	sNotice.byDisplayType = eSERVER_TEXT_TYPE::SERVER_TEXT_SYSNOTICE;
	wcscpy_s(sNotice.awchMessage, BUDOKAI_MAX_NOTICE_LENGTH + 1, (L"Function In developpement..."));
	wcscpy_s(sNotice.awGMChar, MAX_SIZE_CHAR_NAME_UNICODE, (L" GM "));
	sNotice.wMessageLengthInUnicode = (WORD)wcslen(sNotice.awchMessage);

	_player->SendPacket((char*)&sNotice, sizeof(sGU_SYSTEM_DISPLAY_TEXT));

}
