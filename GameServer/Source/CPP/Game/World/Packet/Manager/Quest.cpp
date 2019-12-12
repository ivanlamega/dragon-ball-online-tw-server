#include <Game\World\WorldSession.h>
#include <Packet\Game\PacketGU.h>
#include <Packet\Game\PacketUG.h>
#include <Packet\Community\PacketUT.h>
#include <Packet\Community\PacketTU.h>
#include <Game\Object\Player.h>
#include <Game\Object\Npc.h>
#include <Game\Object\Mob.h>
#include <Game\Object\Object.h>
#include <Game\Maps\MapManager.h>
#include <mysqlconn_wrapper.h>
#include <Logger.h>
#include <World.h>
#include <QuestWrapper.h>
#include <XmlParser2/XmlParser2.h>
#include <TimerJs.h>

ResultCodes	WorldSession::FindPCTriggerInformation(sUG_TS_CONFIRM_STEP_REQ* req)
{
	// example tss
	CNtlTSCont* contBase = sTSM.FindTriggerFromTS(req->tId)->GetGroup(NTL_TS_MAIN_GROUP_ID)->GetChildCont(req->tcCurId);
	if (contBase == NULL)
	{
		return RESULT_FAIL;
	}

	sLog.outError("type: %s %d", contBase->GetClassNameW(), contBase->GetEntityType());
	switch (contBase->GetEntityType())
	{
		case DBO_CONT_TYPE_ID_CONT_START:
		{
			CDboTSContStart* contStart = ((CDboTSContStart*)contBase);
			if (contStart == NULL)
			{
				return RESULT_FAIL;
			}

			for (int i = 0; i < contStart->GetNumOfChildEntity(); i++)
			{
				sLog.outDetail("Cont: %s %d", contStart->GetChildEntity(i)->GetClassNameW(), contStart->GetChildEntity(i)->GetEntityType());
				switch (contStart->GetChildEntity(i)->GetEntityType())
				{
					case DBO_EVENT_TYPE_ID_COL_OBJECT:
					{
						CDboTSColObject* colObject = ((CDboTSColObject*)contStart->GetChildEntity(i));
						if (colObject == NULL)
						{
							return RESULT_FAIL;
						}
						sLog.outDebug("Num objects %d, world %d object (%d) col obj? %d",
							colObject->GetNumOfObjectIdx(), colObject->GetWorldIdx(), req->dwEventData, colObject->HasObjectIdx(req->dwEventData));
						break;
					}
				}
			}
			break;
		}
		case DBO_CONT_TYPE_ID_CONT_GACT:
		{
			CDboTSContGAct* contAct = ((CDboTSContGAct*)contBase);
			if (contAct == NULL)
			{
				return RESULT_FAIL;
			}
			for (int i = 0; i < contAct->GetNumOfChildEntity(); i++)
			{
				sLog.outDetail("Cont: %s %d", contAct->GetChildEntity(i)->GetClassNameW(), contAct->GetChildEntity(i)->GetEntityType());
				switch (contAct->GetChildEntity(i)->GetEntityType())
				{
					case DBO_ACT_TYPE_ID_ACT_PORTAL:
					{
						CDboTSActPortal* actPortal = ((CDboTSActPortal*)contAct->GetChildEntity(i));
						if (actPortal == NULL)
						{
							return RESULT_FAIL;
						}
						switch (actPortal->GetPotalType())
						{
							case ePORTAL_TYPE_GATEWAY:
							{

							}
							case ePORTAL_TYPE_TELEPORT:
							{
								actPortal->GetPosition(_player->GetAttributesManager()->teleportInfo.position.x,
									_player->GetAttributesManager()->teleportInfo.position.y,
									_player->GetAttributesManager()->teleportInfo.position.z);

								actPortal->GetDirection(_player->GetAttributesManager()->teleportInfo.rotation.x,
									_player->GetAttributesManager()->teleportInfo.rotation.y,
									_player->GetAttributesManager()->teleportInfo.rotation.z);

								_player->GetAttributesManager()->teleportInfo.worldInfo.tblidx = actPortal->GetWorldIdx();
								_player->GetAttributesManager()->teleportInfo.worldInfo.worldID = actPortal->GetWorldIdx();

								sLog.outDebug("Teleport: pos %f %f %f rot %f %f %f worldtblidx %d type %d", _player->GetAttributesManager()->teleportInfo.position.x,
									_player->GetAttributesManager()->teleportInfo.position.y,
									_player->GetAttributesManager()->teleportInfo.position.z,
									_player->GetAttributesManager()->teleportInfo.rotation.x,
									_player->GetAttributesManager()->teleportInfo.rotation.y,
									_player->GetAttributesManager()->teleportInfo.rotation.z,
									actPortal->GetWorldIdx(),
									actPortal->GetPotalType());

								sWORLD_TBLDAT* worldTbl = (sWORLD_TBLDAT*)sTBM.GetWorldTable()->FindData(_player->GetAttributesManager()->teleportInfo.worldInfo.tblidx);
								sLog.outDebug("WORLD TBLIDX: %d resourse id: %d", worldTbl->tblidx, worldTbl->dwWorldResourceID);
								_player->GetState()->sCharStateDetail.sCharStateDespawning.byTeleportType = eTELEPORT_TYPE::TELEPORT_TYPE_DEFAULT;
								_player->SetState(eCHARSTATE::CHARSTATE_DESPAWNING);
								break;
							}
						}
						break;
					}
					case DBO_ACT_TYPE_ID_ACT_TWAITTS:
					{
						CDboTSActTWaitTS* waitTs = (CDboTSActTWaitTS*)contAct->GetChildEntity(i);
						if (waitTs == NULL)
						{
							return RESULT_FAIL;
						}
						sLog.outDebug("Wait time %d", waitTs->GetWaitTime());
						break;
					}
					case DBO_ACT_TYPE_ID_ACT_TLQ:
					{
						CDboTSActTLQ* tlq = (CDboTSActTLQ*)contAct->GetChildEntity(i);
						if (tlq == NULL)
						{
							return RESULT_FAIL;
						}
						sLog.outDebug("Dungeon tblidx %d type %d", tlq->GetDungeonTblIdx(), tlq->GetDungeonType());
						switch (tlq->GetDungeonType())
						{
							case eTLQ_DUNGEON_TYPE_ENTER:
							{
								if (tlq->GetDungeonTblIdx() != INVALID_TBLIDX)
								{
									sDUNGEON_TBLDAT* dungeonData = (sDUNGEON_TBLDAT*)sTBM.GetDungeonTable()->FindData(tlq->GetDungeonTblIdx());
									if (dungeonData == NULL)
									{
										return RESULT_FAIL;
									}

									sWORLD_TBLDAT* worldData = (sWORLD_TBLDAT*)sTBM.GetWorldTable()->FindData(dungeonData->linkWorld);

									if (worldData == NULL)
									{
										return RESULT_FAIL;
									}

									_player->GetAttributesManager()->teleportInfo.outWorld.position.x = worldData->outWorldLoc.x;
									_player->GetAttributesManager()->teleportInfo.outWorld.position.y = worldData->outWorldLoc.y;
									_player->GetAttributesManager()->teleportInfo.outWorld.position.z = worldData->outWorldLoc.z;

									_player->GetAttributesManager()->teleportInfo.outWorld.rotation.x = worldData->outWorldDir.x;
									_player->GetAttributesManager()->teleportInfo.outWorld.rotation.y = worldData->outWorldDir.y;
									_player->GetAttributesManager()->teleportInfo.outWorld.rotation.z = worldData->outWorldDir.z;
									_player->GetAttributesManager()->teleportInfo.outWorld.worldTblidx = worldData->outWorldTblidx;

									sLog.outDebug("OUT WORLD %d (%f %f %f)", 
										_player->GetAttributesManager()->teleportInfo.outWorld.worldTblidx, 
										_player->GetAttributesManager()->teleportInfo.outWorld.position.x, 
										_player->GetAttributesManager()->teleportInfo.outWorld.position.y, 
										_player->GetAttributesManager()->teleportInfo.outWorld.position.z);


									_player->GetAttributesManager()->teleportInfo.position.x = worldData->vStart1Loc.x;
									_player->GetAttributesManager()->teleportInfo.position.y = worldData->vStart1Loc.y;
									_player->GetAttributesManager()->teleportInfo.position.z = worldData->vStart1Loc.z;

									_player->GetAttributesManager()->teleportInfo.rotation.x = worldData->vStart1Dir.x;
									_player->GetAttributesManager()->teleportInfo.rotation.y = worldData->vStart1Dir.y;
									_player->GetAttributesManager()->teleportInfo.rotation.z = worldData->vStart1Dir.z;

									_player->GetAttributesManager()->teleportInfo.bIsToMoveAnotherServer = false;
									_player->GetAttributesManager()->teleportInfo.worldInfo.worldID = worldData->tblidx;
									_player->GetAttributesManager()->teleportInfo.worldInfo.tblidx = worldData->tblidx;
									_player->GetAttributesManager()->teleportInfo.worldInfo.hTriggerObjectOffset = 100000;
									_player->GetAttributesManager()->teleportInfo.worldInfo.sRuleInfo.byRuleType = worldData->byWorldRuleType;

									sLog.outDebug("Teleport: pos %f %f %f rot %f %f %f worldtblidx %d type %d ruleType %d", _player->GetAttributesManager()->teleportInfo.position.x,
										_player->GetAttributesManager()->teleportInfo.position.y,
										_player->GetAttributesManager()->teleportInfo.position.z,
										_player->GetAttributesManager()->teleportInfo.rotation.x,
										_player->GetAttributesManager()->teleportInfo.rotation.y,
										_player->GetAttributesManager()->teleportInfo.rotation.z,
										worldData->tblidx,
										dungeonData->byDungeonType,
										worldData->byWorldRuleType);
									SendUpdateCharCondition(80);
									_player->GetState()->sCharStateDetail.sCharStateDespawning.byTeleportType = eTELEPORT_TYPE::TELEPORT_TYPE_TIMEQUEST;
									_player->SetState(eCHARSTATE::CHARSTATE_DESPAWNING);
								}
								else
								{
									return RESULT_FAIL;
								}
								break;
							}
							case eTLQ_DUNGEON_TYPE_LEAVE:
							{
								sLog.outDebug("World %d", _player->GetAttributesManager()->teleportInfo.outWorld.worldTblidx);
								if (_player->GetAttributesManager()->teleportInfo.outWorld.worldTblidx != 0 &&
									_player->GetAttributesManager()->teleportInfo.outWorld.worldTblidx != INVALID_TBLIDX)
								{
									_player->GetAttributesManager()->teleportInfo.position.x = _player->GetAttributesManager()->teleportInfo.outWorld.position.x;
									_player->GetAttributesManager()->teleportInfo.position.y = _player->GetAttributesManager()->teleportInfo.outWorld.position.y;
									_player->GetAttributesManager()->teleportInfo.position.z = _player->GetAttributesManager()->teleportInfo.outWorld.position.z;

									_player->GetAttributesManager()->teleportInfo.rotation.x = _player->GetAttributesManager()->teleportInfo.outWorld.rotation.x;
									_player->GetAttributesManager()->teleportInfo.rotation.y = _player->GetAttributesManager()->teleportInfo.outWorld.rotation.y;
									_player->GetAttributesManager()->teleportInfo.rotation.z = _player->GetAttributesManager()->teleportInfo.outWorld.rotation.z;

									_player->GetAttributesManager()->teleportInfo.bIsToMoveAnotherServer = false;
									_player->GetAttributesManager()->teleportInfo.worldInfo.worldID = _player->GetAttributesManager()->teleportInfo.outWorld.worldTblidx;
									_player->GetAttributesManager()->teleportInfo.worldInfo.tblidx = _player->GetAttributesManager()->teleportInfo.outWorld.worldTblidx;
									_player->GetAttributesManager()->teleportInfo.worldInfo.hTriggerObjectOffset = 100000;
									_player->GetAttributesManager()->teleportInfo.worldInfo.sRuleInfo.byRuleType = 0;

									memset(&_player->GetAttributesManager()->teleportInfo.outWorld, 0, sizeof _player->GetAttributesManager()->teleportInfo.outWorld);

									sLog.outDebug("Teleport: pos %f %f %f rot %f %f %f worldtblidx %d type %d ruleType %d", _player->GetAttributesManager()->teleportInfo.position.x,
										_player->GetAttributesManager()->teleportInfo.position.y,
										_player->GetAttributesManager()->teleportInfo.position.z,
										_player->GetAttributesManager()->teleportInfo.rotation.x,
										_player->GetAttributesManager()->teleportInfo.rotation.y,
										_player->GetAttributesManager()->teleportInfo.rotation.z,
										_player->GetAttributesManager()->teleportInfo.worldInfo.tblidx,
										0,
										_player->GetAttributesManager()->teleportInfo.worldInfo.sRuleInfo.byRuleType);
									SendUpdateCharCondition(80);
									_player->GetState()->sCharStateDetail.sCharStateDespawning.byTeleportType = eTELEPORT_TYPE::TELEPORT_TYPE_TIMEQUEST;
									_player->SetState(eCHARSTATE::CHARSTATE_DESPAWNING);
								}
								else
								{
									return RESULT_FAIL;
								}
								break;
							}
						}
						break;
					}
				}
			}
			break;
		}
		case DBO_CONT_TYPE_ID_CONT_GCOND:
		{
			CDboTSContGCond* contGCond = ((CDboTSContGCond*)contBase);
			if (contGCond == NULL)
			{
				return RESULT_FAIL;
			}
			for (int i = 0; i < contGCond->GetNumOfChildEntity(); i++)
			{
				sLog.outDetail("Cont: %s %d", contGCond->GetChildEntity(i)->GetClassNameW(), contGCond->GetChildEntity(i)->GetEntityType());
				switch (contGCond->GetChildEntity(i)->GetEntityType())
				{
					case DBO_COND_TYPE_ID_CHECK_PROG_QUEST:
					{
						CDboTSCheckProgQuest* progQuest = (CDboTSCheckProgQuest*)contGCond->GetChildEntity(i);
						if (progQuest == NULL)
						{
							return RESULT_FAIL;
						}
						sLog.outDebug("QuestId %d", progQuest->GetQuestID());
						break;
					}
				}
			}
			break;
		}
		case DBO_CONT_TYPE_ID_CONT_END:
		{
			CDboTSContEnd* end = (CDboTSContEnd*)contBase;
			if (end == NULL)
			{
				return RESULT_FAIL;
			}
			break;
		}
	}
}

