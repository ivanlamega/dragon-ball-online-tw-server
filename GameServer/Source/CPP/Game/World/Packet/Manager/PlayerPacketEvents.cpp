#include <Game\World\WorldSession.h>
#include <Packet\Game\PacketGU.h>
#include <Packet\Game\PacketUG.h>
#include <Game\Object\Player.h>
#include <Game\Maps\MapManager.h>
#include <mysqlconn_wrapper.h>
#include <Logger.h>
#include <World.h>
#include <XmlParser.h>


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

		//Set Nigth 
		//Disable Because Disconect Client

		//sGU_AVATAR_ZONE_INFO zoneinfo;
		//zoneinfo.wOpCode = GU_AVATAR_ZONE_INFO;
		//zoneinfo.wPacketSize = sizeof(sGU_AVATAR_ZONE_INFO) - 2;
		//zoneinfo.zoneInfo.bIsDark = true;
		//zoneinfo.zoneInfo.zoneId = 0; // 0 namek start zone
		//SendPacket((char*)&zoneinfo, sizeof(sGU_AVATAR_ZONE_INFO));
		//sWorld.SendToAll((char*)&zoneinfo, sizeof(sGU_AVATAR_ZONE_INFO));

		//Spawn Shenlong
		NPCTable * NpcTable = sTBM.GetNpcTable();
		sNPC_TBLDAT * Npc = reinterpret_cast<sNPC_TBLDAT*>(NpcTable->FindData(6361101));
		if (Npc != NULL)
		{

			SpawnNPC spawnData;
			memset(&spawnData, 0, sizeof(SpawnNPC));

			spawnData.wOpCode = GU_OBJECT_CREATE;
			spawnData.wPacketSize = sizeof(SpawnNPC) - 2;

			spawnData.AspectID = 0;
			spawnData.CurEP = Npc->wBasic_EP;
			spawnData.CurLP = Npc->wBasic_LP;
			spawnData.Handle = INVALID_TBLIDX - 1;
			spawnData.Level = Npc->byLevel;
			spawnData.MaxEP = Npc->wBasic_EP;
			spawnData.MaxLP = Npc->wBasic_LP;
			spawnData.ModelSize = 10;
			spawnData.OBJType = OBJTYPE_NPC;
			spawnData.Position.x = 4708;
			spawnData.Position.y = -52;
			spawnData.Position.z = 4001;
			spawnData.Rotation.x = 0;
			spawnData.Rotation.y = 0;
			spawnData.Rotation.z = 0;
			spawnData.StateID = eCHARSTATE::CHARSTATE_SPAWNING;
			spawnData.Tblidx = 6361101;

			sWorld.SendToAll((char*)&spawnData, sizeof(SpawnNPC));

			sGU_UPDATE_CHAR_STATE update;
			update.wOpCode = GU_UPDATE_CHAR_STATE;
			update.wPacketSize = sizeof(sGU_UPDATE_CHAR_STATE) - 2;
			update.handle = INVALID_TBLIDX - 1;
			update.sCharState.sCharStateBase.byStateID = CHARSTATE_SPAWNING;
			SendPacket((char*)&update, sizeof(sGU_UPDATE_CHAR_STATE));
			sWorld.SendToAll((char*)&spawnData, sizeof(SpawnNPC));
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
			LearnSkill(RewardTabledat->rewardLinkTblidx);
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

		//Set Day Disable because Disconect Client

		//sGU_AVATAR_ZONE_INFO zoneinfo;
		//zoneinfo.wOpCode = GU_AVATAR_ZONE_INFO;
		//zoneinfo.zoneInfo.bIsDark = false;
		//zoneinfo.zoneInfo.zoneId = 0;

		//SendPacket((char*)&zoneinfo, sizeof(sGU_AVATAR_ZONE_INFO));
		//_player->SendToPlayerList((char*)&zoneinfo, sizeof(sGU_AVATAR_ZONE_INFO));

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