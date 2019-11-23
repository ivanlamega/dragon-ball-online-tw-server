#include <Game\World\WorldSession.h>
#include <Packet\Game\PacketGU.h>
#include <Packet\Game\PacketUG.h>
#include <Packet\Community\PacketUT.h>
#include <Packet\Community\PacketTU.h>
#include <Game\Object\Player.h>
#include <Game\Maps\MapManager.h>
#include <mysqlconn_wrapper.h>
#include <Logger.h>
#include <World.h>
#include <XmlParser2/XmlParser2.h>


void WorldSession::SendDragonBallsCheck(Packet & packet)
{
	sUG_DRAGONBALL_CHECK_REQ *req = (sUG_DRAGONBALL_CHECK_REQ*)packet.GetPacketBuffer();
	//printf("hObject %d\n sData %d\n "), req->hObject, req->sData[0].byPlace;

	// Verificacion for not have 2 player Call Shenlong at Same Time
	// we shold validate 1 player for Altar ObjectID 
	//Direct Play is Worong Animation
	if (sWorld.Shenlong == true)
	{
		sGU_DRAGONBALL_CHECK_RES check;
		check.wOpCode = GU_DRAGONBALL_CHECK_RES;
		check.wPacketSize = sizeof(sGU_DRAGONBALL_CHECK_RES) - 2;
		check.hObject = req->hObject;

		check.wResultCode = GAME_COMMON_CANT_DO_THAT_FOR_SOME_REASON;
		SendPacket((char*)&check, sizeof(sGU_DRAGONBALL_CHECK_RES));
	}
	// if Altar no player Call Check dragon Balls 
	if (sWorld.Shenlong == false)
	{
		//Check dragonBalls
		sGU_DRAGONBALL_CHECK_RES check;
		check.wOpCode = GU_DRAGONBALL_CHECK_RES;
		check.wPacketSize = sizeof(sGU_DRAGONBALL_CHECK_RES) - 2;
		check.hObject = req->hObject;

		check.wResultCode = GAME_SUCCESS;
		SendPacket((char*)&check, sizeof(sGU_DRAGONBALL_CHECK_RES));


		sGU_AVATAR_ZONE_INFO zoneinfo;
		zoneinfo.wOpCode = GU_AVATAR_ZONE_INFO;
		zoneinfo.wPacketSize = sizeof(sGU_AVATAR_ZONE_INFO) - 2;
		zoneinfo.zoneInfo.bIsDark = true;
		zoneinfo.zoneInfo.zoneId = 0;
		SendPacket((char*)&zoneinfo, sizeof(sGU_AVATAR_ZONE_INFO));
		sWorld.SendToAll((char*)&zoneinfo, sizeof(sGU_AVATAR_ZONE_INFO));

		//Spawn Shenlong
		NPCTable * NpcTable = sTBM.GetNpcTable();
		sNPC_TBLDAT * Npc = reinterpret_cast<sNPC_TBLDAT*>(NpcTable->FindData(6361101));
		if (Npc != NULL)
		{

			SpawnNPC spawnData;
			memset(&spawnData, 0, sizeof(SpawnNPC));

			spawnData.wOpCode = GU_OBJECT_CREATE;
			spawnData.wPacketSize = sizeof(SpawnNPC) - 2;
			
			spawnData.CurEP = Npc->wBasic_EP;
			spawnData.CurLP = Npc->wBasic_LP;
			spawnData.Handle = INVALID_TBLIDX - 1;			
			spawnData.MaxEP = Npc->wBasic_EP;
			spawnData.MaxLP = Npc->wBasic_LP;			
			spawnData.OBJType = OBJTYPE_NPC;			
			spawnData.Tblidx = 6361101;
			spawnData.State.sCharStateBase.aspectState.sAspectStateBase.byAspectStateId = 255;
			spawnData.State.sCharStateBase.vCurLoc.x = 4708;
			spawnData.State.sCharStateBase.vCurLoc.y = -52;
			spawnData.State.sCharStateBase.vCurLoc.z = 4001;
			spawnData.State.sCharStateBase.vCurDir.x = 0;
			spawnData.State.sCharStateBase.vCurDir.y = 0;
			spawnData.State.sCharStateBase.vCurDir.z = 0;
			spawnData.State.sCharStateBase.byStateID = eCHARSTATE::CHARSTATE_SPAWNING;
			spawnData.State.sCharStateDetail.sCharStateSpawning.byTeleportType = 1;
			spawnData.State.sCharStateDetail.sCharStateSpawning.unk = 1;
			spawnData.Size = 10;
			SendPacket((char*)&spawnData, sizeof(SpawnNPC));
			sWorld.Shenlong = true;			
			
		}
	}
}