void WorldSession::GetQuestPortalInfo(DWORD QuestID, DWORD tcCurId, DWORD tcNextId)
{
	/*if (QuestID == 1 && tcCurId == 254)
	{
		sGU_CHAR_TELEPORT_RES teleport;

		sWORLD_TBLDAT *world = (sWORLD_TBLDAT*)sTBM.GetWorldTable()->FindData(2);
		teleport.wResultCode = GAME_SUCCESS;
		teleport.wOpCode = GU_CHAR_TELEPORT_RES;
		teleport.wPacketSize = sizeof(sGU_CHAR_TELEPORT_RES) - 2;

		if (world != NULL)
		{
			if (world->tblidx != _player->GetWorldID())
			{
				teleport.bIsToMoveAnotherServer = true;
				teleport.sWorldInfo.worldID = world->tblidx;
				teleport.sWorldInfo.tblidx = world->tblidx;
				teleport.sWorldInfo.sRuleInfo.byRuleType = world->byWorldRuleType;
				_player->GetState()->sCharStateDetail.sCharStateTeleporting.byTeleportType = eTELEPORT_TYPE::TELEPORT_TYPE_WORLD_MOVE;
			}
			else
			{
				teleport.bIsToMoveAnotherServer = false;

			}
			teleport.vNewLoc.x = 914;
			teleport.vNewLoc.y = -106;
			teleport.vNewLoc.z = -1104;
			teleport.vNewDir.x = -49;
			teleport.vNewDir.y = -0.78;
			teleport.vNewDir.z = 0.39;


			_player->SetState(eCHARSTATE::CHARSTATE_TELEPORTING);


			_player->SetWorldID(world->tblidx);
			_player->SetWorldTableID(world->tblidx);
			_player->Relocate(teleport.vNewLoc.x, teleport.vNewLoc.y, teleport.vNewLoc.z, teleport.vNewDir.x, teleport.vNewDir.y, teleport.vNewDir.z);

			SendPacket((char*)&teleport, sizeof(sGU_CHAR_TELEPORT_RES));
			Map* map = _player->GetMap();
			map->Remove(_player, false);
			_player->ClearListAndReference();
		}
	}

	if (QuestID == 2 && tcCurId == 254)
	{
		sGU_CHAR_TELEPORT_RES teleport;

		sWORLD_TBLDAT *world = (sWORLD_TBLDAT*)sTBM.GetWorldTable()->FindData(1);
		teleport.wResultCode = GAME_SUCCESS;
		teleport.wOpCode = GU_CHAR_TELEPORT_RES;
		teleport.wPacketSize = sizeof(sGU_CHAR_TELEPORT_RES) - 2;

		if (world != NULL)
		{
			if (world->tblidx != _player->GetWorldID())
			{
				teleport.bIsToMoveAnotherServer = true;
				teleport.sWorldInfo.worldID = world->tblidx;
				teleport.sWorldInfo.tblidx = world->tblidx;
				teleport.sWorldInfo.sRuleInfo.byRuleType = world->byWorldRuleType;
				_player->GetState()->sCharStateDetail.sCharStateTeleporting.byTeleportType = eTELEPORT_TYPE::TELEPORT_TYPE_WORLD_MOVE;
			}
			else
			{
				teleport.bIsToMoveAnotherServer = false;

			}
			teleport.vNewLoc.x = 4231;
			teleport.vNewLoc.y = -34;
			teleport.vNewLoc.z = 4737;
			teleport.vNewDir.x = 0.59;
			teleport.vNewDir.y = -0.52;
			teleport.vNewDir.z = -0.62;


			_player->SetState(eCHARSTATE::CHARSTATE_TELEPORTING);


			_player->SetWorldID(world->tblidx);
			_player->SetWorldTableID(world->tblidx);
			_player->Relocate(teleport.vNewLoc.x, teleport.vNewLoc.y, teleport.vNewLoc.z, teleport.vNewDir.x, teleport.vNewDir.y, teleport.vNewDir.z);

			SendPacket((char*)&teleport, sizeof(sGU_CHAR_TELEPORT_RES));
			Map* map = _player->GetMap();
			map->Remove(_player, false);
			_player->ClearListAndReference();
		}
	}
	if (QuestID == 6000 && tcCurId == 254)
	{
		sGU_CHAR_TELEPORT_RES teleport;

		sWORLD_TBLDAT *world = (sWORLD_TBLDAT*)sTBM.GetWorldTable()->FindData(120000);
		teleport.wResultCode = GAME_SUCCESS;
		teleport.wOpCode = GU_CHAR_TELEPORT_RES;
		teleport.wPacketSize = sizeof(sGU_CHAR_TELEPORT_RES) - 2;

		if (world != NULL)
		{
			if (world->tblidx != _player->GetWorldID())
			{
				teleport.bIsToMoveAnotherServer = false;
				teleport.unk = 0;
				teleport.sWorldInfo.worldID = world->tblidx;
				teleport.sWorldInfo.tblidx = world->tblidx;
				teleport.sWorldInfo.sRuleInfo.byRuleType = world->byWorldRuleType;
				_player->GetState()->sCharStateDetail.sCharStateTeleporting.byTeleportType = eTELEPORT_TYPE::TELEPORT_TYPE_WORLD_MOVE;
			}
			else
			{
				teleport.bIsToMoveAnotherServer = false;

			}
			teleport.vNewDir.x = world->vStart1Dir.x;
			teleport.vNewDir.y = world->vStart1Dir.y;
			teleport.vNewDir.z = world->vStart1Dir.z;
			teleport.vNewLoc.x = world->vStart1Loc.x;
			teleport.vNewLoc.y = world->vStart1Loc.y;
			teleport.vNewLoc.z = world->vStart1Loc.z;


			_player->SetState(eCHARSTATE::CHARSTATE_TELEPORTING);


			_player->SetWorldID(world->tblidx);
			_player->SetWorldTableID(world->tblidx);
			_player->Relocate(teleport.vNewLoc.x, teleport.vNewLoc.y, teleport.vNewLoc.z, teleport.vNewDir.x, teleport.vNewDir.y, teleport.vNewDir.z);

			SendPacket((char*)&teleport, sizeof(sGU_CHAR_TELEPORT_RES));
			Map* map = _player->GetMap();
			map->Remove(_player, false);
			_player->ClearListAndReference();

		}
	}
	if (QuestID == 6002 && tcCurId == 254)
	{
		sGU_CHAR_TELEPORT_RES teleport;

		sWORLD_TBLDAT *world = (sWORLD_TBLDAT*)sTBM.GetWorldTable()->FindData(120000);
		teleport.wResultCode = GAME_SUCCESS;
		teleport.wOpCode = GU_CHAR_TELEPORT_RES;
		teleport.wPacketSize = sizeof(sGU_CHAR_TELEPORT_RES) - 2;

		if (world != NULL)
		{
			if (world->outWorldTblidx != _player->GetWorldID())
			{
				teleport.bIsToMoveAnotherServer = true;
				teleport.sWorldInfo.worldID = world->outWorldTblidx;
				teleport.sWorldInfo.tblidx = world->outWorldTblidx;
				teleport.sWorldInfo.sRuleInfo.byRuleType = world->byWorldRuleType;
				_player->GetState()->sCharStateDetail.sCharStateTeleporting.byTeleportType = eTELEPORT_TYPE::TELEPORT_TYPE_WORLD_MOVE;
			}
			else
			{
				teleport.bIsToMoveAnotherServer = false;

			}
			teleport.vNewDir.x = world->outWorldDir.x;
			teleport.vNewDir.y = world->outWorldDir.y;
			teleport.vNewDir.z = world->outWorldDir.z;
			teleport.vNewLoc.x = world->outWorldLoc.x;
			teleport.vNewLoc.y = world->outWorldLoc.y;
			teleport.vNewLoc.z = world->outWorldLoc.z;


			_player->SetState(eCHARSTATE::CHARSTATE_TELEPORTING);


			_player->SetWorldID(world->outWorldTblidx);
			_player->SetWorldTableID(world->outWorldTblidx);
			_player->Relocate(teleport.vNewLoc.x, teleport.vNewLoc.y, teleport.vNewLoc.z, teleport.vNewDir.x, teleport.vNewDir.y, teleport.vNewDir.z);

			SendPacket((char*)&teleport, sizeof(sGU_CHAR_TELEPORT_RES));
			Map* map = _player->GetMap();
			map->Remove(_player, false);
			_player->ClearListAndReference();
		}
	}
	//SkyDangeon
	if (QuestID == 4547 && tcCurId == 254)
	{
		sGU_CHAR_TELEPORT_RES teleport;

		sWORLD_TBLDAT *world = (sWORLD_TBLDAT*)sTBM.GetWorldTable()->FindData(510000);
		teleport.wResultCode = GAME_SUCCESS;
		teleport.wOpCode = GU_CHAR_TELEPORT_RES;
		teleport.wPacketSize = sizeof(sGU_CHAR_TELEPORT_RES) - 2;

		if (world != NULL)
		{
			if (world->tblidx != _player->GetWorldID())
			{
				teleport.bIsToMoveAnotherServer = true;
				teleport.sWorldInfo.worldID = world->tblidx;
				teleport.sWorldInfo.tblidx = world->tblidx;
				teleport.sWorldInfo.sRuleInfo.byRuleType = world->byWorldRuleType;
				_player->GetState()->sCharStateDetail.sCharStateTeleporting.byTeleportType = eTELEPORT_TYPE::TELEPORT_TYPE_WORLD_MOVE;
			}
			else
			{
				teleport.bIsToMoveAnotherServer = false;

			}
			teleport.vNewDir.x = world->vStart1Dir.x;
			teleport.vNewDir.y = world->vStart1Dir.y;
			teleport.vNewDir.z = world->vStart1Dir.z;
			teleport.vNewLoc.x = world->vStart1Loc.x;
			teleport.vNewLoc.y = world->vStart1Loc.y;
			teleport.vNewLoc.z = world->vStart1Loc.z;


			_player->SetState(eCHARSTATE::CHARSTATE_TELEPORTING);


			_player->SetWorldID(world->tblidx);
			_player->SetWorldTableID(world->tblidx);
			_player->Relocate(teleport.vNewLoc.x, teleport.vNewLoc.y, teleport.vNewLoc.z, teleport.vNewDir.x, teleport.vNewDir.y, teleport.vNewDir.z);

			SendPacket((char*)&teleport, sizeof(sGU_CHAR_TELEPORT_RES));
			Map* map = _player->GetMap();
			map->Remove(_player, false);
			_player->ClearListAndReference();
		}
	}
	if (QuestID == 4548 && tcCurId == 254)
	{
		sGU_CHAR_TELEPORT_RES teleport;

		sWORLD_TBLDAT *world = (sWORLD_TBLDAT*)sTBM.GetWorldTable()->FindData(500000);
		teleport.wResultCode = GAME_SUCCESS;
		teleport.wOpCode = GU_CHAR_TELEPORT_RES;
		teleport.wPacketSize = sizeof(sGU_CHAR_TELEPORT_RES) - 2;

		if (world != NULL)
		{
			if (world->tblidx != _player->GetWorldID())
			{
				teleport.bIsToMoveAnotherServer = true;
				teleport.sWorldInfo.worldID = world->tblidx;
				teleport.sWorldInfo.tblidx = world->tblidx;
				teleport.sWorldInfo.sRuleInfo.byRuleType = world->byWorldRuleType;
				_player->GetState()->sCharStateDetail.sCharStateTeleporting.byTeleportType = eTELEPORT_TYPE::TELEPORT_TYPE_WORLD_MOVE;
			}
			else
			{
				teleport.bIsToMoveAnotherServer = false;

			}
			teleport.vNewDir.x = world->vStart1Dir.x;
			teleport.vNewDir.y = world->vStart1Dir.y;
			teleport.vNewDir.z = world->vStart1Dir.z;
			teleport.vNewLoc.x = world->vStart1Loc.x;
			teleport.vNewLoc.y = world->vStart1Loc.y;
			teleport.vNewLoc.z = world->vStart1Loc.z;


			_player->SetState(eCHARSTATE::CHARSTATE_TELEPORTING);


			_player->SetWorldID(world->tblidx);
			_player->SetWorldTableID(world->tblidx);
			_player->Relocate(teleport.vNewLoc.x, teleport.vNewLoc.y, teleport.vNewLoc.z, teleport.vNewDir.x, teleport.vNewDir.y, teleport.vNewDir.z);

			SendPacket((char*)&teleport, sizeof(sGU_CHAR_TELEPORT_RES));
			Map* map = _player->GetMap();
			map->Remove(_player, false);
			_player->ClearListAndReference();
		}
	}*/
}
void WorldSession::GetQuestInfo(DWORD QuestID, DWORD tcCurId, DWORD tcNextId)
{
	/*int freeslot = 0;
	if (QuestID == 2 || QuestID == 1924)
	{
		for (int i = 0; i <= 30; i++)
		{			
			if (_player->GetAttributesManager()->QuestDat[i].QuestID == 0 || _player->GetAttributesManager()->QuestDat[i].QuestID == INVALID_TBLIDX)
			{
					freeslot = i;
			}				
		}	
		_player->GetAttributesManager()->QuestDat[freeslot].QuestID = QuestID;
		_player->GetAttributesManager()->QuestDat[freeslot].MobID = 4911101;
		_player->GetAttributesManager()->QuestDat[freeslot].count = 0;
		_player->GetAttributesManager()->QuestDat[freeslot].Maxcount = 3;
	}	*/
	if (QuestID == 3 || QuestID == 1925)
	{			
		/*sGU_CHAR_TELEPORT_RES Teleport;
		memset(&Teleport, 0, sizeof(sGU_CHAR_TELEPORT_RES));
		Teleport.wOpCode = GU_CHAR_TELEPORT_RES;
		Teleport.wPacketSize = sizeof(sGU_CHAR_TELEPORT_RES) - 2;
		Teleport.wResultCode = GAME_SUCCESS;
		Teleport.vNewLoc.x = 4474.109863;
		Teleport.vNewLoc.y = -42.000000;
		Teleport.vNewLoc.z = 3958.379883;
		Teleport.vNewDir.x = -0.751000;
		Teleport.vNewDir.y = 0;
		Teleport.vNewDir.z = -0.661000;
		Teleport.unk = INVALID_TBLIDX;
		Teleport.bIsToMoveAnotherServer = false;

		_player->Relocate(Teleport.vNewLoc.x, Teleport.vNewLoc.y, Teleport.vNewLoc.z, Teleport.vNewDir.x, Teleport.vNewDir.y, Teleport.vNewDir.z);
		_player->SetWorldID(1);
		_player->SetWorldTableID(1);
		_player->GetState()->sCharStateDetail.sCharStateTeleporting.byTeleportType = eTELEPORT_TYPE::TELEPORT_TYPE_NPC_PORTAL;
		_player->SetState(eCHARSTATE::CHARSTATE_TELEPORTING);
		SendPacket((char*)&Teleport, sizeof(sGU_CHAR_TELEPORT_RES));	*/		
	}
	/*if (QuestID == 4)
	{
		for (int i = 0; i <= 30; i++)
		{
			if (_player->GetAttributesManager()->QuestDat[i].QuestID == 0 || _player->GetAttributesManager()->QuestDat[i].QuestID == INVALID_TBLIDX)
			{
				freeslot = i;
			}
		}
		_player->GetAttributesManager()->QuestDat[freeslot].QuestID = QuestID;
		_player->GetAttributesManager()->QuestDat[freeslot].MobID = 1411101;
		_player->GetAttributesManager()->QuestDat[freeslot].count = 0;
		_player->GetAttributesManager()->QuestDat[freeslot].Maxcount = 4;
	}
	if (QuestID == 13)
	{
		for (int i = 0; i <= 30; i++)
		{
			if (_player->GetAttributesManager()->QuestDat[i].QuestID == 0 || _player->GetAttributesManager()->QuestDat[i].QuestID == INVALID_TBLIDX)
			{
				freeslot = i;
			}
		}
		_player->GetAttributesManager()->QuestDat[freeslot].QuestID = QuestID;
		_player->GetAttributesManager()->QuestDat[freeslot].MobID = 4912101;
		_player->GetAttributesManager()->QuestDat[freeslot].count = 0;
		_player->GetAttributesManager()->QuestDat[freeslot].Maxcount = 5;
	}
	if (QuestID == 19)
	{
		for (int i = 0; i <= 30; i++)
		{
			if (_player->GetAttributesManager()->QuestDat[i].QuestID == 0 || _player->GetAttributesManager()->QuestDat[i].QuestID == INVALID_TBLIDX)
			{
				freeslot = i;
			}
		}
		_player->GetAttributesManager()->QuestDat[freeslot].QuestID = QuestID;
		_player->GetAttributesManager()->QuestDat[freeslot].MobID = 4911104;
		_player->GetAttributesManager()->QuestDat[freeslot].count = 0;
		_player->GetAttributesManager()->QuestDat[freeslot].Maxcount = 6;
	}
	if (QuestID == 32)
	{
		for (int i = 0; i <= 30; i++)
		{
			if (_player->GetAttributesManager()->QuestDat[i].QuestID == 0 || _player->GetAttributesManager()->QuestDat[i].QuestID == INVALID_TBLIDX)
			{
				freeslot = i;
			}
		}
		_player->GetAttributesManager()->QuestDat[freeslot].QuestID = QuestID;
		_player->GetAttributesManager()->QuestDat[freeslot].MobID = 2131102;
		_player->GetAttributesManager()->QuestDat[freeslot].count = 0;
		_player->GetAttributesManager()->QuestDat[freeslot].Maxcount = 3;
	}
	if (QuestID == 190)
	{
		for (int i = 0; i <= 30; i++)
		{
			if (_player->GetAttributesManager()->QuestDat[i].QuestID == 0 || _player->GetAttributesManager()->QuestDat[i].QuestID == INVALID_TBLIDX)
			{
				freeslot = i;
			}
		}
		_player->GetAttributesManager()->QuestDat[freeslot].QuestID = QuestID;
		_player->GetAttributesManager()->QuestDat[freeslot].MobID = 4912113;
		_player->GetAttributesManager()->QuestDat[freeslot].count = 0;
		_player->GetAttributesManager()->QuestDat[freeslot].Maxcount = 2;
	}
	if (QuestID == 11600)
	{
		for (int i = 0; i <= 30; i++)
		{
			if (_player->GetAttributesManager()->QuestDat[i].QuestID == 0 || _player->GetAttributesManager()->QuestDat[i].QuestID == INVALID_TBLIDX)
			{
				freeslot = i;
			}
		}
		_player->GetAttributesManager()->QuestDat[freeslot].QuestID = QuestID;
		_player->GetAttributesManager()->QuestDat[freeslot].MobID = 4912113;
		_player->GetAttributesManager()->QuestDat[freeslot].count = 0;
		_player->GetAttributesManager()->QuestDat[freeslot].Maxcount = 2;
	}
	if (QuestID == 6861)
	{
		for (int i = 0; i <= 30; i++)
		{
			if (_player->GetAttributesManager()->QuestDat[i].QuestID == 0 || _player->GetAttributesManager()->QuestDat[i].QuestID == INVALID_TBLIDX)
			{
				freeslot = i;
			}
		}
		_player->GetAttributesManager()->QuestDat[freeslot].QuestID = QuestID;
		_player->GetAttributesManager()->QuestDat[freeslot].MobID = 11253101;
		_player->GetAttributesManager()->QuestDat[freeslot].count = 0;
		_player->GetAttributesManager()->QuestDat[freeslot].Maxcount = 30;
	}*/

}
void WorldSession::SendQuestAcept(Packet& packet)
{
	sUG_TS_CONFIRM_STEP_REQ *req = (sUG_TS_CONFIRM_STEP_REQ*)packet.GetPacketBuffer();
	sGU_TS_CONFIRM_STEP_RES res;

	if (req)
	{


		QuestRewardTable * dat = sTBM.GetQuestRewardTable();
		sLog.outDebug("Event type: %u, TS Type: %u, DWData %d, DWParam: %d, tid: %u, CurID: %u, NextID: %u", req->byEventType, req->byTsType, req->dwEventData, req->dwParam, req->tId, req->tcCurId, req->tcNextId);
		res.byTsType = req->byTsType;
		res.dwParam = req->dwParam;
		res.tcCurId = req->tcCurId;
		res.tcNextId = req->tcNextId;
		res.tId = req->tId;
		res.wOpCode = GU_TS_CONFIRM_STEP_RES;
		res.wPacketSize = sizeof(sGU_TS_CONFIRM_STEP_RES) - 2;
		res.wResultCode = RESULT_SUCCESS;

		if (req->byTsType == TS_TYPE_QUEST_CS)
		{		
			sLog.outDebug("TS_TYPE_QUEST_CS");
			int result = FindQuestInformation(req);

			if (req->tcCurId == 2)
			{
				/*sGU_QUEST_SVREVT_START_NFY start;
				start.wOpCode = GU_QUEST_SVREVT_START_NFY;
				start.wPacketSize = sizeof(sGU_QUEST_SVREVT_START_NFY) - 2;
				start.tId = req->tId;
				start.tcId = req->tcCurId;
				start.taId = req->tcNextId;				
				SendPacket((char*)&start, sizeof(sGU_QUEST_SVREVT_START_NFY));*/
				//SendQuestSVRevtStartNotify(req->tId, req->tcCurId, req->tcNextId);
				GetQuestInfo(req->tId, req->tcCurId, req->tcNextId);
			}

			/////////////////////////////////////////////////////////

		}
		if (req->byTsType == TS_TYPE_PC_TRIGGER_CS)
		{
			sLog.outDebug("TS_TYPE_PC_TRIGGER_CS");
			FindPCTriggerInformation(req);
			if (req->tcCurId == 254)
			{
				GetQuestPortalInfo(req->tId, req->tcCurId, req->tcNextId);
				
			}
		}

		if (req->byTsType == TS_TYPE_OBJECT_TRIGGER_S)
		{
			
		}

		//Need Find Logic to Complete Quest for Correct ID
		//Need Load Reward Tables etc....
		// Stop Quest At Correct Step
		
		
		int RWquestID = req->tId * 100;	
		RWquestID += 1;
		if (req->tcCurId == 100)//Reward
		{
			for (int i = 0; i <= 30; i++)
			{
				if (_player->GetAttributesManager()->QuestDat[i].QuestID == req->tId)
				{
					//sLog.outDebug("Remove Quest Finnish");
					_player->GetAttributesManager()->QuestDat[i].QuestID == INVALID_TBLIDX;

					for (int j = 0; j < _player->GetAttributesManager()->QuestDat[i].uEvtData.MAX_MOB_KILL; j++)
					{
						_player->GetAttributesManager()->QuestDat[i].uEvtData.sMobKillCnt[j].uiMobIdx == INVALID_TBLIDX;
						_player->GetAttributesManager()->QuestDat[i].uEvtData.sMobKillCnt[j].nCurMobCnt == INVALID_TBLIDX;
						_player->GetAttributesManager()->QuestDat[i].uEvtData.sMobKillCnt[j].nMobCnt == INVALID_TBLIDX;
					}
					
				}

			}
			//sLog.outDebug("RWquestID %d", RWquestID);
			/*sQUEST_REWARD_TBLDAT * tbldat = reinterpret_cast<sQUEST_REWARD_TBLDAT*>(dat->FindData(RWquestID));
			if (tbldat != NULL)
			{							
				if (_player->GetPcProfile()->byLevel < 70)
				{
					DWORD exp = tbldat->EXP;
					DWORD bonus = 0;*/

					/*sGU_UPDATE_CHAR_EXP expPacket;				
					

					expPacket.dwIncreasedExp = exp + bonus;
					expPacket.dwAcquisitionExp = exp;
					expPacket.dwBonusExp = bonus;
					expPacket.wOpCode = GU_UPDATE_CHAR_EXP;
					expPacket.wPacketSize = sizeof(sGU_UPDATE_CHAR_EXP) - 2;
					expPacket.handle = _player->GetHandle();
					_player->GetPcProfile()->dwCurExp += (exp + bonus);
					expPacket.dwCurExp = _player->GetPcProfile()->dwCurExp;*/

					/*_player->UpdateZennyAmount(tbldat->Zenny, eZENNY_CHANGE_TYPE::ZENNY_CHANGE_TYPE_DB_REWARD);
					_player->UpdateExperienceAmount(exp, bonus);
					/*if (_player->GetPcProfile()->dwCurExp >= _player->GetPcProfile()->dwMaxExpInThisLevel)
					{
						expPacket.dwCurExp = _player->GetPcProfile()->dwCurExp -= _player->GetPcProfile()->dwMaxExpInThisLevel;
						_player->LevelUp();
					}					

					SendPacket((char*)&expPacket, sizeof(sGU_UPDATE_CHAR_EXP));*/
				/*}
			}*/
		}
		SendPacket((char*)&res, sizeof(sGU_TS_CONFIRM_STEP_RES));
	}
}

