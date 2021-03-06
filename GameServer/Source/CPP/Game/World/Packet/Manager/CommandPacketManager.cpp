#include <Game\World\WorldSession.h>
#include <Game\Object\Player.h>
#include <Game\Object\Mob.h>
#include <Game\Object\Npc.h>
#include <Game\Object\Object.h>
#include <Packet\Game\PacketGU.h>
#include <Packet\Game\PacketUG.h>
#include <Logger.h>
#include <World.h>
#include <boost/algorithm/string.hpp>

//----------------------------------------
//	Send announce to all player
//----------------------------------------
void World::SendAnnounce(std::string message)
{
	sGU_SYSTEM_DISPLAY_TEXT sNotice;

	sNotice.wOpCode = GU_SYSTEM_DISPLAY_TEXT;
	sNotice.wPacketSize = sizeof(sGU_SYSTEM_DISPLAY_TEXT) - 2;

	sNotice.byDisplayType = eSERVER_TEXT_TYPE::SERVER_TEXT_EMERGENCY;
	wcscpy_s(sNotice.awchMessage, BUDOKAI_MAX_NOTICE_LENGTH + 1, charToWChar(message.c_str()));
	wcscpy_s(sNotice.awGMChar, MAX_SIZE_CHAR_NAME_UNICODE, (L" GM "));
	sNotice.wMessageLengthInUnicode = (WORD)wcslen(sNotice.awchMessage);

	SendToAll((char*)&sNotice, sizeof(sGU_SYSTEM_DISPLAY_TEXT));
}
//----------------------------------------
//	Spawn NPC by Tblidx
//----------------------------------------
HOBJECT WorldSession::SpawnNPCByTblidx(TBLIDX NPCTblidx)
{
	NPCTable* NpcTable = sTBM.GetNpcTable();
	sNPC_TBLDAT* pNPCTblData = reinterpret_cast<sNPC_TBLDAT*>(NpcTable->FindData(NPCTblidx));
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
		spawnData.Tblidx = NPCTblidx;

		spawnData.fLastWalkingSpeed = 10;
		spawnData.fLastRunningSpeed = 10;
		spawnData.fLastAirSpeed = 10;
		spawnData.fLastAirDashSpeed = 10;
		spawnData.fLastAirDashAccelSpeed = 10;

		spawnData.State.sCharStateBase.aspectState.sAspectStateBase.byAspectStateId = 255;
		spawnData.State.sCharStateBase.vCurLoc.x = _player->m_position.x + rand() % 5;
		spawnData.State.sCharStateBase.vCurLoc.y = _player->m_position.y;
		spawnData.State.sCharStateBase.vCurLoc.z = _player->m_position.z + rand() % 5;
		spawnData.State.sCharStateBase.vCurDir.x = _player->m_rotation.x + rand() % 5;
		spawnData.State.sCharStateBase.vCurDir.y = _player->m_rotation.y;
		spawnData.State.sCharStateBase.vCurDir.z = _player->m_rotation.z + rand() % 5;
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
				return handle;
				//_player->GetAttributesManager()->lastNPCQuest = INVALID_TBLIDX;
			}
			else
				delete created_Npc;
		}
	}
}
//----------------------------------------
//	Spawn Mob by Tblidx
//----------------------------------------
HOBJECT WorldSession::SpawnMobByTblidx(TBLIDX mobTblidx)
{
	MobTable* MobTable = sTBM.GetMobTable();
	sMOB_TBLDAT* pMOBTblData = reinterpret_cast<sMOB_TBLDAT*>(MobTable->FindData(mobTblidx));
	if (pMOBTblData != NULL)
	{

		SpawnMOB spawnData;
		memset(&spawnData, 0, sizeof(SpawnMOB));

		spawnData.wOpCode = GU_OBJECT_CREATE;
		spawnData.wPacketSize = sizeof(SpawnMOB) - 2;


		spawnData.curEP = pMOBTblData->wBasic_EP;
		spawnData.curLP = pMOBTblData->wBasic_LP;
		spawnData.Handle = sWorld.AcquireSerialId();
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
		spawnData.State.sCharStateBase.vCurLoc.x = _player->m_position.x + rand() % 5;
		spawnData.State.sCharStateBase.vCurLoc.y = _player->m_position.y;
		spawnData.State.sCharStateBase.vCurLoc.z = _player->m_position.z + rand() % 5;
		spawnData.State.sCharStateBase.vCurDir.x = _player->m_rotation.x + rand() % 5;
		spawnData.State.sCharStateBase.vCurDir.y = _player->m_rotation.y;
		spawnData.State.sCharStateBase.vCurDir.z = _player->m_rotation.z + rand() % 5;
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
				printf("Mob ID %d inserted into map", mobTblidx);
				return spawnData.Handle;
			}
			else
				delete created_mob;

		}
	}
}
//----------------------------------------
//	Interpret GM command
//----------------------------------------
void WorldSession::ExecuteServerCommand(Packet& packet)
{

	sUG_SERVER_COMMAND * pServerCmd = (sUG_SERVER_COMMAND*)packet.GetPacketBuffer();
	std::string str = WC2MB(pServerCmd->awchCommand);
	sLog.outDetail("GameMaster Command: %s", str.c_str());
	size_t pos = str.find(" ");

	std::string strToken = str.substr(0, pos);
	if (_player->GetPcProfile()->bIsGameMaster == true)
	{
		if (strToken == "@level")
		{
			sLog.outDetail("GM Level Modified");
			strToken = str.substr(pos + 1, std::string::npos);
			unsigned int Level = (unsigned int)atof(strToken.c_str());
			if (Level <= 1)
			{
				Level = 1;
			}
			if (Level >= 100)
			{
				Level = 100;
			}
			_player->LevelUpByComand(Level);
			return;
		}
		else if (strToken == "@getquest")
		{
			sLog.outDetail("Getting a quest...");
			strToken = str.substr(pos + 1, std::string::npos);
			unsigned int tid = (unsigned int)atof(strToken.c_str());
			sGU_QUEST_SHARE_NFY nfy;
			nfy.wOpCode = GU_QUEST_SHARE_NFY;
			nfy.wPacketSize = sizeof(sGU_QUEST_SHARE_NFY) - 2;
			nfy.hActor = _player->GetHandle();
			nfy.wResultCode = RESULT_SUCCESS;
			nfy.tId = tid;
			SendPacket((char*)&nfy, sizeof(sGU_QUEST_SHARE_NFY));
		}
		else if (strToken == "@gettarget")
		{
			strToken = str.substr(pos + 1, std::string::npos);
			unsigned int teid = (unsigned int)atof(strToken.c_str());

			sGU_SKILL_TARGET_LIST_REQ req;
			req.wOpCode = GU_SKILL_TARGET_LIST_REQ;
			req.wPacketSize = sizeof(sGU_SKILL_TARGET_LIST_REQ) - 2;
			req.byAvatarType = 0;
			SendPacket((char*)&req, sizeof(sGU_SKILL_TARGET_LIST_REQ));
		}
		else if (strToken == "@skillopt")
		{
			sLog.outDetail("Respawn object quest");
			strToken = str.substr(pos + 1, std::string::npos);
			unsigned int value = (unsigned int)atof(strToken.c_str());
			int valor = 10;
			_player->GetAttributesManager()->SetCastingTimeChangePercent(0);
			_player->GetAttributesManager()->SetCoolTimeChangePercent(0);
			_player->GetAttributesManager()->SetKeepTimeChangePercent(0);
			_player->GetAttributesManager()->SetKeepTimeChangeSeconds(0);
			_player->GetAttributesManager()->SetDotValueChangePercent(0);
			_player->GetAttributesManager()->SetDotTimeChangeAbsolute(0);
			_player->GetAttributesManager()->SetRequiredEpChangePercent(0);
			switch (value)
			{
				case 1:
				{
					_player->GetAttributesManager()->SetCastingTimeChangePercent(valor);
					break;
				}
				case 2:
				{
					_player->GetAttributesManager()->SetCoolTimeChangePercent(valor);
					break;
				}
				case 3:
				{
					_player->GetAttributesManager()->SetKeepTimeChangePercent(valor);
					break;
				}
				case 4:
				{
					_player->GetAttributesManager()->SetKeepTimeChangeSeconds(valor);
					break;
				}
				case 5: 
				{
					_player->GetAttributesManager()->SetRequiredEpChangePercent(valor);
					break;
				}
				case 6: 
				{
					_player->GetAttributesManager()->SetDotValueChangePercent(valor);
					break;
				}
				case 7:
				{
					_player->GetAttributesManager()->SetDotTimeChangeAbsolute(value);
					break;
				}
			}
			return;
		}
		else if (strToken == "@tp")
		{
			sLog.outDetail("GM Bot Check");
			strToken = str.substr(pos + 1, std::string::npos);
			unsigned int Point = (unsigned int)atof(strToken.c_str());
			_player->TeleportByCommand(Point);
			return;
		}
		else if (strToken == "@kamisama")
		{			
			strToken = str.substr(pos + 1, std::string::npos);
			unsigned int Point = (unsigned int)atof(strToken.c_str());
			_player->TeleportByCommand(211000);
			return;
		}
		else if (strToken == "@airspeed")
		{
			sLog.outDetail("GM LearnTitle Modified");
			strToken = str.substr(pos + 1, std::string::npos);
			unsigned int speed = (unsigned int)atof(strToken.c_str());
			_player->GetAttributesManager()->GetPlayerProfile()->avatarAttribute.fBaseAirSpeed = speed;
			_player->GetAttributesManager()->GetPlayerProfile()->avatarAttribute.fLastAirSpeed = speed;
		}
		else if (strToken == "@dashspeed")
		{
			sLog.outDetail("GM LearnTitle Modified");
			strToken = str.substr(pos + 1, std::string::npos);
			unsigned int speed = (unsigned int)atof(strToken.c_str());
			_player->GetAttributesManager()->GetPlayerProfile()->avatarAttribute.fBaseAirDashSpeed = speed;
			_player->GetAttributesManager()->GetPlayerProfile()->avatarAttribute.fLastAirDashSpeed = speed;
		}
		else if (strToken == "@dash2speed")
		{
			sLog.outDetail("GM LearnTitle Modified");
			strToken = str.substr(pos + 1, std::string::npos);
			unsigned int speed = (unsigned int)atof(strToken.c_str());
			_player->GetAttributesManager()->GetPlayerProfile()->avatarAttribute.fBaseAirDash2Speed = speed;
			_player->GetAttributesManager()->GetPlayerProfile()->avatarAttribute.fLastAirDash2Speed = speed;
		}
		else if (strToken == "@runspeed")
		{
			sLog.outDetail("GM LearnTitle Modified");
			strToken = str.substr(pos + 1, std::string::npos);
			unsigned int speed = (unsigned int)atof(strToken.c_str());
			_player->GetAttributesManager()->GetPlayerProfile()->avatarAttribute.fBaseRunSpeed = speed;
			_player->GetAttributesManager()->GetPlayerProfile()->avatarAttribute.fLastRunSpeed = speed;
		}
		else if (strToken == "@skillspeed")
		{
			sLog.outDetail("GM LearnTitle Modified");
			strToken = str.substr(pos + 1, std::string::npos);
			unsigned int speed = (unsigned int)atof(strToken.c_str());
			_player->GetAttributesManager()->GetPlayerProfile()->avatarAttribute.baseSkillSpeed = speed;
			_player->GetAttributesManager()->GetPlayerProfile()->avatarAttribute.SkillSpeed = speed;
		}
		else if (strToken == "@attackspeed")
		{
			strToken = str.substr(pos + 1, std::string::npos);
			unsigned int speed = (unsigned int)atof(strToken.c_str());
			_player->GetAttributesManager()->GetPlayerProfile()->avatarAttribute.wBaseAttackSpeedRate = speed;
			_player->GetAttributesManager()->GetPlayerProfile()->avatarAttribute.wLastAttackSpeedRate = speed;
			_player->GetAttributesManager()->UpdateAttackspeedRate(INVALID_SYSTEM_EFFECT_CODE, speed, false, false);
			sLog.outDetail("Update speed %d", speed);
		}
		else if (strToken == "@setspeed")
		{
			sLog.outDetail("GM LearnTitle Modified");
			strToken = str.substr(pos + 1, std::string::npos);
			unsigned int speed = (unsigned int)atof(strToken.c_str());
			_player->SetSpeed(speed);
			return;
		}	
		else if (strToken == "@addtitle")
		{
			sLog.outDetail("GM LearnTitle Modified");
			strToken = str.substr(pos + 1, std::string::npos);
			unsigned int TitleID = (unsigned int)atof(strToken.c_str());
			_player->SendAddTitle(TitleID);								
			return;
		}
		else if (strToken == "@god")
		{
			sLog.outDetail("God Mode");
			strToken = str.substr(pos + 1, std::string::npos);
			unsigned int TitleID = (unsigned int)atof(strToken.c_str());
			_player->GetAttributesManager()->SetLastCon(20000);
			_player->GetAttributesManager()->SetLastFoc(20000);
			_player->GetAttributesManager()->SetLastDex(20000);
			_player->GetAttributesManager()->SetLastEng(20000);
			_player->GetAttributesManager()->SetLastSol(20000);
			_player->GetAttributesManager()->SetLastStr(20000);
			_player->GetAttributesManager()->SetLastEnergyOffence(20000);
			_player->GetAttributesManager()->SetLastEnergyCriticalRate(20000);
			_player->GetAttributesManager()->SetLastEnergyDefence(20000);
			_player->GetAttributesManager()->SetLastAttackRate(20000);
			_player->GetAttributesManager()->SetLastDodgeRate(20000);
			_player->GetAttributesManager()->SetLastPhysicalOffence(20000);
			_player->GetAttributesManager()->SetLastPhysicalDefence(20000);
			_player->GetAttributesManager()->SetLastPhysicalCriticalRate(20000);
			_player->GetAttributesManager()->SetLastMaxLP(20000);
			_player->GetAttributesManager()->SetLastMaxEP(20000);
			_player->GetAttributesManager()->SetLastLPRegen(20000);
			_player->GetAttributesManager()->SetLastEPRegen(20000);

			return;
		}
		else if (strToken == "@expbonus")
		{

			strToken = str.substr(pos + 1, std::string::npos);
			unsigned int Bonus = (unsigned int)atof(strToken.c_str());			
			if (Bonus == 0)
			{
				sGU_SYSTEM_DISPLAY_TEXT sNotice;
				sNotice.wOpCode = GU_SYSTEM_DISPLAY_TEXT;
				sNotice.wPacketSize = sizeof(sGU_SYSTEM_DISPLAY_TEXT) - 2;
				sNotice.byDisplayType = 3;
				wcscpy_s(sNotice.awchMessage, BUDOKAI_MAX_NOTICE_LENGTH, L" Exp Event End");
				wcscpy_s(sNotice.awGMChar, MAX_SIZE_CHAR_NAME_UNICODE, (L" GM "));
				sNotice.wMessageLengthInUnicode = 50;
				sWorld.SendToAll((char*)&sNotice, sizeof(sGU_SYSTEM_DISPLAY_TEXT));
				sWorld.BonusActive = false;
				sWorld.BonuxEXP = 0;
			}
			if (Bonus >= 1) /*	Use multipliers like 2, 3, 4. Big values can crash the server.*/
			{
				sGU_SYSTEM_DISPLAY_TEXT sNotice;
				sNotice.wOpCode = GU_SYSTEM_DISPLAY_TEXT;
				sNotice.wPacketSize = sizeof(sGU_SYSTEM_DISPLAY_TEXT) - 2;
				sNotice.byDisplayType = 3;
				wcscpy_s(sNotice.awchMessage, BUDOKAI_MAX_NOTICE_LENGTH, L" Exp Event Is Running");
				wcscpy_s(sNotice.awGMChar, MAX_SIZE_CHAR_NAME_UNICODE, (L"System"));
				sNotice.wMessageLengthInUnicode = 50;
				sWorld.SendToAll((char*)&sNotice, sizeof(sGU_SYSTEM_DISPLAY_TEXT));
				sWorld.BonusActive = true;
				sWorld.BonuxEXP = Bonus;
			}
			return;
		}
		else if (strToken == "@setclass")
		{
			sLog.outDetail("GM Class Modified");
			strToken = str.substr(pos + 1, std::string::npos);
			unsigned int clase = (unsigned int)atof(strToken.c_str());
			_player->ConvertClass(clase, _player->GetTarget());
			return;
		}
		else if (strToken == "@setsize")
		{
			sLog.outDetail("GM Size Modified");
			strToken = str.substr(pos + 1, std::string::npos);
			unsigned int Size = (unsigned int)atof(strToken.c_str());
			_player->SendUpdateSize(Size);
			return;
		}
		else if (strToken == "@setnight")
		{
			strToken = str.substr(pos + 1, std::string::npos);
			unsigned int zoneId = (unsigned int)atof(strToken.c_str());
			sGU_AVATAR_ZONE_INFO zoneinfo;
			zoneinfo.wOpCode = GU_AVATAR_ZONE_INFO;
			zoneinfo.wPacketSize = sizeof(sGU_AVATAR_ZONE_INFO) - 2;
			zoneinfo.zoneInfo.bIsDark = zoneId;
			zoneinfo.zoneInfo.zoneId = 0; // 0 namek start zone
			//SendPacket((char*)&zoneinfo, sizeof(sGU_AVATAR_ZONE_INFO));
			sWorld.SendToAll((char*)&zoneinfo, sizeof(sGU_AVATAR_ZONE_INFO));
		}		
		else if (strToken == "@addnpc")
		{
			strToken = str.substr(pos + 1, std::string::npos);
			unsigned int NPCID = (unsigned int)atof(strToken.c_str());
			printf("Executing NPC Func\n");

			SpawnNPCByTblidx(NPCID);
			printf("Executed\n");
			return;
		}
		else if (strToken == "@addmob")
		{
			strToken = str.substr(pos + 1, std::string::npos);
			unsigned int MobID = (unsigned int)atof(strToken.c_str());
			printf("Executing Mob Func\n");

			SpawnMobByTblidx(MobID);
			/*MobTable * MobTable = sTBM.GetMobTable();
			sMOB_TBLDAT * pMOBTblData = reinterpret_cast<sMOB_TBLDAT*>(MobTable->FindData(MobID));
			if (pMOBTblData != NULL)
			{

				SpawnMOB spawnData;
				memset(&spawnData, 0, sizeof(SpawnMOB));

				spawnData.wOpCode = GU_OBJECT_CREATE;
				spawnData.wPacketSize = sizeof(SpawnMOB) - 2;


				spawnData.curEP = pMOBTblData->wBasic_EP;
				spawnData.curLP = pMOBTblData->wBasic_LP;
				spawnData.Handle = sWorld.AcquireSerialId();
				spawnData.Level = pMOBTblData->byLevel;
				spawnData.maxEP = pMOBTblData->wBasic_EP;
				spawnData.maxLP = pMOBTblData->wBasic_LP;
				spawnData.Size = 10;
				spawnData.Type = OBJTYPE_MOB;
				spawnData.Tblidx = MobID;

				spawnData.fLastWalkingSpeed = 2;
				spawnData.fLastRunningSpeed = 2;
				spawnData.fLastAirgSpeed = 2;
				spawnData.fLastAirgDashSpeed = 2;
				spawnData.fLastAirgDashAccelSpeed = 2;

				spawnData.State.sCharStateBase.aspectState.sAspectStateBase.byAspectStateId = 255;
				spawnData.State.sCharStateBase.vCurLoc.x = _player->m_position.x + rand() % 5;
				spawnData.State.sCharStateBase.vCurLoc.y = _player->m_position.y;
				spawnData.State.sCharStateBase.vCurLoc.z = _player->m_position.z + rand() % 5;
				spawnData.State.sCharStateBase.vCurDir.x = _player->m_rotation.x + rand() % 5;
				spawnData.State.sCharStateBase.vCurDir.y = _player->m_rotation.y;
				spawnData.State.sCharStateBase.vCurDir.z = _player->m_rotation.z + rand() % 5;
				spawnData.State.sCharStateBase.byStateID = eCHARSTATE::CHARSTATE_SPAWNING;

				//	sWorld.SendToAll((char*)&spawnData, sizeof(SpawnMOB));
				//Need Insert In list
				Mob* created_mob = new Mob;
				if (pMOBTblData)
				{
					if (created_mob->Create(pMOBTblData, spawnData) == true)
					{
						created_mob->GetMapRef().link(this->_player->GetMap(), created_mob);
						printf("Mob ID %d inserted into map", MobID);
					}
					else
						delete created_mob;

				}
			}*/
			printf("Executed\n");
			return;
		}
		else if (strToken == "@addmobgroup")
		{
			strToken = str.substr(pos + 1, std::string::npos);
			unsigned int MobID = (unsigned int)atof(strToken.c_str());
			printf("Executing Mob Func\n");

			MobTable * MobTable = sTBM.GetMobTable();
			sMOB_TBLDAT * pMOBTblData = reinterpret_cast<sMOB_TBLDAT*>(MobTable->FindData(MobID));
			if (pMOBTblData != NULL)
			{
				for (int i = 0; i <= 12; i++)
				{
					SpawnMOB spawnData;
					memset(&spawnData, 0, sizeof(SpawnMOB));

					spawnData.wOpCode = GU_OBJECT_CREATE;
					spawnData.wPacketSize = sizeof(SpawnMOB) - 2;


					spawnData.curEP = pMOBTblData->wBasic_EP;
					spawnData.curLP = pMOBTblData->wBasic_LP;
					spawnData.Handle = sWorld.AcquireSerialId();
					spawnData.Level = pMOBTblData->byLevel;
					spawnData.maxEP = pMOBTblData->wBasic_EP;
					spawnData.maxLP = pMOBTblData->wBasic_LP;
					spawnData.Size = 10;
					spawnData.Type = OBJTYPE_MOB;
					spawnData.Tblidx = MobID;

					spawnData.fLastWalkingSpeed = 2;
					spawnData.fLastRunningSpeed = 2;
					spawnData.fLastAirgSpeed = 2;
					spawnData.fLastAirgDashSpeed = 2;
					spawnData.fLastAirgDashAccelSpeed = 2;

					spawnData.State.sCharStateBase.aspectState.sAspectStateBase.byAspectStateId = 255;
					spawnData.State.sCharStateBase.vCurLoc.x = _player->m_position.x + rand() % 20;
					spawnData.State.sCharStateBase.vCurLoc.y = _player->m_position.y;
					spawnData.State.sCharStateBase.vCurLoc.z = _player->m_position.z + rand() % 20;
					spawnData.State.sCharStateBase.vCurDir.x = _player->m_rotation.x + rand() % 20;
					spawnData.State.sCharStateBase.vCurDir.y = _player->m_rotation.y;
					spawnData.State.sCharStateBase.vCurDir.z = _player->m_rotation.z + rand() % 20;
					spawnData.State.sCharStateBase.byStateID = eCHARSTATE::CHARSTATE_SPAWNING;

					//	sWorld.SendToAll((char*)&spawnData, sizeof(SpawnMOB));
					//Need Insert In list
					Mob* created_mob = new Mob;
					if (pMOBTblData)
					{
						if (created_mob->Create(pMOBTblData, spawnData) == true)
						{
							created_mob->GetMapRef().link(this->_player->GetMap(), created_mob);
							printf("Mob ID %d inserted into map", MobID);
						}
						else
							delete created_mob;

					}
				}
			}
			printf("Executed\n");
			return;
		}
		else if (strToken == "@giveitem")
		{
			strToken = str.substr(pos + 1, std::string::npos);
			unsigned int ItemID = (unsigned int)atof(strToken.c_str());
			Player* PlayerInfo = static_cast<Player*>(_player->GetFromList(_player->GetTarget()));
			if (PlayerInfo != NULL)
			{
				DroppedObject *dropped;
				sITEM_TBLDAT *itemSrc = NULL;
				memset(&dropped, 0, sizeof(Drop));
				dropped = new DroppedObject;
				dropped->droppedTime = GetTickCount();
				dropped->objType = OBJTYPE_DROPITEM;
				dropped->owner = PlayerInfo->GetTarget();

				dropped->item.wPacketSize = sizeof(Drop) - 2;
				dropped->item.wOpCode = GU_OBJECT_CREATE;

				dropped->item.Handle = sWorld.AcquireItemSerialId();
				dropped->item.Tblidx = ItemID;

				if ((itemSrc = (sITEM_TBLDAT*)sTBM.GetItemTable()->FindData(dropped->item.Tblidx)) == NULL)
				{
					itemSrc = (sCASHITEM_TBLDAT*)sTBM.GetCashItemTable()->FindData(dropped->item.Tblidx);
				}
				if (itemSrc != NULL)
				{
					dropped->item.Type = OBJTYPE_DROPITEM;
					dropped->item.Grade = 0;
					dropped->item.Rank = itemSrc->eRank;
					dropped->item.BattleAttribute = 0;
					dropped->item.Loc.x = _player->m_position.x + rand() % 6;
					dropped->item.Loc.y = _player->m_position.y;
					dropped->item.Loc.z = _player->m_position.z + rand() % 6;
					dropped->item.IsNew = true;
					dropped->item.NeedToIdentify = false;

					/* Add Drop to list	*/
					PlayerInfo->SendPacket((char*)&dropped->item, sizeof(Drop));
					PlayerInfo->AddDropToList(*dropped, dropped->item.Handle);
				}
			}
			//Need Insert In list			
			return;
		}
		else if (strToken == "@additem")
		{
			strToken = str.substr(pos + 1, std::string::npos);
			unsigned int uiTblId = (unsigned int)atof(strToken.c_str());
			sITEM_PROFILE createdItem;
			WORD result = _player->GetInventoryManager()->PerformShopBuy(uiTblId, 1, createdItem);
			if (result == GAME_SUCCESS && createdItem.tblidx != INVALID_TBLIDX)
			{
				sLog.outDetail("Item Created\n");
				SendItemCreate(&createdItem);
			}
			return;
		}
		else if (strToken == "@topapaya")
		{
			strToken = str.substr(pos + 1, std::string::npos);
			unsigned int Point = (unsigned int)atof(strToken.c_str());
			_player->TeleportByCommand(15);
			return;

		}
		else if (strToken == "@aspect")
		{
			sLog.outDetail("GM Mudusa Modified");
			strToken = str.substr(pos + 1, std::string::npos);
			unsigned int Point = (unsigned int)atof(strToken.c_str());
			//_player->UpdateModusaAmount(Point);
			sGU_UPDATE_CHAR_ASPECT_STATE CharAspect;
			CharAspect.wOpCode = GU_UPDATE_CHAR_ASPECT_STATE;
			CharAspect.wPacketSize = sizeof(sGU_UPDATE_CHAR_ASPECT_STATE) - 2;
			CharAspect.handle = _player->GetHandle();
			CharAspect.aspectState.sAspectStateBase.byAspectStateId = Point;
			CharAspect.aspectState.sAspectStateDetail.sVehicle.bIsEngineOn = false;
			CharAspect.aspectState.sAspectStateDetail.sVehicle.hVehicleItem = 0;
			CharAspect.aspectState.sAspectStateDetail.sVehicle.idVehicleTblidx = 0;
			sWorld.SendToAll((char*)&CharAspect, sizeof(sGU_UPDATE_CHAR_ASPECT_STATE));
			return;
		}
		else if (strToken == "@kick")
		{
		strToken = str.substr(pos + 1, std::string::npos);
		/// get player from name or kick target
		}
		else if (strToken == "@setsize")
		{
			sLog.outDetail("GM Size Modified");
			strToken = str.substr(pos + 1, std::string::npos);
			unsigned int Size = (unsigned int)atof(strToken.c_str());
			_player->SendUpdateSize(Size);
			return;
		}
		else if (strToken == "@addallskill")
		{
			strToken = str.substr(pos + 1, std::string::npos);
			unsigned int tblidx = (unsigned int)atof(strToken.c_str());
			_player->skillManager.LoadSkill(_player->charid);
			for (auto it = sTBM.GetSkillTable()->Begin(); it != sTBM.GetSkillTable()->End(); it++)
			{
				sSKILL_TBLDAT* skillData = (sSKILL_TBLDAT*)it->second;
				if (skillData != NULL)
				{
					if (_player->GetClassFlag(_player->GetMyClass(), ITEM_TYPE_UNKNOWN) == skillData->dwPC_Class_Bit_Flag)
					{
						if (skillData->bySkill_Grade == 1 && skillData->bySkill_Class != eSKILL_CLASS::SKILL_CLASS_HTB && _player->skillManager.isSkillLearned(skillData->tblidx) == false)
						{
							//sLog.outDetail("Learn the skill \n");
							LearnSkill(skillData->tblidx);
						}
					}
				}
			}
			return;
		}
		else if (strToken == "@addhtb")
		{
			strToken = str.substr(pos + 1, std::string::npos);
			unsigned int tblidx = (unsigned int)atof(strToken.c_str());
			//_player->skillManager.LoadSkill(_player->charid);
			int Slotid = NULL;
			//if (_player->GetPcProfile()->dwSpPoint >= 1 || _player->GetPcProfile()->bIsGameMaster == true)
			//{
			//	SendUpdateSkillPassiveAtributeByID(tblidx, true);
				sGU_HTB_LEARN_RES res;
				res.wOpCode = GU_HTB_LEARN_RES;
				res.wPacketSize = sizeof(sGU_HTB_LEARN_RES) - 2;
				res.wResultCode = GAME_SUCCESS;
				res.skillId = tblidx;
				res.bySkillSlot = 0;// _player->skillManager.getSkillsCount() + 1;
				res.unknown = 0;
				_player->HTBID = res.skillId;
				SendPacket((char*)&res, sizeof(sGU_HTB_LEARN_RES));
				
				//sDB.LearnSkill(skillID, _player->GetCharacterID(), nfy.bySlot);
				//Load skill for can use after that
				//_player->skillManager.LoadSkill(_player->charid);
				//SendAvatarSkillInfo();

				//SendUpdateSkillPassiveAtributeByID(skillID, false);
			return;
		}
		else if (strToken == "@tlp")
		{

			_player->GetAttributesManager()->teleportInfo.worldInfo.tblidx = 1;
			_player->GetAttributesManager()->teleportInfo.worldInfo.worldID = 1;

			_player->GetAttributesManager()->teleportInfo.position.x = 5142.0;
			_player->GetAttributesManager()->teleportInfo.position.y = 0.0;
			_player->GetAttributesManager()->teleportInfo.position.z = 4240.0;
			_player->GetAttributesManager()->teleportInfo.byTeleportType = eTELEPORT_TYPE::TELEPORT_TYPE_COMMAND;
			/*sGU_UPDATE_CHAR_CONDITION condition;
			condition.wOpCode = GU_UPDATE_CHAR_CONDITION;
			condition.wPacketSize = sizeof(sGU_UPDATE_CHAR_CONDITION) - 2;

			condition.handle = _player->GetHandle();
			condition.dwConditionFlag = 80;
			condition.unknown = 0;

			sWorld.SendToAll((char*)&condition, sizeof(sGU_UPDATE_CHAR_CONDITION));*/
			SendUpdateCharCondition(80);

			_player->GetState()->sCharStateDetail.sCharStateDespawning.byTeleportType = eTELEPORT_TYPE::TELEPORT_TYPE_COMMAND;
			_player->SetState(eCHARSTATE::CHARSTATE_DESPAWNING);
		}
		else if (strToken == "@dbhuntstart")
		{
			strToken = str.substr(pos + 1, std::string::npos);
			unsigned int sMarking = (unsigned int)atof(strToken.c_str());

			sGU_DRAGONBALL_SCHEDULE_INFO res;

			res.bIsAlive = static_cast<bool>(sMarking);
			res.byEventType = sMarking;
			res.byTermType = 1;
			res.dwMainTerm = 1;
			res.dwSubTerm = 1;
			res.nEndTime = 100;
			res.nStartTime = 1;
			res.wOpCode = GU_DRAGONBALL_SCHEDULE_INFO;
			res.wPacketSize = sizeof(sGU_DRAGONBALL_SCHEDULE_INFO) - 2;

			sWorld.SendToAll((char*)&res, sizeof(sGU_DRAGONBALL_SCHEDULE_INFO));
			if (sMarking >= 1)
			{
				sGU_SYSTEM_DISPLAY_TEXT sNotice;
				sNotice.wOpCode = GU_SYSTEM_DISPLAY_TEXT;
				sNotice.wPacketSize = sizeof(sGU_SYSTEM_DISPLAY_TEXT) - 2;
				sNotice.byDisplayType = 3;
				wcscpy_s(sNotice.awchMessage, BUDOKAI_MAX_NOTICE_LENGTH, L" Dragon Ball Hunt Start");
				wcscpy_s(sNotice.awGMChar, MAX_SIZE_CHAR_NAME_UNICODE, (L" GM "));
				sNotice.wMessageLengthInUnicode = 50;
				sWorld.SendToAll((char*)&sNotice, sizeof(sGU_SYSTEM_DISPLAY_TEXT));
				sWorld.DragonBallEventa = true;
			}
			else
			{
				sGU_SYSTEM_DISPLAY_TEXT sNotice;

				sNotice.wOpCode = GU_SYSTEM_DISPLAY_TEXT;
				sNotice.wPacketSize = sizeof(sGU_SYSTEM_DISPLAY_TEXT) - 2;
				sNotice.byDisplayType = 3;
				wcscpy_s(sNotice.awchMessage, BUDOKAI_MAX_NOTICE_LENGTH, L" Dragon Ball Hunt End");
				wcscpy_s(sNotice.awGMChar, MAX_SIZE_CHAR_NAME_UNICODE, (L" GM "));
				sNotice.wMessageLengthInUnicode = 50;

				sWorld.SendToAll((char*)&sNotice, sizeof(sGU_SYSTEM_DISPLAY_TEXT));
				sWorld.DragonBallEventa = false;
			}
			return;
		}
		else if (strToken == "@announce")
		{
			strToken = str.substr(pos + 1, std::string::npos);
			sWorld.SendAnnounce(strToken);
		}
		else if (strToken == "@notice")
		{
			strToken = str.substr(pos + 1, std::string::npos);
			sGU_SYSTEM_DISPLAY_TEXT sNotice;

			sNotice.wOpCode = GU_SYSTEM_DISPLAY_TEXT;
			sNotice.wPacketSize = sizeof(sGU_SYSTEM_DISPLAY_TEXT) - 2;

			sNotice.byDisplayType = eSERVER_TEXT_TYPE::SERVER_TEXT_EMERGENCY;
			wcscpy_s(sNotice.awchMessage, BUDOKAI_MAX_NOTICE_LENGTH + 1, charToWChar(strToken.c_str()));
			wcscpy_s(sNotice.awGMChar, MAX_SIZE_CHAR_NAME_UNICODE, (L"System"));
			sNotice.wMessageLengthInUnicode = (WORD)wcslen(sNotice.awchMessage);

			sWorld.SendToAll((char*)&sNotice, sizeof(sGU_SYSTEM_DISPLAY_TEXT));
		}
		else if (strToken == "@speed")
		{
			strToken = str.substr(pos + 1, std::string::npos);
			unsigned int SpeedRate = (unsigned int)atof(strToken.c_str());
			sGU_UPDATE_CHAR_ATTACK_SPEEDRATE sAttackSpeed;
			sAttackSpeed.wOpCode = GU_UPDATE_CHAR_ATTACK_SPEEDRATE;
			sAttackSpeed.wPacketSize = sizeof(sGU_UPDATE_CHAR_ATTACK_SPEEDRATE) - 2;
			sAttackSpeed.handle = _player->GetHandle();
			int attackspeed = 1400 / 100 * SpeedRate;
			sAttackSpeed.wAttackSpeedRate = _player->GetPcProfile()->avatarAttribute.wLastAttackSpeedRate;
			_player->GetAttributesManager()->AddLastAttackSpeedRate(attackspeed * -1);

			if (_player->GetPcProfile()->avatarAttribute.wLastAttackSpeedRate <= 0 || _player->GetPcProfile()->avatarAttribute.wLastAttackSpeedRate >= 1400)
			{
				_player->GetPcProfile()->avatarAttribute.wLastAttackSpeedRate = 1400;
				_player->GetAttributesManager()->AddLastAttackSpeedRate(0);
				sAttackSpeed.wAttackSpeedRate = _player->GetPcProfile()->avatarAttribute.wLastAttackSpeedRate;
			}

			SendPacket((char*)&sAttackSpeed, sizeof(sGU_UPDATE_CHAR_ATTACK_SPEEDRATE));
			_player->SendToPlayerList((char*)&sAttackSpeed, sizeof(sGU_UPDATE_CHAR_ATTACK_SPEEDRATE));

		}
		else
		{
			sGU_SYSTEM_DISPLAY_TEXT sNotice;

			sNotice.wOpCode = GU_SYSTEM_DISPLAY_TEXT;
			sNotice.wPacketSize = sizeof(sGU_SYSTEM_DISPLAY_TEXT) - 2;

			sNotice.byDisplayType = eSERVER_TEXT_TYPE::SERVER_TEXT_SYSNOTICE;
			wcscpy_s(sNotice.awchMessage, BUDOKAI_MAX_NOTICE_LENGTH + 1, (L"Invalid command."));
			wcscpy_s(sNotice.awGMChar, MAX_SIZE_CHAR_NAME_UNICODE, (L"System"));
			sNotice.wMessageLengthInUnicode = (WORD)wcslen(sNotice.awchMessage);

			SendPacket((char*)&sNotice, sizeof(sGU_SYSTEM_DISPLAY_TEXT));
		}
	}
	else
	{
		if (strToken == "@additem") // for non gm players
		{
			strToken = str.substr(pos + 1, std::string::npos);
			unsigned int uiTblId = (unsigned int)atof(strToken.c_str());
			sITEM_PROFILE createdItem;
			WORD result = _player->GetInventoryManager()->PerformShopBuy(uiTblId, 1, createdItem);
			if (result == GAME_SUCCESS && createdItem.tblidx != INVALID_TBLIDX)
			{
				sLog.outDetail("Item Created\n");
				SendItemCreate(&createdItem);
			}
			return;
		}

		else if (strToken == "@unstuck") // for non gm players
			{
				strToken = str.substr(pos + 1, std::string::npos);
				unsigned int Point = (unsigned int)atof(strToken.c_str());
				_player->TeleportByCommand(1);
				return;
			}
		else if (strToken == "@topapaya") // for non gm players
		{
			strToken = str.substr(pos + 1, std::string::npos);
			unsigned int Point = (unsigned int)atof(strToken.c_str());
			_player->TeleportByCommand(15);
			return;

		}
		
		else if (strToken == "@karin") // for non gm players
		{
			strToken = str.substr(pos + 1, std::string::npos);
			unsigned int Point = (unsigned int)atof(strToken.c_str());
			_player->TeleportByCommand(800000);
			return;

		}

		else
		{
			sGU_SYSTEM_DISPLAY_TEXT sNotice;

			sNotice.wOpCode = GU_SYSTEM_DISPLAY_TEXT;
			sNotice.wPacketSize = sizeof(sGU_SYSTEM_DISPLAY_TEXT) - 2;

			sNotice.byDisplayType = eSERVER_TEXT_TYPE::SERVER_TEXT_SYSNOTICE;
			wcscpy_s(sNotice.awchMessage, BUDOKAI_MAX_NOTICE_LENGTH + 1, (L"You can't control that power, be carefoul with that..."));
			wcscpy_s(sNotice.awGMChar, MAX_SIZE_CHAR_NAME_UNICODE, (L" GM "));
			sNotice.wMessageLengthInUnicode = (WORD)wcslen(sNotice.awchMessage);

			_player->SendPacket((char*)&sNotice, sizeof(sGU_SYSTEM_DISPLAY_TEXT));
		}
	}
}