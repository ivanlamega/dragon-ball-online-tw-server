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
#include <QuestWrapper.h>
#include <XmlParser2/XmlParser2.h>


void WorldSession::GetQuestPortalInfo(DWORD QuestID, DWORD tcCurId, DWORD tcNextId)
{
	if (QuestID == 1 && tcCurId == 254)
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
	}
}
void WorldSession::GetQuestInfo(DWORD QuestID, DWORD tcCurId, DWORD tcNextId)
{
	int freeslot = 0;	
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
	}	
	if (QuestID == 3 || QuestID == 1925)
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
	}
	if (QuestID == 4)
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
	}

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
			if (req->tcCurId == 2)
			{
				sGU_QUEST_SVREVT_START_NFY start;
				start.wOpCode = GU_QUEST_SVREVT_START_NFY;
				start.wPacketSize = sizeof(sGU_QUEST_SVREVT_START_NFY) - 2;
				start.tId = req->tId;
				start.tcId = req->tcCurId;
				start.taId = req->tcNextId;				
				SendPacket((char*)&start, sizeof(sGU_QUEST_SVREVT_START_NFY));
				GetQuestInfo(req->tId, req->tcCurId, req->tcNextId);
			}

			/////////////////////////////////////////////////////////
			
			FindQuestInformation(req);

		}
		if (req->byTsType == TS_TYPE_PC_TRIGGER_CS)
		{
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
					_player->GetAttributesManager()->QuestDat[i].MobID == INVALID_TBLIDX;
					_player->GetAttributesManager()->QuestDat[i].count == INVALID_TBLIDX;
					_player->GetAttributesManager()->QuestDat[i].Maxcount == INVALID_TBLIDX;
				}

			}
			//sLog.outDebug("RWquestID %d", RWquestID);
			sQUEST_REWARD_TBLDAT * tbldat = reinterpret_cast<sQUEST_REWARD_TBLDAT*>(dat->FindData(RWquestID));
			if (tbldat != NULL)
			{							
				if (_player->GetPcProfile()->byLevel < 70)
				{
					DWORD exp = tbldat->EXP;

					sGU_UPDATE_CHAR_EXP expPacket;				
					DWORD bonus = 0;

					expPacket.dwIncreasedExp = exp + bonus;
					expPacket.dwAcquisitionExp = exp;
					expPacket.dwBonusExp = bonus;
					expPacket.wOpCode = GU_UPDATE_CHAR_EXP;
					expPacket.wPacketSize = sizeof(sGU_UPDATE_CHAR_EXP) - 2;
					expPacket.handle = _player->GetHandle();
					_player->GetPcProfile()->dwCurExp += (exp + bonus);
					expPacket.dwCurExp = _player->GetPcProfile()->dwCurExp;

					_player->UpdateZennyAmount(tbldat->Zenny, eZENNY_CHANGE_TYPE::ZENNY_CHANGE_TYPE_DB_REWARD);

					if (_player->GetPcProfile()->dwCurExp >= _player->GetPcProfile()->dwMaxExpInThisLevel)
					{
						expPacket.dwCurExp = _player->GetPcProfile()->dwCurExp -= _player->GetPcProfile()->dwMaxExpInThisLevel;
						_player->LevelUp();
					}					

					SendPacket((char*)&expPacket, sizeof(sGU_UPDATE_CHAR_EXP));
				}
			}
		}
		SendPacket((char*)&res, sizeof(sGU_TS_CONFIRM_STEP_RES));
	}
}

void WorldSession::FindQuestInformation(sUG_TS_CONFIRM_STEP_REQ * req)
{
	// example ts
	CNtlTSCont * cont = sTSM.FindQuestFromTS(req->tId)->GetGroup(NTL_TS_MAIN_GROUP_ID)->GetChildCont(req->tcCurId);
	for (int i = 0; i < cont->GetNumOfChildEntity(); i++)
	{
		sLog.outDetail("Cont: %s %d, %d", cont->GetChildEntity(i)->GetClassNameW(), cont->GetChildEntity(i)->GetEntityType(), DBO_COND_TYPE_ID_CHECK_LVL);
		switch (cont->GetChildEntity(i)->GetEntityType())
		{
		case DBO_COND_TYPE_ID_CHECK_LVL:
		{
			CDboTSCheckLvl * checkLvl = ((CDboTSCheckLvl*)cont->GetChildEntity(i));
			sLog.outDetail("Quest: minlvl %d maxlvl %d", checkLvl->GetMinLvl(), checkLvl->GetMaxLvl());
			break;
		}
		case DBO_COND_TYPE_ID_CHECK_CLRQST:
		{
			CDboTSCheckClrQst * clrQst = ((CDboTSCheckClrQst*)cont->GetChildEntity(i));
			sLog.outDetail("Quest: not size: %d  and size: %d or size: %d", clrQst->GetNotIdList().size(), clrQst->GetAndIdList().size(), clrQst->GetOrIdList().size());
			break;
		}
		case DBO_EVENT_TYPE_ID_CLICK_NPC:
		{
			CDboTSClickNPC * clickNpc = ((CDboTSClickNPC*)cont->GetChildEntity(i));
			sLog.outDetail("Quest: Npc tblidx %d", clickNpc->GetNPCIdx());
			break;
		}
		case DBO_COND_TYPE_ID_CHECK_PCRACE:
		{
			CDboTSCheckPCRace * pcRace = ((CDboTSCheckPCRace*)cont->GetChildEntity(i));
			sLog.outDetail("Quest: race flag %d", pcRace->GetRaceFlags());
			break;
		}
		case DBO_COND_TYPE_ID_CHECK_PCCLS:
		{
			CDboTSCheckPCCls * pcClass = ((CDboTSCheckPCCls*)cont->GetChildEntity(i));
			sLog.outDetail("Quest: class flag %d", pcClass->GetClsFlags());
			break;
		}
		}
	}
}