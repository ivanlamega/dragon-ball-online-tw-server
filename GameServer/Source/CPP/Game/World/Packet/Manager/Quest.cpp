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
								sLog.outDebug("ePORTAL_TYPE_GATEWAY");

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
									_player->GetAttributesManager()->teleportInfo.worldInfo.hTriggerObjectOffset = HANDLE_TRIGGER_OBJECT_OFFSET;
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
									_player->GetAttributesManager()->teleportInfo.worldInfo.hTriggerObjectOffset = HANDLE_TRIGGER_OBJECT_OFFSET;
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
	return RESULT_SUCCESS;
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
	/*if (QuestID == 3 || QuestID == 1925)
	{			
		sGU_CHAR_TELEPORT_RES Teleport;
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
		SendPacket((char*)&Teleport, sizeof(sGU_CHAR_TELEPORT_RES));		
	}*/	
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

			//res.wResultCode = result;

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
		/*if (req->tcCurId == 100)//Reward
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
		}*/
		SendPacket((char*)&res, sizeof(sGU_TS_CONFIRM_STEP_RES));
	}
}

ResultCodes WorldSession::ProcessTSContStart(CDboTSContStart * contStart, NTL_TS_T_ID tid)
{
	// Add quest new system
	QuestData newQuest;
	memset(&newQuest, 0, sizeof QuestData);
	newQuest.QuestID = tid;
	newQuest.evtDataType = eSTOC_EVT_DATA_TYPE_INVALID;
	_player->GetQuestManager()->AddQuest(newQuest);
	sLog.outBasic("New quest added");

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
			case DBO_EVENT_TYPE_ID_RCV_SVR_EVT:
			{
				CDboTSRcvSvrEvt* rcvSvrEvt = (CDboTSRcvSvrEvt*)contStart->GetChildEntity(i);
				if (rcvSvrEvt)
				{
					sLog.outDebug("Quest evt id %d", rcvSvrEvt->GetEvtID());

					if (rcvSvrEvt->GetEvtID() == 16200)
					{
						CreateNPCTrunksTLQ1();
					}
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
				QuestData* quest = _player->GetQuestManager()->FindQuestById(tid);
				if (quest)
				{
					quest->lastNPCQuest = NPCConv->GetNPCIdx();
				}
				//_player->GetAttributesManager()->lastNPCQuest = NPCConv->GetNPCIdx();

				if (tcId == 7 && NPCConv->GetNPCIdx() == 4261111)
				{
					TBLIDX worldTblidx = sTBM.GetWorldTable()->FindWorldByLink(tid);
					//Exit of sub class quest world
					if (worldTblidx != INVALID_TBLIDX)
					{
						sWORLD_TBLDAT* worldData = (sWORLD_TBLDAT*)sTBM.GetWorldTable()->FindData(worldTblidx);
						if (worldData)
						{

							_player->GetAttributesManager()->teleportInfo.position.x = worldData->outWorldLoc.x;
							_player->GetAttributesManager()->teleportInfo.position.y = worldData->outWorldLoc.y;
							_player->GetAttributesManager()->teleportInfo.position.z = worldData->outWorldLoc.z;

							_player->GetAttributesManager()->teleportInfo.rotation.x = worldData->outWorldDir.x;
							_player->GetAttributesManager()->teleportInfo.rotation.y = worldData->outWorldDir.y;
							_player->GetAttributesManager()->teleportInfo.rotation.z = worldData->outWorldDir.z;

							_player->GetAttributesManager()->teleportInfo.bIsToMoveAnotherServer = false;
							_player->GetAttributesManager()->teleportInfo.worldInfo.worldID = worldData->outWorldTblidx;
							_player->GetAttributesManager()->teleportInfo.worldInfo.tblidx = worldData->outWorldTblidx;
							_player->GetAttributesManager()->teleportInfo.worldInfo.hTriggerObjectOffset = HANDLE_TRIGGER_OBJECT_OFFSET;
							_player->GetAttributesManager()->teleportInfo.worldInfo.sRuleInfo.byRuleType = worldData->byWorldRuleType;

							sLog.outDebug("Teleport: pos %f %f %f rot %f %f %f worldtblidx %d type %d ruleType %d", _player->GetAttributesManager()->teleportInfo.position.x,
								_player->GetAttributesManager()->teleportInfo.position.y,
								_player->GetAttributesManager()->teleportInfo.position.z,
								_player->GetAttributesManager()->teleportInfo.rotation.x,
								_player->GetAttributesManager()->teleportInfo.rotation.y,
								_player->GetAttributesManager()->teleportInfo.rotation.z,
								_player->GetAttributesManager()->teleportInfo.worldInfo.tblidx,
								-1,
								worldData->byWorldRuleType);
							SendUpdateCharCondition(80);
							_player->GetState()->sCharStateDetail.sCharStateDespawning.byTeleportType = eTELEPORT_TYPE::TELEPORT_TYPE_TIMEQUEST;
							_player->SetState(eCHARSTATE::CHARSTATE_DESPAWNING);

							/*sGU_CHAR_TELEPORT_RES teleport;
							teleport.wResultCode = GAME_SUCCESS;
							teleport.wOpCode = GU_CHAR_TELEPORT_RES;
							teleport.wPacketSize = sizeof(sGU_CHAR_TELEPORT_RES) - 2;

							teleport.bIsToMoveAnotherServer = false;
							teleport.sWorldInfo.worldID = world->outWorldTblidx;
							teleport.sWorldInfo.tblidx = world->outWorldTblidx;
							teleport.sWorldInfo.hTriggerObjectOffset = HANDLE_TRIGGER_OBJECT_OFFSET;
							teleport.sWorldInfo.sRuleInfo.byRuleType = world->byWorldRuleType;
							_player->GetState()->sCharStateDetail.sCharStateTeleporting.byTeleportType = eTELEPORT_TYPE::TELEPORT_TYPE_TIMEQUEST;
							teleport.vNewLoc.x = world->outWorldLoc.x;
							teleport.vNewLoc.y = world->outWorldLoc.y;
							teleport.vNewLoc.z = world->outWorldLoc.z;
							teleport.vNewDir.x = world->outWorldDir.x;
							teleport.vNewDir.y = world->outWorldDir.y;
							teleport.vNewDir.z = world->outWorldDir.z;



							_player->SetState(eCHARSTATE::CHARSTATE_TELEPORTING);


							_player->SetWorldID(teleport.sWorldInfo.worldID);
							_player->SetWorldTableID(teleport.sWorldInfo.tblidx);
							_player->Relocate(teleport.vNewLoc.x, teleport.vNewLoc.y, teleport.vNewLoc.z, teleport.vNewDir.x, teleport.vNewDir.y, teleport.vNewDir.z);

							SendPacket((char*)&teleport, sizeof(sGU_CHAR_TELEPORT_RES));
							Map* map = _player->GetMap();
							map->Remove(_player, false);
							_player->ClearListAndReference();*/
						}
					}
				}

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
				// Add quest new system
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
					// TLQ1 --------------------

					if (sendSvrEvt->GetSvrEvtID() == 16130)
					{
						sOBJECT_TBLDAT* obj = (sOBJECT_TBLDAT*)sTBM.GetObjectTable(120000)->FindData(6);
						if (obj)
						{
							sLog.outDebug("Obj %d %d %s handle %d", obj->tblidx, obj->dwSequence, obj->szModelName, 100000 + obj->dwSequence);
							SendTObjectUpdateState(100000 + obj->dwSequence,
								obj->tblidx, 1, TOBJECT_SUBSTATE_FLAG_SHOW, 2775787718);
						}
					}
					else if (sendSvrEvt->GetSvrEvtID() == 16260)
					{
						ConvertGohanMobNPC(7451107);
					}
					else if (sendSvrEvt->GetSvrEvtID() == 16210)
					{
						Npc* npcInfo = static_cast<Npc*>(_player->GetFromList(_player->GetTarget()));
						if (npcInfo)
						{
							npcInfo->GetState()->sCharStateDetail.sCharStateDirectPlay.byDirectPlayType = DIRECT_PLAY_NORMAL;
							npcInfo->GetState()->sCharStateDetail.sCharStateDirectPlay.directTblidx = 50044;
							npcInfo->UpdateState(eCHARSTATE::CHARSTATE_DIRECT_PLAY);

						}
					}

					if (sendSvrEvt->GetSvrEvtID() == 16040)
					{

						sOBJECT_TBLDAT* obj = (sOBJECT_TBLDAT*)sTBM.GetObjectTable(120000)->FindData(8);
						if (obj)
						{
							sLog.outDebug("Obj %d %d %s handle %d", obj->tblidx, obj->dwSequence, obj->szModelName, 100000 + obj->dwSequence);
							SendTObjectUpdateState(100000 + obj->dwSequence,
								obj->tblidx, 0, 0, 2775787718);
						}

						SendCharDirectPlay(true, 1, 1026);

						
						try {
							Timer.setTimeout([&]() {
								SendTSUpdateEventNfy(TS_TYPE_QUEST_CS, 16050);
								sLog.outDebug("Event send %d", 16050);
								}, 4000);
						}
						catch (int e)
						{
							sLog.outError("Ocurrio un error al enviar el evento.");
						}
					}
					else
					{
						SendTSUpdateEventNfy(TS_TYPE_QUEST_CS, sendSvrEvt->GetSvrEvtID());
						/*sGU_TS_UPDATE_EVENT_NFY nfy;
						nfy.wOpCode = GU_TS_UPDATE_EVENT_NFY;
						nfy.wPacketSize = sizeof(sGU_TS_UPDATE_EVENT_NFY) - 2;
						nfy.byTsType = 0;
						nfy.teid = sendSvrEvt->GetSvrEvtID();
						SendPacket((char*)&nfy, sizeof(sGU_TS_UPDATE_EVENT_NFY));*/
					}
					// TLQ1 --------------------
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
						if (tid == 6002)
						{
							SendQuestSVRevtEndNotify(tid, 2, 2);
						}
						else
						{
							SendQuestSVRevtEndNotify(tid, tcId, sToCEvt->GetActionId());
						}
						
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
							_player->GetQuestManager()->AddItemGiveQuest(createdItem.tblidx, tid);

							if (createdItem.tblidx == 98011)
							{
								/*_player->GetAttributesManager()->growUpInfo.inQuest = true;*/
								_player->GetAttributesManager()->questSubCls.curQuestId = tid;
								//New system
								QuestData* quest = _player->GetQuestManager()->FindQuestById(tid);
								if (quest)
								{
									quest->growUpInfo.inQuest = true;
									quest->questSubCls.curQuestId = tid;
								}
								//New system
							}
							if (createdItem.tblidx == 99096)
							{
								_player->GetAttributesManager()->questSubCls.useItemTblidx = createdItem.tblidx;
								_player->GetAttributesManager()->questSubCls.curQuestId = tid;

								//New system
								QuestData* quest = _player->GetQuestManager()->FindQuestById(tid);
								if (quest)
								{
									quest->questSubCls.useItemTblidx = createdItem.tblidx;
									quest->questSubCls.curQuestId = tid;
								}
								//New system
							}
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
				//New system
				QuestData* quest = _player->GetQuestManager()->FindQuestById(tid);
				if (quest)
				{
					quest->sPawnMobQuest = worldPlayScript->IsStart();
					sLog.outBasic("Newy system spawn mob quest: %d", quest->sPawnMobQuest);
				}
				//New system
				//_player->GetAttributesManager()->sPawnMobQuest = worldPlayScript->IsStart();
				sLog.outDebug("Quest: isStart %d script %d", worldPlayScript->IsStart(), worldPlayScript->GetScriptID());
				// SUB CLASS ---------------------
				if (worldPlayScript->IsStart() && _player->GetWorldTableID() == 800000)// worldPlayScript->GetScriptID() == 6055)
				{
					//New system
					QuestData* quest = _player->GetQuestManager()->FindQuestById(tid);
					if (quest)
					{
						quest->questSubCls.inQuest = true;
						quest->questSubCls.curQuestId = tid;
					}
					//New system

					TBLIDX objTblidx1 = INVALID_TBLIDX;
					TBLIDX objTblidx2 = INVALID_TBLIDX;
					_player->GetAttributesManager()->questSubCls.inQuest = true;
					_player->GetAttributesManager()->questSubCls.curQuestId = tid;
					switch (_player->GetMyClass())
					{
						case ePC_CLASS::PC_CLASS_HUMAN_FIGHTER:
						{
							objTblidx1 = 2;
							objTblidx2 = 3;

							// Swordman
							_player->GetAttributesManager()->questSubCls.objData[0].mobsTblidx.push_back(8471110);
							_player->GetAttributesManager()->questSubCls.objData[0].mobsTblidx.push_back(8471110);
							_player->GetAttributesManager()->questSubCls.objData[0].mobsTblidx.push_back(8471110);
							_player->GetAttributesManager()->questSubCls.objData[0].mobsTblidx.push_back(8471110);
							_player->GetAttributesManager()->questSubCls.objData[0].mobsTblidx.push_back(3604104);

							_player->GetAttributesManager()->questSubCls.objData[0].NPCTblidx.push_back(2804129);

							_player->GetAttributesManager()->questSubCls.objData[0].objTblidx = objTblidx1;
							_player->GetAttributesManager()->questSubCls.objData[0].triggerId = 6005;
							_player->GetAttributesManager()->questSubCls.objData[0].triggerObject = 6013;
							_player->GetAttributesManager()->questSubCls.objData[0].specificQuestId = 6007;
							_player->GetAttributesManager()->questSubCls.objData[0].evtId = 417;

							// Figther
							_player->GetAttributesManager()->questSubCls.objData[1].mobsTblidx.push_back(3411210);
							_player->GetAttributesManager()->questSubCls.objData[1].mobsTblidx.push_back(3411210);
							_player->GetAttributesManager()->questSubCls.objData[1].mobsTblidx.push_back(8411110);
							_player->GetAttributesManager()->questSubCls.objData[1].mobsTblidx.push_back(8411110);
							_player->GetAttributesManager()->questSubCls.objData[1].mobsTblidx.push_back(8411110);
							_player->GetAttributesManager()->questSubCls.objData[1].mobsTblidx.push_back(8411110);
							_player->GetAttributesManager()->questSubCls.objData[1].NPCTblidx.push_back(1751108);

							_player->GetAttributesManager()->questSubCls.objData[1].objTblidx = objTblidx2;
							_player->GetAttributesManager()->questSubCls.objData[1].triggerId = 6001;
							_player->GetAttributesManager()->questSubCls.objData[1].evtId = 416;
							sLog.outDebug("PC_CLASS_HUMAN_FIGHTER");
							break;
						}
						case ePC_CLASS::PC_CLASS_HUMAN_MYSTIC:
						{
							objTblidx1 = 4;
							objTblidx2 = 5;

							// Crane
							_player->GetAttributesManager()->questSubCls.objData[0].mobsTblidx.push_back(4311110);
							_player->GetAttributesManager()->questSubCls.objData[0].NPCTblidx.push_back(3332303);

							_player->GetAttributesManager()->questSubCls.objData[0].objTblidx = objTblidx1;
							_player->GetAttributesManager()->questSubCls.objData[0].triggerId = 6002;
							_player->GetAttributesManager()->questSubCls.objData[0].evtId = 419;

							// Turtle
							_player->GetAttributesManager()->questSubCls.objData[1].mobsTblidx.push_back(5761110);
							_player->GetAttributesManager()->questSubCls.objData[1].NPCTblidx.push_back(3181304);

							_player->GetAttributesManager()->questSubCls.objData[1].objTblidx = objTblidx2;
							_player->GetAttributesManager()->questSubCls.objData[1].triggerId = 6003;
							_player->GetAttributesManager()->questSubCls.objData[1].triggerObject = 6017;
							_player->GetAttributesManager()->questSubCls.objData[1].specificQuestId = 6021;
							_player->GetAttributesManager()->questSubCls.objData[1].evtId = 418;
							sLog.outDebug("PC_CLASS_HUMAN_MYSTIC");
							break;
						}
						case ePC_CLASS::PC_CLASS_HUMAN_ENGINEER:
						{
							sLog.outDebug("PC_CLASS_HUMAN_ENGINEER");
							break;
						}
						case ePC_CLASS::PC_CLASS_NAMEK_FIGHTER:
						{
							objTblidx1 = 6;
							objTblidx2 = 7;

							// Dark warrior
							_player->GetAttributesManager()->questSubCls.objData[0].mobsTblidx.push_back(5791104);
							_player->GetAttributesManager()->questSubCls.objData[0].NPCTblidx.push_back(4511411);

							_player->GetAttributesManager()->questSubCls.objData[0].objTblidx = objTblidx1;
							_player->GetAttributesManager()->questSubCls.objData[0].triggerId = 6006;
							_player->GetAttributesManager()->questSubCls.objData[0].evtId = 420;

							// shadow knight
							_player->GetAttributesManager()->questSubCls.objData[1].mobsTblidx.push_back(5873104);
							_player->GetAttributesManager()->questSubCls.objData[1].NPCTblidx.push_back(4511609);

							_player->GetAttributesManager()->questSubCls.objData[1].objTblidx = objTblidx2;
							_player->GetAttributesManager()->questSubCls.objData[1].triggerId = 6004;
							_player->GetAttributesManager()->questSubCls.objData[1].evtId = 421;
							sLog.outDebug("PC_CLASS_NAMEK_FIGHTER");
							break;
						}
						case ePC_CLASS::PC_CLASS_NAMEK_MYSTIC:
						{
							objTblidx1 = 8;
							objTblidx2 = 9;

							// Dende
							_player->GetAttributesManager()->questSubCls.objData[0].mobsTblidx.push_back(4883104);
							_player->GetAttributesManager()->questSubCls.objData[0].NPCTblidx.push_back(4751109);
							_player->GetAttributesManager()->questSubCls.objData[0].NPCTblidx.push_back(4511515);

							_player->GetAttributesManager()->questSubCls.objData[0].objTblidx = objTblidx1;
							_player->GetAttributesManager()->questSubCls.objData[0].triggerId = 6007;
							_player->GetAttributesManager()->questSubCls.objData[0].evtId = 422;


							// Poco priest
							_player->GetAttributesManager()->questSubCls.objData[1].mobsTblidx.push_back(6651207);
							_player->GetAttributesManager()->questSubCls.objData[1].NPCTblidx.push_back(4751408);

							_player->GetAttributesManager()->questSubCls.objData[1].objTblidx = objTblidx2;
							_player->GetAttributesManager()->questSubCls.objData[1].triggerId = 6008;
							_player->GetAttributesManager()->questSubCls.objData[1].evtId = 423;
							sLog.outDebug("PC_CLASS_NAMEK_MYSTIC");
							break;
						}
						case ePC_CLASS::PC_CLASS_MIGHTY_MAJIN:
						{
							objTblidx1 = 10;
							objTblidx2 = 11;
							// Majin cheff
							_player->GetAttributesManager()->questSubCls.objData[0].mobsTblidx.push_back(8112122);
							_player->GetAttributesManager()->questSubCls.objData[0].NPCTblidx.push_back(4151110);

							_player->GetAttributesManager()->questSubCls.objData[0].objTblidx = objTblidx1;
							_player->GetAttributesManager()->questSubCls.objData[0].triggerId = 6010;
							_player->GetAttributesManager()->questSubCls.objData[0].evtId = 425;

							// Majin ultimate
							_player->GetAttributesManager()->questSubCls.objData[1].mobsTblidx.push_back(8511113);
							_player->GetAttributesManager()->questSubCls.objData[1].NPCTblidx.push_back(4141114);

							_player->GetAttributesManager()->questSubCls.objData[1].objTblidx = objTblidx2;
							_player->GetAttributesManager()->questSubCls.objData[1].triggerId = 6009;
							_player->GetAttributesManager()->questSubCls.objData[1].evtId = 424;
							sLog.outDebug("PC_CLASS_MIGHTY_MAJIN");
							break;
						}
						case ePC_CLASS::PC_CLASS_WONDER_MAJIN:
						{
							objTblidx1 = 12;
							objTblidx2 = 13;

							// Majin Karma
							_player->GetAttributesManager()->questSubCls.objData[0].mobsTblidx.push_back(4131104);
							_player->GetAttributesManager()->questSubCls.objData[0].mobsTblidx.push_back(4131104);
							_player->GetAttributesManager()->questSubCls.objData[0].NPCTblidx.push_back(4261113);
							_player->GetAttributesManager()->questSubCls.objData[0].objTblidx = objTblidx1;
							_player->GetAttributesManager()->questSubCls.objData[0].triggerId = 6012;
							_player->GetAttributesManager()->questSubCls.objData[0].evtId = 427;

							// Majin plasma
							_player->GetAttributesManager()->questSubCls.objData[1].mobsTblidx.push_back(2671101);
							_player->GetAttributesManager()->questSubCls.objData[1].NPCTblidx.push_back(4371315);

							_player->GetAttributesManager()->questSubCls.objData[1].objTblidx = objTblidx2;
							_player->GetAttributesManager()->questSubCls.objData[1].triggerId = 6011;
							_player->GetAttributesManager()->questSubCls.objData[1].evtId = 426;

							//SendTObjectUpdateState();
							sLog.outDebug("PC_CLASS_WONDER_MAJIN");
							break;
						}
					}

					//New System
					if (quest)
					{
						quest->questSubCls.objData[0].objTblidx = objTblidx1;
						quest->questSubCls.objData[1].objTblidx = objTblidx2;
						std::vector<NTL_TS_T_ID> triggerIds = sTSM.FindTriggerByQuest(tid);
						for (int i = 0; i < triggerIds.size(); i++)
						{
							LoadObjectsTriggersForQuest(triggerIds[i], quest->QuestID);
						}
					}
					//New System

					sLog.outDebug("1 Mobs %d NPCs %d", _player->GetAttributesManager()->questSubCls.objData[1].mobsTblidx.size(),
						_player->GetAttributesManager()->questSubCls.objData[1].NPCTblidx.size());
					sLog.outDebug("0 Mobs %d NPCs %d", _player->GetAttributesManager()->questSubCls.objData[0].mobsTblidx.size(),
						_player->GetAttributesManager()->questSubCls.objData[0].NPCTblidx.size());
					sOBJECT_TBLDAT* objData = (sOBJECT_TBLDAT*)sTBM.GetObjectTable(_player->GetWorldTableID())->FindData(objTblidx1);
					if (objData)
					{
						sLog.outDebug("Object %d, %d %s", objData->tblidx, HANDLE_TRIGGER_OBJECT_OFFSET + objData->dwSequence, objData->szModelName);
						SendTObjectUpdateState(HANDLE_TRIGGER_OBJECT_OFFSET + objData->dwSequence,
							objTblidx1, 0, TOBJECT_SUBSTATE_FLAG_SHOW, 3909524734);
					}
					else
					{
						sLog.outDebug("OBJECT NOT FOUND %d", objTblidx1);
					}

					objData = (sOBJECT_TBLDAT*)sTBM.GetObjectTable(_player->GetWorldTableID())->FindData(objTblidx2);
					if (objData)
					{
						sLog.outDebug("Object %d, %d %s", objData->tblidx, HANDLE_TRIGGER_OBJECT_OFFSET + objData->dwSequence, objData->szModelName);
						SendTObjectUpdateState(HANDLE_TRIGGER_OBJECT_OFFSET + objData->dwSequence,
							objTblidx2, 0, TOBJECT_SUBSTATE_FLAG_SHOW, 3909524843);
					}
					else
					{
						sLog.outDebug("OBJECT NOT FOUND %d", objTblidx2);
					}
				}
				// Bypass Temporal hasta reparar quest de dende
				if (worldPlayScript->IsStart() && worldPlayScript->GetScriptID() == 6037)
				{
					//SendQuestForcedCompletionNfy(tid);
					_player->GetAttributesManager()->questSubCls.npcHandle = SpawnNPCByTblidxQuestDende(3174103);
					//New system
					if (quest)
					{
						quest->questSubCls.npcHandle = _player->GetAttributesManager()->questSubCls.npcHandle;
					}
					//New system
					sLog.outDebug("Player handle %d npc handle %d", _player->GetHandle(), _player->GetAttributesManager()->questSubCls.npcHandle);
				}
				// SUB CLASS ---------------------
				// TLQ 1 -----------------------
				if (worldPlayScript->GetScriptID() == 11604)
				{
					sLog.outDebug("NPC HANDLE %d", _player->GetAttributesManager()->tlq1Info.handleNpc);
					ConvertGohanMobNPC(7451101);
				}
				if (worldPlayScript->GetScriptID() == 11603)
				{
					_player->GetAttributesManager()->tlq1Info.handleNpc = CreateNPCGohanTLQ1();
					sLog.outDebug("NPC HANDLE %d", _player->GetAttributesManager()->tlq1Info.handleNpc);
				}
				// TLQ 1 -----------------------
				break;
			}
			case DBO_ACT_TYPE_ID_ACT_DIRINDICATOR:
			{
				CDboTSActDirIndicator* dirIndicator = (CDboTSActDirIndicator*)contGAct->GetChildEntity(i);
				if (dirIndicator)
				{
					sLog.outDebug("Quest indicator type %d", dirIndicator->GetDirectionIndicatorType());
					switch (dirIndicator->GetDirectionIndicatorType())
					{
						case DIRECTION_INDICATE_TYPE_TOBJECT:
						{
							sLog.outDebug("Object tblidx", dirIndicator->GetDirectionIndicatorData().sTObj.uiObjTblIdx);
							sLog.outDebug("DIRECTION_INDICATE_TYPE_TOBJECT");
							break;
						}
						case DIRECTION_INDICATE_TYPE_NPC:
						{
							sLog.outDebug("NPC tblidx", dirIndicator->GetDirectionIndicatorData().sNPC.uiNPCTblIdx);
							sLog.outDebug("DIRECTION_INDICATE_TYPE_NPC");
							break;
						}
						case DIRECTION_INDICATE_TYPE_POINT:
						{
							sLog.outDebug("Pos %f %f %f",
								dirIndicator->GetDirectionIndicatorData().sPos.fX, dirIndicator->GetDirectionIndicatorData().sPos.fY, dirIndicator->GetDirectionIndicatorData().sPos.fZ);
							SendDirectionIndicateNfy(dirIndicator->GetDirectionIndicatorData().sPos.fX,
								dirIndicator->GetDirectionIndicatorData().sPos.fY,
								dirIndicator->GetDirectionIndicatorData().sPos.fZ);
							sLog.outDebug("DIRECTION_INDICATE_TYPE_POINT");
							break;
						}
					}
				}
				break;
			}
			case DBO_ACT_TYPE_ID_ACT_EXCEPT_TIMER_S:
			{
				CDboTSActETimerS* timerS = (CDboTSActETimerS*)contGAct->GetChildEntity(i);
				if (timerS)
				{
					// SUBCLASS
					sLog.outDebug("TGId %d time %d timerSort %d", timerS->GetTGId(), timerS->GetTime(), timerS->GetTimerSort());
					if (tid == 6062)
					{
						Timer.setTimeout([&]() {
							int index = _player->GetAttributesManager()->questSubCls.objChoseIndex;
							SendTSUpdateEventNfy(TS_TYPE_QUEST_CS, _player->GetAttributesManager()->questSubCls.objData[index].evtId);
							}, timerS->GetTime());
					}
					// SUBCLASS
				}
				break;
			}
			case DBO_ACT_TYPE_ID_ACT_AVATAR_DEAD:
			{
				CDboTSActAvatarDead* avatarDead = (CDboTSActAvatarDead*)contGAct->GetChildEntity(i);
				if (avatarDead)
				{
					sLog.outDebug("Start %d", avatarDead->GetStart());
					if (avatarDead->GetStart())
					{

					}
				}
				break;
			}
			case DBO_ACT_TYPE_ID_ACT_TLQ:
			{
				CDboTSActTLQ* tlq = (CDboTSActTLQ*)contGAct->GetChildEntity(i);
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
							_player->GetAttributesManager()->teleportInfo.worldInfo.hTriggerObjectOffset = HANDLE_TRIGGER_OBJECT_OFFSET;
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

							QuestData* quest = _player->GetQuestManager()->FindQuestById(tid);
							if (quest)
							{
								switch (tlq->GetDungeonTblIdx())
								{
									//Swordman
									case 201:
									{
										quest->questSubCls.objData[0].mobsTblidx.push_back(8471110);
										quest->questSubCls.objData[0].mobsTblidx.push_back(8471110);
										quest->questSubCls.objData[0].mobsTblidx.push_back(8471110);
										quest->questSubCls.objData[0].mobsTblidx.push_back(8471110);
										quest->questSubCls.objData[0].mobsTblidx.push_back(3604104);

										quest->questSubCls.objData[0].NPCTblidx.push_back(2804129);
										quest->questSubCls.objData[0].evtId = 417;
										break;
									}
									//Figther
									case 202:
									{
										
										quest->questSubCls.objData[0].mobsTblidx.push_back(3411210);
										quest->questSubCls.objData[0].mobsTblidx.push_back(3411210);
										quest->questSubCls.objData[0].mobsTblidx.push_back(8411110);
										quest->questSubCls.objData[0].mobsTblidx.push_back(8411110);
										quest->questSubCls.objData[0].mobsTblidx.push_back(8411110);
										quest->questSubCls.objData[0].mobsTblidx.push_back(8411110);
										quest->questSubCls.objData[0].NPCTblidx.push_back(1751108);
										quest->questSubCls.objData[0].evtId = 416;
										break;
									}
									//Crane
									case 204:
									{
										quest->questSubCls.objData[0].mobsTblidx.push_back(4311110);
										quest->questSubCls.objData[0].NPCTblidx.push_back(3332303);

										quest->questSubCls.objData[0].evtId = 419;
										break;
									}

								}

								if (quest->questSubCls.objData[0].mobsTblidx.size() > 0)
								{
									quest->questSubCls.inQuest = true;
								}
							}

							


							// Spawn mobs for sub class quest
							Timer.setIntervalArg([&](NTL_TS_T_ID questId) {
									sLog.outBasic("Check if player is ready %d", questId);
									if (_player->GetIsReady())
									{
										QuestData* quest = _player->GetQuestManager()->FindQuestById(questId);
										if (quest)
										{
											std::vector<TBLIDX> mobs = quest->questSubCls.objData[0].mobsTblidx;
											std::vector<TBLIDX> NPCs = quest->questSubCls.objData[0].NPCTblidx;
											sLog.outBasic("New System: ----------SPAWN MOBS FOR SUB CLASS HERE-----------------");
											sLog.outBasic("New System: mobs %d npcs %d", mobs.size(), NPCs.size());
											for (std::vector<TBLIDX>::size_type i = 0; i != mobs.size(); i++)
											{
												sLog.outBasic("Mob: %d", mobs[i]);
												_player->GetQuestManager()->AddMobQuest(mobs[i], quest->QuestID);
											}

											for (std::vector<TBLIDX>::size_type i = 0; i != NPCs.size(); i++)
											{
												sLog.outBasic("Npc: %d", NPCs[i]);
											}
										}
										else
										{
											sLog.outBasic("Lost object of quest");
										}

										int index = _player->GetAttributesManager()->questSubCls.objChoseIndex;
										std::vector<TBLIDX> mobs = _player->GetAttributesManager()->questSubCls.objData[index].mobsTblidx;
										std::vector<TBLIDX> NPCs = _player->GetAttributesManager()->questSubCls.objData[index].NPCTblidx;
										sLog.outDebug("----------SPAWN MOBS FOR SUB CLASS HERE-----------------");
										sLog.outDebug("mobs %d npcs %d", mobs.size(), NPCs.size());
										for (std::vector<TBLIDX>::size_type i = 0; i != mobs.size(); i++)
										{
											SpawnMobByTblidx(mobs[i]);
										}

										for (std::vector<TBLIDX>::size_type i = 0; i != NPCs.size(); i++)
										{
											SpawnNPCByTblidx(NPCs[i]);
										}
										_player->SetIsReady(false);
										Timer.stop();
									}
								}, 1000, tid);
							/*Timer.setTimeout([&]() {
								int index = _player->GetAttributesManager()->questSubCls.objChoseIndex;
								std::vector<TBLIDX> mobs = _player->GetAttributesManager()->questSubCls.objData[index].mobsTblidx;
								std::vector<TBLIDX> NPCs = _player->GetAttributesManager()->questSubCls.objData[index].NPCTblidx;
								sLog.outDebug("----------SPAWN MOBS FOR SUB CLASS HERE-----------------");
								sLog.outDebug("mobs %d npcs %d", mobs.size(), NPCs.size());
								for (std::vector<TBLIDX>::size_type i = 0; i != mobs.size(); i++)
								{
									SpawnMobByTblidx(mobs[i]);
								}

								for (std::vector<TBLIDX>::size_type i = 0; i != NPCs.size(); i++)
								{
									SpawnNPCByTblidx(NPCs[i]);
								}

								}, 10000);*/
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
							_player->GetAttributesManager()->teleportInfo.worldInfo.hTriggerObjectOffset = HANDLE_TRIGGER_OBJECT_OFFSET;
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
			case DBO_ACT_TYPE_ID_ACT_QITEM:
			{
				CDboTSActQItem* qItem = ((CDboTSActQItem*)contGAct->GetChildEntity(i));
				if (qItem)
				{
					for (int slot = 0; slot < qItem->eMAX_TS_QITEM_COUNT; slot++)
					{
						sLog.outDebug("Type %d Itemidx %d count %d probability %f", qItem->GetQItemType(),
							qItem->GetQItemInfo(slot).uiQItemIdx, qItem->GetQItemInfo(slot).nQItemCnt, qItem->GetQItemInfo(slot).fProbability);
						if (qItem->GetQItemInfo(slot).uiQItemIdx != INVALID_TBLIDX)
						{
							
							QuestItem newQuestItem;
							newQuestItem.qItemTblidx = qItem->GetQItemInfo(slot).uiQItemIdx;
							newQuestItem.byCurCount = qItem->GetQItemInfo(slot).nQItemCnt;
							BYTE pos = _player->GetQuestInventoryManager()->AddItemQuest(newQuestItem);
							if (pos != -1)
							{
								SendQuestItemCreate(pos, newQuestItem.qItemTblidx, newQuestItem.byCurCount);
							}
							else
							{
								sLog.outDebug("Inventory quest is full");
							}
							//SendQuestItemCreate(0, qItem->GetQItemInfo(slot).uiQItemIdx, qItem->GetQItemInfo(slot).nQItemCnt);
						}

					}
					break;
				}
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
				sOBJECT_TBLDAT* object = (sOBJECT_TBLDAT*)sTBM.GetObjectTable(_player->GetPcProfile()->bindWorldId)->FindData(_player->GetPcProfile()->bindObjectTblidx);
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
		for (int i = 0; i < MAX_DEFAULT_REWARD; i++)
		{
			sLog.outDebug("rwdTbl %d value %d type %d", contReward->GetDefReward(i).m_uiIdx, contReward->GetDefReward(i).m_nValue, contReward->GetDefReward(i).m_eType);
			switch (contReward->GetDefReward(i).m_eType)
			{
				case eREWARD_TYPE_NORMAL_ITEM:
				{
					sLog.outDebug("eREWARD_TYPE_NORMAL_ITEM");
					break;
				}
				case eREWARD_TYPE_QUEST_ITEM:
				{
					sLog.outDebug("eREWARD_TYPE_QUEST_ITEM");
					break;
				}
				case eREWARD_TYPE_EXP:
				{
					sLog.outDebug("eREWARD_TYPE_EXP");
					break;
				}
				case eREWARD_TYPE_SKILL:
				{
					sHTB_SET_TBLDAT* htb = (sHTB_SET_TBLDAT*)sTBM.GetHTBSetTable()->FindData(contReward->GetDefReward(i).m_uiIdx);
					if (htb)
					{
						sLog.outDebug("Htb %d %d %d", htb->tblidx, htb->wNeed_EP, htb->dwPC_Class_Bit_Flag);
						DWORD myFlag;
						myFlag = MAKE_BIT_FLAG(static_cast<int>(_player->GetMyClass()));
						sLog.outDetail("My flag: %d flag need %d my class: %d is same %d",
							myFlag, htb->dwPC_Class_Bit_Flag, _player->GetMyClass(), (myFlag & htb->dwPC_Class_Bit_Flag));
						if (myFlag & htb->dwPC_Class_Bit_Flag)// lo mismo que !(myFlag & itemTblSelect->dwNeedClassBitFlag)
						{
							LearnHtb(htb->tblidx, 0);
						}

					}
					sLog.outDebug("eREWARD_TYPE_SKILL");
					break;
				}
				case eREWARD_TYPE_ZENY:
				{
					sLog.outDebug("eREWARD_TYPE_ZENY");
					break;
				}
				case eREWARD_TYPE_CHANGE_CLASS:
				{
					sLog.outDebug("eREWARD_TYPE_CHANGE_CLASS");
					break;
				}
				case eREWARD_TYPE_BUFF:
				{
					sLog.outDebug("eREWARD_TYPE_BUFF");
					break;
				}
				case eREWARD_TYPE_PROBABILITY:
				{
					sLog.outDebug("eREWARD_TYPE_PROBABILITY");
					break;
				}
				case eREWARD_TYPE_REPUTATION:
				{
					sLog.outDebug("eREWARD_TYPE_REPUTATION");
					break;
				}
				case eREWARD_TYPE_CHANGE_ADULT:
				{
					_player->ConvertAdult(true);
					sLog.outDebug("eREWARD_TYPE_CHANGE_ADULT");
					break;
				}
				case eREWARD_TYPE_GET_CONVERT_CLASS_RIGHT:
				{
					sLog.outDebug("eREWARD_TYPE_GET_CONVERT_CLASS_RIGHT");
					break;
				}
			}
		}

		for (int i = 0; i < MAX_SELECTION_REWARD; i++)
		{
			sLog.outDebug("rwdTbl %d value %d type %d", contReward->GetSelReward(i).m_uiIdx, contReward->GetSelReward(i).m_nValue, contReward->GetSelReward(i).m_eType);
		}


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

	ResultCodes result = GivePlayerQuestReward(contReward->GetRewardTableIndex(), contReward->GetRewardContType(), dwParam, contReward->GetID());
	if (result == RESULT_FAIL)
	{
		return RESULT_FAIL;
	}

	return RESULT_SUCCESS;
}

ResultCodes WorldSession::GivePlayerItemReward(sQUEST_REWARD_TBLDAT* rewardTbl, DWORD dwParam, NTL_TS_TC_ID tcId)
{
	for (int rw = 0; rw < QUEST_REWARD_DEF_MAX_CNT; rw++)
	{
		if (rewardTbl->rewardDefData[rw].rwdIdx == INVALID_TBLIDX)
		{
			break; // cambiar por continue si causa bug
		}

		switch (rewardTbl->rewardDefData->unknown)
		{
			case eREWARD_TYPE_SKILL:
			{
				sLog.outDebug("eREWARD_TYPE_SKILL");
				sLog.outDebug("Cid %d", tcId);
				if (tcId != 101)
				{
					sSKILL_TBLDAT* skillData = (sSKILL_TBLDAT*)sTBM.GetSkillTable()->FindData(rewardTbl->rewardDefData[0].rwdIdx);
					if (skillData != NULL)
					{

						if (skillData->bySkill_Grade == 1 && skillData->bySkill_Class != eSKILL_CLASS::SKILL_CLASS_HTB && _player->skillManager.isSkillLearned(skillData->tblidx) == false)
						{

							if (_player->GetMyClass() == _player->GetBaseClass((ePC_CLASS)skillData->byPC_Class_Change))
							{
								LearnSkill(skillData->tblidx);
								_player->ChangeClass((ePC_CLASS)skillData->byPC_Class_Change);
								sLog.outDetail("Learn the skill %d", rewardTbl->rewardDefData[0].rwdIdx);
							}

							// fix sub class reward
							/*if (skillData->tblidx == 2029991)
							{
								_player->ConvertClass(ePC_CLASS::PC_CLASS_KAR_MA, _player->GetHandle());
							}*/
						}
						else
						{
							sLog.outDetail("ERROR to skill %d", rewardTbl->rewardDefData[0].rwdIdx);
						}
					}
				}
				
				break;
			}
			case eREWARD_TYPE_NORMAL_ITEM:
			{
				sLog.outDebug("eREWARD_TYPE_NORMAL_ITEM");

				break;
			}
			case eREWARD_TYPE_GET_QUEST_REWARD_SELECT:
			{
				sLog.outDebug("eREWARD_TYPE_GET_QUEST_REWARD_SELECT");
				break;
			}
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
						case eREWARD_TYPE_SKILL:
						{
							sLog.outDebug("eREWARD_TYPE_SKILL");
							sSKILL_TBLDAT* skillData = (sSKILL_TBLDAT*)sTBM.GetSkillTable()->FindData(rewardSelect1->rewardData[itRw].itemTblidx);
							if (skillData != NULL)
							{
								DWORD myFlag;
								if (_player->GetMyClass() <= PC_CLASS_1_LAST)
								{
									myFlag = MAKE_BIT_FLAG(static_cast<int>(_player->GetMyClass()));
								}
								else
								{
									myFlag = MAKE_BIT_FLAG(static_cast<int>(_player->GetBaseClass(_player->GetMyClass())));
								}
								
								sLog.outDetail("My flag: %d flag need %d my class: %d is same %d",
									myFlag, skillData->dwPC_Class_Bit_Flag, _player->GetBaseClass(_player->GetMyClass()), (myFlag & skillData->dwPC_Class_Bit_Flag));
								if (myFlag & skillData->dwPC_Class_Bit_Flag)// (_player->GetClassFlag(_player->GetMyClass(), ITEM_TYPE_UNKNOWN) == skillData->dwPC_Class_Bit_Flag)
								{
									if (skillData->bySkill_Grade == 1 && skillData->bySkill_Class != eSKILL_CLASS::SKILL_CLASS_HTB && _player->skillManager.isSkillLearned(skillData->tblidx) == false)
									{
										sLog.outDetail("Learn the skill \n");
										LearnSkill(skillData->tblidx);
									}
									else
									{
										sLog.outDetail("ERROR to skill 1 %d", skillData->tblidx);
									}
								}
								else
								{
									sLog.outDetail("ERROR to skill 2 %d %d %d %d", 
										skillData->tblidx, skillData->dwPC_Class_Bit_Flag, _player->GetBaseClass(_player->GetMyClass()), _player->GetClassFlag(_player->GetMyClass(), ITEM_TYPE_UNKNOWN));
								}
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

ResultCodes WorldSession::GivePlayerQuestReward(TBLIDX tblidx, eREWARD_CONTAINER_TYPE rewardContType, DWORD dwParam, NTL_TS_TC_ID tcId)
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

		if (GivePlayerItemReward(rewardTbl, dwParam, tcId) != RESULT_SUCCESS)
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

		// TLQ1 -------------------
		if (trigger->GetID() == 11604)
		{
			SendTSUpdateEventNfy(TS_TYPE_QUEST_CS, 16100);
		}
		if (trigger->GetID() == 11610)
		{
			SendTSUpdateEventNfy(TS_TYPE_QUEST_CS, 16310);
		}
		// TLQ1 -------------------
	}
	_player->GetQuestManager()->DeleteQuest(trigger->GetID());
	sLog.outBasic("Quest delete from list");
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
			if (ProcessTSContStart(contStart, req->tId) == RESULT_FAIL)
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

void WorldSession::EvtMobKillCount(CDboTSActSToCEvt* sToCEvt, NTL_TS_T_ID tid)
{
	//New system
	for (int i = 0; i < sToCEvt->GetEvtData().MAX_MOB_KILL; i++)
	{
		TBLIDX groupTblidx = sToCEvt->GetEvtData().sMobKillCnt[i].uiMobIdx;
		TBLIDX mobTblidx = sTBM.GetMobTable()->FindTblidxByGroup(groupTblidx);


		if (mobTblidx && mobTblidx != INVALID_TBLIDX)
		{
			//New system
			QuestData* quest = _player->GetQuestManager()->FindQuestById(tid);
			if (quest != NULL)
			{
				quest->uEvtData.sMobKillCnt[i].uiMobIdx = mobTblidx;
				quest->uEvtData.sMobKillCnt[i].nCurMobCnt = sToCEvt->GetEvtData().sMobKillCnt[i].nCurMobCnt;
				quest->uEvtData.sMobKillCnt[i].nMobCnt = sToCEvt->GetEvtData().sMobKillCnt[i].nMobCnt;

				_player->GetQuestManager()->AddMobQuest(mobTblidx, tid);
			}
			//New system
			/*
			//old system
			_player->GetAttributesManager()->QuestDat[freeslot].uEvtData.sMobKillCnt[i].uiMobIdx = mobTblidx;
			_player->GetAttributesManager()->QuestDat[freeslot].uEvtData.sMobKillCnt[i].nCurMobCnt = sToCEvt->GetEvtData().sMobKillCnt[i].nCurMobCnt;
			_player->GetAttributesManager()->QuestDat[freeslot].uEvtData.sMobKillCnt[i].nMobCnt = sToCEvt->GetEvtData().sMobKillCnt[i].nMobCnt;
			*/


			sLog.outError("ROOT TS: %d", tid);
			sLog.outDetail("Mob kill: group tblidx: %d  mobTblidx: %d count: %d, curcout: %d",
				groupTblidx, mobTblidx, sToCEvt->GetEvtData().sMobKillCnt[i].nMobCnt, sToCEvt->GetEvtData().sMobKillCnt[i].nCurMobCnt);

			//New system
			if (quest != NULL)
			{
				sLog.outBasic("New system spawn mob quest: %d", quest->sPawnMobQuest);

				//New system
				if (quest->sPawnMobQuest)//(_player->GetAttributesManager()->sPawnMobQuest)
				{
					sMOB_TBLDAT* mob = (sMOB_TBLDAT*)sTBM.GetMobTable()->FindData(mobTblidx);
					if (mob)
					{
						sLog.outDebug("obj tblidx %d %d %s", mob->tblidx, mob->Mob_Group, mob->szNameText);

						sLog.outBasic("Last NPC Quest %d", quest->lastNPCQuest);

						sNPC_TBLDAT* npc = (sNPC_TBLDAT*)sTBM.GetNpcTable()->FindData(quest->lastNPCQuest);//_player->GetAttributesManager()->lastNPCQuest);
						if (npc)
						{
							sLog.outDebug("npc tblidx %d %s %d %d", npc->tblidx, npc->szNameText, strcmp(npc->szModel, mob->szModel), npc->byNpcType == mob->byMob_Type);
							if (!strcmp(npc->szModel, mob->szModel)) //&& (npc->byNpcType == mob->byMob_Type))
							{
								Npc* curr_Npc = static_cast<Npc*>(_player->GetFromList(_player->GetTarget()));
								//sLog.outDebug("Conver NPC to MOB %d %d", curr_Npc->GetNpcData().MonsterID, _player->GetAttributesManager()->lastNPCQuest);
								sLog.outBasic("Conver NPC to MOB %d %d", curr_Npc->GetNpcData().MonsterID, quest->lastNPCQuest);
								if (curr_Npc->GetNpcData().MonsterID == quest->lastNPCQuest)//_player->GetAttributesManager()->lastNPCQuest)
								{
									//New system
									if (quest != NULL)
									{
										quest->npcClick = curr_Npc->GetNpcData().MonsterID;
									}
									//New system
									/*
									//old system
									_player->GetAttributesManager()->QuestDat[freeslot].npcClick = curr_Npc->GetNpcData().MonsterID;*/

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

									HOBJECT mobHandle = SpawnMobForQuest(mobTblidx, curr_Npc->GetNpcData().MonsterID, 0);
									//New System
									if (quest != NULL)
									{
										quest->mobHandle = mobHandle;
									}
									//New system
									/*
									//Old system
									_player->GetAttributesManager()->QuestDat[freeslot].mobHandle = mobHandle;//SpawnMobForQuest(mobTblidx, curr_Npc->GetNpcData().MonsterID, 0);
									*/
									sLog.outDebug("MOB Created");

								}
								else
								{
									sLog.outDebug("NPC NOT FOUND");
									//New system
									if (quest != NULL)
									{
										quest->sPawnMobQuest = false;
										sLog.outBasic("New system spawn mob quest: %d", quest->sPawnMobQuest);
									}
									//New system
									//_player->GetAttributesManager()->sPawnMobQuest = false;
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
}

void WorldSession::EvtMobItemKillCount(CDboTSActSToCEvt* sToCEvt, NTL_TS_T_ID tid)
{
	for (int i = 0; i < sToCEvt->GetEvtData().MAX_MOB_KILL_ITEM; i++)
	{
		//New system
		QuestData* quest = _player->GetQuestManager()->FindQuestById(tid);
		if (quest != NULL)
		{
			quest->uEvtData.sMobKillItemCnt[i].uiMobLIIdx = sToCEvt->GetEvtData().sMobKillItemCnt[i].uiMobLIIdx;
			quest->uEvtData.sMobKillItemCnt[i].nMobLICnt = sToCEvt->GetEvtData().sMobKillItemCnt[i].nMobLICnt;
			quest->uEvtData.sMobKillItemCnt[i].nCurMobLICnt = sToCEvt->GetEvtData().sMobKillItemCnt[i].nCurMobLICnt;

			std::vector<TBLIDX> dropTable = sTBM.GetQuestDropTable()->FindByItemTblidx(sToCEvt->GetEvtData().sMobKillItemCnt[i].uiMobLIIdx);
			for (std::vector<TBLIDX>::size_type item = 0; item != dropTable.size(); item++)
			{
				std::vector<TBLIDX> mobsTblidx = sTBM.GetMobTable()->FindTblidxsByQuestDrop(dropTable[item]);

				sLog.outDetail("Mobs count new system %d quest %d drop %d", mobsTblidx.size(), tid, dropTable[item]);
				for (std::vector<TBLIDX>::size_type i = 0; i != mobsTblidx.size(); i++)
				{
					_player->GetQuestManager()->AddMobQuest(mobsTblidx[i], tid);
					sLog.outDetail("Mob found %d item %d quest %d", mobsTblidx[i], sToCEvt->GetEvtData().sMobKillItemCnt[i].uiMobLIIdx, tid);
				}
			}
			
		}
		//New System
		/* old system
		_player->GetAttributesManager()->QuestDat[freeslot].uEvtData.sMobKillItemCnt[i].uiMobLIIdx = sToCEvt->GetEvtData().sMobKillItemCnt[i].uiMobLIIdx;
		_player->GetAttributesManager()->QuestDat[freeslot].uEvtData.sMobKillItemCnt[i].nMobLICnt = sToCEvt->GetEvtData().sMobKillItemCnt[i].nMobLICnt;
		_player->GetAttributesManager()->QuestDat[freeslot].uEvtData.sMobKillItemCnt[i].nCurMobLICnt = sToCEvt->GetEvtData().sMobKillItemCnt[i].nCurMobLICnt;*/
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

			//New system
			if (quest != NULL)
			{
				sLog.outBasic("New system spawn mob quest: %d", quest->sPawnMobQuest);

				//New system
				if (!(mobTblidx == INVALID_TBLIDX) && quest->sPawnMobQuest)//_player->GetAttributesManager()->sPawnMobQuest)
				{
					sMOB_TBLDAT* mob = (sMOB_TBLDAT*)sTBM.GetMobTable()->FindData(mobTblidx);
					if (mob)
					{
						sLog.outDebug("obj tblidx %d %d %s", mob->tblidx, mob->Mob_Group, mob->szNameText);
						sLog.outBasic("Last NPC Quest %d", quest->lastNPCQuest);
						sNPC_TBLDAT* npc = (sNPC_TBLDAT*)sTBM.GetNpcTable()->FindData(quest->lastNPCQuest);//_player->GetAttributesManager()->lastNPCQuest);
						if (npc)
						{
							sLog.outDebug("npc tblidx %d %s %d %d", npc->tblidx, npc->szNameText, strcmp(npc->szModel, mob->szModel), npc->byNpcType == mob->byMob_Type);
							if (!strcmp(npc->szModel, mob->szModel))// && (npc->byNpcType == mob->byMob_Type))
							{
								Npc* curr_Npc = static_cast<Npc*>(_player->GetFromList(_player->GetTarget()));
								//sLog.outDebug("Convert NPC to MOB %d %d", curr_Npc->GetNpcData().MonsterID, _player->GetAttributesManager()->lastNPCQuest);
								sLog.outBasic("Convert NPC to MOB %d %d", curr_Npc->GetNpcData().MonsterID, quest->lastNPCQuest);
								if (curr_Npc->GetNpcData().MonsterID == quest->lastNPCQuest)//_player->GetAttributesManager()->lastNPCQuest)
								{
									sLog.outDebug("Converting NPC to MOB...");
									//New system
									if (quest != NULL)
									{
										quest->npcClick = curr_Npc->GetNpcData().MonsterID;
									}
									//New system
									// old system _player->GetAttributesManager()->QuestDat[freeslot].npcClick = curr_Npc->GetNpcData().MonsterID;


									sGU_OBJECT_DESTROY sPacket;

									sPacket.wOpCode = GU_OBJECT_DESTROY;
									sPacket.handle = curr_Npc->GetHandle();
									sPacket.wPacketSize = sizeof(sGU_OBJECT_DESTROY) - 2;

									_player->SendPacket((char*)&sPacket, sizeof(sGU_OBJECT_DESTROY));

									_player->RemoveFromList(*curr_Npc);
									curr_Npc->SetIsBecomeMob(true);
									curr_Npc->RemoveFromWorld();
									sLog.outDebug("NPC deleted");

									//New system
									if (quest != NULL)
									{
										quest->mobHandle = SpawnMobForQuest(mobTblidx, curr_Npc->GetNpcData().MonsterID, 0);
									}
									//New system
									/*Old system
									_player->GetAttributesManager()->QuestDat[freeslot].mobHandle = SpawnMobForQuest(mobTblidx, curr_Npc->GetNpcData().MonsterID, 0);*/
									sLog.outDebug("MOB created");
								}
								else
								{
									sLog.outDebug("NPC NOT FOUND");
									//New system
									if (quest != NULL)
									{
										quest->sPawnMobQuest = false;
										sLog.outBasic("New system spawn mob quest: %d", quest->sPawnMobQuest);
									}
									//New system
									//_player->GetAttributesManager()->sPawnMobQuest = false;
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
	}
}

void WorldSession::EvtDeliveryItem(CDboTSActSToCEvt* sToCEvt, NTL_TS_T_ID tid)
{//New system
	QuestData* quest = _player->GetQuestManager()->FindQuestById(tid);
	if (quest != NULL)
	{
		for (int i = 0; i < sToCEvt->GetEvtData().MAX_DELIVERY_ITEM; i++)
		{

			quest->uEvtData.sDeliveryItemCnt[i].uiItemIdx = sToCEvt->GetEvtData().sDeliveryItemCnt[i].uiItemIdx;
			quest->uEvtData.sDeliveryItemCnt[i].nItemCnt = sToCEvt->GetEvtData().sDeliveryItemCnt[i].nItemCnt;
			quest->uEvtData.sDeliveryItemCnt[i].nCurItemCnt = sToCEvt->GetEvtData().sDeliveryItemCnt[i].nCurItemCnt;

			//New System
			/*_player->GetAttributesManager()->QuestDat[freeslot].uEvtData.sDeliveryItemCnt[i].uiItemIdx = sToCEvt->GetEvtData().sDeliveryItemCnt[i].uiItemIdx;
			_player->GetAttributesManager()->QuestDat[freeslot].uEvtData.sDeliveryItemCnt[i].nItemCnt = sToCEvt->GetEvtData().sDeliveryItemCnt[i].nItemCnt;
			_player->GetAttributesManager()->QuestDat[freeslot].uEvtData.sDeliveryItemCnt[i].nCurItemCnt = sToCEvt->GetEvtData().sDeliveryItemCnt[i].nCurItemCnt;*/
			sLog.outDebug("Item tblidx: %d count %d curcount %d",
				sToCEvt->GetEvtData().sDeliveryItemCnt[i].uiItemIdx,
				sToCEvt->GetEvtData().sDeliveryItemCnt[i].nItemCnt,
				sToCEvt->GetEvtData().sDeliveryItemCnt[i].nCurItemCnt);
			if (sToCEvt->GetEvtData().sDeliveryItemCnt[i].uiItemIdx != INVALID_TBLIDX)
			{
				QuestItem newQuestItem;
				newQuestItem.qItemTblidx = sToCEvt->GetEvtData().sDeliveryItemCnt[i].uiItemIdx;
				newQuestItem.byCurCount = sToCEvt->GetEvtData().sDeliveryItemCnt[i].nItemCnt;
				BYTE pos = _player->GetQuestInventoryManager()->AddItemQuest(newQuestItem);
				if (pos != -1)
				{
					SendQuestItemCreate(pos, newQuestItem.qItemTblidx, newQuestItem.byCurCount);
				}
				else
				{
					sLog.outDebug("Inventory quest is full");
				}
				//SendQuestItemCreate(0, sToCEvt->GetEvtData().sDeliveryItemCnt[i].uiItemIdx, 1);
			}
		}
	}
}

void WorldSession::EvtObjectItem(CDboTSActSToCEvt* sToCEvt, NTL_TS_T_ID tid)
{

	//New system
	sLog.outBasic("Search for quest %d...", tid);
	QuestData* quest = _player->GetQuestManager()->FindQuestById(tid);
	if (quest != NULL)
	{
		sLog.outBasic("Quest found!");
		sLog.outBasic("Search trigger...");
		std::vector<NTL_TS_T_ID> triggerIds = sTSM.FindTriggerByQuest(tid);
		NTL_TS_T_ID triggerId;
		if (triggerIds.size() > 0)
		{
			triggerId = triggerIds[0];
		}
		else
		{
			triggerId = NTL_TS_T_ID_INVALID;
		}
		
		if (triggerId != NTL_TS_T_ID_INVALID)
		{
			sLog.outBasic("Trigger %d found!", triggerId);
			LoadObjectsTriggersForQuest(triggerId, tid);
		}

		for (int i = 0; i < sToCEvt->GetEvtData().MAX_OBJECT_ITEM; i++)
		{
			quest->uEvtData.sObjectItemCnt[i].uiItemIdx = sToCEvt->GetEvtData().sObjectItemCnt[i].uiItemIdx;
			quest->uEvtData.sObjectItemCnt[i].nItemCnt = sToCEvt->GetEvtData().sObjectItemCnt[i].nItemCnt;
			quest->uEvtData.sObjectItemCnt[i].nCurItemCnt = sToCEvt->GetEvtData().sObjectItemCnt[i].nCurItemCnt;
		}
	}

	/*for (int i = 0; i < sToCEvt->GetEvtData().MAX_OBJECT_ITEM; i++)
	{
		/* //New system
		QuestData* quest = _player->GetQuestManager()->FindQuestById(tid);
		if (quest != NULL)
		{
			quest->uEvtData.sObjectItemCnt[i].uiItemIdx = sToCEvt->GetEvtData().sObjectItemCnt[i].uiItemIdx;
			quest->uEvtData.sObjectItemCnt[i].nItemCnt = sToCEvt->GetEvtData().sObjectItemCnt[i].nItemCnt;
			quest->uEvtData.sObjectItemCnt[i].nCurItemCnt = sToCEvt->GetEvtData().sObjectItemCnt[i].nCurItemCnt;

			NTL_TS_T_ID triggerId = sTSM.FindTriggerByQuest(tid);
			if (triggerId != NTL_TS_T_ID_INVALID)
			{
				LoadObjectsTriggersForQuest(triggerId, tid);
			}
		}
		//New system*/
		/*_player->GetAttributesManager()->QuestDat[freeslot].uEvtData.sObjectItemCnt[i].uiItemIdx = sToCEvt->GetEvtData().sObjectItemCnt[i].uiItemIdx;
		_player->GetAttributesManager()->QuestDat[freeslot].uEvtData.sObjectItemCnt[i].nItemCnt = sToCEvt->GetEvtData().sObjectItemCnt[i].nItemCnt;
		_player->GetAttributesManager()->QuestDat[freeslot].uEvtData.sObjectItemCnt[i].nCurItemCnt = sToCEvt->GetEvtData().sObjectItemCnt[i].nCurItemCnt;
		sLog.outDebug("Item tblidx: %d count %d curcount %d",
			sToCEvt->GetEvtData().sObjectItemCnt[i].uiItemIdx,
			sToCEvt->GetEvtData().sObjectItemCnt[i].nItemCnt,
			sToCEvt->GetEvtData().sObjectItemCnt[i].nCurItemCnt);
	}*/
}

void WorldSession::EvtCustomEventCount(CDboTSActSToCEvt* sToCEvt, NTL_TS_T_ID tid)
{
	//New system
	QuestData* quest = _player->GetQuestManager()->FindQuestById(tid);
	if (quest != NULL)
	{
		//NTL_TS_T_ID triggerId = sTSM.FindTriggerByQuest(tid);
		std::vector<NTL_TS_T_ID> triggerIds = sTSM.FindTriggerByQuest(tid);
		NTL_TS_T_ID triggerId;
		if (triggerIds.size() > 0)
		{
			triggerId = triggerIds[0];
		}
		else
		{
			triggerId = NTL_TS_T_ID_INVALID;
		}

		if (triggerId != NTL_TS_T_ID_INVALID)
		{
			LoadObjectsTriggersForQuest(triggerId, tid);
		}

		for (int i = 0; i < sToCEvt->GetEvtData().MAX_CUSTOM_EVT_CNT; i++)
		{
			quest->uEvtData.sCustomEvtCnt[i].nCurCnt = sToCEvt->GetEvtData().sCustomEvtCnt[i].nCurCnt;
			quest->uEvtData.sCustomEvtCnt[i].nMaxCnt = sToCEvt->GetEvtData().sCustomEvtCnt[i].nMaxCnt;
			quest->uEvtData.sCustomEvtCnt[i].uiCustomEvtID = sToCEvt->GetEvtData().sCustomEvtCnt[i].uiCustomEvtID;
			quest->uEvtData.sCustomEvtCnt[i].uiQTextTblIdx = sToCEvt->GetEvtData().sCustomEvtCnt[i].uiQTextTblIdx;
		}

		
	}
	//New system

	/*for (int i = 0; i < sToCEvt->GetEvtData().MAX_CUSTOM_EVT_CNT; i++)
	{
		/* //New system
		QuestData* quest = _player->GetQuestManager()->FindQuestById(tid);
		if (quest != NULL)
		{
			quest->uEvtData.sCustomEvtCnt[i].nCurCnt = sToCEvt->GetEvtData().sCustomEvtCnt[i].nCurCnt;
			quest->uEvtData.sCustomEvtCnt[i].nMaxCnt = sToCEvt->GetEvtData().sCustomEvtCnt[i].nMaxCnt;
			quest->uEvtData.sCustomEvtCnt[i].uiCustomEvtID = sToCEvt->GetEvtData().sCustomEvtCnt[i].uiCustomEvtID;
			quest->uEvtData.sCustomEvtCnt[i].uiQTextTblIdx = sToCEvt->GetEvtData().sCustomEvtCnt[i].uiQTextTblIdx;

			NTL_TS_T_ID triggerId = sTSM.FindTriggerByQuest(tid);
			if (triggerId != NTL_TS_T_ID_INVALID)
			{
				LoadObjectsTriggersForQuest(triggerId, tid);
			}
		}
		//New system*/
		/*_player->GetAttributesManager()->QuestDat[freeslot].uEvtData.sCustomEvtCnt[i].nCurCnt = sToCEvt->GetEvtData().sCustomEvtCnt[i].nCurCnt;
		_player->GetAttributesManager()->QuestDat[freeslot].uEvtData.sCustomEvtCnt[i].nMaxCnt = sToCEvt->GetEvtData().sCustomEvtCnt[i].nMaxCnt;
		_player->GetAttributesManager()->QuestDat[freeslot].uEvtData.sCustomEvtCnt[i].uiCustomEvtID = sToCEvt->GetEvtData().sCustomEvtCnt[i].uiCustomEvtID;
		_player->GetAttributesManager()->QuestDat[freeslot].uEvtData.sCustomEvtCnt[i].uiQTextTblIdx = sToCEvt->GetEvtData().sCustomEvtCnt[i].uiQTextTblIdx;

		sLog.outDebug("Quest: maxCount %d curCount %d evtId %d texttblidx %d",
			sToCEvt->GetEvtData().sCustomEvtCnt[i].nMaxCnt, sToCEvt->GetEvtData().sCustomEvtCnt[i].nCurCnt, sToCEvt->GetEvtData().sCustomEvtCnt[i].uiCustomEvtID,
			sToCEvt->GetEvtData().sCustomEvtCnt[i].uiQTextTblIdx);
	}*/

	switch (sToCEvt->GetEvtCondDataType())
	{
		case eSTOC_EVT_COND_DATA_TYPE_AUTO_EQUIP_ITEM:
		{
			if (sToCEvt->GetEvtType() == eSTOC_EVT_TYPE_START)
			{
				sLog.outDebug("Item %d", sToCEvt->GetEvtCondData().sAutoEquipItem[0].uiItemTblIdx);
				sITEM_PROFILE createdItem;
				WORD result = _player->GetInventoryManager()->PerformShopBuy(sToCEvt->GetEvtCondData().sAutoEquipItem[0].uiItemTblIdx, 1, createdItem);
				if (result == GAME_SUCCESS && createdItem.tblidx != INVALID_TBLIDX)
				{
					sLog.outDetail("Item Created\n");
					SendItemCreate(&createdItem);
					_player->GetQuestManager()->AddItemGiveQuest(createdItem.tblidx, tid);
				}
				// TLQ1 -------------------
				SendTSUpdateEventNfy(TS_TYPE_QUEST_CS, 16140);
			}

			sLog.outDebug("eSTOC_EVT_COND_DATA_TYPE_AUTO_EQUIP_ITEM");
		}
		break;
		case eSTOC_EVT_COND_DATA_TYPE_EQUIP_ITEM:
		{
		}
		break;
		case eSTOC_EVT_COND_DATA_TYPE_HAVE_ITEM:
		{
		}
		break;
		case eSTOC_EVT_COND_DATA_TYPE_HAVE_QITEM:
		{
		}
		break;
	}
}

void WorldSession::EvtVisit(CDboTSActSToCEvt* sToCEvt, NTL_TS_T_ID tid)
{
	//New system
	QuestData* quest = _player->GetQuestManager()->FindQuestById(tid);
	if (quest != NULL)
	{
		for (int i = 0; i < sToCEvt->GetEvtData().MAX_VISIT_EVT; i++)
		{
			quest->uEvtData.sVisitEvt[i].uiWorldTblIdx = sToCEvt->GetEvtData().sVisitEvt[i].uiWorldTblIdx;
			quest->uEvtData.sVisitEvt[i].uiObjTblIdx = sToCEvt->GetEvtData().sVisitEvt[i].uiObjTblIdx;
			quest->uEvtData.sVisitEvt[i].uiItemTblIdx = sToCEvt->GetEvtData().sVisitEvt[i].uiItemTblIdx;
			quest->uEvtData.sVisitEvt[i].uiIndicatorQText = sToCEvt->GetEvtData().sVisitEvt[i].uiIndicatorQText;
			quest->uEvtData.sVisitEvt[i].uiDialogText = sToCEvt->GetEvtData().sVisitEvt[i].uiDialogText;
			quest->uEvtData.sVisitEvt[i].byObjType = sToCEvt->GetEvtData().sVisitEvt[i].byObjType;
			quest->uEvtData.sVisitEvt[i].bCompleted = sToCEvt->GetEvtData().sVisitEvt[i].bCompleted;

			sLog.outDebug("Quest: world %d objTblidx %d itemTblidx %d indictaroQtext %d dialogText %d objType %d completed %d",
				sToCEvt->GetEvtData().sVisitEvt[i].uiWorldTblIdx, sToCEvt->GetEvtData().sVisitEvt[i].uiObjTblIdx, sToCEvt->GetEvtData().sVisitEvt[i].uiItemTblIdx,
				sToCEvt->GetEvtData().sVisitEvt[i].uiIndicatorQText, sToCEvt->GetEvtData().sVisitEvt[i].uiDialogText, sToCEvt->GetEvtData().sVisitEvt[i].byObjType,
				sToCEvt->GetEvtData().sVisitEvt[i].bCompleted);
			sLog.outDebug("Quest id %d", quest->QuestID);
		}
	}
	//New system

	/*for (int i = 0; i < sToCEvt->GetEvtData().MAX_VISIT_EVT; i++)
	{
		//New system
		QuestData* quest = _player->GetQuestManager()->FindQuestById(tid);
		if (quest != NULL)
		{
			quest->uEvtData.sVisitEvt[i].uiWorldTblIdx = sToCEvt->GetEvtData().sVisitEvt[i].uiWorldTblIdx;
			quest->uEvtData.sVisitEvt[i].uiObjTblIdx = sToCEvt->GetEvtData().sVisitEvt[i].uiObjTblIdx;
			quest->uEvtData.sVisitEvt[i].uiItemTblIdx = sToCEvt->GetEvtData().sVisitEvt[i].uiItemTblIdx;
			quest->uEvtData.sVisitEvt[i].uiIndicatorQText = sToCEvt->GetEvtData().sVisitEvt[i].uiIndicatorQText;
			quest->uEvtData.sVisitEvt[i].uiDialogText = sToCEvt->GetEvtData().sVisitEvt[i].uiDialogText;
			quest->uEvtData.sVisitEvt[i].byObjType = sToCEvt->GetEvtData().sVisitEvt[i].byObjType;
			quest->uEvtData.sVisitEvt[i].bCompleted = sToCEvt->GetEvtData().sVisitEvt[i].bCompleted;
		}
		//New system
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
	}*/
}

ResultCodes	WorldSession::CheckEvtDataType(CDboTSActSToCEvt* sToCEvt, NTL_TS_TC_ID tcId)
{
	CNtlTSTrigger* trigger = (CNtlTSTrigger*)sToCEvt->GetRoot();

	if (trigger == NULL)
	{
		return RESULT_FAIL;
	}
	//memset(_player->GetAttributesManager()->QuestDat, 0, sizeof _player->GetAttributesManager()->QuestDat);

	/*int freeslot = 0;
	for (int i = 0; i < 30; i++)
	{
		if (_player->GetAttributesManager()->QuestDat[i].QuestID == 0 || _player->GetAttributesManager()->QuestDat[i].QuestID == INVALID_TBLIDX)
		{
			freeslot = i;
			break;
		}
	}*/

	// new system
	QuestData* quest = _player->GetQuestManager()->FindQuestById(trigger->GetID());
	if (quest != NULL)
	{
		quest->evtDataType = sToCEvt->GetEvtDataType();
		quest->tcId = tcId;
		quest->taId = sToCEvt->GetActionId();

		quest->progressInfo.byVer = 0;
		quest->progressInfo.tId = trigger->GetID();
		quest->progressInfo.uData.sQInfoV0.wQState = 0;
		quest->progressInfo.uData.sQInfoV0.sMainTSP.tcCurId = tcId;
		quest->progressInfo.uData.sQInfoV0.sMainTSP.tcPreId = -1;
		quest->progressInfo.uData.sQInfoV0.sSToCEvtData.tcId = tcId;
		quest->progressInfo.uData.sQInfoV0.sSToCEvtData.taId = sToCEvt->GetActionId();
	}
	// new system

	/*_player->GetAttributesManager()->QuestDat[freeslot].QuestID = trigger->GetID();
	_player->GetAttributesManager()->QuestDat[freeslot].evtDataType = sToCEvt->GetEvtDataType();
	_player->GetAttributesManager()->QuestDat[freeslot].tcId = tcId;
	_player->GetAttributesManager()->QuestDat[freeslot].taId = sToCEvt->GetActionId();*/

	switch (sToCEvt->GetEvtDataType())
	{
		case eSTOC_EVT_DATA_TYPE_MOB_KILL_CNT:
		{
			EvtMobKillCount(sToCEvt, trigger->GetID());
			sLog.outDetail("Quest: type eSTOC_EVT_DATA_TYPE_MOB_KILL_CNT");
			break;
		}
		case eSTOC_EVT_DATA_TYPE_MOB_KILL_ITEM_CNT:
		{
			EvtMobItemKillCount(sToCEvt, trigger->GetID());
			sLog.outDetail("Quest: type eSTOC_EVT_DATA_TYPE_MOB_KILL_ITEM_CNT");
			break;
		}
		case eSTOC_EVT_DATA_TYPE_DELIVERY_ITEM:
		{
			EvtDeliveryItem(sToCEvt, trigger->GetID());
			sLog.outDetail("Quest: type eSTOC_EVT_DATA_TYPE_DELIVERY_ITEM");
			break;
		}
		case eSTOC_EVT_DATA_TYPE_OBJECT_ITEM:
		{
			EvtObjectItem(sToCEvt, trigger->GetID());
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
			EvtCustomEventCount(sToCEvt, trigger->GetID());
			sLog.outDetail("Quest: type eSTOC_EVT_DATA_TYPE_CUSTOM_EVT_CNT");
			break;
		}
		case eSTOC_EVT_DATA_TYPE_VISIT:
		{
			EvtVisit(sToCEvt, trigger->GetID());
			sLog.outDetail("Quest: type eSTOC_EVT_DATA_TYPE_VISIT");
			break;
		}
	}
	return RESULT_SUCCESS;
}

HOBJECT WorldSession::ConvertGohanMobNPC(TBLIDX mobTblidx)
{
	sLog.outDebug("GOHAN NPC HANDLES 1: %d 2 %d", _player->GetAttributesManager()->tlq1Info.handleNpc, _player->GetTarget());
	Npc* curr_Npc = static_cast<Npc*>(_player->GetFromList(_player->GetTarget()));
	if (curr_Npc)
	{

		MobTable* MobTable = sTBM.GetMobTable();
		sMOB_TBLDAT* pMOBTblData = reinterpret_cast<sMOB_TBLDAT*>(MobTable->FindData(mobTblidx));
		if (pMOBTblData != NULL)
		{
			sLog.outDebug("Converting...");
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
			spawnData.Tblidx = pMOBTblData->tblidx;

			spawnData.fLastWalkingSpeed = 1.0;
			spawnData.fLastRunningSpeed = 6.0;
			spawnData.fLastAirgSpeed = 6.0;
			spawnData.fLastAirgDashSpeed = 1.0;
			spawnData.fLastAirgDashAccelSpeed = 1.0;
			spawnData.AttackSpeedRate = 1000;
			spawnData.SkillAnnimationSpeedModifier = 100.0;
			spawnData.TBLIDXMovementAcionPattern = 5;
			spawnData.Level = 5;
			spawnData.byBallType = 0;

			spawnData.State.sCharStateBase.aspectState.sAspectStateBase.byAspectStateId = 255;
			spawnData.State.sCharStateBase.vCurLoc.x = curr_Npc->GetVectorPosition().x;
			spawnData.State.sCharStateBase.vCurLoc.y = curr_Npc->GetVectorPosition().y;
			spawnData.State.sCharStateBase.vCurLoc.z = curr_Npc->GetVectorPosition().z;
			spawnData.State.sCharStateBase.vCurDir.x = curr_Npc->GetVectorOriantation().x;
			spawnData.State.sCharStateBase.vCurDir.y = curr_Npc->GetVectorOriantation().y;
			spawnData.State.sCharStateBase.vCurDir.z = curr_Npc->GetVectorOriantation().z;
			spawnData.State.sCharStateBase.byStateID = eCHARSTATE::CHARSTATE_SPAWNING;

			//	sWorld.SendToAll((char*)&spawnData, sizeof(SpawnMOB));
			//Need Insert In list
			Mob* created_mob = new Mob;
			if (pMOBTblData)
			{
				if (created_mob->Create(pMOBTblData, spawnData) == true)
				{
					created_mob->GetMapRef().link(this->_player->GetMap(), created_mob);
					created_mob->SetInitialSpawn(true);
					sLog.outDebug("--------------MOB QUEST ----------------");
					sLog.outDebug("Mob ID %d inserted into map", pMOBTblData->tblidx);
					NTL_TS_T_ID questId = _player->GetQuestManager()->FindQuestByMob(mobTblidx);
					QuestData* quest = _player->GetQuestManager()->FindQuestById(questId);
					if (quest)
					{
						quest->sPawnMobQuest = false;
						sLog.outBasic("New system spawn mob quest: %d", quest->sPawnMobQuest);
					}
					
					//_player->GetAttributesManager()->sPawnMobQuest = false;

					
					sGU_OBJECT_DESTROY sPacket;

					sPacket.wOpCode = GU_OBJECT_DESTROY;
					sPacket.handle = curr_Npc->GetHandle();//_player->GetAttributesManager()->tlq1Info.handleNpc;
					sPacket.wPacketSize = sizeof(sGU_OBJECT_DESTROY) - 2;

					_player->SendPacket((char*)&sPacket, sizeof(sGU_OBJECT_DESTROY));
					curr_Npc->SetIsBecomeMob(true);
					curr_Npc->RemoveFromWorld();
					_player->RemoveFromList(*curr_Npc);
					sLog.outDebug("NPC deleted");

					return handle;
				}
				else
					delete created_mob;
			}
			else
			{
				sLog.outDebug("--------------MOB NOT FOUND----------------");
			}
			//}
			//sLog.outDebug("INVALID_TBLIDX SPAWN NOT FOUND");
			//return INVALID_TBLIDX;
		}
	}
	sLog.outDebug("--------------NPC NOT FOUND----------------");
	return INVALID_TBLIDX;
}

HOBJECT WorldSession::CreateNPCTrunksTLQ1()
{
	NPCTable* NpcTable = sTBM.GetNpcTable();
	sNPC_TBLDAT* pNPCTblData = reinterpret_cast<sNPC_TBLDAT*>(NpcTable->FindData(7511101));
	if (pNPCTblData != NULL)
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
		spawnData.Tblidx = pNPCTblData->tblidx;

		spawnData.fLastWalkingSpeed = 0.89999998;
		spawnData.fLastRunningSpeed = 10.0;
		spawnData.fLastAirSpeed = 10.0;
		spawnData.fLastAirDashSpeed = 0.89999998;
		spawnData.fLastAirDashAccelSpeed = 0.89999998;
		spawnData.AttackSpeedRate = 1000;
		spawnData.SkillAnimationSpeedModifier = 100.0;

		sLog.outDebug("WalkSpeed %f run %d runOrigin %f walkOrigin %f",
			pNPCTblData->fWalk_Speed, pNPCTblData->fRun_Speed, pNPCTblData->fRun_Speed_Origin, pNPCTblData->fWalk_Speed_Origin);
		spawnData.TblidxMovementActionPatern = 1;

		spawnData.State.sCharStateBase.aspectState.sAspectStateBase.byAspectStateId = 255;
		spawnData.State.sCharStateBase.vCurLoc.x = 896.77002;// _player->m_position.x + rand() % 5;
		spawnData.State.sCharStateBase.vCurLoc.y = 7.0;//_player->m_position.y;
		spawnData.State.sCharStateBase.vCurLoc.z = -981.52002;//_player->m_position.z + rand() % 5;
		spawnData.State.sCharStateBase.vCurDir.x = 0.99000001;//_player->m_rotation.x + rand() % 5;
		spawnData.State.sCharStateBase.vCurDir.y = 0.0;// _player->m_rotation.y;
		spawnData.State.sCharStateBase.vCurDir.z = 0.16;//_player->m_rotation.z + rand() % 5;
		spawnData.State.sCharStateBase.byStateID = eCHARSTATE::CHARSTATE_SPAWNING;

		//	sWorld.SendToAll((char*)&spawnData, sizeof(SpawnMOB));
		//Need Insert In list
		Npc* created_Npc = new Npc;
		if (pNPCTblData)
		{
			if (created_Npc->Create(pNPCTblData, spawnData) == true)
			{
				created_Npc->GetMapRef().link(this->_player->GetMap(), created_Npc);
				printf("Npc ID %d inserted into map", pNPCTblData->tblidx);
				return handle;
				//_player->GetAttributesManager()->lastNPCQuest = INVALID_TBLIDX;
				/*Timer.setTimeout([&]() {
					created_Npc->GetState()->sCharStateDetail.sCharStateDestMove.byMoveFlag = 1;
					created_Npc->GetState()->sCharStateDetail.sCharStateDestMove.byDestLocCount = 1;
					created_Npc->GetState()->sCharStateDetail.sCharStateDestMove.avDestLoc[0].x = 881.15002;
					created_Npc->GetState()->sCharStateDetail.sCharStateDestMove.avDestLoc[0].y = 0.0;
					created_Npc->GetState()->sCharStateDetail.sCharStateDestMove.avDestLoc[0].z = -1002.0;
					created_Npc->UpdateState(eCHARSTATE::CHARSTATE_DESTMOVE);
					}, 2000);*/
			}
			else
			{
				delete created_Npc;
			}
		}
	}
	return INVALID_TBLIDX;
}

HOBJECT WorldSession::CreateNPCGohanTLQ1()
{
	NPCTable* NpcTable = sTBM.GetNpcTable();
	sNPC_TBLDAT* pNPCTblData = reinterpret_cast<sNPC_TBLDAT*>(NpcTable->FindData(6201101));
	if (pNPCTblData != NULL)
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
		spawnData.Tblidx = pNPCTblData->tblidx;

		spawnData.fLastWalkingSpeed = 0.89999998;
		spawnData.fLastRunningSpeed = 7.0;
		spawnData.fLastAirSpeed = 7.0;
		spawnData.fLastAirDashSpeed = 0.89999998;
		spawnData.fLastAirDashAccelSpeed = 0.89999998;
		spawnData.AttackSpeedRate = 1000;
		spawnData.SkillAnimationSpeedModifier = 100;

		sLog.outDebug("WalkSpeed %f run %d runOrigin %f walkOrigin %f",
			pNPCTblData->fWalk_Speed, pNPCTblData->fRun_Speed, pNPCTblData->fRun_Speed_Origin, pNPCTblData->fWalk_Speed_Origin);
		spawnData.TblidxMovementActionPatern = 1;

		spawnData.State.sCharStateBase.aspectState.sAspectStateBase.byAspectStateId = 255;
		spawnData.State.sCharStateBase.vCurLoc.x = 915.42999;// _player->m_position.x + rand() % 5;
		spawnData.State.sCharStateBase.vCurLoc.y = 9.0;//_player->m_position.y;
		spawnData.State.sCharStateBase.vCurLoc.z = -963.71002;//_player->m_position.z + rand() % 5;
		spawnData.State.sCharStateBase.vCurDir.x = -0.22;//_player->m_rotation.x + rand() % 5;
		spawnData.State.sCharStateBase.vCurDir.y = 0.0;// _player->m_rotation.y;
		spawnData.State.sCharStateBase.vCurDir.z = -0.97000003;//_player->m_rotation.z + rand() % 5;
		spawnData.State.sCharStateBase.byStateID = eCHARSTATE::CHARSTATE_SPAWNING;

		//	sWorld.SendToAll((char*)&spawnData, sizeof(SpawnMOB));
		//Need Insert In list
		Npc* created_Npc = new Npc;
		if (pNPCTblData)
		{
			if (created_Npc->Create(pNPCTblData, spawnData) == true)
			{
				created_Npc->GetMapRef().link(this->_player->GetMap(), created_Npc);
				printf("Npc ID %d inserted into map", pNPCTblData->tblidx);
				return handle;
				//_player->GetAttributesManager()->lastNPCQuest = INVALID_TBLIDX;
				/*Timer.setTimeout([&]() {
					created_Npc->GetState()->sCharStateDetail.sCharStateDestMove.byMoveFlag = 1;
					created_Npc->GetState()->sCharStateDetail.sCharStateDestMove.byDestLocCount = 1;
					created_Npc->GetState()->sCharStateDetail.sCharStateDestMove.avDestLoc[0].x = 881.15002;
					created_Npc->GetState()->sCharStateDetail.sCharStateDestMove.avDestLoc[0].y = 0.0;
					created_Npc->GetState()->sCharStateDetail.sCharStateDestMove.avDestLoc[0].z = -1002.0;
					created_Npc->UpdateState(eCHARSTATE::CHARSTATE_DESTMOVE);
					}, 2000);*/
			}
			else
			{
				delete created_Npc;
			}
		}
	}
	return INVALID_TBLIDX;
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

HOBJECT	WorldSession::SpawnNPCByTblidxQuestDende(TBLIDX npcTblidx)
{
	NPCTable* NpcTable = sTBM.GetNpcTable();
	sNPC_TBLDAT* pNPCTblData = reinterpret_cast<sNPC_TBLDAT*>(NpcTable->FindData(npcTblidx));
	if (pNPCTblData != NULL)
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
		spawnData.Tblidx = npcTblidx;

		spawnData.fLastWalkingSpeed = 0.89999998;
		spawnData.fLastRunningSpeed = 5.;
		spawnData.fLastAirSpeed = 5.;
		spawnData.fLastAirDashSpeed = 0.89999998;
		spawnData.fLastAirDashAccelSpeed = 0.89999998;

		spawnData.AttackSpeedRate = 1000;
		spawnData.SkillAnimationSpeedModifier = 100.;
		spawnData.TblidxMovementActionPatern = 1;

		
		spawnData.State.sCharStateBase.dwStateTime = 48344;
		spawnData.State.sCharStateBase.aspectState.sAspectStateBase.byAspectStateId = 255;
		spawnData.State.sCharStateBase.vCurLoc.x = 5731.9302;//_player->m_position.x + rand() % 5;
		spawnData.State.sCharStateBase.vCurLoc.y = -88.579002;//_player->m_position.y;
		spawnData.State.sCharStateBase.vCurLoc.z = 3947.2209;//_player->m_position.z + rand() % 5;
		spawnData.State.sCharStateBase.vCurDir.x = 0.616;//_player->m_rotation.x + rand() % 5;
		spawnData.State.sCharStateBase.vCurDir.y = 0.78799999;//_player->m_rotation.y;
		spawnData.State.sCharStateBase.vCurDir.z = 0;//_player->m_rotation.z + rand() % 5;
		spawnData.State.sCharStateBase.byStateID = eCHARSTATE::CHARSTATE_DIRECT_PLAY;
		//spawnData.State.sCharStateBase.byStateID = eCHARSTATE::CHARSTATE_SPAWNING;

		spawnData.State.sCharStateDetail.sCharStateDirectPlay.byDirectPlayType = DIRECT_PLAY_NORMAL;
		spawnData.State.sCharStateDetail.sCharStateDirectPlay.directTblidx = 60001;


		//	sWorld.SendToAll((char*)&spawnData, sizeof(SpawnMOB));
		//Need Insert In list
		Npc* created_Npc = new Npc;
		if (pNPCTblData)
		{
			if (created_Npc->Create(pNPCTblData, spawnData) == true)
			{
				created_Npc->GetMapRef().link(this->_player->GetMap(), created_Npc);
				printf("Npc ID %d inserted into map", npcTblidx);
				return handle;
				//_player->GetAttributesManager()->lastNPCQuest = INVALID_TBLIDX;
			}
			else
				delete created_Npc;
		}
	}
}

HOBJECT WorldSession::SpawnMobForQuest(TBLIDX mobTblidx, TBLIDX NPCSpawnTblidx, int index)
{
	MobTable* MobTable = sTBM.GetMobTable();
	sMOB_TBLDAT* pMOBTblData = reinterpret_cast<sMOB_TBLDAT*>(MobTable->FindData(mobTblidx));
	if (pMOBTblData != NULL)
	{
		std::vector<TBLIDX> spawnIdxs;
		if (NPCSpawnTblidx != 0 && NPCSpawnTblidx != INVALID_TBLIDX)
		{
			spawnIdxs = sTBM.GetNpcSpawnTable(_player->GetWorldID())->FindSpawnByObjectTblidx(NPCSpawnTblidx);
		}
		else
		{
			//spawnIdxs = sTBM.GetMobSpawnTable(_player->GetWorldID())->FindSpawnByObjectTblidx(mobTblidx);
		}
		sLog.outDebug("SPAWNING...");
		/*for (std::vector<TBLIDX>::size_type spI = 0; spI != spawnIdxs.size(); spI++)
		{
			sSPAWN_TBLDAT* spawnTblTest = (sSPAWN_TBLDAT*)sTBM.GetMobSpawnTable(_player->GetWorldID())->FindData(spawnIdxs[spI]);
			sLog.outDebug("Spawn %d (%f %f %f)", spawnTblTest->tblidx, spawnTblTest->vSpawn_Loc.x, spawnTblTest->vSpawn_Loc.y, spawnTblTest->vSpawn_Loc.z);
		}*/

		sSPAWN_TBLDAT* spawnTbl;
		sVECTOR3 position;
		sVECTOR3 direction;

		if (NPCSpawnTblidx != 0 && NPCSpawnTblidx != INVALID_TBLIDX)
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

			sLog.outDebug("SPAWN IN RANGE OF PLAYER");
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
				created_mob->SetInitialSpawn(true);
				sLog.outDebug("--------------MOB QUEST ----------------");
				sLog.outDebug("Mob ID %d inserted into map", mobTblidx);
				NTL_TS_T_ID questId = _player->GetQuestManager()->FindQuestByMob(mobTblidx);
				QuestData* quest = _player->GetQuestManager()->FindQuestById(questId);
				if (quest)
				{
					quest->sPawnMobQuest = false;
					sLog.outBasic("New system spawn mob quest: %d", quest->sPawnMobQuest);
				}
				//_player->GetAttributesManager()->sPawnMobQuest = false;
			}
			else
				delete created_mob;
		}
		else
		{
			sLog.outDebug("--------------MOB NOT FOUND----------------");
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

void WorldSession::LoadObjectsTriggersForQuest(NTL_TS_T_ID triggerId, NTL_TS_T_ID questId)
{
	sLog.outDetail("Load quest objects info");
	CNtlTSGroup* groupTS = sTSM.FindObjectFromTS(triggerId)->GetGroup(NTL_TS_MAIN_GROUP_ID);
	int countSteps = groupTS->GetNumOfChildCont();
	sLog.outDebug("count %d", countSteps);
	for (int curEnt = 0; curEnt < countSteps; curEnt++)
	{

		CNtlTSCont* contBase = groupTS->GetChildCont(0);
		if (contBase == NULL)
		{
			continue;
		}

		sLog.outDebug("Nombre %s cid %d", contBase->GetClassNameW(), 0);

		switch (contBase->GetEntityType())
		{
			case DBO_CONT_TYPE_ID_CONT_START:
			{
				CDboTSContStart* contStart = ((CDboTSContStart*)contBase);
				if (contStart == NULL)
				{
					return;
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
								bool first = true;
								TBLIDX objTblidx = INVALID_TBLIDX;
								sLog.outDetail("Count of objecs %d", clickObject->GetNumOfObjectIdx());
								for (int i = 0; i < clickObject->GetNumOfObjectIdx(); i++)
								{
									if (first)
									{
										sLog.outDebug("obj idx %d", clickObject->BeginObjectIdx());
										first = false;
										objTblidx = clickObject->BeginObjectIdx();
									}
									else
									{
										objTblidx = clickObject->NextObjectIdx();
										sLog.outDebug("obj idx %d", objTblidx);
									
									}

									_player->GetQuestManager()->AddObjectQuest(objTblidx, questId);
									_player->GetQuestManager()->AddObjectTrigger(objTblidx, triggerId, _player->GetWorldTableID());
								}
								return;
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
						case DBO_COND_TYPE_ID_CHECK_ATTACH_OBJ:
						{
							CDboTSCheckAttachObj* attachObj = ((CDboTSCheckAttachObj*)contStart->GetChildEntity(i));
							if (attachObj)
							{
								bool first = true;
								TBLIDX objTblidx = INVALID_TBLIDX;
								sLog.outDebug("Atach Num obj %d world %d", attachObj->GetNumOfObjectIdx(), attachObj->GetWorldIdx(), attachObj->HasObjectIdx(objTblidx));
								for (int i = 0; i < attachObj->GetNumOfObjectIdx() - 1; i++)
								{
									if (first)
									{
										sLog.outDebug("Add obj idx %d", attachObj->BeginObjectIdx());
										first = false;
										objTblidx = attachObj->BeginObjectIdx();
									}
									else
									{
										objTblidx = attachObj->NextObjectIdx();
										sLog.outDebug("Add obj idx %d", objTblidx);

									}

									_player->GetQuestManager()->AddObjectQuest(objTblidx, questId);
									_player->GetQuestManager()->AddObjectTrigger(objTblidx, triggerId, _player->GetWorldTableID());
								}
								return;
							}
							break;
						}
					}
				}
				break;
			}
		}
	}
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

	 info.progressInfo[0].byVer = info.progressInfo[0].eCUR_VERSION;
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
	 info.progressInfo[1].byVer = info.progressInfo[0].eCUR_VERSION;
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

	 QuestData* quest = _player->GetQuestManager()->FindQuestById(req->tId);
	 if (quest)
	 {
		 sLog.outDetail("Quest found %d", quest->QuestID);
		 if (quest->npcClick != INVALID_TBLIDX && quest->lastNPCQuest/*_player->GetAttributesManager()->lastNPCQuest*/ != INVALID_TBLIDX)
		 {
			 sLog.outDetail("npcClickl %d", quest->npcClick);
			 sLog.outDetail("Last NPC Quest %d", quest->lastNPCQuest);
			 if (quest->npcClick == quest->lastNPCQuest)//_player->GetAttributesManager()->lastNPCQuest)
			 {
				 if (SpawnNPCForQuest(quest->npcClick, 0) != INVALID_TBLIDX)
				 {
					 if (quest->mobHandle != INVALID_TBLIDX && quest->mobHandle != 0)
					 {
						 Mob* curr_Mob = static_cast<Mob*>(_player->GetFromList(quest->mobHandle));
						 //sLog.outDebug("Conver MOB to NPC %d %d", curr_Mob->GetMobData().MonsterID, _player->GetAttributesManager()->lastNPCQuest);
						 sLog.outDetail("Conver MOB to NPC %d %d", curr_Mob->GetMobData().MonsterID, quest->lastNPCQuest);
						 sGU_OBJECT_DESTROY sPacket;

						 sPacket.wOpCode = GU_OBJECT_DESTROY;
						 sPacket.handle = curr_Mob->GetHandle();
						 sPacket.wPacketSize = sizeof(sGU_OBJECT_DESTROY) - 2;

						 _player->SendPacket((char*)&sPacket, sizeof(sGU_OBJECT_DESTROY));
						 //curr_Npc->RemoveFromWorld();
						 curr_Mob->RemoveFromWorld();
						 _player->RemoveFromList(*curr_Mob);
						 //_player->GetAttributesManager()->lastNPCQuest = INVALID_TBLIDX;
						 quest->lastNPCQuest = INVALID_TBLIDX;

					 }
				 }
			 }
		 }
		 _player->GetQuestManager()->DeleteQuest(req->tId);
	 }

	 /*for (int i = 0; i < 30; i++)
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
	 }*/

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

	 _player->GetQuestInventoryManager()->DeleteItemQuest(req->byDeletePos);
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

	 QuestItem* questItemSrc = _player->GetQuestInventoryManager()->FindItemQuestBySlot(req->bySrcPos);

	 if (questItemSrc != NULL)
	 {
		 res.bySrcPos = req->bySrcPos;
		 res.byDestPos = req->byDestPos;
		 res.dwSrcTblidx = questItemSrc->qItemTblidx;

		 QuestItem* questItemSrcTest = _player->GetQuestInventoryManager()->FindItemQuestByTblidx(questItemSrc->qItemTblidx);
		 sLog.outDebug("Actual real pos: %d, item pos %d dest pos %d", questItemSrcTest->byPos, questItemSrc->byPos, req->bySrcPos);

		 QuestItem* questItemDest = _player->GetQuestInventoryManager()->FindItemQuestBySlot(req->byDestPos);
		 if (questItemDest != NULL)
		 {
			 //Change item pos
			 questItemDest->byPos = req->bySrcPos;
			 res.dwDestTblidx = questItemDest->qItemTblidx;
		 }
		 else
		 {
			 res.dwDestTblidx = INVALID_TBLIDX;
		 }

		 //Change item pos
		 questItemSrc->byPos = req->byDestPos;
		 
	 }
	 else
	 {
		 res.wResultCode = GAME_TS_ERROR_CANNOT_FIND_ITEM_TBLIDX;
	 }

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

 void WorldSession::SendTSUpdateEventNfy(BYTE byTsType, NTL_TS_EVENT_ID evtId)
 {
	 sGU_TS_UPDATE_EVENT_NFY nfy;
	 nfy.wOpCode = GU_TS_UPDATE_EVENT_NFY;
	 nfy.wPacketSize = sizeof(sGU_TS_UPDATE_EVENT_NFY) - 2;
	 nfy.byTsType = byTsType;
	 nfy.teid = evtId;
	 SendPacket((char*)&nfy, sizeof(sGU_TS_UPDATE_EVENT_NFY));
 }

 void WorldSession::SendDirectionIndicateNfy(float x, float y, float z)
 {
	 sGU_DIRECTION_INDICATE_NFY nfy;
	 nfy.wOpCode = GU_DIRECTION_INDICATE_NFY;
	 nfy.wPacketSize = sizeof(sGU_DIRECTION_INDICATE_NFY) - 2;
	 nfy.bIndicate = 1;
	 nfy.unknown = 1;
	 nfy.vLoc.x = x;
	 nfy.vLoc.y = y;
	 nfy.vLoc.z = z;
	 SendPacket((char*)&nfy, sizeof(sGU_DIRECTION_INDICATE_NFY));
 }

 void WorldSession::SendTObjectUpdateState(HOBJECT handle, TBLIDX objTblidx, BYTE state, BYTE substate, DWORD stateTime)
 {
	 sGU_TOBJECT_UPDATE_STATE stateObj;
	 stateObj.wOpCode = GU_TOBJECT_UPDATE_STATE;
	 stateObj.wPacketSize = sizeof(sGU_TOBJECT_UPDATE_STATE) - 2;
	 stateObj.handle = handle;
	 stateObj.tobjectBrief.objectID = objTblidx;
	 stateObj.tobjectState.byState = state;
	 stateObj.tobjectState.bySubStateFlag = substate;
	 stateObj.tobjectState.dwStateTime = stateTime;
	 SendPacket((char*)&stateObj, sizeof(sGU_TOBJECT_UPDATE_STATE));
 }

 void WorldSession::SendCharDirectPlay(bool bSynchronize, BYTE byPlayMode, TBLIDX directTblidx)
 {
	 sGU_CHAR_DIRECT_PLAY res;

	 res.wOpCode = GU_CHAR_DIRECT_PLAY;
	 res.wPacketSize = sizeof(sGU_CHAR_DIRECT_PLAY) - 2;
	 res.hSubject = _player->GetHandle();
	 res.bSynchronize = bSynchronize;
	 res.byPlayMode = byPlayMode;
	 res.directTblidx = directTblidx;

	 SendPacket((char*)&res, sizeof(sGU_CHAR_DIRECT_PLAY));
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

 void WorldSession::SendQuestForcedCompletionNfy(NTL_TS_T_ID tid)
 {
	 sGU_QUEST_FORCED_COMPLETION_NFY nfy;
	 nfy.wOpCode = GU_QUEST_FORCED_COMPLETION_NFY;
	 nfy.wPacketSize = sizeof(sGU_QUEST_FORCED_COMPLETION_NFY) - 2;
	 nfy.questId = tid;
	 SendPacket((char*)&nfy, sizeof(sGU_QUEST_FORCED_COMPLETION_NFY));
 }

ResultCodes WorldSession::FindObjectTriggerInformation(NTL_TS_T_ID tid, QuestData* questData, HOBJECT hTarget, TBLIDX objTblidx)
{
	NTL_TS_TC_ID nextLink = 0;
	CNtlTSGroup * groupTS = sTSM.FindObjectFromTS(tid)->GetGroup(NTL_TS_MAIN_GROUP_ID);
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
						case DBO_COND_TYPE_ID_CHECK_PROG_QUEST:
						{
							CDboTSCheckProgQuest* checkQuest = (CDboTSCheckProgQuest*)contStart->GetChildEntity(i);
							if (checkQuest)
							{
								sLog.outDebug("Quest id: %d", checkQuest->GetQuestID());
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
										//questData->uEvtData.sCustomEvtCnt[i].nCurCnt += 1;
										// Cambiar esto por el inventario de item de quest
										QuestItem * questItem = _player->GetQuestInventoryManager()->FindItemQuestByTblidx(questData->uEvtData.sCustomEvtCnt[i].uiCustomEvtID);
										if (questItem == NULL)
										{
											QuestItem newQuestItem;
											newQuestItem.qItemTblidx = questData->uEvtData.sCustomEvtCnt[i].uiCustomEvtID;
											newQuestItem.byCurCount = 1;
											BYTE pos = _player->GetQuestInventoryManager()->AddItemQuest(newQuestItem);
											if (pos != -1)
											{
												questData->uEvtData.sCustomEvtCnt[i].nCurCnt = newQuestItem.byCurCount;
												SendQuestItemCreate(pos, newQuestItem.qItemTblidx, newQuestItem.byCurCount);
											}
										}
										else
										{
											questItem->byCurCount++;
											questData->uEvtData.sCustomEvtCnt[i].nCurCnt = questItem->byCurCount;
											SendQuestItemUpdateNfy(questItem->byPos, questItem->byCurCount);
										}
										/*if (questData->uEvtData.sCustomEvtCnt[i].nCurCnt <= 1)
										{
											QuestItem questItem;
											questItem.qItemTblidx = questData->uEvtData.sCustomEvtCnt[i].uiCustomEvtID;
											questItem.byCurCount = 1;
											BYTE pos = _player->GetQuestInventoryManager()->AddItemQuest(questItem);
											SendQuestItemCreate(pos, questItem.qItemTblidx, questItem.byCurCount);
										}
										else
										{
											SendQuestItemUpdateNfy(0, questData->uEvtData.sCustomEvtCnt[i].nCurCnt);
										}*/
										
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
								if (questData->QuestID == _player->GetAttributesManager()->questSubCls.curQuestId)
								{
									for (int slot = 0; slot < qItem->eMAX_TS_QITEM_COUNT; slot++)
									{
										sLog.outDebug("Type %d Itemidx %d count %d probability %f", qItem->GetQItemType(),
											qItem->GetQItemInfo(slot).uiQItemIdx, qItem->GetQItemInfo(slot).nQItemCnt, qItem->GetQItemInfo(slot).fProbability);
										if (qItem->GetQItemInfo(slot).uiQItemIdx != INVALID_TBLIDX)
										{
											
											QuestItem newQuestItem;
											newQuestItem.qItemTblidx = qItem->GetQItemInfo(slot).uiQItemIdx;
											newQuestItem.byCurCount = qItem->GetQItemInfo(slot).nQItemCnt;
											BYTE pos = _player->GetQuestInventoryManager()->AddItemQuest(newQuestItem);
											if (pos != -1)
											{
												questData->uEvtData.sCustomEvtCnt[i].nCurCnt = newQuestItem.byCurCount;
												SendQuestItemCreate(pos, newQuestItem.qItemTblidx, newQuestItem.byCurCount);
											}
											else
											{
												sLog.outDebug("Inventory is full");
											}
											//SendQuestItemCreate(0, qItem->GetQItemInfo(slot).uiQItemIdx, qItem->GetQItemInfo(slot).nQItemCnt);
										}
										
									}
									break;
								}

								
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
										QuestItem* questItem = _player->GetQuestInventoryManager()->FindItemQuestByTblidx(questData->uEvtData.sObjectItemCnt[slot].uiItemIdx);
										if (questItem == NULL)
										{
											QuestItem newQuestItem;
											newQuestItem.qItemTblidx = questData->uEvtData.sObjectItemCnt[slot].uiItemIdx;
											newQuestItem.byCurCount = qItem->GetQItemInfo(slot).nQItemCnt;
											BYTE pos = _player->GetQuestInventoryManager()->AddItemQuest(newQuestItem);
											if (pos != -1)
											{
												questData->uEvtData.sObjectItemCnt[slot].nCurItemCnt = newQuestItem.byCurCount;
												SendQuestItemCreate(pos, newQuestItem.qItemTblidx, newQuestItem.byCurCount);
											}
											else
											{
												sLog.outDebug("Inventory quest is full");
											}
										}
										else
										{
											questItem->byCurCount++;
											questData->uEvtData.sObjectItemCnt[slot].nCurItemCnt = questItem->byCurCount;
											SendQuestItemUpdateNfy(questItem->byPos, questItem->byCurCount);
										}
										/*questData->uEvtData.sObjectItemCnt[slot].nCurItemCnt += qItem->GetQItemInfo(slot).nQItemCnt;

										if (questData->uEvtData.sObjectItemCnt[slot].nCurItemCnt <= 1)
										{
											SendQuestItemCreate(0, questData->uEvtData.sObjectItemCnt[slot].uiItemIdx, qItem->GetQItemInfo(slot).nQItemCnt);
										}
										else
										{
											SendQuestItemUpdateNfy(0, questData->uEvtData.sObjectItemCnt[slot].nCurItemCnt);
										}*/
										

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

								if (_player->GetAttributesManager()->questSubCls.inQuest)
								{
									if (objState->GetObjectIdx() != INVALID_TBLIDX)
									{
										sOBJECT_TBLDAT* obj = (sOBJECT_TBLDAT*)sTBM.GetObjectTable(objState->GetWorldIdx())->FindData(objState->GetObjectIdx());
										if (obj)
										{
											SendTObjectUpdateState(HANDLE_TRIGGER_OBJECT_OFFSET + obj->dwSequence,
												objState->GetObjectIdx(), 0, TOBJECT_SUBSTATE_FLAG_UNSELECT, 3909615265);
										}
										 
									}
								}
								else
								{
									/*sGU_TOBJECT_UPDATE_STATE state;
									state.wOpCode = GU_TOBJECT_UPDATE_STATE;
									state.wPacketSize = sizeof(sGU_TOBJECT_UPDATE_STATE) - 2;
									state.handle = hTarget;
									state.tobjectBrief.objectID = objTblidx;
									state.tobjectState.byState = 0;
									state.tobjectState.bySubStateFlag = TOBJECT_SUBSTATE_FLAG_UNSELECT;
									state.tobjectState.dwStateTime = 1832245140;
									SendPacket((char*)&state, sizeof(sGU_TOBJECT_UPDATE_STATE));*/

									SendTObjectUpdateState(hTarget, objTblidx, 0, TOBJECT_SUBSTATE_FLAG_UNSELECT, 1832245140);

									_player->objectHandle = hTarget;
									_player->objectTblidx = objTblidx;
								}
							}
							break;
						}
						case DBO_ACT_TYPE_ID_ACT_ITEM:
						{
							CDboTSActItem* actItem = (CDboTSActItem*)contAct->GetChildEntity(i);
							if (actItem)
							{
								sLog.outDebug("Type %d Item %d slot %d", actItem->GetItemType(), actItem->GetItemInfo(i).uiItemIdx, actItem->GetItemInfo(i).eItemSlotType);
								if (actItem->GetItemType() == eTSITEM_TYPE::eTSITEM_TYPE_CREATE)
								{
									for (int itemId = 0; itemId < actItem->eMAX_TS_ITEM_COUNT; itemId++)
									{
										sLog.outDebug("Quest: item tblidx %d slot type %d",
											actItem->GetItemInfo(itemId).uiItemIdx, actItem->GetItemInfo(itemId).eItemSlotType);
										if (actItem->GetItemInfo(itemId).uiItemIdx != INVALID_TBLIDX)
										{
											sITEM_PROFILE createdItem;
											WORD result = _player->GetInventoryManager()->PerformShopBuy(actItem->GetItemInfo(itemId).uiItemIdx, 1, createdItem);
											if (result == GAME_SUCCESS && createdItem.tblidx != INVALID_TBLIDX)
											{
												sLog.outDetail("Item Created\n");
												SendItemCreate(&createdItem);
											}
										}
									}
								}
							}
							break;
						}
						case DBO_ACT_TYPE_ID_ACT_SEND_SVR_EVT:
						{
							CDboTSActSendSvrEvt* sendEvt = (CDboTSActSendSvrEvt*)contAct->GetChildEntity(i);
							if (sendEvt)
							{
								sLog.outDebug("Evt send type %d evtId %d evt trigger type %d tblidx %d evt type %d", sendEvt->GetEvtSendType(), sendEvt->GetSvrEvtID(),
									sendEvt->GetSvrEvtTriggerType(), sendEvt->GetTblIdx(), sendEvt->GetSvrEvtType());
								SendTSUpdateEventNfy(TS_TYPE_QUEST_CS, sendEvt->GetSvrEvtID());
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

	switch (req->byEvtGenType)
	{
		case eEVENT_GEN_TYPE_CLICK_OBJECT:
		{
			break;
		}
	}
	TBLIDX objTblidx = INVALID_TBLIDX;
	Map* map = _player->GetMap();
	sLog.outDebug("Worldid player %d world object %d", _player->GetWorldID(), map);
	//sLog.outDebug("Request handle interaction == %d", req->hTarget);
	if (map)
	{
		sLog.outDebug("Worldid player %d world %d", _player->GetWorldID(), map->GetId());
		WorldObjectRefManager ref = map->GetWorldObject();
		for (auto reference = ref.begin(); reference != ref.end(); ++reference)
		{
			if (reference->getSource()->GetHandle() == req->hTarget)
			{
				objTblidx = ((WorldObject*)reference->getSource())->GetTblidx();
				sLog.outString("FOUNDED object tblidx %d hTarget %d", objTblidx, req->hTarget);

				//NEw system
				NTL_TS_T_ID questId = _player->GetQuestManager()->FindQuestByObject(objTblidx);
				QuestData* quest = _player->GetQuestManager()->FindQuestById(questId);
				if (quest)
				{
					sLog.outBasic("New system: Is in sub class quest or growup %d", quest->questSubCls.inQuest);
				}
				//New system
				sLog.outDebug("Is in sub class quest or growup %d", _player->GetAttributesManager()->questSubCls.inQuest);
				if (_player->GetAttributesManager()->questSubCls.inQuest)
				{
					for (int i = 0; i < 2; i++)
					{
						//New system
						if (quest)
						{
							NTL_TS_T_ID triggerId = _player->GetQuestManager()->FindTriggerByObject(objTblidx, _player->GetWorldTableID());
							quest->questSubCls.objData[i].triggerId = triggerId;
							sLog.outBasic("Item %d trigger %d object founded %d", quest->questSubCls.objData[i].objTblidx, quest->questSubCls.objData[i].triggerId, objTblidx);
						}
						//New system
						sLog.outDebug("Item %d trigger %d object founded %d", 
							_player->GetAttributesManager()->questSubCls.objData[i].objTblidx, _player->GetAttributesManager()->questSubCls.objData[i].triggerId,
							objTblidx);
						if (_player->GetAttributesManager()->questSubCls.objData[i].objTblidx == objTblidx)
						{
							
							sLog.outDebug("Item chose %d mobs %d", objTblidx, _player->GetAttributesManager()->questSubCls.objData[i].mobsTblidx.size());
							_player->GetAttributesManager()->questSubCls.objChoseIndex = i;
							QuestData questData;
							questData.QuestID = _player->GetAttributesManager()->questSubCls.objData[i].triggerId;
							FindObjectTriggerInformation(questData.QuestID, &questData, req->hTarget, objTblidx);

							if (quest)
							{
								quest->questSubCls.objChoseIndex = i;
							}
						}
					}
				}

				//New System
				//NTL_TS_T_ID questId = _player->GetQuestManager()->FindQuestByObject(objTblidx);
				if (questId != NTL_TS_T_ID_INVALID)
				{
					sLog.outDetail("Quest found %d", questId);
					QuestData* quest = _player->GetQuestManager()->FindQuestById(questId);
					if (quest)
					{
						sLog.outDetail("New EVT TYPE %d", quest->evtDataType);
						switch (quest->evtDataType)
						{
						case eSTOC_EVT_DATA_TYPE_OBJECT_ITEM:
						{
							for (int slot = 0; slot < quest->uEvtData.MAX_OBJECT_ITEM; slot++)
							{
								sLog.outDetail("New ITEM COUNT %d", quest->uEvtData.sObjectItemCnt[slot].nCurItemCnt);


								sLog.outError("New QUEST ID: %d", quest->QuestID);
								if (quest->uEvtData.sObjectItemCnt[slot].nCurItemCnt < quest->uEvtData.sObjectItemCnt[slot].nItemCnt)
								{
									sLog.outDetail("New Item Tblidx %d %d", quest->uEvtData.sObjectItemCnt[slot].uiItemIdx,
										((WorldObject*)reference->getSource())->GetTblidx());

									NTL_TS_T_ID objTriggerId = quest->QuestID;

									//New System
									sLog.outBasic("New system: New Quest Id sub Class %d", quest->QuestID);
									NTL_TS_T_ID triggerId = _player->GetQuestManager()->FindTriggerByObject(objTblidx, _player->GetWorldTableID());
									sLog.outBasic("New System: New Ts Trigger %d", triggerId);
									//New System

									int indexClass = _player->GetAttributesManager()->questSubCls.objChoseIndex;
									sLog.outDetail("New Quest Id sub Class %d", _player->GetAttributesManager()->questSubCls.objData[indexClass].specificQuestId);
									if (_player->GetAttributesManager()->questSubCls.objData[indexClass].specificQuestId == quest->QuestID)
									{
										sLog.outDetail("New USE Trigger subclass");
										int index = _player->GetAttributesManager()->questSubCls.objChoseIndex;
										objTriggerId = _player->GetAttributesManager()->questSubCls.objData[index].triggerObject;
										sLog.outDetail("New Ts Trigger %d", objTriggerId);
									}

									if (FindObjectTriggerInformation(objTriggerId, quest, req->hTarget, objTblidx) == RESULT_SUCCESS)
									{
										sGU_TS_EXCUTE_TRIGGER_OBJECT_RES res;
										res.wOpCode = GU_TS_EXCUTE_TRIGGER_OBJECT_RES;
										res.wPacketSize = sizeof(sGU_TS_EXCUTE_TRIGGER_OBJECT_RES) - 2;
										res.wResultCode = RESULT_SUCCESS;
										res.hTriggerObject = req->hTarget;
										//SendPacket((char*)&res, sizeof(sGU_TS_EXCUTE_TRIGGER_OBJECT_RES));
										sLog.outDetail("New Item trigger: %d %d %d", res.hTriggerObject, req->hSource, req->hTarget);
										break;
									}
								}
							}
							break;
						}
						}
					}
				}
				//New System

				/*for (int i = 0; i <= 30; i++)
				{
					//--------------------------------
					if (_player->GetAttributesManager()->QuestDat[i].QuestID == 0)
					{
						continue;
					}
					sLog.outDebug("EVT TYPE %d", _player->GetAttributesManager()->QuestDat[i].evtDataType);
					switch (_player->GetAttributesManager()->QuestDat[i].evtDataType)
					{
						case eSTOC_EVT_DATA_TYPE_OBJECT_ITEM:
						{
							for (int slot = 0; slot < _player->GetAttributesManager()->QuestDat[i].uEvtData.MAX_OBJECT_ITEM; slot++)
							{
								sLog.outDebug("ITEM COUNT %d", _player->GetAttributesManager()->QuestDat[i].uEvtData.sObjectItemCnt[slot].nCurItemCnt);

								
								sLog.outError("QUEST ID: %d", _player->GetAttributesManager()->QuestDat[i].QuestID);
								if (_player->GetAttributesManager()->QuestDat[i].uEvtData.sObjectItemCnt[slot].nCurItemCnt <
									_player->GetAttributesManager()->QuestDat[i].uEvtData.sObjectItemCnt[slot].nItemCnt)
								{
									sLog.outDebug("Item Tblidx %d %d", _player->GetAttributesManager()->QuestDat[i].uEvtData.sObjectItemCnt[slot].uiItemIdx,
										((WorldObject*)reference->getSource())->GetTblidx());

									NTL_TS_T_ID objTriggerId = _player->GetAttributesManager()->QuestDat[i].QuestID;

									
									int indexClass = _player->GetAttributesManager()->questSubCls.objChoseIndex;
									sLog.outDebug("Quest Id sub Class %d", _player->GetAttributesManager()->questSubCls.objData[indexClass].specificQuestId);
									if (_player->GetAttributesManager()->questSubCls.objData[indexClass].specificQuestId == _player->GetAttributesManager()->QuestDat[i].QuestID) 
									{
										sLog.outDebug("USE Trigger subclass");
										int index = _player->GetAttributesManager()->questSubCls.objChoseIndex;
										objTriggerId = _player->GetAttributesManager()->questSubCls.objData[index].triggerObject;
										sLog.outDebug("Ts Trigger %d", objTriggerId);
									}

									if (FindObjectTriggerInformation(objTriggerId, &_player->GetAttributesManager()->QuestDat[i], req->hTarget, objTblidx) == RESULT_SUCCESS)
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
									/*}
								}
							}
							break;
						}
					}
				}*/

				//--------------------------------

				break;
			}
		}
	}
 }