ResultCodes WorldSession::ProcessTSContStart(CDboTSContStart * contStart)
{
	for (int i = 0; i < contStart->GetNumOfChildEntity(); i++)
	{
		sLog.outDetail("Cont: %s %d", contStart->GetChildEntity(i)->GetClassNameW(), contStart->GetChildEntity(i)->GetEntityType());
		switch (contStart->GetChildEntity(i)->GetEntityType())
		{
			case DBO_COND_TYPE_ID_CHECK_LVL:
			{
				CDboTSCheckLvl * checkLvl = ((CDboTSCheckLvl*)contStart->GetChildEntity(i));
				if (checkLvl == NULL)
				{
					return RESULT_FAIL;
				}
				
				if (_player->GetPcProfile()->byLevel >= checkLvl->GetMinLvl() && _player->GetPcProfile()->byLevel <= checkLvl->GetMaxLvl())
				{
					sLog.outDetail("Quest: minlvl %d maxlvl %d player lvl: %d", checkLvl->GetMinLvl(), checkLvl->GetMaxLvl(), _player->GetPcProfile()->byLevel);
					continue;
				}
				break;
			}
			case DBO_COND_TYPE_ID_CHECK_CLRQST:
			{
				CDboTSCheckClrQst * clrQst = ((CDboTSCheckClrQst*)contStart->GetChildEntity(i));
				if (clrQst == NULL)
				{
					return RESULT_FAIL;
				}
				sLog.outDetail("Quest: not size: %d  and size: %d or size: %d", clrQst->GetNotIdList().size(), clrQst->GetAndIdList().size(), clrQst->GetOrIdList().size());
				break;
			}
			case DBO_EVENT_TYPE_ID_CLICK_NPC:
			{
				CDboTSClickNPC * clickNpc = ((CDboTSClickNPC*)contStart->GetChildEntity(i));
				if (clickNpc == NULL)
				{
					return RESULT_FAIL;
				}
				sLog.outDetail("Quest: Npc tblidx %d", clickNpc->GetNPCIdx());
				break;
			}
			case DBO_COND_TYPE_ID_CHECK_PCRACE:
			{
				CDboTSCheckPCRace * pcRace = ((CDboTSCheckPCRace*)contStart->GetChildEntity(i));
				if (pcRace == NULL)
				{
					return RESULT_FAIL;
				}
				unsigned int uiRace = _player->GetAttributesManager()->PlayerRaceID;
				if (pcRace->GetRaceFlags() & (1 << uiRace))
				{
					sLog.outDetail("Quest: race flag %d uirace: %d player race: %d", pcRace->GetRaceFlags(), 1 << uiRace, uiRace);
					continue;
				}
				break;
			}
			case DBO_COND_TYPE_ID_CHECK_PCCLS:
			{
				CDboTSCheckPCCls * pcClass = ((CDboTSCheckPCCls*)contStart->GetChildEntity(i));
				if (pcClass == NULL)
				{
					return RESULT_FAIL;
				}
				unsigned int uiCls = _player->GetAttributesManager()->PlayerClassID;
				if (pcClass->GetClsFlags() & (1 << uiCls))
				{
					sLog.outDetail("Quest: class flag %d uiclass: %d class player: %d", pcClass->GetClsFlags(), 1 << uiCls, uiCls);
					continue;
				}
				break;
			}
		}
	}
	return RESULT_SUCCESS;
}

ResultCodes WorldSession::ProcessTsContGAct(CDboTSContGAct * contGAct, NTL_TS_T_ID tid, NTL_TS_TC_ID tcId)
{
	for (int i = 0; i < contGAct->GetNumOfChildEntity(); i++)
	{
		sLog.outDetail("Cont: %s %d, %d", contGAct->GetChildEntity(i)->GetClassNameW(), contGAct->GetChildEntity(i)->GetEntityType(), DBO_COND_TYPE_ID_CHECK_LVL);
		switch (contGAct->GetChildEntity(i)->GetEntityType())
		{
			case DBO_ACT_TYPE_ID_ACT_NPCCONV:
			{
				CDboTSActNPCConv * NPCConv = (CDboTSActNPCConv*)contGAct->GetChildEntity(i);
				if (NPCConv == NULL)
				{
					return RESULT_FAIL;
				}
				_player->GetAttributesManager()->lastNPCQuest = NPCConv->GetNPCIdx();
				sLog.outDetail("Quest: npc tblidx %d", NPCConv->GetNPCIdx());
				break;
			}
			case DBO_ACT_TYPE_ID_ACT_REGQINFO:
			{
				CDboTSActRegQInfo * regQInfo = (CDboTSActRegQInfo*)contGAct->GetChildEntity(i);
				if (regQInfo == NULL)
				{
					return RESULT_FAIL;
				}
				sLog.outDetail("Quest: reward %d world tblidx %d tooltip tblidx %d pos: (%f, %f, %f)", regQInfo->GetReward(), regQInfo->GetQuestMarkInfo(0).uiWorldTblIdx,
					regQInfo->GetQuestMarkInfo(0).uiTooltipIdx, regQInfo->GetQuestMarkInfo(0).fX, regQInfo->GetQuestMarkInfo(0).fY, regQInfo->GetQuestMarkInfo(0).fZ);
				break;
			}
			case DBO_ACT_TYPE_ID_ACT_OUTMSG:
			{
				CDboTSActOutMsg * outMsg = (CDboTSActOutMsg*)contGAct->GetChildEntity(i);
				if (outMsg == NULL)
				{
					return RESULT_FAIL;
				}
				sLog.outDetail("Quest: message tblidx %d, action id %d", outMsg->GetMsgIdx(), outMsg->GetActionId());
				break;
			}
			case DBO_ACT_TYPE_ID_ACT_SEND_SVR_EVT:
			{
				CDboTSActSendSvrEvt* sendSvrEvt = (CDboTSActSendSvrEvt*)contGAct->GetChildEntity(i);
				if (sendSvrEvt)
				{
					sLog.outDebug("Quest: evtSendType %d radius %d evtType %d evtId %d trigger type %d tblidx %d", 
						sendSvrEvt->GetEvtSendType(), sendSvrEvt->GetEvtSendType_Radius(), sendSvrEvt->GetSvrEvtType(), 
						sendSvrEvt->GetSvrEvtID(), sendSvrEvt->GetSvrEvtTriggerType(), sendSvrEvt->GetTblIdx());

					sGU_TS_UPDATE_EVENT_NFY nfy;
					nfy.wOpCode = GU_TS_UPDATE_EVENT_NFY;
					nfy.wPacketSize = sizeof(sGU_TS_UPDATE_EVENT_NFY) - 2;
					nfy.byTsType = 0;
					nfy.teid = sendSvrEvt->GetSvrEvtID();
					SendPacket((char*)&nfy, sizeof(sGU_TS_UPDATE_EVENT_NFY));
				}
				break;
			}
			case DBO_ACT_TYPE_ID_ACT_STOCEVT:
			{
				CDboTSActSToCEvt* sToCEvt = (CDboTSActSToCEvt*)contGAct->GetChildEntity(i);
				if (sToCEvt == NULL)
				{
					return RESULT_FAIL;
				}
				sLog.outDetail("Quest %d", sToCEvt->GetEvtDataType());

				switch (sToCEvt->GetEvtType())
				{
					case eSTOC_EVT_TYPE::eSTOC_EVT_TYPE_START:
					{
						SendQuestSVRevtStartNotify(tid, tcId, sToCEvt->GetActionId());//req->tcNextId);
						sLog.outDebug("--------START QUEST--------");
						break;
					}
					case eSTOC_EVT_TYPE::eSTOC_EVT_TYPE_END:
					{
						SendQuestSVRevtEndNotify(tid, tcId, sToCEvt->GetActionId());
						sLog.outDebug("--------END QUEST--------");
						break;
					}
				}

				switch (sToCEvt->GetEvtCondDataType())
				{
					case eSTOC_EVT_COND_DATA_TYPE::eSTOC_EVT_COND_DATA_TYPE_AUTO_EQUIP_ITEM:
					{
						break;
					}
					case eSTOC_EVT_COND_DATA_TYPE::eSTOC_EVT_COND_DATA_TYPE_EQUIP_ITEM:
					{
						break;
					}
					case eSTOC_EVT_COND_DATA_TYPE::eSTOC_EVT_COND_DATA_TYPE_HAVE_ITEM:
					{
						break;
					}
					case eSTOC_EVT_COND_DATA_TYPE::eSTOC_EVT_COND_DATA_TYPE_HAVE_QITEM:
					{
						break;
					}
				}
				

				if (CheckEvtDataType(sToCEvt, tcId) == RESULT_FAIL)
				{
					return RESULT_FAIL;
				}
				break;
			}
			case DBO_ACT_TYPE_ID_ACT_PORTAL:
			{
				CDboTSActPortal* sPortal = (CDboTSActPortal*)contGAct->GetChildEntity(i);
				if (sPortal == NULL)
				{
					return RESULT_FAIL;
				}

				if (ePORTAL_TYPE_TELEPORT == sPortal->GetPotalType())
				{
					sPortal->GetPosition(_player->GetAttributesManager()->teleportInfo.position.x,
						_player->GetAttributesManager()->teleportInfo.position.y,
						_player->GetAttributesManager()->teleportInfo.position.z);

					sPortal->GetDirection(_player->GetAttributesManager()->teleportInfo.rotation.x,
						_player->GetAttributesManager()->teleportInfo.rotation.y,
						_player->GetAttributesManager()->teleportInfo.rotation.z);

					_player->GetAttributesManager()->teleportInfo.worldInfo.tblidx = sPortal->GetWorldIdx();

					sLog.outDebug("Teleport: pos %f %f %f rot %f %f %f worldtblidx %d type %d", _player->GetAttributesManager()->teleportInfo.position.x,
						_player->GetAttributesManager()->teleportInfo.position.y,
						_player->GetAttributesManager()->teleportInfo.position.z,
						_player->GetAttributesManager()->teleportInfo.rotation.x,
						_player->GetAttributesManager()->teleportInfo.rotation.y,
						_player->GetAttributesManager()->teleportInfo.rotation.z,
						sPortal->GetWorldIdx(),
						sPortal->GetPotalType());

					sWORLD_TBLDAT* worldTbl = (sWORLD_TBLDAT*)sTBM.GetWorldTable()->FindData(_player->GetAttributesManager()->teleportInfo.worldInfo.tblidx);
					sLog.outDebug("WORLD TBLIDX: %d resourse id: %d", worldTbl->tblidx, worldTbl->dwWorldResourceID);
					_player->GetState()->sCharStateDetail.sCharStateDespawning.byTeleportType = eTELEPORT_TYPE::TELEPORT_TYPE_DEFAULT;
					_player->SetState(eCHARSTATE::CHARSTATE_DESPAWNING);
				}

				

				/*sGU_CHAR_TELEPORT_RES Teleport;
				memset(&Teleport, 0, sizeof(sGU_CHAR_TELEPORT_RES));
				Teleport.wOpCode = GU_CHAR_TELEPORT_RES;
				Teleport.wPacketSize = sizeof(sGU_CHAR_TELEPORT_RES) - 2;
				Teleport.wResultCode = GAME_SUCCESS;
				Teleport.vNewLoc.x = 4474.109863;
				Teleport.vNewLoc.y = -42.000000;
				Teleport.vNewLoc.z = 3958.379883;
				Teleport.vNewDir.x = -0.751000;
				Teleport.vNewDir.y = 0;
				Teleport.vNewDir.z = -0.661000;
				Teleport.unk = INVALID_TBLIDX;
				Teleport.bIsToMoveAnotherServer = false;

				_player->Relocate(Teleport.vNewLoc.x, Teleport.vNewLoc.y, Teleport.vNewLoc.z, Teleport.vNewDir.x, Teleport.vNewDir.y, Teleport.vNewDir.z);
				_player->SetWorldID(1);
				_player->SetWorldTableID(1);
				_player->GetState()->sCharStateDetail.sCharStateTeleporting.byTeleportType = eTELEPORT_TYPE::TELEPORT_TYPE_NPC_PORTAL;
				_player->SetState(eCHARSTATE::CHARSTATE_TELEPORTING);
				SendPacket((char*)&Teleport, sizeof(sGU_CHAR_TELEPORT_RES));*/

				break;
			}
			case DBO_ACT_TYPE_ID_ACT_ITEM:
			{
				CDboTSActItem* actItem = (CDboTSActItem*)contGAct->GetChildEntity(i);
				if (actItem == NULL)
				{
					return RESULT_FAIL;
				}
				sLog.outDebug("Quest: Item type %d", actItem->GetItemType());
				if (actItem->GetItemType() == eTSITEM_TYPE::eTSITEM_TYPE_CREATE)
				{
					for (int itemId = 0; itemId < actItem->eMAX_TS_ITEM_COUNT; itemId++)
					{
						sLog.outDebug("Quest: item tblidx %d slot type %d",
							actItem->GetItemInfo(itemId).uiItemIdx, actItem->GetItemInfo(itemId).eItemSlotType);
						sITEM_PROFILE createdItem;
						WORD result = _player->GetInventoryManager()->PerformShopBuy(actItem->GetItemInfo(itemId).uiItemIdx, 1, createdItem);
						if (result == GAME_SUCCESS && createdItem.tblidx != INVALID_TBLIDX)
						{
							sLog.outDetail("Item Created\n");
							SendItemCreate(&createdItem);
						}
					}
				}
				break;
			}
			case DBO_ACT_TYPE_ID_ACT_OPEN_WINDOW:
			{
				CDboTSActOpenWindow* openWindow = (CDboTSActOpenWindow*)contGAct->GetChildEntity(i);
				if (openWindow == NULL)
				{
					return RESULT_FAIL;
				}
				sLog.outDetail("Quest: tableidx %d, type %d", openWindow->GetTableIdx(), openWindow->GetWindowType());
				break;
			}
			case DBO_ACT_TYPE_ID_ACT_WORLDPLAYSCRIPT:
			{
				CDboTSActWorldPlayScript* worldPlayScript = (CDboTSActWorldPlayScript*)contGAct->GetChildEntity(i);
				if (worldPlayScript == NULL)
				{
					return RESULT_FAIL;
				}
				_player->GetAttributesManager()->sPawnMobQuest = worldPlayScript->IsStart();
				sLog.outDebug("Quest: isStart %d", worldPlayScript->IsStart());
				break;
			}
		}
	}
	return RESULT_SUCCESS;
}

