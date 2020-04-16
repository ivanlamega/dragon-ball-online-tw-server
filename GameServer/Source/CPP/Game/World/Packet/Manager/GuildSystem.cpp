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
	
	sGU_GUILD_CREATE_RES res;

	res.wOpCode = GU_GUILD_CREATE_RES;

	int result = sDB.CreateGuild(WC2MB(req->wszGuildName), _player->GetCharacterID());
	
	switch (result) {

	case GAME_SUCCESS:
	{
		//Send Result Packet SUCCESS
		res.wResultCode = GAME_SUCCESS;
		res.wPacketSize = sizeof(sGU_GUILD_CREATE_RES) - 2;
		SendPacket((char*)&res, sizeof(sGU_GUILD_CREATE_RES));


		// CREATE Guild Creation packet
		sTU_GUILD_CREATED_NFY res2;
		res2.wOpCode = TU_GUILD_CREATED_NFY;
		res2.wPacketSize = sizeof(sTU_GUILD_CREATED_NFY) - 2;
		memcpy(res2.wszGuildName, req->wszGuildName, sizeof(wchar_t)* MAX_SIZE_GUILD_NAME_IN_UNICODE);
		SendPacket((char*)&res2, sizeof(sTU_GUILD_CREATED_NFY));

		//Show Guild Info After creation using TU PACKETS 
		TU_LoadGuildINFO();

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
void WorldSession::GU_LoadGuildINFO() {
		
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

		sLog.outDebug("GU_GUILD_NAME_CHANGED_NFY SENT");


		delete query;
	}
	
}


//SHOW GUILD DATA TO ALL GUILD PLAYERS
void WorldSession::TU_LoadGuildINFO() {
	
	//GET GUILD DATA
	sTU_GUILD_INFO req;

	int result = sDB.GetGuildID(_player->GetCharacterID());

	if (result > 0) {

		// GUILD INFORMATIONS
		sTU_GUILD_INFO res;
		res.wOpCode = TU_GUILD_INFO;
		sql::ResultSet* GuildInfo = sDB.executes("select * from Guilds where GuildID = %d;", result);

		if (!GuildInfo) return;
		if (GuildInfo && GuildInfo->rowsCount() == 0) return;

		res.guildId = GuildInfo->getInt("GuildID");
		res.guildMaster = GuildInfo->getInt("GuildMaster");

		res.guildSecondMaster[0] = GuildInfo->getInt("GuildSecondMaster");
		res.guildSecondMaster[1] = INVALID_TBLIDX;
		res.guildSecondMaster[2] = INVALID_TBLIDX;
		res.guildSecondMaster[3] = INVALID_TBLIDX;

		wcscpy_s(res.wszName, 16 + 1, s2ws(GuildInfo->getString("GuildName")).c_str());
		wcscpy_s(res.awchName, 16 + 1, s2ws(GuildInfo->getString("GuildName")).c_str());
		res.dwGuildReputation = 5000;//1 here is 0 in game i dont know why
		res.dwMaxGuildPointEver = 5000;
		res.qwGuildFunctionFlag = 31984135289;//Need discover how set the bitflag

		res.unk[7] = {0};
		res.unk1 = 0;
		res.wAligniament = 27760;

		wcscpy_s(res.awchNotice, 256 + 1, s2ws(GuildInfo->getString("GuildNotice")).c_str());
		//Mark set Guild Logo we not need set When Create Guild
		res.sMark.byMarkMain = 0;
		res.sMark.byMarkMainColor = 0;
		res.sMark.byMarkInColor = 0;
		res.sMark.byMarkInLine = 0;
		res.sMark.byMarkOutColor = 0;
		res.sMark.byMarkOutLine = 0;
		//sDogi set GuildLogo on Guild Doji
		res.sDogi.guildId = GuildInfo->getInt("GuildID");
		res.sDogi.byType = -1;
		res.sDogi.byGuildColor = -1;
		res.sDogi.byDojoColor = -1;
		res.wPacketSize = sizeof(sTU_GUILD_INFO) - 2;

		SendPacket((char*)&res, sizeof(sTU_GUILD_INFO));


		sql::ResultSet * GuildMembers = sDB.executes("");


		// Need Load Guild Member By GuildID and send 1 packet for player
		sTU_GUILD_MEMBER_INFO res2;


		res2.wOpCode = TU_GUILD_MEMBER_INFO;
		res2.wPacketSize = sizeof(sTU_GUILD_MEMBER_INFO) - 2;
		res2.guildMemberInfo.charId = _player->GetCharacterID();
		wcscpy_s(res2.guildMemberInfo.wszMemberName, 16 + 1, _player->GetPcProfile()->awchName);

		res2.guildMemberInfo.byRace = _player->GetAttributesManager()->PlayerRaceID;
		res2.guildMemberInfo.byClass = _player->GetAttributesManager()->PlayerClassID;
		res2.guildMemberInfo.byLevel = _player->GetPcProfile()->byLevel;
		res2.guildMemberInfo.bIsOnline = true;
		res2.guildMemberInfo.WORLDID = 1;
		res2.guildMemberInfo.MAPID = 200107100; //4294967295 Need fix map ids
		res2.guildMemberInfo.unk[0] = 0;
		res2.guildMemberInfo.unk[1] = 0;
		res2.guildMemberInfo.dwReputation = 0;


		SendPacket((char*)&res2, sizeof(sTU_GUILD_MEMBER_INFO));
		sLog.outDebug("sTU_GUILD_MEMBER_INFO sent");


	}

	GU_LoadGuildINFO();
}






//Invite Player in the world to Guild
void WorldSession::InvitePlayertoGuild(Packet& packet) {

	//Cast Packet
	sUG_GUILD_INVITE_REQ * req = (sUG_GUILD_INVITE_REQ*)packet.GetPacketBuffer();

	//Cast Player
	Player* PlayerInfo = static_cast<Player*>(_player->GetFromList(req->hTarget));

	//Prepare response Packet
	sGU_GUILD_INVITE_RES res;
	res.wOpCode = GU_GUILD_INVITE_RES;
	res.wResultCode = GAME_SUCCESS;
	res.wPacketSize = sizeof(sGU_GUILD_INVITE_RES) - 2;
	wcscpy_s(res.wszTargetName, 16 + 1, PlayerInfo->GetPcProfile()->awchName);
	SendPacket((char*)&res, sizeof(sGU_GUILD_INVITE_RES));


}


