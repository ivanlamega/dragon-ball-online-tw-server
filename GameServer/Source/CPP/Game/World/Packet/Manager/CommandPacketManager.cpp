#include <Game\World\WorldSession.h>
#include <Game\Object\Player.h>
#include <Game\Object\Mob.h>
#include <Game\Object\Object.h>
#include <Packet\Game\PacketGU.h>
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

	sNotice.byDisplayType = eSERVER_TEXT_TYPE::SERVER_TEXT_EMERGENCY;
	wcscpy_s(sNotice.awchMessage, BUDOKAI_MAX_NOTICE_LENGTH + 1, charToWChar(message.c_str()));
	wcscpy_s(sNotice.awGMChar, MAX_SIZE_CHAR_NAME_UNICODE, (L" GM "));
	sNotice.wMessageLengthInUnicode = (WORD)wcslen(sNotice.awchMessage);

	SendToAll((char*)&sNotice, sizeof(sGU_SYSTEM_DISPLAY_TEXT));
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
		else if (strToken == "@delete")
		{
			sLog.outDetail("Delete item quest");
			strToken = str.substr(pos + 1, std::string::npos);
			unsigned int Level = (unsigned int)atof(strToken.c_str());
			sGU_QUEST_ITEM_DELETE_NFY delItm;
			delItm.wOpCode = GU_QUEST_ITEM_DELETE_NFY;
			delItm.wPacketSize = sizeof(sGU_QUEST_ITEM_DELETE_NFY) - 1;
			delItm.byDeletePos = 0;
			SendPacket((char*)&delItm, sizeof(sGU_QUEST_ITEM_DELETE_NFY));
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
			sLog.outDetail("GM LearnTitle Modified");
			strToken = str.substr(pos + 1, std::string::npos);
			unsigned int TitleID = (unsigned int)atof(strToken.c_str());
			_player->GetAttributesManager()->SetLastMaxLP(20000);
			_player->GetAttributesManager()->SetLastMaxEP(20000);
			_player->GetAttributesManager()->SetLastPhysicalOffence(20000);
			_player->GetAttributesManager()->SetLastPhysicalCriticalRate(20000);
			_player->GetAttributesManager()->SetLastPhysicalDefence(20000);
			_player->GetAttributesManager()->SetLastEnergyOffence(20000);
			_player->GetAttributesManager()->SetLastEnergyCriticalRate(20000);
			_player->GetAttributesManager()->SetLastEnergyDefence(20000);
			_player->GetAttributesManager()->SetLastAttackRate(20000);
			_player->GetAttributesManager()->SetLastDodgeRate(20000);			
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
		else if (strToken == "@addmob")
		{
			strToken = str.substr(pos + 1, std::string::npos);
			unsigned int MobID = (unsigned int)atof(strToken.c_str());
			printf("Executing Mob Func\n");

			MobTable * MobTable = sTBM.GetMobTable();
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
			}
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
				res.bySkillSlot = _player->skillManager.getSkillsCount() + 1;
				_player->HTBID = res.skillId;
				SendPacket((char*)&res, sizeof(sGU_HTB_LEARN_RES));
				
				//sDB.LearnSkill(skillID, _player->GetCharacterID(), nfy.bySlot);
				//Load skill for can use after that
				//_player->skillManager.LoadSkill(_player->charid);
				//SendAvatarSkillInfo();

				//SendUpdateSkillPassiveAtributeByID(skillID, false);
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
			_player->GetAttributesManager()->SetLastAttackSpeedRate(attackspeed * -1);

			if (_player->GetPcProfile()->avatarAttribute.wLastAttackSpeedRate <= 0 || _player->GetPcProfile()->avatarAttribute.wLastAttackSpeedRate >= 1400)
			{
				_player->GetPcProfile()->avatarAttribute.wLastAttackSpeedRate = 1400;
				_player->GetAttributesManager()->SetLastAttackSpeedRate(0);
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
		else if (strToken == "@topapaya")
		{
			strToken = str.substr(pos + 1, std::string::npos);
			unsigned int Point = (unsigned int)atof(strToken.c_str());
			_player->TeleportByCommand(15);
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