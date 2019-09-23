#include <Game\World\WorldSession.h>
#include <Game\Object\Player.h>
#include <Packet\Game\PacketGU.h>
#include <Game\Object\Mob.h>
#include <Game\Object\Object.h>
#include <Packet\Game\PacketUG.h>
#include <Logger.h>
#include <World.h>

//----------------------------------------
//	Send announce to all player
//----------------------------------------
void World::SendAnnounce(std::string message)
{
	sGU_SYSTEM_DISPLAY_TEXT sNotice;

	sNotice.wOpCode = GU_SYSTEM_DISPLAY_TEXT;
	sNotice.wPacketSize = sizeof(sGU_SYSTEM_DISPLAY_TEXT) - 2;

	sNotice.byDisplayType = eSERVER_TEXT_TYPE::SERVER_TEXT_NOTICE;
	wcscpy_s(sNotice.awchMessage, BUDOKAI_MAX_NOTICE_LENGTH + 1, charToWChar(message.c_str()));
	wcscpy_s(sNotice.awGMChar, MAX_SIZE_CHAR_NAME_UNICODE, (L"System"));
	sNotice.wMessageLengthInUnicode = (WORD)wcslen(sNotice.awchMessage);

	SendToAll((char*)&sNotice, sizeof(sGU_SYSTEM_DISPLAY_TEXT));
}
//----------------------------------------
//	Interpret GM command
//----------------------------------------
void WorldSession::ExecuteServerCommand(Packet& packet)
{
	if (_player->GetPcProfile()->bIsGameMaster == true)
	{
		sUG_SERVER_COMMAND * pServerCmd = (sUG_SERVER_COMMAND*)packet.GetPacketBuffer();
		std::string str = WC2MB(pServerCmd->awchCommand);
		sLog.outDetail("GameMaster Command: %s", str.c_str());
		size_t pos = str.find(" ");

		std::string strToken = str.substr(0, pos);

		if (strToken == "@setspeed")
		{
			sLog.outDetail("GM Speed Modified");
			printf("received char speed command");
			strToken = str.substr(pos + 1, std::string::npos);
			unsigned int fSpeed = (unsigned int)atof(strToken.c_str());
			_player->SetSpeed(fSpeed);
			return;
		}
		else if (strToken == "@setlevel")
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
		else if (strToken == "@changemap")
		{
			sLog.outDetail("GM Bot Check");
			strToken = str.substr(pos + 1, std::string::npos);
			unsigned int Point = (unsigned int)atof(strToken.c_str());
			//_player->UpdateModusaAmount(Point);
			
			sGU_CHAR_TELEPORT_RES teleport;
			
			sWORLD_TBLDAT *world = (sWORLD_TBLDAT*)sTBM.GetWorldTable()->FindData(Point);
			teleport.wResultCode = GAME_SUCCESS;
			teleport.wOpCode = GU_CHAR_TELEPORT_RES;
			teleport.wPacketSize = sizeof(sGU_CHAR_TELEPORT_RES) - 2;

			if (world != NULL)
			{	
				if (Point != _player->GetWorldID())
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
			
				
			}
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
		else if (strToken == "@setclass")
		{
			sLog.outDetail("GM Class Modified");
			strToken = str.substr(pos + 1, std::string::npos);
			unsigned int clase = (unsigned int)atof(strToken.c_str());
			_player->ConvertClass(clase);
			return;
		}
		else if (strToken == "@setadult")
		{
			sLog.outDetail("GM Adult Modified");
			strToken = str.substr(pos + 1, std::string::npos);
			unsigned int adult = (unsigned int)atof(strToken.c_str());
			_player->ConvertAdult(adult);
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
		else if (strToken == "@addnpc")//fixed
		{
			strToken = str.substr(pos + 1, std::string::npos);
			unsigned int NpcID = (unsigned int)atof(strToken.c_str());
			printf("Executing Mob Func\n");
			NPCTable * NpcTable = sTBM.GetNpcTable();
			sNPC_TBLDAT * Npc = reinterpret_cast<sNPC_TBLDAT*>(NpcTable->FindData(NpcID));
			if (Npc != NULL)
			{

				SpawnNPC spawnData;
				memset(&spawnData, 0, sizeof(SpawnNPC));

				spawnData.wOpCode = GU_OBJECT_CREATE;
				spawnData.wPacketSize = sizeof(SpawnNPC) - 2;

				spawnData.AspectID = 0;
				spawnData.CurEP = Npc->wBasic_EP;
				spawnData.CurLP = Npc->wBasic_LP;
				spawnData.Handle = sWorld.AcquireSerialId();
				spawnData.Level = Npc->byLevel;
				spawnData.MaxEP = Npc->wBasic_EP;
				spawnData.MaxLP = Npc->wBasic_LP;
				spawnData.ModelSize = 10;
				spawnData.OBJType = OBJTYPE_NPC;
				spawnData.Position.x = _player->m_position.x;
				spawnData.Position.y = _player->m_position.y;
				spawnData.Position.z = _player->m_position.z;
				spawnData.Rotation.x = _player->m_rotation.x;
				spawnData.Rotation.y = _player->m_rotation.y;
				spawnData.Rotation.z = _player->m_rotation.z;
				spawnData.StateID = eCHARSTATE::CHARSTATE_SPAWNING;
				spawnData.Tblidx = NpcID;

				sWorld.SendToAll((char*)&spawnData, sizeof(SpawnNPC));
			}
			//Need Insert In list
			printf("Executed\n");
			return;
		}
		else if (strToken == "@addmob")
		{
			strToken = str.substr(pos + 1, std::string::npos);
			unsigned int MobID = (unsigned int)atof(strToken.c_str());
			printf("Executing Mob Func\n");
			
			MobTable * MobTable = sTBM.GetMobTable();
			sMOB_TBLDAT * mob = reinterpret_cast<sMOB_TBLDAT*>(MobTable->FindData(MobID));
			if (mob != NULL)
			{

				SpawnMOB spawnData;
				memset(&spawnData, 0, sizeof(SpawnMOB));

				spawnData.wOpCode = GU_OBJECT_CREATE;
				spawnData.wPacketSize = sizeof(SpawnMOB) - 2;

				spawnData.AspectID = 0;
				spawnData.curEP = mob->wBasic_EP;
				spawnData.curLP = mob->wBasic_LP;
				spawnData.Handle = sWorld.AcquireSerialId();
				spawnData.Level = mob->byLevel;
				spawnData.maxEP = mob->wBasic_EP;
				spawnData.maxLP = mob->wBasic_LP;
				spawnData.Size = 10;
				spawnData.Type = OBJTYPE_MOB;
				spawnData.Position.x = _player->m_position.x + 5.0f;
				spawnData.Position.y = _player->m_position.y;
				spawnData.Position.z = _player->m_position.z;
				spawnData.Rotation.x = _player->m_rotation.x - 180.0f;
				spawnData.Rotation.y = _player->m_rotation.y;
				spawnData.Rotation.z = _player->m_rotation.z;
				spawnData.StateID = eCHARSTATE::CHARSTATE_SPAWNING;
				spawnData.Tblidx = MobID;

				spawnData.Run_Speed = 2;
				spawnData.Run_Speed_origin = 2;
				spawnData.Walk_Speed = 2;
				spawnData.Walk_Speed_origin = 2;

				Mob* created_mob = new Mob;
				sMOB_TBLDAT* pMOBTblData = (sMOB_TBLDAT*)sTBM.GetMobTable()->FindData(MobID);
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
			printf("Executed\n");
			return;
		}
		else if (strToken == "@dropitem")
		{
			strToken = str.substr(pos + 1, std::string::npos);
			unsigned int MobID = (unsigned int)atof(strToken.c_str());
			printf("Executing Mob Func\n");
			

				Drop spawnData;
				memset(&spawnData, 0, sizeof(Drop));

				spawnData.wOpCode = GU_OBJECT_CREATE;
				spawnData.wPacketSize = sizeof(Drop) - 2;

				
				spawnData.Handle = sWorld.AcquireItemSerialId();				
				spawnData.Type = OBJTYPE_DROPITEM;
				spawnData.Tblidx = MobID;
				spawnData.Grade = 0;
				spawnData.Rank = 0;
				spawnData.BattleAttribute = 0;
				spawnData.Loc.x = _player->m_position.x;
				spawnData.Loc.y = _player->m_position.y;
				spawnData.Loc.z = _player->m_position.z;				
				spawnData.IsNew = true;
				spawnData.NeedToIdentify = false;
				

				sWorld.SendToAll((char*)&spawnData, sizeof(Drop));
				//Need Insert In list
			
			printf("Executed\n");
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
					if (_player->GetClassFlag(_player->GetAttributesManager()->PlayerClassID , ITEM_TYPE_UNKNOWN) == skillData->dwPC_Class_Bit_Flag)
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
		else if (strToken == "@learnhtb")
		{
			strToken = str.substr(pos + 1, std::string::npos);
			unsigned int uiTblId = (unsigned int)atof(strToken.c_str());
			return;
		}
		else if (strToken == "@dbhuntend")
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

			sGU_SYSTEM_DISPLAY_TEXT sNotice;

			sNotice.wOpCode = GU_SYSTEM_DISPLAY_TEXT;
			sNotice.wPacketSize = sizeof(sGU_SYSTEM_DISPLAY_TEXT) - 2;
			sNotice.byDisplayType = 3;
			wcscpy_s(sNotice.awchMessage, BUDOKAI_MAX_NOTICE_LENGTH, L" Dragon Ball Hunt End");
			wcscpy_s(sNotice.awGMChar, MAX_SIZE_CHAR_NAME_UNICODE, (L"System"));
			sNotice.wMessageLengthInUnicode = 50;

			sWorld.SendToAll((char*)&sNotice, sizeof(sGU_SYSTEM_DISPLAY_TEXT));
			return;
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

			sGU_SYSTEM_DISPLAY_TEXT sNotice;

			sNotice.wOpCode = GU_SYSTEM_DISPLAY_TEXT;
			sNotice.wPacketSize = sizeof(sGU_SYSTEM_DISPLAY_TEXT) - 2;
			sNotice.byDisplayType = 3;
			wcscpy_s(sNotice.awchMessage, BUDOKAI_MAX_NOTICE_LENGTH, L" Dragon Ball Hunt Start");
			wcscpy_s(sNotice.awGMChar, MAX_SIZE_CHAR_NAME_UNICODE, (L"System"));
			sNotice.wMessageLengthInUnicode = 50;

			sWorld.SendToAll((char*)&sNotice, sizeof(sGU_SYSTEM_DISPLAY_TEXT));
			return;
		}
		else if (strToken == "@teleportto")
		{
			std::string charName = strToken;
			// GET PLAYER TO TELEPORT TO

			sGU_AVATAR_WORLD_INFO teleport;
			teleport.worldInfo.sRuleInfo.byRuleType = GAMERULE_NORMAL;
			teleport.worldInfo.hTriggerObjectOffset = 100000;
			teleport.worldInfo.tblidx = 1;
			teleport.worldInfo.worldID = 1;
			teleport.vCurDir = sVECTOR3();
			teleport.vCurLoc = sVECTOR3();
			teleport.wOpCode = GU_AVATAR_WORLD_INFO;
			SendPacket((char*)&teleport, sizeof(sGU_AVATAR_WORLD_INFO));
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
		else if (strToken == "@kick")
		{
			strToken = str.substr(pos + 1, std::string::npos);
			/// get player from name or kick target
		}
		else if (strToken == "@chat")
		{
			sGU_AUTH_KEY_FOR_COMMUNITY_SERVER_RES res;

			res.wOpCode = GU_AUTH_KEY_FOR_COMMUNITY_SERVER_RES;
			res.wResultCode = GAME_SUCCESS;
			res.wPacketSize = sizeof(sGU_AUTH_KEY_FOR_COMMUNITY_SERVER_RES) - 2;
			memcpy(res.abyAuthKey, "SE@WASDE#$RFWD@F", MAX_SIZE_AUTH_KEY);

			SendPacket((char*)&res, sizeof(sGU_AUTH_KEY_FOR_COMMUNITY_SERVER_RES));

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

			_player->SendPacket((char*)&sNotice, sizeof(sGU_SYSTEM_DISPLAY_TEXT));
		}
	}
	else
	{
		sGU_SYSTEM_DISPLAY_TEXT sNotice;

		sNotice.wOpCode = GU_SYSTEM_DISPLAY_TEXT;
		sNotice.wPacketSize = sizeof(sGU_SYSTEM_DISPLAY_TEXT) - 2;

		sNotice.byDisplayType = eSERVER_TEXT_TYPE::SERVER_TEXT_SYSNOTICE;
		wcscpy_s(sNotice.awchMessage, BUDOKAI_MAX_NOTICE_LENGTH + 1, (L"No eres Gm, no mames..."));
		wcscpy_s(sNotice.awGMChar, MAX_SIZE_CHAR_NAME_UNICODE, (L"System"));
		sNotice.wMessageLengthInUnicode = (WORD)wcslen(sNotice.awchMessage);

		_player->SendPacket((char*)&sNotice, sizeof(sGU_SYSTEM_DISPLAY_TEXT));
	}
}