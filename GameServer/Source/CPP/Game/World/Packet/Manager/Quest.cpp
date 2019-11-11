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
	/*if (QuestID == 2 || QuestID == 1924)
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

ResultCodes WorldSession::ProcessTsContGAct(CDboTSContGAct * contGAct)
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
			case DBO_ACT_TYPE_ID_ACT_STOCEVT:
			{
				CDboTSActSToCEvt* sToCEvt = (CDboTSActSToCEvt*)contGAct->GetChildEntity(i);
				if (sToCEvt == NULL)
				{
					return RESULT_FAIL;
				}
				sLog.outDetail("Quest %d", sToCEvt->GetEvtDataType());
				if (CheckEvtDataType(sToCEvt) == RESULT_FAIL)
				{
					return RESULT_FAIL;
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

		for (int rw = 0; rw < QUEST_REWARD_DEF_MAX_CNT; rw++)
		{
			if (rewardTbl->rewardDefData[rw].rwdIdx == INVALID_TBLIDX)
			{
				continue;
			}

			sQUEST_REWARD_SELECT_TBLDAT* rewardSelect = (sQUEST_REWARD_SELECT_TBLDAT*)sTBM.GetQuestRewardSelectTable()->FindData(rewardTbl->rewardDefData[rw].rwdIdx);

			if (rewardSelect)
			{
				sLog.outDebug("Reward Select table: %d type: %d", rewardSelect->tblidx, rewardSelect->unknown);

				switch (rewardSelect->unknown)
				{
					case eREWARD_SLOT_TYPE_SELECTION:
					{
						break;
					}
					case eREWARD_SLOT_TYPE_DEFAULT:
					{
						for (int itRw = 0; itRw < QUEST_REWARD_SELECT_MAX_CNT; itRw++)
						{
							switch (rewardSelect->rewardData[itRw].unknown)
							{
								case eREWARD_TYPE_NORMAL_ITEM:
								{
									sITEM_TBLDAT* itemTbl = (sITEM_TBLDAT*)sTBM.GetItemTable()->FindData(rewardSelect->rewardData[itRw].itemTblidx);

									if (itemTbl)
									{
										sLog.outDebug("Item tblidx :%d", itemTbl->tblidx);
										sITEM_PROFILE createdItem;
										WORD result = _player->GetInventoryManager()->PerformShopBuy(itemTbl->tblidx, rewardSelect->rewardData[itRw].amount, createdItem);
										if (result == GAME_SUCCESS && createdItem.tblidx != INVALID_TBLIDX)
										{
											sLog.outDetail("Item Reward Created\n");
											SendItemCreate(&createdItem);
										}
									}
									break;
								}
							}
						}
						break;
					}
				}
			}

			sITEM_TBLDAT* itemTbl = (sITEM_TBLDAT*)sTBM.GetItemTable()->FindData(rewardTbl->rewardDefData[rw].rwdIdx);
			if (itemTbl)
			{
				sITEM_PROFILE createdItem;
				WORD result = _player->GetInventoryManager()->PerformShopBuy(itemTbl->tblidx, rewardTbl->rewardDefData[rw].Amount, createdItem);
				if (result == GAME_SUCCESS && createdItem.tblidx != INVALID_TBLIDX)
				{
					sLog.outDetail("Item Reward Created\n");
					SendItemCreate(&createdItem);
				}
			}
		}

		for (int rw = 0; rw < QUEST_REWARD_SEL_MAX_CNT; rw++)
		{
			if (rewardTbl->rewardDefData[rw].rwdIdx == INVALID_TBLIDX)
			{
				continue;
			}

			sQUEST_REWARD_SELECT_TBLDAT* rewardSelect = (sQUEST_REWARD_SELECT_TBLDAT*)sTBM.GetQuestRewardSelectTable()->FindData(rewardTbl->rewardDefData[rw].rwdIdx);

			if (rewardSelect)
			{
				sLog.outDebug("Reward Select table: %d type: %d", rewardSelect->tblidx, rewardSelect->unknown);

				switch (rewardSelect->unknown)
				{
				case eREWARD_SLOT_TYPE_DEFAULT:
				{
					break;
				}
				case eREWARD_SLOT_TYPE_SELECTION:
				{
					switch (rewardSelect->rewardData[dwParam].unknown)
					{
						case eREWARD_TYPE_NORMAL_ITEM:
						{
							sITEM_TBLDAT* itemTbl = (sITEM_TBLDAT*)sTBM.GetItemTable()->FindData(rewardSelect->rewardData[dwParam].itemTblidx);

							if (itemTbl)
							{
								sLog.outDebug("Item tblidx :%d", itemTbl->tblidx);
								sITEM_PROFILE createdItem;
								WORD result = _player->GetInventoryManager()->PerformShopBuy(itemTbl->tblidx, rewardSelect->rewardData[dwParam].amount, createdItem);
								if (result == GAME_SUCCESS && createdItem.tblidx != INVALID_TBLIDX)
								{
									sLog.outDetail("Item Reward Created\n");
									SendItemCreate(&createdItem);
								}
							}
							break;
						}
					}
					break;
				}
				}
			}

			sITEM_TBLDAT* itemTbl = (sITEM_TBLDAT*)sTBM.GetItemTable()->FindData(rewardTbl->rewardDefData[rw].rwdIdx);
			if (itemTbl)
			{
				sITEM_PROFILE createdItem;
				WORD result = _player->GetInventoryManager()->PerformShopBuy(itemTbl->tblidx, rewardTbl->rewardDefData[rw].Amount, createdItem);
				if (result == GAME_SUCCESS && createdItem.tblidx != INVALID_TBLIDX)
				{
					sLog.outDetail("Item Reward Created\n");
					SendItemCreate(&createdItem);
				}
			}
		}
		/*
			strToken = str.substr(pos + 1, std::string::npos);
			unsigned int uiTblId = (unsigned int)atof(strToken.c_str());
			sITEM_PROFILE createdItem;
			WORD result = _player->GetInventoryManager()->PerformShopBuy(uiTblId, 1, createdItem);
			if (result == GAME_SUCCESS && createdItem.tblidx != INVALID_TBLIDX)
			{
				sLog.outDetail("Item Created\n");
				SendItemCreate(&createdItem);
			}
			*/

		DWORD bonus = 0;

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
	}
}