ResultCodes WorldSession::ProcessTsContGCond(CDboTSContGCond * contGCond)
{
	for (int i = 0; i < contGCond->GetNumOfChildEntity(); i++)
	{
		sLog.outDetail("Cont: %s %d, %d", contGCond->GetChildEntity(i)->GetClassNameW(), contGCond->GetChildEntity(i)->GetEntityType(), DBO_EVENT_TYPE_ID_SCOUT_USE);
		switch (contGCond->GetChildEntity(i)->GetEntityType())
		{
			case DBO_EVENT_TYPE_ID_SCOUT_USE:
			{
				CDboTSScoutUse * scoutUse = (CDboTSScoutUse*)contGCond->GetChildEntity(i);
				if (scoutUse == NULL)
				{
					return RESULT_FAIL;
				}

				Npc* NpcInfo = static_cast<Npc*>(_player->GetFromList(_player->GetTarget()));
				if (NpcInfo == NULL)
				{
					sLog.outError("NPC NOT FOUND");
					return RESULT_FAIL;
				}

				if (NpcInfo->GetNpcData().MonsterID == scoutUse->GetTargetIdx())
				{ 
					sLog.outError("NPC IS THE TARGET");
					sLog.outDetail("Quest: item tblidx %d, target tblidx %d, target type %d, npc tblidx %d",
						scoutUse->GetItemIdx(), scoutUse->GetTargetIdx(), scoutUse->GetTargetType(), NpcInfo->GetNpcData().MonsterID);
					continue;
				}
				break;
			}
			case DBO_EVENT_TYPE_ID_BIND_STONE:
			{
				CDboTSBindStone* bindStone = (CDboTSBindStone*)contGCond->GetChildEntity(i);
				if (bindStone == NULL)
				{
					return RESULT_FAIL;
				}
				sOBJECT_TBLDAT* object = (sOBJECT_TBLDAT*)sTBM.GetObjectTable(_player->GetPcProfile()->bindObjectTblidx)->FindData(_player->GetPcProfile()->bindObjectTblidx);
				if (object != NULL)
				{
					//Mob * MobInfo = static_cast<Mob*>(object)
					sLog.outDebug("Object: handle %d", object->tblidx);
				}
				sLog.outDebug("Object: tblidx %d worldid %d typebind %d", _player->GetPcProfile()->bindObjectTblidx, _player->GetPcProfile()->bindWorldId, _player->GetPcProfile()->byBindType);
				break;
			}
			case DBO_EVENT_TYPE_ID_TELEPORT:
			{
				CDboTSTeleport* teleport = (CDboTSTeleport*)contGCond->GetChildEntity(i);
				if (teleport == NULL)
				{
					return RESULT_FAIL;
				}
				sLog.outDebug("Teleport by npc quest");
				break;
			}
			case DBO_EVENT_TYPE_ID_ITEM_UPGRADE:
			{
				CDboTSItemUpgrade* itemUpgrade = (CDboTSItemUpgrade*)contGCond->GetChildEntity(i);
				if (itemUpgrade == NULL)
				{
					return RESULT_FAIL;
				}
				break;
			}
			case DBO_EVENT_TYPE_ID_FREEBATTLE:
			{
				CDboTSFreeBattle* freeBattle = (CDboTSFreeBattle*)contGCond->GetChildEntity(i);
				if (freeBattle == NULL)
				{
					return RESULT_FAIL;
				}
				break;
			}
			case DBO_EVENT_TYPE_ID_ITEMIDENTITY:
			{
				CDboTSItemIdentity* itemIdentify = (CDboTSItemIdentity*)contGCond->GetChildEntity(i);
				if (itemIdentify == NULL)
				{
					return RESULT_FAIL;
				}
				break;
			}
			case DBO_EVENT_TYPE_ID_PARTY:
			{
				CDboTSParty* party = (CDboTSParty*)contGCond->GetChildEntity(i);
				if (party == NULL)
				{
					return RESULT_FAIL;
				}
				break;
			}
			case DBO_EVENT_TYPE_ID_RB:
			{
				CDboTSRB* RB = (CDboTSRB*)contGCond->GetChildEntity(i);
				if (RB == NULL)
				{
					return RESULT_FAIL;
				}
				break;
			}
			case DBO_EVENT_TYPE_ID_DIALOG_OPEN:
			{
				CDboTSDialogOpen* dialogOpen = (CDboTSDialogOpen*)contGCond->GetChildEntity(i);
				if (dialogOpen == NULL)
				{
					return RESULT_FAIL;
				}
				break;
			}
			case DBO_COND_TYPE_ID_CHECK_STOCEVT:
			{
				CDboTSCheckSToCEvt* checkSToCevt = (CDboTSCheckSToCEvt*)contGCond->GetChildEntity(i);
				if (checkSToCevt == NULL)
				{
					return RESULT_FAIL;
				}

				break;
			}
		}
	}

	return RESULT_SUCCESS;
}

ResultCodes WorldSession::ProcessTsContReward(CDboTSContReward * contReward, DWORD dwParam)
{
	for (int i = 0; i < contReward->GetNumOfChildEntity(); i++)
	{
		sLog.outDetail("Cont: %s %d, %d", contReward->GetChildEntity(i)->GetClassNameW(), contReward->GetChildEntity(i)->GetEntityType(), DBO_EVENT_TYPE_ID_CLICK_NPC);

		//sLog.outDebug("Reward: tblidx %d value %d type %d", rwdInfo.m_uiIdx, rwdInfo.m_nValue, rwdInfo.m_eType);
		sLog.outDebug("Reward: tblidx %d zenny %d type %d experience %d", contReward->GetRewardTableIndex(), contReward->GetRewardZeny(), contReward->GetRewardContType(), contReward->GetRewardExp());
		switch (contReward->GetChildEntity(i)->GetEntityType())
		{
			case DBO_EVENT_TYPE_ID_CLICK_NPC:
			{
				//Check here if npc is the same of the quest
				CDboTSClickNPC * clickNpc = (CDboTSClickNPC*)contReward->GetChildEntity(i);
				if (clickNpc == NULL)
				{
					return RESULT_FAIL;
				}
				sLog.outDetail("Quest: npc tblidx %d", clickNpc->GetNPCIdx());
				break;
			}
		}
	}

	ResultCodes result = GivePlayerQuestReward(contReward->GetRewardTableIndex(), contReward->GetRewardContType(), dwParam);
	if (result == RESULT_FAIL)
	{
		return RESULT_FAIL;
	}

	return RESULT_SUCCESS;
}

ResultCodes WorldSession::GivePlayerItemReward(sQUEST_REWARD_TBLDAT* rewardTbl, DWORD dwParam)
{
	for (int rw = 0; rw < QUEST_REWARD_DEF_MAX_CNT; rw++)
	{
		if (rewardTbl->rewardDefData[rw].rwdIdx == INVALID_TBLIDX)
		{
			break; // cambiar por continue si causa bug
		}

		sITEM_TBLDAT* itemTblDefault = (sITEM_TBLDAT*)sTBM.GetItemTable()->FindData(rewardTbl->rewardDefData[rw].rwdIdx);
		if (itemTblDefault)
		{
			sITEM_PROFILE createdItem;
			WORD result = _player->GetInventoryManager()->PerformShopBuy(itemTblDefault->tblidx, rewardTbl->rewardDefData[rw].Amount, createdItem);
			if (result == GAME_SUCCESS && createdItem.tblidx != INVALID_TBLIDX)
			{
				sLog.outDetail("Item Reward Created\n");
				SendItemCreate(&createdItem);
			}
			continue;
		}

		sQUEST_REWARD_SELECT_TBLDAT* rewardSelect1 = (sQUEST_REWARD_SELECT_TBLDAT*)sTBM.GetQuestRewardSelectTable()->FindData(rewardTbl->rewardDefData[rw].rwdIdx);

		if (rewardSelect1)
		{
			sLog.outDebug("Reward Select table: %d type: %d", rewardSelect1->tblidx, rewardSelect1->unknown);

			if (rewardSelect1->unknown == eREWARD_SLOT_TYPE_DEFAULT)
			{
				sITEM_TBLDAT* itemTblSelect;
				for (int itRw = 0; itRw < QUEST_REWARD_SELECT_MAX_CNT; itRw++)
				{
					if (rewardSelect1->rewardData[itRw].itemTblidx == INVALID_TBLIDX) // quitar si causa bugs
					{
						break;
					}

					switch (rewardSelect1->rewardData[itRw].unknown)
					{
						case eREWARD_TYPE_NORMAL_ITEM:
						{
							sLog.outDebug("Item tblidx :%d", rewardSelect1->rewardData[itRw].itemTblidx);

							itemTblSelect = (sITEM_TBLDAT*)sTBM.GetItemTable()->FindData(rewardSelect1->rewardData[itRw].itemTblidx);

							if (itemTblSelect == NULL)
							{
								continue;
							}

							DWORD myFlag;
							// if we have double spec
							// (0x01 << 0) | (0x01 << plr->GetMyClass());
							myFlag = MAKE_BIT_FLAG(static_cast<int>(_player->GetMyClass()));
							sLog.outDebug("Item tblidx2 :%d", itemTblSelect->tblidx);
							sLog.outDetail("My flag: %d flag need %d my class: %d is not same %d", 
								myFlag, itemTblSelect->dwNeedClassBitFlag, _player->GetMyClass(), (myFlag & ~itemTblSelect->dwNeedClassBitFlag));
							if (itemTblSelect->dwNeedClassBitFlag == INVALID_TBLIDX || (myFlag & ~itemTblSelect->dwNeedClassBitFlag))// lo mismo que !(myFlag & itemTblSelect->dwNeedClassBitFlag)
							{
								sLog.outDebug("Special class: %u, need class: %d", itemTblSelect->byClassSpecial, itemTblSelect->dwNeedClassBitFlag);
								sLog.outError("This item is not for this class");
								continue;
							}

							sITEM_PROFILE createdItem;
							WORD result = _player->GetInventoryManager()->PerformShopBuy(rewardSelect1->rewardData[itRw].itemTblidx, rewardSelect1->rewardData[itRw].amount, createdItem);
							if (result == GAME_SUCCESS && createdItem.tblidx != INVALID_TBLIDX)
							{
								sLog.outDetail("Item Reward Created\n");
								SendItemCreate(&createdItem);
							}
							else 
							{
								sLog.outError("Item reward not found");
								return RESULT_FAIL;
							}
							break;
						}
					}
				}
			}
		}
	}

	for (int rw = 0; rw < QUEST_REWARD_SEL_MAX_CNT; rw++)
	{
		if (rewardTbl->rewardSelData[rw].rwdIdx == INVALID_TBLIDX)
		{
			break; // cambiar por continue si causa bugs
		}

		sITEM_TBLDAT* itemTblDefault = (sITEM_TBLDAT*)sTBM.GetItemTable()->FindData(rewardTbl->rewardSelData[rw].rwdIdx);
		if (itemTblDefault)
		{
			sITEM_PROFILE createdItem;
			WORD result = _player->GetInventoryManager()->PerformShopBuy(itemTblDefault->tblidx, rewardTbl->rewardSelData[rw].Amount, createdItem);
			if (result == GAME_SUCCESS && createdItem.tblidx != INVALID_TBLIDX)
			{
				sLog.outDetail("Item Reward Created %d", itemTblDefault->tblidx);
				SendItemCreate(&createdItem);
			}
			continue;
		}

		sQUEST_REWARD_SELECT_TBLDAT* rewardSelect2 = (sQUEST_REWARD_SELECT_TBLDAT*)sTBM.GetQuestRewardSelectTable()->FindData(rewardTbl->rewardSelData[rw].rwdIdx);

		if (rewardSelect2)
		{
			sLog.outDebug("Reward Select table: %d type: %d", rewardSelect2->tblidx, rewardSelect2->unknown);

			if (dwParam == INVALID_TBLIDX)
			{
				break; //Cambiar si causa bugs
			}

			if (rewardSelect2->unknown == eREWARD_SLOT_TYPE_SELECTION)
			{
				switch (rewardSelect2->rewardData[dwParam].unknown)
				{
					case eREWARD_TYPE_NORMAL_ITEM:
					{
						sLog.outDebug("Item tblidx :%d type item: %d", rewardSelect2->rewardData[dwParam].itemTblidx, rewardSelect2->rewardData[dwParam].unknown);

						sITEM_PROFILE createdItem;
						WORD result = _player->GetInventoryManager()->PerformShopBuy(rewardSelect2->rewardData[dwParam].itemTblidx, rewardSelect2->rewardData[dwParam].amount, createdItem);
						if (result == GAME_SUCCESS && createdItem.tblidx != INVALID_TBLIDX)
						{
							sLog.outDetail("Item Reward Created");
							SendItemCreate(&createdItem);
						}
						else
						{
							return RESULT_FAIL;
						}
						break;
					}
				}
			}
		}
	}

	return RESULT_SUCCESS;
}

ResultCodes WorldSession::GivePlayerQuestReward(TBLIDX tblidx, eREWARD_CONTAINER_TYPE rewardContType, DWORD dwParam)
{
	if (rewardContType == eREWARD_CONTAINER_TYPE_QUEST)
	{
		QuestRewardTable* dat = sTBM.GetQuestRewardTable();
		sQUEST_REWARD_TBLDAT* rewardTbl = reinterpret_cast<sQUEST_REWARD_TBLDAT*>(dat->FindData(tblidx));
		if (rewardTbl == NULL)
		{
			return RESULT_FAIL;
		}
		sLog.outDebug("Reward table: %d", rewardTbl->tblidx);

		DWORD bonus = 0;

		if (GivePlayerItemReward(rewardTbl, dwParam) != RESULT_SUCCESS)
		{
			return RESULT_FAIL;
		}

		_player->UpdateZennyAmount(rewardTbl->Zenny, eZENNY_CHANGE_TYPE::ZENNY_CHANGE_TYPE_DB_REWARD);
		_player->UpdateExperienceAmount(rewardTbl->EXP, bonus);
	}

	return RESULT_SUCCESS;
}


void WorldSession::ProcessTsContEnd(CDboTSContEnd * contEnd)
{
	for (int i = 0; i < contEnd->GetNumOfChildEntity(); i++)
	{
		sLog.outDetail("Cont: %s %d, %d", contEnd->GetChildEntity(i)->GetClassNameW(), contEnd->GetChildEntity(i)->GetEntityType(), DBO_EVENT_TYPE_ID_CLICK_NPC);
		sLog.outDebug("End of quest");

		
	}
	CNtlTSTrigger* trigger = (CNtlTSTrigger*)contEnd->GetRoot();
	if (contEnd->GetEndType() == eEND_TYPE::eEND_TYPE_COMPLETE)
	{
		sDB.SaveQuestStatus(_player->charid, trigger->GetID(), true);
	}
}

