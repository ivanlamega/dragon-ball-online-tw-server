#include <Game\World\WorldSession.h>
#include <Packet\Game\PacketGU.h>
#include <Packet\Game\PacketUG.h>
#include <Game\Object\Player.h>
#include <Game\Maps\MapManager.h>
#include <mysqlconn_wrapper.h>
#include <Logger.h>
#include <World.h>

void WorldSession::SendUpdateCharCondition(DWORD conditionFlag)
{
	sGU_UPDATE_CHAR_CONDITION condition;
	condition.wOpCode = GU_UPDATE_CHAR_CONDITION;
	condition.wPacketSize = sizeof(sGU_UPDATE_CHAR_CONDITION) - 2;

	condition.handle = _player->GetHandle();
	condition.dwConditionFlag = conditionFlag;
	condition.unknown = 0;

	sWorld.SendToAll((char*)&condition, sizeof(sGU_UPDATE_CHAR_CONDITION));
}

void WorldSession::SendCharTeleportRes(Packet& packet)
{
	sGU_CHAR_TELEPORT_RES Teleport;
	memset(&Teleport, 0, sizeof(sGU_CHAR_TELEPORT_RES));
	Teleport.wOpCode = GU_CHAR_TELEPORT_RES;
	Teleport.wPacketSize = sizeof(sGU_CHAR_TELEPORT_RES) - 2;
	Teleport.wResultCode = GAME_CAN_NOT_TELEPORT;

	switch (_player->GetState()->sCharStateDetail.sCharStateDespawning.byTeleportType)
	{
		case eTELEPORT_TYPE::TELEPORT_TYPE_DEFAULT:
		{
			Teleport.wResultCode = GAME_SUCCESS;
			Teleport.vNewLoc.x = _player->GetAttributesManager()->teleportInfo.position.x;//4474.109863;
			Teleport.vNewLoc.y = _player->GetAttributesManager()->teleportInfo.position.y;//-42.000000;
			Teleport.vNewLoc.z = _player->GetAttributesManager()->teleportInfo.position.z; //3958.379883;
			Teleport.vNewDir.x = _player->GetAttributesManager()->teleportInfo.rotation.x; //-0.751000;
			Teleport.vNewDir.y = _player->GetAttributesManager()->teleportInfo.rotation.y;//0;
			Teleport.vNewDir.z = _player->GetAttributesManager()->teleportInfo.rotation.z; //-0.661000;
			Teleport.unk = INVALID_TBLIDX;
			Teleport.bIsToMoveAnotherServer = false;

			_player->Relocate(Teleport.vNewLoc.x, Teleport.vNewLoc.y, Teleport.vNewLoc.z, Teleport.vNewDir.x, Teleport.vNewDir.y, Teleport.vNewDir.z);

			sWORLD_TBLDAT* worldTbl = (sWORLD_TBLDAT*)sTBM.GetWorldTable()->FindData(_player->GetAttributesManager()->teleportInfo.worldInfo.tblidx);
			sLog.outDebug("1------------WORLD TBLIDX %d-----------------", _player->GetAttributesManager()->teleportInfo.worldInfo.tblidx);
			if (worldTbl != NULL)
			{
				_player->SetWorldID(worldTbl->tblidx);
				_player->SetWorldTableID(worldTbl->tblidx);
				_player->GetState()->sCharStateDetail.sCharStateTeleporting.byTeleportType = eTELEPORT_TYPE::TELEPORT_TYPE_DEFAULT;//eTELEPORT_TYPE::TELEPORT_TYPE_NPC_PORTAL;
				_player->SetState(eCHARSTATE::CHARSTATE_TELEPORTING);
			}
			else {
				Teleport.wResultCode = GAME_CAN_NOT_TELEPORT;
				_player->SetState(eCHARSTATE::CHARSTATE_STANDING);
			}
			/*	   NOT SURE IF THIS IS A GOOD IDEA FOR NOW		*/
			Map* map = _player->GetMap();
			map->Remove(_player, false);
			_player->ClearListAndReference();
			sLog.outDebug("--------TELEPORT DEFAULT--------");
			break;
		}
		case eTELEPORT_TYPE::TELEPORT_TYPE_NPC_PORTAL:
		{
			Teleport.wResultCode = GAME_SUCCESS;
			Teleport.vNewLoc.x = _player->GetAttributesManager()->teleportInfo.position.x;//4474.109863;
			Teleport.vNewLoc.y = _player->GetAttributesManager()->teleportInfo.position.y;//-42.000000;
			Teleport.vNewLoc.z = _player->GetAttributesManager()->teleportInfo.position.z; //3958.379883;
			Teleport.vNewDir.x = _player->GetAttributesManager()->teleportInfo.rotation.x; //-0.751000;
			Teleport.vNewDir.y = _player->GetAttributesManager()->teleportInfo.rotation.y;//0;
			Teleport.vNewDir.z = _player->GetAttributesManager()->teleportInfo.rotation.z; //-0.661000;
			Teleport.unk = INVALID_TBLIDX;
			Teleport.bIsToMoveAnotherServer = _player->GetAttributesManager()->teleportInfo.bIsToMoveAnotherServer;
			Teleport.sWorldInfo.worldID = _player->GetAttributesManager()->teleportInfo.worldInfo.worldID;
			Teleport.sWorldInfo.tblidx = _player->GetAttributesManager()->teleportInfo.worldInfo.tblidx;
			Teleport.sWorldInfo.sRuleInfo.byRuleType = _player->GetAttributesManager()->teleportInfo.worldInfo.sRuleInfo.byRuleType;

			_player->Relocate(Teleport.vNewLoc.x, Teleport.vNewLoc.y, Teleport.vNewLoc.z, Teleport.vNewDir.x, Teleport.vNewDir.y, Teleport.vNewDir.z);
			_player->SetWorldID(Teleport.sWorldInfo.worldID);
			_player->SetWorldTableID(Teleport.sWorldInfo.tblidx);

			/*sGU_UPDATE_CHAR_CONDITION condition;
			condition.wOpCode = GU_UPDATE_CHAR_CONDITION;
			condition.wPacketSize = sizeof(sGU_UPDATE_CHAR_CONDITION) - 2;

			condition.handle = _player->GetHandle();
			condition.dwConditionFlag = 0;
			condition.unknown = 0;

			sWorld.SendToAll((char*)&condition, sizeof(sGU_UPDATE_CHAR_CONDITION));*/
			SendUpdateCharCondition(0);

			memset(&(_player->GetAttributesManager()->teleportInfo), 0, sizeof _player->GetAttributesManager()->teleportInfo);
			sLog.outDebug("--------TELEPORT NPC--------");
			sLog.outDebug("Type teleport %d", _player->GetState()->sCharStateDetail.sCharStateDespawning.byTeleportType);

			_player->GetState()->sCharStateDetail.sCharStateTeleporting.byTeleportType = eTELEPORT_TYPE::TELEPORT_TYPE_NPC_PORTAL;
			_player->UpdateState(eCHARSTATE::CHARSTATE_TELEPORTING);

			/*	   NOT SURE IF THIS IS A GOOD IDEA FOR NOW		*/
			Map* map = _player->GetMap();
			map->Remove(_player, false);
			_player->ClearListAndReference();
			break;
		}
		case eTELEPORT_TYPE::TELEPORT_TYPE_TIMEQUEST:
		{
			Teleport.wResultCode = GAME_SUCCESS;
			Teleport.vNewLoc.x = _player->GetAttributesManager()->teleportInfo.position.x;
			Teleport.vNewLoc.y = _player->GetAttributesManager()->teleportInfo.position.y;
			Teleport.vNewLoc.z = _player->GetAttributesManager()->teleportInfo.position.z;

			Teleport.vNewDir.x = _player->GetAttributesManager()->teleportInfo.rotation.x;
			Teleport.vNewDir.y = _player->GetAttributesManager()->teleportInfo.rotation.y;
			Teleport.vNewDir.z = _player->GetAttributesManager()->teleportInfo.rotation.z;
			Teleport.unk = INVALID_TBLIDX;

			Teleport.bIsToMoveAnotherServer = _player->GetAttributesManager()->teleportInfo.bIsToMoveAnotherServer;
			Teleport.sWorldInfo.worldID = _player->GetAttributesManager()->teleportInfo.worldInfo.worldID;
			Teleport.sWorldInfo.tblidx = _player->GetAttributesManager()->teleportInfo.worldInfo.tblidx;
			Teleport.sWorldInfo.hTriggerObjectOffset = _player->GetAttributesManager()->teleportInfo.worldInfo.hTriggerObjectOffset = 100000;
			Teleport.sWorldInfo.sRuleInfo.byRuleType = _player->GetAttributesManager()->teleportInfo.worldInfo.sRuleInfo.byRuleType;

			_player->Relocate(Teleport.vNewLoc.x, Teleport.vNewLoc.y, Teleport.vNewLoc.z, Teleport.vNewDir.x, Teleport.vNewDir.y, Teleport.vNewDir.z);

			_player->SetWorldID(Teleport.sWorldInfo.worldID);
			_player->SetWorldTableID(Teleport.sWorldInfo.tblidx);
			_player->GetState()->sCharStateDetail.sCharStateTeleporting.byTeleportType = _player->GetState()->sCharStateDetail.sCharStateDespawning.byTeleportType;
			_player->SetState(eCHARSTATE::CHARSTATE_TELEPORTING);
			sLog.outDebug("--------TELEPORT TIME QUEST--------");
			sLog.outDebug("Teleport: pos %f %f %f rot %f %f %f worldtblidx %d ruleType %d", _player->GetAttributesManager()->teleportInfo.position.x,
				_player->GetAttributesManager()->teleportInfo.position.y,
				_player->GetAttributesManager()->teleportInfo.position.z,
				_player->GetAttributesManager()->teleportInfo.rotation.x,
				_player->GetAttributesManager()->teleportInfo.rotation.y,
				_player->GetAttributesManager()->teleportInfo.rotation.z,
				_player->GetAttributesManager()->teleportInfo.worldInfo.tblidx,
				_player->GetAttributesManager()->teleportInfo.worldInfo.sRuleInfo.byRuleType);
			/*	   NOT SURE IF THIS IS A GOOD IDEA FOR NOW		*/
			Map* map = _player->GetMap();
			map->Remove(_player, false);
			_player->ClearListAndReference();
			break;
		}
	}

	SendPacket((char*)&Teleport, sizeof(sGU_CHAR_TELEPORT_RES));
	memset(&(_player->GetAttributesManager()->teleportInfo), 0, sizeof _player->GetAttributesManager()->teleportInfo);
}