void WorldSession::SendShenlongReward(Packet & packet)
{
	sUG_DRAGONBALL_REWARD_REQ *req = (sUG_DRAGONBALL_REWARD_REQ*)packet.GetPacketBuffer();
	//Load Table
//	printf("DRAGONBALL_REWARD_TYPE_ITEM \n");
	DragonBallRewardTable* retwardtable = sTBM.GetDragonBallRewardTable();
	sDRAGONBALL_REWARD_TBLDAT* RewardTabledat = reinterpret_cast<sDRAGONBALL_REWARD_TBLDAT*>(retwardtable->FindData(req->rewardTblidx));
	if (RewardTabledat != NULL)
	{
		//printf("DRAGONBALL_REWARD_TYPE_ITEM %d \n", RewardTabledat->rewardLinkTblidx);
		// Check What is Your Reward Choice
		switch (RewardTabledat->byRewardType)
		{

		case DRAGONBALL_REWARD_TYPE_ITEM:
		{
			//printf("DRAGONBALL_REWARD_TYPE_ITEM %d \n", RewardTabledat->rewardLinkTblidx);
			sITEM_PROFILE *data = _player->inventoryManager.CreateNewItem(RewardTabledat->rewardLinkTblidx, 1);
			if (data != NULL)
			{
				SendItemCreate(data);
			}
			break;
		}
		case DRAGONBALL_REWARD_TYPE_SKILL:
		{
			//printf("DRAGONBALL_REWARD_TYPE_SKILL %d \n", RewardTabledat->rewardLinkTblidx);
			RewardSkill(RewardTabledat->rewardLinkTblidx);
			break;
		}
		case DRAGONBALL_REWARD_TYPE_ZENNY:
		{
			//printf("DRAGONBALL_REWARD_TYPE_ZENNY %d \n", RewardTabledat->dwRewardZenny);
			_player->UpdateZennyAmount(RewardTabledat->dwRewardZenny * _player->GetPcProfile()->byLevel, eZENNY_CHANGE_TYPE::ZENNY_CHANGE_TYPE_DB_REWARD);
			break;
		}
		case DRAGONBALL_REWARD_TYPE_HTB:
		{
			printf("DRAGONBALL_REWARD_TYPE_HTB %d \n", RewardTabledat->rewardLinkTblidx);
			//Send LearnSkill
			//LearnSkill(RewardTabledat->rewardLinkTblidx);
			break;
		}
		}
		// switch End

		//Confirm Reward
		sGU_DRAGONBALL_REWARD_RES Reward;
		Reward.wOpCode = GU_DRAGONBALL_REWARD_RES;
		Reward.wPacketSize = sizeof(sGU_DRAGONBALL_REWARD_RES) - 2;
		Reward.hObject = req->hObject;
		Reward.wResultCode = GAME_SUCCESS;
		SendPacket((char*)&Reward, sizeof(sGU_DRAGONBALL_REWARD_RES));

		

		sGU_AVATAR_ZONE_INFO zoneinfo;
		zoneinfo.wOpCode = GU_AVATAR_ZONE_INFO;
		zoneinfo.wPacketSize = sizeof(sGU_AVATAR_ZONE_INFO) - 2;
		zoneinfo.zoneInfo.bIsDark = false;
		zoneinfo.zoneInfo.zoneId = 0; 
		SendPacket((char*)&zoneinfo, sizeof(sGU_AVATAR_ZONE_INFO));
		sWorld.SendToAll((char*)&zoneinfo, sizeof(sGU_AVATAR_ZONE_INFO));

		// Despawning Shenlong
		sGU_UPDATE_CHAR_STATE update;
		update.wOpCode = GU_UPDATE_CHAR_STATE;
		update.wPacketSize = sizeof(sGU_UPDATE_CHAR_STATE) - 2;
		update.handle = INVALID_TBLIDX - 1;
		update.sCharState.sCharStateBase.byStateID = CHARSTATE_DESPAWNING;

		SendPacket((char*)&update, sizeof(sGU_UPDATE_CHAR_STATE));
		sWorld.SendToAll((char*)&update, sizeof(sGU_UPDATE_CHAR_STATE));

		sGU_OBJECT_DESTROY destroy;
		destroy.wOpCode = GU_OBJECT_DESTROY;
		destroy.wPacketSize = sizeof(sGU_OBJECT_DESTROY) - 2;
		destroy.handle = INVALID_TBLIDX - 1;
		SendPacket((char*)&destroy, sizeof(sGU_OBJECT_DESTROY));
		sWorld.SendToAll((char*)&destroy, sizeof(sGU_OBJECT_DESTROY));
		sWorld.Shenlong = false;

		// Need Delet DragonBalls from Bag Here
		//Direct Play Bug Camera after Despawning
	}
}
void WorldSession::SendGuildCreateReq(Packet& packet)
{
	//printf("--- create guild request --- \n");

	sUG_GUILD_CREATE_REQ * req = (sUG_GUILD_CREATE_REQ*)packet.GetPacketBuffer();

	
	sGU_GUILD_CREATE_RES res;

	res.wOpCode = GU_GUILD_CREATE_RES;
	printf("guild manager id: %i ", req->hGuildManagerNpc);

	int result = sDB.CreateGuild(WC2MB(req->wszGuildName), _player->GetCharacterID());

	printf("create guild result %i \n ", result);
	res.wResultCode = result;
	res.wPacketSize = sizeof(sGU_GUILD_CREATE_RES) - 2;

	SendPacket((char*)&res, sizeof(sGU_GUILD_CREATE_RES));
	if (result == 500) {

		// CREATE GUILDPacket packet2(sizeof(sTU_GUILD_CREATED_NFY));
		sTU_GUILD_CREATED_NFY res2;
		res2.wOpCode = TU_GUILD_CREATED_NFY;
		res2.wPacketSize = sizeof(sTU_GUILD_CREATED_NFY) - 2;
		memcpy(res2.wszGuildName, req->wszGuildName, sizeof(wchar_t)* MAX_SIZE_GUILD_NAME_IN_UNICODE);
		SendPacket((char*)&res2, sizeof(sTU_GUILD_CREATED_NFY));

		// GUILD INFORMATIONS		
		sTU_GUILD_INFO res3;
		res3.wOpCode = TU_GUILD_INFO;		
		sql::ResultSet* sql = sDB.executes("select * from Guilds where GuildMaster = %d", _player->GetCharacterID());

		res3.guildId = sql->getInt("GuildID");
		res3.guildMaster = _player->GetCharacterID();
		res3.guildSecondMaster[0] = INVALID_TBLIDX;
		res3.guildSecondMaster[1] = INVALID_TBLIDX;
		res3.guildSecondMaster[2] = INVALID_TBLIDX;
		res3.guildSecondMaster[3] = INVALID_TBLIDX;
		memcpy(res3.wszName, req->wszGuildName, sizeof(wchar_t) * 17);
		wcscpy_s(res3.awchName, MAX_SIZE_CHAR_NAME_UNICODE + 1, s2ws(_player->GetName()).c_str());
		res3.dwGuildReputation = 1;//1 here is 0 in game i dont know why
		res3.dwMaxGuildPointEver = 0;
		res3.qwGuildFunctionFlag = 0;//Need discover how set the bitflag
		wcscpy_s(res3.awchName, 16 + 1, req->wszGuildName);
		wcscpy_s(res3.awchNotice, 256 + 1, req->wszGuildName);
		//Mark set Guild Logo we not need set When Create Guild
		res3.sMark.byMarkMain = 0;
		res3.sMark.byMarkMainColor = 0;
		res3.sMark.byMarkInColor = 0;
		res3.sMark.byMarkInLine = 0;
		res3.sMark.byMarkOutColor = 0;
		res3.sMark.byMarkOutLine = 0;
		//sDogi set GuildLogo on Guild Doji 
		res3.sDogi.guildId = 1;
		res3.sDogi.byType = -1;
		res3.sDogi.byGuildColor = -1;
		res3.sDogi.byDojoColor = -1;
		res3.wPacketSize = sizeof(sTU_GUILD_INFO) - 2;
		SendPacket((char*)&res3, sizeof(sTU_GUILD_INFO));
		sLog.outDebug("sTU_GUILD_INFO sent");
		// GUILD MEMBER INFORMATIONS 
		// Need Load Guild Member By GuildID and send 1 packet for player		
		sTU_GUILD_MEMBER_INFO res4;

		res4.wOpCode = TU_GUILD_MEMBER_INFO;
		res4.guildMemberInfo.bIsOnline = true;
		res4.guildMemberInfo.charId = _player->GetCharacterID();
		wcscpy_s(res4.guildMemberInfo.wszMemberName, 16 + 1, _player->GetPcProfile()->awchName);

		res4.guildMemberInfo.byRace = _player->GetAttributesManager()->PlayerRaceID;
		res4.guildMemberInfo.byClass = _player->GetAttributesManager()->PlayerClassID;
		res4.guildMemberInfo.byLevel = _player->GetPcProfile()->byLevel;
		res4.guildMemberInfo.bIsOnline = 1;
		res4.guildMemberInfo.WORLDID = 1;
		res4.guildMemberInfo.MAPID = 200101000;

		wcscpy_s(res4.guildMemberInfo.wszMemberName, MAX_SIZE_CHAR_NAME_UNICODE, s2ws(_player->GetName()).c_str());
		res4.wPacketSize = sizeof(sTU_GUILD_MEMBER_INFO) - 2;

		SendPacket((char*)&res4, sizeof(sTU_GUILD_MEMBER_INFO));
		sLog.outDebug("sTU_GUILD_MEMBER_INFO sent");

	}
}