ResultCodes WorldSession::FindQuestInformation(sUG_TS_CONFIRM_STEP_REQ * req)
{
	switch (req->byEventType)
	{
		case eEVENT_GEN_TYPE_CLICK_NPC:
		{
			sLog.outDebug("-----eEVENT_GEN_TYPE_CLICK_NPC------");
			break;
		}
		case eEVENT_GEN_TYPE_CLICK_OBJECT:
		{
			sLog.outDebug("-----eEVENT_GEN_TYPE_CLICK_OBJECT------");
			break;
		}
		case eEVENT_GEN_TYPE_COL_OBJECT:
		{
			sLog.outDebug("-----eEVENT_GEN_TYPE_COL_OBJECT------");
			break;
		}
		case eEVENT_GEN_TYPE_ITEM_USE:
		{
			sLog.outDebug("-----eEVENT_GEN_TYPE_ITEM_USE------");
			break;
		}
		case eEVENT_GEN_TYPE_ITEM_GET:
		{
			sLog.outDebug("-----eEVENT_GEN_TYPE_ITEM_GET------");
			break;
		}
		case eEVENT_GEN_TYPE_ITEM_EQUIP:
		{
			sLog.outDebug("-----eEVENT_GEN_TYPE_ITEM_EQUIP------");
			break;
		}
		case eEVENT_GEN_TYPE_SCOUT_USE:
		{
			sLog.outDebug("-----eEVENT_GEN_TYPE_SCOUT_USE------");
			break;
		}
		case eEVENT_GEN_TYPE_RCV_SVR_EVT:
		{
			sLog.outDebug("-----eEVENT_GEN_TYPE_RCV_SVR_EVT------");
			break;
		}
		case eEVENT_GEN_TYPE_SKILL_USE:
		{
			sLog.outDebug("-----eEVENT_GEN_TYPE_SKILL_USE------");
			break;
		}
		case eEVENT_GEN_TYPE_COL_REGION:
		{
			sLog.outDebug("-----eEVENT_GEN_TYPE_COL_REGION------");
			break;
		}
		case eEVENT_GEN_TYPE_RB:
		{
			sLog.outDebug("-----eEVENT_GEN_TYPE_RB------");
			break;
		}
		case eEVENT_GEN_TYPE_CLICK_MOB:
		{
			sLog.outDebug("-----eEVENT_GEN_TYPE_CLICK_MOB------");
			break;
		}
		case eEVENT_GEN_TYPE_SKIP_CONT:
		{
			sLog.outDebug("-----eEVENT_GEN_TYPE_SKIP_CONT------");
			break;
		}
		case eEVENT_GEN_TYPE_BIND_STONE:
		{
			sLog.outDebug("-----eEVENT_GEN_TYPE_BIND_STONE------");
			break;
		}
		case eEVENT_GEN_TYPE_SEARCH_QUEST:
		{
			sLog.outDebug("-----eEVENT_GEN_TYPE_SEARCH_QUEST------");
			break;
		}
		case eEVENT_GEN_TYPE_ITEM_UPGRADE:
		{
			sLog.outDebug("-----eEVENT_GEN_TYPE_ITEM_UPGRADE------");
			break;
		}
		case eEVENT_GEN_TYPE_TELEPORT:
		{
			sLog.outDebug("-----eEVENT_GEN_TYPE_TELEPORT------");
			break;
		}
		case eEVENT_GEN_TYPE_BUDOKAI:
		{
			sLog.outDebug("-----eEVENT_GEN_TYPE_BUDOKAI------");
			break;
		}
		case eEVENT_GEN_TYPE_SLOTMACHINE:
		{
			sLog.outDebug("-----eEVENT_GEN_TYPE_SLOTMACHINE------");
			break;
		}
		case eEVENT_GEN_TYPE_HOIPOIMIX:
		{
			sLog.outDebug("-----eEVENT_GEN_TYPE_HOIPOIMIX------");
			break;
		}
		case eEVENT_GEN_TYPE_PRIVATESHOP:
		{
			sLog.outDebug("-----eEVENT_GEN_TYPE_PRIVATESHOP------");
			break;
		}
		case eEVENT_GEN_TYPE_FREEBATTLE:
		{
			sLog.outDebug("-----eEVENT_GEN_TYPE_FREEBATTLE------");
			break;
		}
		case eEVENT_GEN_TYPE_ITEMIDENTITY:
		{
			sLog.outDebug("-----eEVENT_GEN_TYPE_ITEMIDENTITY------");
			break;
		}
		case eEVENT_GEN_TYPE_USEMAIL:
		{
			sLog.outDebug("-----eEVENT_GEN_TYPE_USEMAIL------");
			break;
		}
		case eEVENT_GEN_TYPE_PARTY:
		{
			sLog.outDebug("-----eEVENT_GEN_TYPE_PARTY------");
			break;
		}
		case eEVENT_GEN_TYPE_INVALID:
		{
			sLog.outDebug("-----eEVENT_GEN_TYPE_INVALID------");
			break;
		}
	}


	// example tss
	CNtlTSCont * contBase = sTSM.FindQuestFromTS(req->tId)->GetGroup(NTL_TS_MAIN_GROUP_ID)->GetChildCont(req->tcCurId);
	if (contBase == NULL)
	{
		return RESULT_FAIL;
	}

	sLog.outError("type: %s %d", contBase->GetClassNameW(), contBase->GetEntityType());
	switch (contBase->GetEntityType())
	{
		case DBO_CONT_TYPE_ID_CONT_START:
		{
			CDboTSContStart * contStart = ((CDboTSContStart*)contBase);
			if (contStart == NULL)
			{
				return RESULT_FAIL;
			}
			if (ProcessTSContStart(contStart) == RESULT_FAIL);
			{
				return RESULT_FAIL;
			}
			break;
		}

		case DBO_CONT_TYPE_ID_CONT_GACT:
		{
			CDboTSContGAct * contGAct = ((CDboTSContGAct*)contBase);
			if (contGAct == NULL)
			{
				return RESULT_FAIL;
			}
			if (ProcessTsContGAct(contGAct, req->tId, req->tcCurId) == RESULT_FAIL)
			{
				return RESULT_FAIL;
			}
			break;
		}

		case DBO_CONT_TYPE_ID_CONT_PROPOSAL:
		{
			CDboTSContProposal* contProposal = ((CDboTSContProposal*)contBase);
			if (contProposal == NULL)
			{
				return RESULT_FAIL;
			}
			break;
		}

		case DBO_CONT_TYPE_ID_CONT_GCOND:
		{
			CDboTSContGCond * contGCond = ((CDboTSContGCond*)contBase);
			sLog.outDebug("Check if the quest is completed correctly");

			if (contGCond == NULL)
			{
				return RESULT_FAIL;
			}
			if (ProcessTsContGCond(contGCond) == RESULT_FAIL)
			{
				return RESULT_FAIL;
			}
			sLog.outDebug("Quest complete correctly");
			break;
		}

		case DBO_CONT_TYPE_ID_CONT_REWARD:
		{
			CDboTSContReward * contReward = ((CDboTSContReward*)contBase);
			if (contReward == NULL)
			{
				return RESULT_FAIL;
			}
			if (ProcessTsContReward(contReward, req->dwParam) == RESULT_FAIL)
			{
				return RESULT_FAIL;
			}
			break;
		}

		case DBO_CONT_TYPE_ID_CONT_END:
		{
			CDboTSContEnd * contEnd = ((CDboTSContEnd*)contBase);
			if (contEnd == NULL)
			{
				return RESULT_FAIL;
			}
			ProcessTsContEnd(contEnd);
			break;
		}
	}

	return RESULT_SUCCESS;
}

ResultCodes	WorldSession::CheckEvtDataType(CDboTSActSToCEvt* sToCEvt, NTL_TS_TC_ID tcId)
{
	CNtlTSTrigger* trigger = (CNtlTSTrigger*)sToCEvt->GetRoot();

	if (trigger == NULL)
	{
		return RESULT_FAIL;
	}
	//memset(_player->GetAttributesManager()->QuestDat, 0, sizeof _player->GetAttributesManager()->QuestDat);

	int freeslot = 0;
	for (int i = 0; i < 30; i++)
	{
		if (_player->GetAttributesManager()->QuestDat[i].QuestID == 0 || _player->GetAttributesManager()->QuestDat[i].QuestID == INVALID_TBLIDX)
		{
			freeslot = i;
			break;
		}
	}

	_player->GetAttributesManager()->QuestDat[freeslot].QuestID = trigger->GetID();
	_player->GetAttributesManager()->QuestDat[freeslot].evtDataType = sToCEvt->GetEvtDataType();
	_player->GetAttributesManager()->QuestDat[freeslot].tcId = tcId;
	_player->GetAttributesManager()->QuestDat[freeslot].taId = sToCEvt->GetActionId();

	switch (sToCEvt->GetEvtDataType())
	{
		case eSTOC_EVT_DATA_TYPE_MOB_KILL_CNT:
		{

			for (int i = 0; i < sToCEvt->GetEvtData().MAX_MOB_KILL; i++)
			{
				TBLIDX groupTblidx = sToCEvt->GetEvtData().sMobKillCnt[i].uiMobIdx;
				TBLIDX mobTblidx = sTBM.GetMobTable()->FindTblidxByGroup(groupTblidx);

				if (mobTblidx && mobTblidx != INVALID_TBLIDX)
				{
					_player->GetAttributesManager()->QuestDat[freeslot].uEvtData.sMobKillCnt[i].uiMobIdx = mobTblidx;
					_player->GetAttributesManager()->QuestDat[freeslot].uEvtData.sMobKillCnt[i].nCurMobCnt = sToCEvt->GetEvtData().sMobKillCnt[i].nCurMobCnt;
					_player->GetAttributesManager()->QuestDat[freeslot].uEvtData.sMobKillCnt[i].nMobCnt = sToCEvt->GetEvtData().sMobKillCnt[i].nMobCnt;


					sLog.outError("ROOT TS: %d", trigger->GetID());
					sLog.outDetail("Mob kill: group tblidx: %d  mobTblidx: %d count: %d, curcout: %d",
						groupTblidx, mobTblidx, sToCEvt->GetEvtData().sMobKillCnt[i].nMobCnt, sToCEvt->GetEvtData().sMobKillCnt[i].nCurMobCnt);


					if (_player->GetAttributesManager()->sPawnMobQuest)
					{
						sMOB_TBLDAT* mob = (sMOB_TBLDAT*)sTBM.GetMobTable()->FindData(mobTblidx);
						if (mob)
						{
							sLog.outDebug("obj tblidx %d %d %s", mob->tblidx, mob->Mob_Group, mob->szNameText);

							sNPC_TBLDAT* npc = (sNPC_TBLDAT*)sTBM.GetNpcTable()->FindData(_player->GetAttributesManager()->lastNPCQuest);
							if (npc)
							{
								sLog.outDebug("npc tblidx %d %s %d %d", npc->tblidx, npc->szNameText, strcmp(npc->szModel, mob->szModel), npc->byNpcType == mob->byMob_Type);
								if (!strcmp(npc->szModel, mob->szModel)) //&& (npc->byNpcType == mob->byMob_Type))
								{
									Npc * curr_Npc = static_cast<Npc*>(_player->GetFromList(_player->GetTarget()));
									sLog.outDebug("Conver NPC to MOB %d %d", curr_Npc->GetNpcData().MonsterID, _player->GetAttributesManager()->lastNPCQuest);
									if (curr_Npc->GetNpcData().MonsterID == _player->GetAttributesManager()->lastNPCQuest)
									{
										_player->GetAttributesManager()->QuestDat[freeslot].npcClick = curr_Npc->GetNpcData().MonsterID;

										sLog.outDebug("Converting...");
										sGU_OBJECT_DESTROY sPacket;

										sPacket.wOpCode = GU_OBJECT_DESTROY;
										sPacket.handle = curr_Npc->GetHandle();
										sPacket.wPacketSize = sizeof(sGU_OBJECT_DESTROY) - 2;

										_player->SendPacket((char*)&sPacket, sizeof(sGU_OBJECT_DESTROY));
										curr_Npc->SetIsBecomeMob(true);
										curr_Npc->RemoveFromWorld();
										_player->RemoveFromList(*curr_Npc);
										sLog.outDebug("NPC deleted");

										_player->GetAttributesManager()->QuestDat[freeslot].mobHandle = SpawnMobForQuest(mobTblidx, curr_Npc->GetNpcData().MonsterID, 0);
										sLog.outDebug("MOB Created");

									}
									else
									{
										sLog.outDebug("NPC NOT FOUND");
										_player->GetAttributesManager()->sPawnMobQuest = false;
									}
									
								}
								else
								{
									for (int count = 0; count < sToCEvt->GetEvtData().sMobKillCnt[i].nMobCnt; count++)
									{
										SpawnMobForQuest(mobTblidx, 0, count);
									}
								}
							}
						}
					}
				}
			}
			sLog.outDetail("Quest: type eSTOC_EVT_DATA_TYPE_MOB_KILL_CNT");
			break;
		}
		case eSTOC_EVT_DATA_TYPE_MOB_KILL_ITEM_CNT:
		{
			for (int i = 0; i < sToCEvt->GetEvtData().MAX_MOB_KILL_ITEM; i++)
			{
				_player->GetAttributesManager()->QuestDat[freeslot].uEvtData.sMobKillItemCnt[i].uiMobLIIdx = sToCEvt->GetEvtData().sMobKillItemCnt[i].uiMobLIIdx;
				_player->GetAttributesManager()->QuestDat[freeslot].uEvtData.sMobKillItemCnt[i].nMobLICnt = sToCEvt->GetEvtData().sMobKillItemCnt[i].nMobLICnt;
				_player->GetAttributesManager()->QuestDat[freeslot].uEvtData.sMobKillItemCnt[i].nCurMobLICnt = sToCEvt->GetEvtData().sMobKillItemCnt[i].nCurMobLICnt;
				sLog.outDebug("Item tblidx: %d count %d curcount %d", 
					sToCEvt->GetEvtData().sMobKillItemCnt[i].uiMobLIIdx, 
					sToCEvt->GetEvtData().sMobKillItemCnt[i].nMobLICnt,
					sToCEvt->GetEvtData().sMobKillItemCnt[i].nCurMobLICnt);

				if (sToCEvt->GetEvtData().sMobKillItemCnt[i].uiMobLIIdx == INVALID_TBLIDX)
				{
					continue;
				}

				std::vector<TBLIDX> dropTable = sTBM.GetQuestDropTable()->FindByItemTblidx(sToCEvt->GetEvtData().sMobKillItemCnt[i].uiMobLIIdx);
				for (std::vector<TBLIDX>::size_type item = 0; item != dropTable.size(); item++)
				{
					/* std::cout << v[i]; ... */
					sLog.outDebug("Drop Table %d", dropTable[item]);
					//-----------------
					TBLIDX mobTblidx = INVALID_TBLIDX;
					std::vector<TBLIDX> mobsTblidx = sTBM.GetMobTable()->FindTblidxsByQuestDrop(dropTable[item]);
					if (mobsTblidx.size() > 0)
					{
						mobTblidx = mobsTblidx[0];
					}

					if (!(mobTblidx == INVALID_TBLIDX) && _player->GetAttributesManager()->sPawnMobQuest)
					{
						sMOB_TBLDAT* mob = (sMOB_TBLDAT*)sTBM.GetMobTable()->FindData(mobTblidx);
						if (mob)
						{
							sLog.outDebug("obj tblidx %d %d %s", mob->tblidx, mob->Mob_Group, mob->szNameText);

							sNPC_TBLDAT* npc = (sNPC_TBLDAT*)sTBM.GetNpcTable()->FindData(_player->GetAttributesManager()->lastNPCQuest);
							if (npc)
							{
								sLog.outDebug("npc tblidx %d %s %d %d", npc->tblidx, npc->szNameText, strcmp(npc->szModel, mob->szModel), npc->byNpcType == mob->byMob_Type);
								if (!strcmp(npc->szModel, mob->szModel))// && (npc->byNpcType == mob->byMob_Type))
								{
									Npc* curr_Npc = static_cast<Npc*>(_player->GetFromList(_player->GetTarget()));
									sLog.outDebug("Convert NPC to MOB %d %d", curr_Npc->GetNpcData().MonsterID, _player->GetAttributesManager()->lastNPCQuest);
									if (curr_Npc->GetNpcData().MonsterID == _player->GetAttributesManager()->lastNPCQuest)
									{
										sLog.outDebug("Converting NPC to MOB...");
										_player->GetAttributesManager()->QuestDat[freeslot].npcClick = curr_Npc->GetNpcData().MonsterID;


										sGU_OBJECT_DESTROY sPacket;

										sPacket.wOpCode = GU_OBJECT_DESTROY;
										sPacket.handle = curr_Npc->GetHandle();
										sPacket.wPacketSize = sizeof(sGU_OBJECT_DESTROY) - 2;

										_player->SendPacket((char*)&sPacket, sizeof(sGU_OBJECT_DESTROY));

										_player->RemoveFromList(*curr_Npc);
										curr_Npc->SetIsBecomeMob(true);
										curr_Npc->RemoveFromWorld();
										sLog.outDebug("NPC deleted");
										
										_player->GetAttributesManager()->QuestDat[freeslot].mobHandle = SpawnMobForQuest(mobTblidx, curr_Npc->GetNpcData().MonsterID, 0);
										sLog.outDebug("MOB created");
									}
									else
									{
										sLog.outDebug("NPC NOT FOUND");
										_player->GetAttributesManager()->sPawnMobQuest = false;
									}

								}
								else
								{
									for (int count = 0; count < sToCEvt->GetEvtData().sMobKillCnt[i].nMobCnt; count++)
									{
										SpawnMobForQuest(mobTblidx, 0, count);
									}
								}
							}
						}
					}

					//-----------------

				}

				
			}

			sLog.outDetail("Quest: type eSTOC_EVT_DATA_TYPE_MOB_KILL_ITEM_CNT");
			break;
		}
		case eSTOC_EVT_DATA_TYPE_DELIVERY_ITEM:
		{
			sLog.outDetail("Quest: type eSTOC_EVT_DATA_TYPE_DELIVERY_ITEM");
			break;
		}
		case eSTOC_EVT_DATA_TYPE_OBJECT_ITEM:
		{
			for (int i = 0; i < sToCEvt->GetEvtData().MAX_OBJECT_ITEM; i++)
			{
				_player->GetAttributesManager()->QuestDat[freeslot].uEvtData.sObjectItemCnt[i].uiItemIdx = sToCEvt->GetEvtData().sObjectItemCnt[i].uiItemIdx;
				_player->GetAttributesManager()->QuestDat[freeslot].uEvtData.sObjectItemCnt[i].nItemCnt = sToCEvt->GetEvtData().sObjectItemCnt[i].nItemCnt;
				_player->GetAttributesManager()->QuestDat[freeslot].uEvtData.sObjectItemCnt[i].nCurItemCnt = sToCEvt->GetEvtData().sObjectItemCnt[i].nCurItemCnt;
				sLog.outDebug("Item tblidx: %d count %d curcount %d",
					sToCEvt->GetEvtData().sObjectItemCnt[i].uiItemIdx,
					sToCEvt->GetEvtData().sObjectItemCnt[i].nItemCnt,
					sToCEvt->GetEvtData().sObjectItemCnt[i].nCurItemCnt);
			}
			sLog.outDetail("Quest: type eSTOC_EVT_DATA_TYPE_OBJECT_ITEM");
			break;
		}
		case eSTOC_EVT_DATA_TYPE_PUBLIC_MOB_ITEM_CNT:
		{
			sLog.outDetail("Quest: type eSTOC_EVT_DATA_TYPE_PUBLIC_MOB_ITEM_CNT");
			break;
		}
		case eSTOC_EVT_DATA_TYPE_CUSTOM_EVT_CNT:
		{
			for (int i = 0; i < sToCEvt->GetEvtData().MAX_CUSTOM_EVT_CNT; i++)
			{
				_player->GetAttributesManager()->QuestDat[freeslot].uEvtData.sCustomEvtCnt[i].nCurCnt = sToCEvt->GetEvtData().sCustomEvtCnt[i].nCurCnt;
				_player->GetAttributesManager()->QuestDat[freeslot].uEvtData.sCustomEvtCnt[i].nMaxCnt = sToCEvt->GetEvtData().sCustomEvtCnt[i].nMaxCnt;
				_player->GetAttributesManager()->QuestDat[freeslot].uEvtData.sCustomEvtCnt[i].uiCustomEvtID = sToCEvt->GetEvtData().sCustomEvtCnt[i].uiCustomEvtID;
				_player->GetAttributesManager()->QuestDat[freeslot].uEvtData.sCustomEvtCnt[i].uiQTextTblIdx = sToCEvt->GetEvtData().sCustomEvtCnt[i].uiQTextTblIdx;

				sLog.outDebug("Quest: maxCount %d curCount %d evtId %d texttblidx %d", 
					sToCEvt->GetEvtData().sCustomEvtCnt[i].nMaxCnt, sToCEvt->GetEvtData().sCustomEvtCnt[i].nCurCnt, sToCEvt->GetEvtData().sCustomEvtCnt[i].uiCustomEvtID,
					sToCEvt->GetEvtData().sCustomEvtCnt[i].uiQTextTblIdx);
			}
			sLog.outDetail("Quest: type eSTOC_EVT_DATA_TYPE_CUSTOM_EVT_CNT");
			break;
		}
		case eSTOC_EVT_DATA_TYPE_VISIT:
		{
			for (int i = 0; i < sToCEvt->GetEvtData().MAX_VISIT_EVT; i++)
			{
				_player->GetAttributesManager()->QuestDat[freeslot].uEvtData.sVisitEvt[i].uiWorldTblIdx = sToCEvt->GetEvtData().sVisitEvt[i].uiWorldTblIdx;
				_player->GetAttributesManager()->QuestDat[freeslot].uEvtData.sVisitEvt[i].uiObjTblIdx = sToCEvt->GetEvtData().sVisitEvt[i].uiObjTblIdx;
				_player->GetAttributesManager()->QuestDat[freeslot].uEvtData.sVisitEvt[i].uiItemTblIdx = sToCEvt->GetEvtData().sVisitEvt[i].uiItemTblIdx;
				_player->GetAttributesManager()->QuestDat[freeslot].uEvtData.sVisitEvt[i].uiIndicatorQText = sToCEvt->GetEvtData().sVisitEvt[i].uiIndicatorQText;
				_player->GetAttributesManager()->QuestDat[freeslot].uEvtData.sVisitEvt[i].uiDialogText = sToCEvt->GetEvtData().sVisitEvt[i].uiDialogText;
				_player->GetAttributesManager()->QuestDat[freeslot].uEvtData.sVisitEvt[i].byObjType = sToCEvt->GetEvtData().sVisitEvt[i].byObjType;
				_player->GetAttributesManager()->QuestDat[freeslot].uEvtData.sVisitEvt[i].bCompleted = sToCEvt->GetEvtData().sVisitEvt[i].bCompleted;

				sLog.outDebug("Quest: world %d objTblidx %d itemTblidx %d indictaroQtext %d dialogText %d objType %d completed %d", 
					sToCEvt->GetEvtData().sVisitEvt[i].uiWorldTblIdx, sToCEvt->GetEvtData().sVisitEvt[i].uiObjTblIdx, sToCEvt->GetEvtData().sVisitEvt[i].uiItemTblIdx,
					sToCEvt->GetEvtData().sVisitEvt[i].uiIndicatorQText, sToCEvt->GetEvtData().sVisitEvt[i].uiDialogText, sToCEvt->GetEvtData().sVisitEvt[i].byObjType,
					sToCEvt->GetEvtData().sVisitEvt[i].bCompleted);
				sLog.outDebug("Quest id %d", _player->GetAttributesManager()->QuestDat[freeslot].QuestID);
			}
			sLog.outDetail("Quest: type eSTOC_EVT_DATA_TYPE_VISIT");
			break;
		}
	}
	return RESULT_SUCCESS;
}