ResultCodes WorldSession::FindQuestInformation(sUG_TS_CONFIRM_STEP_REQ * req)
{
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
			if (ProcessTsContGAct(contGAct) == RESULT_FAIL)
			{
				return RESULT_FAIL;
			}
			SendQuestSVRevtStartNotify(req->tId, req->tcCurId, req->tcNextId);
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

ResultCodes	WorldSession::CheckEvtDataType(CDboTSActSToCEvt* sToCEvt)
{
	switch (sToCEvt->GetEvtDataType())
	{
		case eSTOC_EVT_DATA_TYPE_MOB_KILL_CNT:
		{
			CNtlTSTrigger* trigger = (CNtlTSTrigger*)sToCEvt->GetRoot();

			if (trigger == NULL)
			{
				return RESULT_FAIL;
			}

			int freeslot = 0;
			for (int i = 0; i <= 30; i++)
			{
				if (_player->GetAttributesManager()->QuestDat[i].QuestID == 0 || _player->GetAttributesManager()->QuestDat[i].QuestID == INVALID_TBLIDX)
				{
					freeslot = i;
				}
			}

			_player->GetAttributesManager()->QuestDat[freeslot].QuestID = trigger->GetID();

			for (int i = 0; i < sToCEvt->GetEvtData().MAX_MOB_KILL; i++)
			{
				TBLIDX groupTblidx = sToCEvt->GetEvtData().sMobKillCnt[i].uiMobIdx;
				TBLIDX mobTblidx = sTBM.GetMobTable()->FindTblidxByGroup(groupTblidx);

				_player->GetAttributesManager()->QuestDat[freeslot].uEvtData.sMobKillCnt[i].uiMobIdx = mobTblidx;
				_player->GetAttributesManager()->QuestDat[freeslot].uEvtData.sMobKillCnt[i].nCurMobCnt = sToCEvt->GetEvtData().sMobKillCnt[i].nCurMobCnt;
				_player->GetAttributesManager()->QuestDat[freeslot].uEvtData.sMobKillCnt[i].nMobCnt = sToCEvt->GetEvtData().sMobKillCnt[i].nMobCnt;

				sLog.outError("ROOT TS: %d", trigger->GetID());
				sLog.outDetail("Mob kill: group tblidx: %d  mobTblidx: %d count: %d, curcout: %d", 
					groupTblidx, mobTblidx, sToCEvt->GetEvtData().sMobKillCnt[i].nMobCnt, sToCEvt->GetEvtData().sMobKillCnt[i].nCurMobCnt);
			}
			sLog.outDetail("Quest: type eSTOC_EVT_DATA_TYPE_MOB_KILL_CNT");
			break;
		}
		case eSTOC_EVT_DATA_TYPE_MOB_KILL_ITEM_CNT:
		{
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
			sLog.outDetail("Quest: type eSTOC_EVT_DATA_TYPE_CUSTOM_EVT_CNT");
			break;
		}
		case eSTOC_EVT_DATA_TYPE_VISIT:
		{
			sLog.outDetail("Quest: type eSTOC_EVT_DATA_TYPE_VISIT");
			break;
		}
	}
	return RESULT_SUCCESS;
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

 void WorldSession::SendQuestCompleteInfo()
{
	sGU_AVATAR_QUEST_COMPLETE_INFO info;
	memset(&info, 0, sizeof sGU_AVATAR_QUEST_COMPLETE_INFO);
    info.wOpCode = GU_AVATAR_QUEST_COMPLETE_INFO;
    info.wPacketSize = sizeof(sGU_AVATAR_QUEST_COMPLETE_INFO) -2;
	info.completeInfo.abyQCInfo[0] = 0;

    SendPacket((char*)&info, sizeof sGU_AVATAR_QUEST_COMPLETE_INFO);
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

	 SendPacket((char*)&res, sizeof sGU_QUEST_GIVEUP_RES);
 }