HOBJECT WorldSession::SpawnNPCForQuest(TBLIDX NPCTblidx, int index)
{
	NPCTable* NpcTable = sTBM.GetNpcTable();
	sNPC_TBLDAT* pNPCTblData = reinterpret_cast<sNPC_TBLDAT*>(NpcTable->FindData(NPCTblidx));
	if (pNPCTblData != NULL)
	{

		std::vector<TBLIDX> spawnIdxs = sTBM.GetNpcSpawnTable(_player->GetWorldID())->FindSpawnByObjectTblidx(pNPCTblData->tblidx);

		int newIndex = index;

		if (spawnIdxs.size() <= 0)
		{
			return INVALID_TBLIDX;
		}
		else if (newIndex > (spawnIdxs.size() - 1))
		{
			newIndex = spawnIdxs.size() - 1;
		}
		sSPAWN_TBLDAT* spawnTbl = (sSPAWN_TBLDAT*)sTBM.GetNpcSpawnTable(_player->GetWorldID())->FindData(spawnIdxs[newIndex]);

		if (spawnTbl)
		{
			SpawnNPC spawnData;
			memset(&spawnData, 0, sizeof(SpawnNPC));

			spawnData.wOpCode = GU_OBJECT_CREATE;
			spawnData.wPacketSize = sizeof(SpawnNPC) - 2;


			spawnData.CurEP = pNPCTblData->wBasic_EP;
			spawnData.CurLP = pNPCTblData->wBasic_LP;
			HOBJECT handle = sWorld.AcquireSerialId();
			spawnData.Handle = handle;

			//spawnData.Level = pNPCTblData->byLevel;
			spawnData.MaxEP = pNPCTblData->wBasic_EP;
			spawnData.MaxLP = pNPCTblData->wBasic_LP;
			spawnData.Size = 10;
			spawnData.OBJType = OBJTYPE_NPC;
			spawnData.Tblidx = NPCTblidx;

			spawnData.fLastWalkingSpeed = 10;
			spawnData.fLastRunningSpeed = 10;
			spawnData.fLastAirSpeed = 10;
			spawnData.fLastAirDashSpeed = 10;
			spawnData.fLastAirDashAccelSpeed = 10;

			spawnData.State.sCharStateBase.aspectState.sAspectStateBase.byAspectStateId = 255;
			spawnData.State.sCharStateBase.vCurLoc.x = spawnTbl->vSpawn_Loc.x;// _player->m_position.x + rand() % 5;
			spawnData.State.sCharStateBase.vCurLoc.y = spawnTbl->vSpawn_Loc.y;//_player->m_position.y;
			spawnData.State.sCharStateBase.vCurLoc.z = spawnTbl->vSpawn_Loc.z;//_player->m_position.z + rand() % 5;
			spawnData.State.sCharStateBase.vCurDir.x = spawnTbl->vSpawn_Dir.x;//_player->m_rotation.x + rand() % 5;
			spawnData.State.sCharStateBase.vCurDir.y = spawnTbl->vSpawn_Dir.y;// _player->m_rotation.y;
			spawnData.State.sCharStateBase.vCurDir.z = spawnTbl->vSpawn_Dir.z;//_player->m_rotation.z + rand() % 5;
			spawnData.State.sCharStateBase.byStateID = eCHARSTATE::CHARSTATE_SPAWNING;

			//	sWorld.SendToAll((char*)&spawnData, sizeof(SpawnMOB));
			//Need Insert In list
			Npc* created_Npc = new Npc;
			if (pNPCTblData)
			{
				if (created_Npc->Create(pNPCTblData, spawnData) == true)
				{
					created_Npc->GetMapRef().link(this->_player->GetMap(), created_Npc);
					printf("Npc ID %d inserted into map", NPCTblidx);
					//_player->GetAttributesManager()->lastNPCQuest = INVALID_TBLIDX;
				}
				else
					delete created_Npc;
			}
			return handle;
		}

		return INVALID_TBLIDX;
	}
	return INVALID_TBLIDX;
}

HOBJECT WorldSession::SpawnMobForQuest(TBLIDX mobTblidx, TBLIDX NPCSpawnTblidx, int index)
{
	MobTable* MobTable = sTBM.GetMobTable();
	sMOB_TBLDAT* pMOBTblData = reinterpret_cast<sMOB_TBLDAT*>(MobTable->FindData(mobTblidx));
	if (pMOBTblData != NULL)
	{
		std::vector<TBLIDX> spawnIdxs;
		if (NPCSpawnTblidx != 0)
		{
			spawnIdxs = sTBM.GetNpcSpawnTable(_player->GetWorldID())->FindSpawnByObjectTblidx(NPCSpawnTblidx);
		}
		else
		{
			//spawnIdxs = sTBM.GetMobSpawnTable(_player->GetWorldID())->FindSpawnByObjectTblidx(mobTblidx);
		}

		/*for (std::vector<TBLIDX>::size_type spI = 0; spI != spawnIdxs.size(); spI++)
		{
			sSPAWN_TBLDAT* spawnTblTest = (sSPAWN_TBLDAT*)sTBM.GetMobSpawnTable(_player->GetWorldID())->FindData(spawnIdxs[spI]);
			sLog.outDebug("Spawn %d (%f %f %f)", spawnTblTest->tblidx, spawnTblTest->vSpawn_Loc.x, spawnTblTest->vSpawn_Loc.y, spawnTblTest->vSpawn_Loc.z);
		}*/

		sSPAWN_TBLDAT* spawnTbl;
		sVECTOR3 position;
		sVECTOR3 direction;

		if (NPCSpawnTblidx != 0)
		{

			int newIndex = index;

			if (spawnIdxs.size() <= 0)
			{
				sLog.outDebug("INVALID_TBLIDX MOB SPAWN QUEST");
				return INVALID_TBLIDX;
			}
			else if (newIndex > (spawnIdxs.size() - 1))
			{
				newIndex = spawnIdxs.size() - 1;
			}

			spawnTbl = (sSPAWN_TBLDAT*)sTBM.GetNpcSpawnTable(_player->GetWorldID())->FindData(spawnIdxs[newIndex]);
			if (spawnTbl)
			{
				position.x = spawnTbl->vSpawn_Loc.x;
				position.y = spawnTbl->vSpawn_Loc.y;
				position.z = spawnTbl->vSpawn_Loc.z;

				direction.x = spawnTbl->vSpawn_Dir.x;
				direction.y = spawnTbl->vSpawn_Dir.y;
				direction.z = spawnTbl->vSpawn_Dir.z;
			}
			else
			{
				sLog.outDebug("INVALID_TBLIDX SPAWN NOT FOUND");
				return INVALID_TBLIDX;
			}
			
		}
		else
		{
			//spawnTbl = (sSPAWN_TBLDAT*)sTBM.GetMobSpawnTable(_player->GetWorldID())->FindData(spawnIdxs[newIndex]);
			position.x = _player->m_position.x + rand() % 5;
			position.y = _player->m_position.y;
			position.z = _player->m_position.z + rand() % 5;

			direction.x = _player->m_rotation.x + rand() % 5;
			direction.y = _player->m_rotation.y;
			direction.z = _player->m_rotation.z + rand() % 5;
		}

		//if (spawnTbl)
		//{
		SpawnMOB spawnData;
		memset(&spawnData, 0, sizeof(SpawnMOB));

		spawnData.wOpCode = GU_OBJECT_CREATE;
		spawnData.wPacketSize = sizeof(SpawnMOB) - 2;


		spawnData.curEP = pMOBTblData->wBasic_EP;
		spawnData.curLP = pMOBTblData->wBasic_LP;
		HOBJECT handle = sWorld.AcquireSerialId();
		spawnData.Handle = handle;

		spawnData.Level = pMOBTblData->byLevel;
		spawnData.maxEP = pMOBTblData->wBasic_EP;
		spawnData.maxLP = pMOBTblData->wBasic_LP;
		spawnData.Size = 10;
		spawnData.Type = OBJTYPE_MOB;
		spawnData.Tblidx = mobTblidx;

		spawnData.fLastWalkingSpeed = 2;
		spawnData.fLastRunningSpeed = 2;
		spawnData.fLastAirgSpeed = 2;
		spawnData.fLastAirgDashSpeed = 2;
		spawnData.fLastAirgDashAccelSpeed = 2;

		spawnData.State.sCharStateBase.aspectState.sAspectStateBase.byAspectStateId = 255;
		spawnData.State.sCharStateBase.vCurLoc.x = position.x;
		spawnData.State.sCharStateBase.vCurLoc.y = position.y;
		spawnData.State.sCharStateBase.vCurLoc.z = position.z;
		spawnData.State.sCharStateBase.vCurDir.x = direction.x;
		spawnData.State.sCharStateBase.vCurDir.y = direction.y;
		spawnData.State.sCharStateBase.vCurDir.z = direction.z;
		spawnData.State.sCharStateBase.byStateID = eCHARSTATE::CHARSTATE_SPAWNING;

		//	sWorld.SendToAll((char*)&spawnData, sizeof(SpawnMOB));
		//Need Insert In list
		Mob* created_mob = new Mob;
		if (pMOBTblData)
		{
			if (created_mob->Create(pMOBTblData, spawnData) == true)
			{
				created_mob->GetMapRef().link(this->_player->GetMap(), created_mob);
				sLog.outDebug("--------------MOB QUEST ----------------");
				sLog.outDebug("Mob ID %d inserted into map", mobTblidx);
				_player->GetAttributesManager()->sPawnMobQuest = false;
			}
			else
				delete created_mob;
		}
		return handle;
		//}
		//sLog.outDebug("INVALID_TBLIDX SPAWN NOT FOUND");
		//return INVALID_TBLIDX;
	}
	sLog.outDebug("INVALID_TBLIDX MOB NOT FOUND");
	return INVALID_TBLIDX;
}

void WorldSession::SendQuestSVRevtUpdateNotify(NTL_TS_T_ID tid, NTL_TS_TC_ID tcId, NTL_TS_TA_ID taId, BYTE svrEvtType, BYTE slot, uSTOC_EVT_DATA*evtData)
{
	sGU_QUEST_SVREVT_UPDATE_NFY update;
	update.wOpCode = GU_QUEST_SVREVT_UPDATE_NFY;
	update.wPacketSize = sizeof(sGU_QUEST_SVREVT_UPDATE_NFY) - 2;
	update.tId = tid;
	update.tcId = tcId;
	update.taId = taId;
	update.bySvrEvtType = svrEvtType;
	update.bySlot = slot;
	
	switch (svrEvtType)
	{
		case eSTOC_EVT_DATA_TYPE_MOB_KILL_CNT:
		{
			update.uEvtData.sMobKillCnt.nCurMobCnt = evtData->sMobKillCnt[slot].nCurMobCnt;
			break;
		}
		case eSTOC_EVT_DATA_TYPE_MOB_KILL_ITEM_CNT:
		{
			update.uEvtData.sMobKillItemCnt.nCurMobLICnt = evtData->sMobKillItemCnt[slot].nCurMobLICnt;
			break;
		}
		case eSTOC_EVT_DATA_TYPE_DELIVERY_ITEM:
		{
			update.uEvtData.sDeliveryItemCnt.nCurItemCnt = evtData->sDeliveryItemCnt[slot].nCurItemCnt;
			break;
		}
		case eSTOC_EVT_DATA_TYPE_OBJECT_ITEM:
		{
			update.uEvtData.sObjectItemCnt.nCurItemCnt = evtData->sObjectItemCnt[slot].nCurItemCnt;
			break;
		}
		case eSTOC_EVT_DATA_TYPE_PUBLIC_MOB_ITEM_CNT:
		{
			update.uEvtData.sPublicMobItemCnt.nCurItemCnt = evtData->sPublicMobItemCnt[slot].nCurItemCnt;
			break;
		}
		case eSTOC_EVT_DATA_TYPE_CUSTOM_EVT_CNT:
		{
			update.uEvtData.sCustomEvtCnt.nCurCnt = evtData->sCustomEvtCnt[slot].nCurCnt;
			break;
		}
		case eSTOC_EVT_DATA_TYPE_VISIT:
		{
			update.uEvtData.sVisitEvt.bCompleted = evtData->sVisitEvt[slot].bCompleted;
			break;
		}
	}


	SendPacket((char*)&update, sizeof(sGU_QUEST_SVREVT_UPDATE_NFY));
}

void WorldSession::SendQuestSVRevtStartNotify(NTL_TS_T_ID tid, NTL_TS_TC_ID tcId, NTL_TS_TA_ID taId)
{
	sGU_QUEST_SVREVT_START_NFY start;
	start.wOpCode = GU_QUEST_SVREVT_START_NFY;
	start.wPacketSize = sizeof(sGU_QUEST_SVREVT_START_NFY) - 2;
	start.tId = tid;
	start.tcId = tcId;
	start.taId = taId;
	SendPacket((char*)&start, sizeof(sGU_QUEST_SVREVT_START_NFY));
}

void WorldSession::SendQuestSVRevtEndNotify(NTL_TS_T_ID tid, NTL_TS_TC_ID tcId, NTL_TS_TA_ID taId)
{
	sGU_QUEST_SVREVT_END_NFY end;
	end.wOpCode = GU_QUEST_SVREVT_END_NFY;
	end.wPacketSize = sizeof(sGU_QUEST_SVREVT_END_NFY) - 2;
	end.tId = tid;
	end.tcId = tcId;
	end.taId = taId;
	SendPacket((char*)&end, sizeof(sGU_QUEST_SVREVT_END_NFY));
}

 void WorldSession::SendQuestCompleteInfo()
{
	sGU_AVATAR_QUEST_COMPLETE_INFO info;
	memset(&info, 0, sizeof sGU_AVATAR_QUEST_COMPLETE_INFO);
    info.wOpCode = GU_AVATAR_QUEST_COMPLETE_INFO;
    info.wPacketSize = sizeof(sGU_AVATAR_QUEST_COMPLETE_INFO) -2;

	sDB.LoadQuestComplete(_player->charid, &info.completeInfo);
	//info.completeInfo.abyQCInfo[0] = 0;

    SendPacket((char*)&info, sizeof sGU_AVATAR_QUEST_COMPLETE_INFO);
}

 void WorldSession::SendQuestProgressInfo()
 {
	 sGU_AVATAR_QUEST_PROGRESS_INFO info;
	 memset(&info, 0, sizeof sGU_AVATAR_QUEST_PROGRESS_INFO);
	 info.wOpCode = GU_AVATAR_QUEST_PROGRESS_INFO;
	 info.wPacketSize = sizeof sGU_AVATAR_QUEST_PROGRESS_INFO -2; 

	 //int test[10];

	 info.byProgressCount = 2;

	 info.progressInfo[0].byVer = 0;
	 info.progressInfo[0].tId = 811;
	 info.progressInfo[0].uData.sQInfoV0.unknown = 0;
	 info.progressInfo[0].uData.sQInfoV0.wQState = 0;
	 info.progressInfo[0].uData.sQInfoV0.sMainTSP.tcCurId = 3;
	 info.progressInfo[0].uData.sQInfoV0.sMainTSP.tcPreId = 2;
	 info.progressInfo[0].uData.sQInfoV0.sSToCEvtData.tcId = 2;
	 info.progressInfo[0].uData.sQInfoV0.sSToCEvtData.taId = 3;

	 info.progressInfo[0].uData.sQInfoV0.sSToCEvtData.m_aUserData[0] = 1;
	 info.progressInfo[0].uData.sQInfoV0.sSToCEvtData.m_aUserData[1] = 2;
	 info.progressInfo[0].uData.sQInfoV0.sSToCEvtData.m_aUserData[2] = 3;
	 info.progressInfo[0].uData.sQInfoV0.sSToCEvtData.m_aUserData[3] = 0;

	 info.progressInfo[0].uData.sQInfoV0.tgExcCGroup = 0;
	 info.progressInfo[0].uData.sQInfoV0.tcQuestInfo = 2;
	 info.progressInfo[0].uData.sQInfoV0.taQuestInfo = 1;

	 for (int i = 0; i < info.progressInfo[0].uData.sQInfoV0.sSSM.eSTORAGE_SLOT_MEMORY_MAX; i++)
	 {
		 info.progressInfo[0].uData.sQInfoV0.sSSM.auiSSM[i] = -1;
	 }
	
	 
	 for (int i = 0; i < info.progressInfo[0].uData.sQInfoV0.sETSlot.eTIMER_SLOT_MAX; i++)
	 {
		 info.progressInfo[0].uData.sQInfoV0.sETSlot.asExceptTimer[i].taId = -1;
		 info.progressInfo[0].uData.sQInfoV0.sETSlot.asExceptTimer[i].tcId = -1;
		 info.progressInfo[0].uData.sQInfoV0.sETSlot.asExceptTimer[i].uiRemainTime = 0;
	 }

	 // second quest
	 info.progressInfo[1].byVer = 0;
	 info.progressInfo[1].tId = 1256;
	 info.progressInfo[1].uData.sQInfoV0.unknown = 0;//1;
	 info.progressInfo[1].uData.sQInfoV0.wQState = 0;//32;
	 info.progressInfo[1].uData.sQInfoV0.sMainTSP.tcCurId = 3;
	 info.progressInfo[1].uData.sQInfoV0.sMainTSP.tcPreId = 2;
	 info.progressInfo[1].uData.sQInfoV0.sSToCEvtData.tcId = 2;
	 info.progressInfo[1].uData.sQInfoV0.sSToCEvtData.taId = 3;

	 info.progressInfo[1].uData.sQInfoV0.sSToCEvtData.m_aUserData[0] = 0;
	 info.progressInfo[1].uData.sQInfoV0.sSToCEvtData.m_aUserData[1] = 0;
	 info.progressInfo[1].uData.sQInfoV0.sSToCEvtData.m_aUserData[2] = 0;
	 info.progressInfo[1].uData.sQInfoV0.sSToCEvtData.m_aUserData[3] = 0;

	 info.progressInfo[1].uData.sQInfoV0.tgExcCGroup = 0;
	 info.progressInfo[1].uData.sQInfoV0.tcQuestInfo = 2;
	 info.progressInfo[1].uData.sQInfoV0.taQuestInfo = 1;

	 for (int i = 0; i < info.progressInfo[1].uData.sQInfoV0.sSSM.eSTORAGE_SLOT_MEMORY_MAX; i++)
	 {
		 info.progressInfo[1].uData.sQInfoV0.sSSM.auiSSM[i] = -1;
	 }


	 for (int i = 0; i < info.progressInfo[1].uData.sQInfoV0.sETSlot.eTIMER_SLOT_MAX; i++)
	 {
		 info.progressInfo[1].uData.sQInfoV0.sETSlot.asExceptTimer[i].taId = -1;
		 info.progressInfo[1].uData.sQInfoV0.sETSlot.asExceptTimer[i].tcId = -1;
		 info.progressInfo[1].uData.sQInfoV0.sETSlot.asExceptTimer[i].uiRemainTime = 0;
	 }

	 info.progressInfo[1].uData.sQInfoV0.sETSlot.asExceptTimer[0].tcId = 2;
	 info.progressInfo[1].uData.sQInfoV0.sETSlot.asExceptTimer[0].taId = 4;
	 info.progressInfo[1].uData.sQInfoV0.sETSlot.asExceptTimer[0].uiRemainTime = 1795297;
	 

	 SendPacket((char*)&info, sizeof sGU_AVATAR_QUEST_PROGRESS_INFO);
 }

 void WorldSession::SendQuestGiveUp(Packet& packet)
 {
	 sUG_QUEST_GIVEUP_REQ* req = (sUG_QUEST_GIVEUP_REQ*)packet.GetPacketBuffer();

	 sGU_QUEST_GIVEUP_RES res;
	 memset(&res, 0, sizeof sGU_QUEST_GIVEUP_RES);

	 res.wOpCode = GU_QUEST_GIVEUP_RES;
	 res.wPacketSize = sizeof(sGU_QUEST_GIVEUP_RES) - 2;
	 res.tId = req->tId;
	 res.wResultCode = RESULT_SUCCESS;

	 for (int i = 0; i < 30; i++)
	 {
		 if (_player->GetAttributesManager()->QuestDat[i].QuestID == req->tId)
		 {
			 if (_player->GetAttributesManager()->QuestDat[i].npcClick != INVALID_TBLIDX && _player->GetAttributesManager()->lastNPCQuest != INVALID_TBLIDX)
			 {
				 if (_player->GetAttributesManager()->QuestDat[i].npcClick == _player->GetAttributesManager()->lastNPCQuest)
				 {
					 if (SpawnNPCForQuest(_player->GetAttributesManager()->QuestDat[i].npcClick, 0) != INVALID_TBLIDX)
					 {
						 if (_player->GetAttributesManager()->QuestDat[i].mobHandle != INVALID_TBLIDX && _player->GetAttributesManager()->QuestDat[i].mobHandle != 0)
						 {
							 Mob* curr_Mob = static_cast<Mob*>(_player->GetFromList(_player->GetAttributesManager()->QuestDat[i].mobHandle));
							 sLog.outDebug("Conver MOB to NPC %d %d", curr_Mob->GetMobData().MonsterID, _player->GetAttributesManager()->lastNPCQuest);
							 sGU_OBJECT_DESTROY sPacket;

							 sPacket.wOpCode = GU_OBJECT_DESTROY;
							 sPacket.handle = curr_Mob->GetHandle();
							 sPacket.wPacketSize = sizeof(sGU_OBJECT_DESTROY) - 2;

							 _player->SendPacket((char*)&sPacket, sizeof(sGU_OBJECT_DESTROY));
							 //curr_Npc->RemoveFromWorld();
							 curr_Mob->RemoveFromWorld();
							 _player->RemoveFromList(*curr_Mob);
							 _player->GetAttributesManager()->lastNPCQuest = INVALID_TBLIDX;
							 
						 }
						 break;
					 }
				 }
			 }
		 }
	 }

	 SendPacket((char*)&res, sizeof sGU_QUEST_GIVEUP_RES);
 }

 void WorldSession::SendQuestItemDelete(Packet& packet)
 {
	 sUG_QUEST_ITEM_DELETE_REQ* req = (sUG_QUEST_ITEM_DELETE_REQ*)packet.GetPacketBuffer();

	 sGU_QUEST_ITEM_DELETE_RES res;
	 res.wOpCode = GU_QUEST_ITEM_DELETE_RES;
	 res.wPacketSize = sizeof(sGU_QUEST_ITEM_DELETE_RES) - 2;
	 res.wResultCode = GAME_SUCCESS;
	 res.byDeletePos = req->byDeletePos;

	 SendQuestItemDeleteNfy(req->byDeletePos);

	 SendPacket((char*)&res, sizeof sGU_QUEST_ITEM_DELETE_RES);
 }

 void WorldSession::SendQuestItemDeleteNfy(BYTE pos)
 {
	 sGU_QUEST_ITEM_DELETE_NFY nfy;
	 nfy.wOpCode = GU_QUEST_ITEM_DELETE_NFY;
	 nfy.wPacketSize = sizeof(sGU_QUEST_ITEM_DELETE_NFY) - 2;
	 nfy.byDeletePos = pos;
	 SendPacket((char*)&nfy, sizeof(sGU_QUEST_ITEM_DELETE_NFY));
 }

 void WorldSession::SendQuestItemUpdateNfy(BYTE pos, BYTE count)
 {
	 sGU_QUEST_ITEM_UPDATE_NFY nfy;
	 nfy.wOpCode = GU_QUEST_ITEM_UPDATE_NFY;
	 nfy.wPacketSize = sizeof(sGU_QUEST_ITEM_UPDATE_NFY) - 2;
	 nfy.byPos = pos;
	 nfy.byCurCount = count;
	 SendPacket((char*)&nfy, sizeof(sGU_QUEST_ITEM_UPDATE_NFY));
 }

 void WorldSession::SendQuestItemMove(Packet& packet)
 {
	 sUG_QUEST_ITEM_MOVE_REQ* req = (sUG_QUEST_ITEM_MOVE_REQ*)packet.GetPacketBuffer();

	 sGU_QUEST_ITEM_MOVE_RES res;
	 res.wOpCode = GU_QUEST_ITEM_MOVE_RES;
	 res.wPacketSize = sizeof(sGU_QUEST_ITEM_MOVE_RES) - 2;
	 res.wResultCode = GAME_SUCCESS;

	 res.bySrcPos = req->bySrcPos;
	 res.dwSrcTblidx = 427;
	 res.byDestPos = req->byDestPos;
	 res.dwSrcTblidx = INVALID_TBLIDX;

	 SendPacket((char*)&res, sizeof(sGU_QUEST_ITEM_MOVE_RES));
 }

 void WorldSession::SendQuestItemCreate(BYTE pos, TBLIDX itemTblidx, BYTE count)
 {
	 sGU_QUEST_ITEM_CREATE_NFY nfy;
	 nfy.wOpCode = GU_QUEST_ITEM_CREATE_NFY;
	 nfy.wPacketSize = sizeof(sGU_QUEST_ITEM_CREATE_NFY) - 2;

	 nfy.byPos = pos;
	 nfy.qItemTblidx = itemTblidx;
	 nfy.byCurCount = count;

	 SendPacket((char*)&nfy, sizeof(sGU_QUEST_ITEM_CREATE_NFY));
 }

 void WorldSession::SendQuestInventoryInfo()
 {
	 sGU_AVATAR_QUEST_INVENTORY_INFO info;
	 info.wOpCode = GU_AVATAR_QUEST_INVENTORY_INFO;
	 info.wPacketSize = sizeof(sGU_AVATAR_QUEST_INVENTORY_INFO) - 2;
	 info.byItemCount = 2;
	 info.aInventoryInfo[0].tblidx = 568;
	 info.aInventoryInfo[0].byPos = 0;
	 info.aInventoryInfo[0].byCurStackCount = 2;

	 info.aInventoryInfo[1].tblidx = 1288;
	 info.aInventoryInfo[1].byPos = 1;
	 info.aInventoryInfo[1].byCurStackCount = 3;
	 
	 SendPacket((char*)&info, sizeof(sGU_AVATAR_QUEST_INVENTORY_INFO));
 }

 ResultCodes WorldSession::FindObjectTriggerInformation(QuestData* questData, HOBJECT hTarget, TBLIDX objTblidx)
 {
	 NTL_TS_TC_ID nextLink = 0;
	 CNtlTSGroup * groupTS = sTSM.FindObjectFromTS(questData->QuestID)->GetGroup(NTL_TS_MAIN_GROUP_ID);
	 int countSteps = groupTS->GetNumOfChildCont();
	 sLog.outDebug("count %d", countSteps);
	 for (int curEnt = 0; curEnt < countSteps; curEnt++)
	 {

		 if (nextLink == -1)
		 {
			 break;
		 }

		 CNtlTSCont* contBase = groupTS->GetChildCont(nextLink);
		 if (contBase == NULL)
		 {
			 continue;
		 }

		 sLog.outDebug("Nombre %s cid %d", contBase->GetClassNameW(), nextLink);

		 switch (contBase->GetEntityType())
		 {
			 case DBO_CONT_TYPE_ID_CONT_START:
			 {
				 CDboTSContStart* contStart = ((CDboTSContStart*)contBase);
				 nextLink = contStart->GetYesLinkID();
				 if (contStart == NULL)
				 {
					 return RESULT_FAIL;
				 }
				 for (int i = 0; i < contStart->GetNumOfChildEntity(); i++)
				 {
					 sLog.outDetail("Cont: %s %d", contStart->GetChildEntity(i)->GetClassNameW(), contStart->GetChildEntity(i)->GetEntityType());
					 switch (contStart->GetChildEntity(i)->GetEntityType())
					 {
						 case DBO_COND_TYPE_ID_CHECK_OBJITEM:
						 {
							 CDboTSCheckObjItem* checkObjItem = ((CDboTSCheckObjItem*)contStart->GetChildEntity(i));
							 if (checkObjItem)
							 {
								 sLog.outDebug("QuestId %d", checkObjItem->GetQuestId());
							 }
							 break;
						 }
						 case DBO_EVENT_TYPE_ID_CLICK_OBJECT:
						 {
							 CDboTSClickObject* clickObject = ((CDboTSClickObject*)contStart->GetChildEntity(i));
							 if (clickObject)
							 {
								 sLog.outDebug("WorldIdx %d num %d has(%d)? %d", 
									 clickObject->GetWorldIdx(), clickObject->GetNumOfObjectIdx(), objTblidx, clickObject->HasObjectIdx(objTblidx));

								 if (clickObject->HasObjectIdx(objTblidx))
								 {
									 contStart->GetYesLinkID();
								 }
								 else
								 {
									 return RESULT_FAIL;
								 }
							 }
							 break;
						 }
						 case DBO_COND_TYPE_ID_CHECK_ATTACH_OBJ:
						 {
							 CDboTSCheckAttachObj* attachObj = ((CDboTSCheckAttachObj*)contStart->GetChildEntity(i));
							 if (attachObj)
							 {
								 sLog.outDebug("Num obj %d world %d", attachObj->GetNumOfObjectIdx(), attachObj->GetWorldIdx(), attachObj->HasObjectIdx(objTblidx));

								 if (attachObj->HasObjectIdx(objTblidx))
								 {
									 contStart->GetYesLinkID();
								 }
								 else
								 {
									 return RESULT_FAIL;
								 }
							 }
							 break;
						 }
						 case DBO_COND_TYPE_ID_CHECK_CUSTOMEVENT:
						 {
							 CDboTSCheckCustomEvent* customEvent = ((CDboTSCheckCustomEvent*)contStart->GetChildEntity(i));
							 if (customEvent)
							 {
								 sLog.outDebug("Quest idx %d", customEvent->GetQuestID());
							 }
							 break;
						 }
						 case DBO_COND_TYPE_ID_CHECK_ITEM:
						 {
							 CDboTSCheckItem* checkItem = ((CDboTSCheckItem*)contStart->GetChildEntity(i));
							 if (checkItem)
							 {
								 sLog.outDebug("Item tblidx %d count %d", checkItem->GetItemIdx(), checkItem->GetItemCnt());
							 }
							 break;
						 }
					 }
				 }
				 break;
			 }
			 case DBO_CONT_TYPE_ID_CONT_GACT:
			 {
				 CDboTSContGAct* contAct = ((CDboTSContGAct*)contBase);
				 nextLink = contAct->GetNextLinkID();
				 if (contAct == NULL)
				 {
					 continue;
				 }
				 for (int i = 0; i < contAct->GetNumOfChildEntity(); i++)
				 {
					 sLog.outDetail("Cont: %s %d", contAct->GetChildEntity(i)->GetClassNameW(), contAct->GetChildEntity(i)->GetEntityType());
					 switch (contAct->GetChildEntity(i)->GetEntityType())
					 {
						 case DBO_ACT_TYPE_ID_ACT_OPERATEOBJECT:
						 {
							 CDboTSActOPObject* opObject = ((CDboTSActOPObject*)contAct->GetChildEntity(i));
							 if (opObject)
							 {
								 if (opObject->GetDirectionTableIndex() != INVALID_TBLIDX)
								 {
									 _player->GetState()->sCharStateDetail.sCharStateOperating.hTargetObject = hTarget;
									 _player->GetState()->sCharStateDetail.sCharStateOperating.dwOperateTime = opObject->GetOperateTime();
									 _player->GetState()->sCharStateDetail.sCharStateOperating.directTblidx = opObject->GetDirectionTableIndex();
									 _player->UpdateState(eCHARSTATE::CHARSTATE_OPERATING);
									 sLog.outDebug("DirTblidx %d time %d", opObject->GetDirectionTableIndex(), opObject->GetOperateTime());

									 // testing timer https://www.fluentcpp.com/2018/12/28/timer-cpp/

									 Timer.setTimeout([&]() {
										 _player->UpdateState(eCHARSTATE::CHARSTATE_STANDING);
										 }, opObject->GetOperateTime());
								 }
								 
							 }
							 break;
						 }
						 case DBO_ACT_TYPE_ID_ACT_CUSTOMEVT:
						 {
							 CDboTSActCustomEvt * customEvt = ((CDboTSActCustomEvt*)contAct->GetChildEntity(i));
							 if (customEvt)
							 {
								 sLog.outDebug("EVT ID trigger %d quest EVT ID %d", customEvt->GetCustomEvtID(), questData->uEvtData.sCustomEvtCnt[i].uiCustomEvtID);
								 for (int slot = 0; slot < questData->uEvtData.MAX_CUSTOM_EVT_CNT; slot++)
								 {
									 if (questData->uEvtData.sCustomEvtCnt[i].uiCustomEvtID == INVALID_TBLIDX || customEvt->GetCustomEvtID() == INVALID_TBLIDX)
									 {
										 continue;
									 }

									 if (questData->uEvtData.sCustomEvtCnt[i].uiCustomEvtID == customEvt->GetCustomEvtID())
									 {
										 questData->uEvtData.sCustomEvtCnt[i].nCurCnt += 1;
										 SendQuestItemCreate(0, questData->uEvtData.sCustomEvtCnt[i].uiCustomEvtID, 1);
										 SendQuestSVRevtUpdateNotify(questData->QuestID,
											 questData->tcId,
											 questData->taId,
											 questData->evtDataType,
											 slot,
											 &questData->uEvtData);
									 }
								 }
							 }
							 break;
						 }
						 case DBO_ACT_TYPE_ID_ACT_QITEM:
						 {
							 CDboTSActQItem* qItem = ((CDboTSActQItem*)contAct->GetChildEntity(i));
							 if (qItem)
							 {
								 for (int slot = 0; slot < qItem->eMAX_TS_QITEM_COUNT; slot++)
								 {
									 sLog.outError("Init quest tblidx %d trigger tblidx %d",
										 questData->uEvtData.sObjectItemCnt[slot].uiItemIdx, qItem->GetQItemInfo(slot).uiQItemIdx);
									 if (questData->uEvtData.sObjectItemCnt[slot].uiItemIdx == INVALID_TBLIDX || qItem->GetQItemInfo(slot).uiQItemIdx == INVALID_TBLIDX)
									 {
										 continue;
									 }

									 if (questData->uEvtData.sObjectItemCnt[slot].uiItemIdx == qItem->GetQItemInfo(slot).uiQItemIdx)
									 {
										 questData->uEvtData.sObjectItemCnt[slot].nCurItemCnt += qItem->GetQItemInfo(slot).nQItemCnt;

										 SendQuestItemCreate(0, questData->uEvtData.sObjectItemCnt[slot].uiItemIdx, qItem->GetQItemInfo(slot).nQItemCnt);

										 SendQuestSVRevtUpdateNotify(questData->QuestID,
											 questData->tcId,
											 questData->taId,
											 questData->evtDataType,
											 slot,
											 &questData->uEvtData);
										 sLog.outDebug("Type %d Itemidx %d count %d probability %f", qItem->GetQItemType(),
											 qItem->GetQItemInfo(slot).uiQItemIdx, qItem->GetQItemInfo(slot).nQItemCnt, qItem->GetQItemInfo(slot).fProbability);
									 }
									 
								 }
							 }
							 break;
						 }
						 case DBO_ACT_TYPE_ID_ACT_PCCONV:
						 {
							 CDboTSActPCConv* PCConv = ((CDboTSActPCConv*)contAct->GetChildEntity(i));
							 if (PCConv)
							 {
								 sLog.outDebug("Tblidx %d", PCConv->GetConvTblIdx());
								 sGU_TS_PC_DIALOG_NFY nfy;
								 nfy.wOpCode = GU_TS_PC_DIALOG_NFY;
								 nfy.wPacketSize = sizeof(sGU_TS_PC_DIALOG_NFY) - 2;
								 nfy.textTblidx = PCConv->GetConvTblIdx();
								 SendPacket((char*)&nfy, sizeof(sGU_TS_PC_DIALOG_NFY));

							 }
							 break;
						 }
						 case DBO_ACT_TYPE_ID_ACT_TWAITTS:
						 {
							 CDboTSActTWaitTS* waitTs = ((CDboTSActTWaitTS*)contAct->GetChildEntity(i));
							 if (waitTs)
							 {
								 sLog.outDebug("Time %d", waitTs->GetWaitTime());
							 }
							 break;
						 }
						 case DBO_ACT_TYPE_ID_ACT_OBJSTATE:
						 {
							 CDboTSActObjState* objState = ((CDboTSActObjState*)contAct->GetChildEntity(i));
							 if (objState)
							 {
								 sLog.outDebug("Check %d tblidx %d main state %d showHide %d world %d",
									 objState->GetObjectCheckUncheck(), objState->GetObjectIdx(), objState->GetObjectMainState(), objState->GetObjectShowHide(),
									 objState->GetWorldIdx());

								 sGU_TOBJECT_UPDATE_STATE state;
								 state.wOpCode = GU_TOBJECT_UPDATE_STATE;
								 state.wPacketSize = sizeof(sGU_TOBJECT_UPDATE_STATE) - 2;
								 state.handle = hTarget;
								 state.tobjectBrief.objectID = objTblidx;
								 state.tobjectState.byState = 0;
								 state.tobjectState.bySubStateFlag = TOBJECT_SUBSTATE_FLAG_UNSELECT;
								 state.tobjectState.dwStateTime = 1832245140;
								 SendPacket((char*)&state, sizeof(sGU_TOBJECT_UPDATE_STATE));

								 _player->objectHandle = hTarget;
								 _player->objectTblidx = objTblidx;
							 }
							 break;
						 }
					 }
				 }
				 break;
			 }
			 case DBO_CONT_TYPE_ID_CONT_GCOND:
			 {
				 CDboTSContGCond* contCond = ((CDboTSContGCond*)contBase);
				 if (contCond)
				 {
					 nextLink = contCond->GetYesLinkID();
					 for (int i = 0; i < contCond->GetNumOfChildEntity(); i++)
					 {
						 sLog.outDetail("Cont: %s %d", contCond->GetChildEntity(i)->GetClassNameW(), contCond->GetChildEntity(i)->GetEntityType());
						 switch (contCond->GetChildEntity(i)->GetEntityType())
						 {
							 case DBO_COND_TYPE_ID_CHECK_OPERATEOBJECT:
							 {
								 CDboTSCheckOPObject* checkOpObject = ((CDboTSCheckOPObject*)contCond->GetChildEntity(i));
								 break;
							 }
						 }
					 }
				 }
				 break;
			 }
			 case DBO_CONT_TYPE_ID_CONT_END:
			 {
				 CDboTSContEnd* contEnd = ((CDboTSContEnd*)contBase);
				 if (contEnd)
				 {
					 nextLink = -1;
					 sLog.outDebug("next link %d", contEnd->GetNextLinkID());
				 }
				 break;
			 }
		 }
	 }
	 return RESULT_SUCCESS;
 }

 void WorldSession::SendTsExcuteTriggerObject(Packet& packet)
 {
	 sUG_TS_EXCUTE_TRIGGER_OBJECT* req = (sUG_TS_EXCUTE_TRIGGER_OBJECT*)packet.GetPacketBuffer();
	 TBLIDX objTblidx = INVALID_TBLIDX;
	 Map* map = _player->GetMap();
	 //sLog.outDebug("Request handle interaction == %d", req->hTarget);
	 if (map)
	 {
		 WorldObjectRefManager ref = map->GetWorldObject();
		 for (auto reference = ref.begin(); reference != ref.end(); ++reference)
		 {
			 if (reference->getSource()->GetHandle() == req->hTarget)
			 {
				 objTblidx = ((WorldObject*)reference->getSource())->GetTblidx();
				 sLog.outString("FOUNDED object tblidx %d hTarget %d", objTblidx, req->hTarget);

				 for (int i = 0; i <= 30; i++)
				 {
					 //--------------------------------
					 sLog.outDebug("EVT TYPE %d", _player->GetAttributesManager()->QuestDat[i].evtDataType);
					 switch (_player->GetAttributesManager()->QuestDat[i].evtDataType)
					 {
					 case eSTOC_EVT_DATA_TYPE_OBJECT_ITEM:
					 {
						 for (int slot = 0; slot < _player->GetAttributesManager()->QuestDat[i].uEvtData.MAX_OBJECT_ITEM; slot++)
						 {
							 sLog.outDebug("ITEM COUNT %d", _player->GetAttributesManager()->QuestDat[i].uEvtData.sObjectItemCnt[slot].nCurItemCnt);

							 if (_player->GetAttributesManager()->QuestDat[i].QuestID == 0)
							 {
								 continue;
							 }
							 sLog.outError("QUEST ID: %d", _player->GetAttributesManager()->QuestDat[i].QuestID);
							 if (_player->GetAttributesManager()->QuestDat[i].uEvtData.sObjectItemCnt[slot].nCurItemCnt <
								 _player->GetAttributesManager()->QuestDat[i].uEvtData.sObjectItemCnt[slot].nItemCnt)
							 {
								 sLog.outDebug("Item Tblidx %d %d", _player->GetAttributesManager()->QuestDat[i].uEvtData.sObjectItemCnt[slot].uiItemIdx,
									 ((WorldObject*)reference->getSource())->GetTblidx());
								 if (FindObjectTriggerInformation(&_player->GetAttributesManager()->QuestDat[i], req->hTarget, objTblidx) == RESULT_SUCCESS)
								 {
									 sGU_TS_EXCUTE_TRIGGER_OBJECT_RES res;
									 res.wOpCode = GU_TS_EXCUTE_TRIGGER_OBJECT_RES;
									 res.wPacketSize = sizeof(sGU_TS_EXCUTE_TRIGGER_OBJECT_RES) - 2;
									 res.wResultCode = RESULT_SUCCESS;
									 res.hTriggerObject = req->hTarget;
									 SendPacket((char*)&res, sizeof(sGU_TS_EXCUTE_TRIGGER_OBJECT_RES));
									 sLog.outDebug("Item trigger: %d %d %d", res.hTriggerObject, req->hSource, req->hTarget);
									 

									 /*_player->GetState()->sCharStateDetail.sCharStateOperating.hTargetObject = req->hTarget;
									 _player->GetState()->sCharStateDetail.sCharStateOperating.dwOperateTime = 3000;
									 _player->GetState()->sCharStateDetail.sCharStateOperating.directTblidx = 10003;
									 _player->UpdateState(eCHARSTATE::CHARSTATE_OPERATING);*/


									 /*_player->GetAttributesManager()->QuestDat[i].uEvtData.sObjectItemCnt[slot].nCurItemCnt += 1;

									 SendQuestItemCreate(0, _player->GetAttributesManager()->QuestDat[i].uEvtData.sObjectItemCnt[slot].uiItemIdx, 1);

									 SendQuestSVRevtUpdateNotify(_player->GetAttributesManager()->QuestDat[i].QuestID,
										 _player->GetAttributesManager()->QuestDat[i].tcId,
										 _player->GetAttributesManager()->QuestDat[i].taId,
										 _player->GetAttributesManager()->QuestDat[i].evtDataType,
										 slot,
										 _player->GetAttributesManager()->QuestDat[i].uEvtData.sObjectItemCnt[slot].nCurItemCnt);*/

									 /*sGU_QUEST_SVREVT_UPDATE_NFY update;
									 update.wOpCode = GU_QUEST_SVREVT_UPDATE_NFY;
									 update.wPacketSize = sizeof(sGU_QUEST_SVREVT_UPDATE_NFY) - 2;
									 update.tId = 296;
									 update.tcId = 2;
									 update.taId = 3;
									 update.bySvrEvtType = eSTOC_EVT_DATA_TYPE_OBJECT_ITEM;
									 update.bySlot = 0;
									 update.uEvtData.sObjectItemCnt.nCurItemCnt = 1;
									 SendPacket((char*)&update, sizeof(sGU_QUEST_SVREVT_UPDATE_NFY));*/
								 }
							 }
						 }
						 break;
					 }
					 }
				 }

				 //--------------------------------

				 break;
			 }
		 }
	 }
 }