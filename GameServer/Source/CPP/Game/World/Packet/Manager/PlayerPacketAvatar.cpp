#include <Game\World\WorldSession.h>
#include <Packet\Game\PacketGU.h>
#include <Packet\Game\PacketUG.h>
#include <Game\Object\Player.h>
#include <Game\Object\Npc.h>
#include <Game\Maps\MapManager.h>
#include <mysqlconn_wrapper.h>
#include <Logger.h>
#include <World.h>
#include <XmlParser2/XmlParser2.h>
typedef WorldObjectRefManager WorldObjectList;

//----------------------------------------
//	Send the avatar info get from database
//----------------------------------------
void	WorldSession::SendAvatarCharInfo()
{
	Packet packet(sizeof(sGU_AVATAR_CHAR_INFO));

	sGU_AVATAR_CHAR_INFO res;
	memset(&res, 0, sizeof(sGU_AVATAR_CHAR_INFO));

	res.wPacketSize = sizeof(sGU_AVATAR_CHAR_INFO) - 2;
	res.wOpCode = GU_AVATAR_CHAR_INFO;

	res.handle = _player->GetHandle();

	memcpy(&res.sPcProfile, _player->GetPcProfile(), sizeof(sPC_PROFILE));
	memcpy(&res.sCharState, _player->GetState(), sizeof(sCHARSTATE));
	res.wCharStateSize = sizeof(sCHARSTATE_BASE);

	SendPacket((char*)&res, sizeof(sGU_AVATAR_CHAR_INFO));
	
	_player->SetGSHandle();
}
//----------------------------------------
//	Tell our character we load everything
//----------------------------------------
void WorldSession::SendAvatarInfoEnd()
{
	sGU_AVATAR_INFO_END res;
	memset(&res, 0, sizeof(sGU_AVATAR_INFO_END));

	res.wPacketSize = sizeof(sGU_AVATAR_INFO_END) - 2;
	res.wOpCode = GU_AVATAR_INFO_END;
	SendPacket((char*)&res, sizeof(sGU_AVATAR_INFO_END));
	_player->characterManager.SendRpBallInformation();
}
void WorldSession::SendAvatarWagguInfo()
{
	sGU_WAGUWAGUMACHINE_COIN_INFO res;
	memset(&res, 0, sizeof(sGU_WAGUWAGUMACHINE_COIN_INFO));
	res.wPacketSize = sizeof(sGU_WAGUWAGUMACHINE_COIN_INFO) - 2;
	res.wOpCode = GU_WAGUWAGUMACHINE_COIN_INFO;
	res.WagguCoin = _player->GetAttributesManager()->WagguCoin;
	SendPacket((char*)&res, sizeof(sGU_WAGUWAGUMACHINE_COIN_INFO));
}

void WorldSession::SendAvatarItemCashInfo()
{
	sGU_CASHITEM_ADD_NFY item;
	memset(&item, 0, sizeof(sGU_CASHITEM_ADD_NFY));
	item.wOpCode = GU_CASHITEM_ADD_NFY;
	item.wPacketSize = sizeof(sGU_CASHITEM_ADD_NFY) - 2;

	sql::ResultSet* result = sDB.executes("SELECT * FROM cashitem WHERE owner_id = '%d';", _player->GetCharacterID());
	if (result == NULL)
		return;
	if (result->rowsCount() <= 0)
	{
		delete result;
		return;
	}
	int count = result->rowsCount();
	int i = 0;
	while (true)
	{
		item.handle = result->getInt("Handle");//ItemHandle
		item.sInfo.dwProductId = 0;
		item.sInfo.ItemHLSTableID = result->getInt("tblidx");//ItemHLSTableID "Not is Tblidx of item in Bag" Maybe they convert ID on Item Move;
		item.sInfo.byStackCount = result->getInt("byStackCount");//Item count
		item.unk1[8] = 1;
		//for (int i = 0; i <= 17; i++) { item.awchName[i] = 0; }
		wcscpy_s(item.awchName, 16 + 1, (L" Marco "));		
		//Time of Item Creation
		item.Year = 2017;
		item.Moch = 0;
		item.Day = 0;
		item.Hour = 0;
		item.Minute = 0;
		item.Secound = 0;
		item.unk2 = 0;
		i++;
		SendPacket((char*)&item, sizeof(sGU_CASHITEM_ADD_NFY));
		/*sql::ResultSet* result1 = sDB.executes("UPDATE cashitem SET Handle = '%d' WHERE owner_id = '%d' AND tblidx = '%d';",
			item.handle, _player->GetCharacterID(), item.sInfo.ItemHLSTableID);
		if (result1 != NULL)
			delete result1;*/

		if (result->next())
			continue;
		else
			break;
	}
	delete result;
	
}
//----------------------------------------
//	Send the war fog info (map)
//----------------------------------------
void WorldSession::SendAvatarWarFogInfo()
{
	sGU_WAR_FOG_INFO res;
	memset(&res, 0, sizeof(sGU_WAR_FOG_INFO));

	res.wOpCode = GU_WAR_FOG_INFO;
	res.wPacketSize = sizeof(sGU_WAR_FOG_INFO) - 2;

	sql::ResultSet* result = sDB.executes("SELECT * FROM warfoginfo WHERE owner_id = '%d';", _player->GetCharacterID());
	if (result == NULL)
		return;
	if (result->rowsCount() <= 0)
	{
		delete result;
		return;
	}	
	int iPosition = 0;
	while (true)
	{
		
			uint32 uiIndex = result->getInt("hObject");
			uint32 uiArrayPos = uiIndex / 8;
			uint8 byCurBit = (uint8)(uiIndex % 8);
			res.abyWarFogInfo[uiArrayPos] |= 0x01ui8 << byCurBit;			
			_player->WarFrogList[iPosition] = result->getInt("hObject");
			iPosition++;
				
		if (result->next())
			continue;
		else
			break;
	}
	delete result;
	_player->WarFrogcount = iPosition;	
	SendPacket((char*)&res, sizeof(sGU_WAR_FOG_INFO));
}
//----------------------------------------
//	Send the portal info
//----------------------------------------
void WorldSession::SendPortalInfo()
{
	sGU_PORTAL_INFO portal;
	memset(&portal, 0, sizeof(sGU_PORTAL_INFO));
	portal.wOpCode = GU_PORTAL_INFO;
	portal.wPacketSize = sizeof(sGU_PORTAL_INFO) - 2;

	sql::ResultSet* result = sDB.executes("SELECT * FROM portals WHERE characterID = '%d';", _player->GetCharacterID());
	if (result == NULL)
		return;
	if (result->rowsCount() <= 0)
	{
		delete result;
		return;
	}
	portal.byCount = result->rowsCount();
	int i = 0;
	while (true)
	{
		portal.aPortalID[i] = result->getInt("PortalID");
		i++;
		if (result->next())
			continue;
		else
			break;
	}
	delete result;
	SendPacket((char*)&portal, sizeof(sGU_PORTAL_INFO));
}
//----------------------------------------
//	Send the Title info
//----------------------------------------
void WorldSession::SendAvatarTitleInfo() 
{
	sGU_CHARTITLE_LIST_INFO title;
	//memset(&title, 0, sizeof(sGU_CHARTITLE_LIST_INFO));
	title.wOpCode = GU_CHARTITLE_LIST_INFO;
	title.wPacketSize = sizeof(sGU_CHARTITLE_LIST_INFO) - 2;
	sql::ResultSet* result = sDB.executes("SELECT * FROM titlelist WHERE characterID = '%d';", _player->GetCharacterID());
	if (result == NULL)
		return;
	if (result->rowsCount() <= 0)
	{
		delete result;
		return;
	}
	int i = 0;
	while (true)
	{		
		uint16 titleID = result->getInt("TitleID") - 1;
		title.TitleFlagArray[uint16(titleID / 8)] |= (1 << (titleID - (8 * uint16(titleID / 8))));
		
		i++;		
		if (result->next())
			continue;
		else
			break;
	}
	delete result;
	SendPacket((char*)&title, sizeof(sGU_CHARTITLE_LIST_INFO));
}
//----------------------------------------
//	Send the Mascot info
//----------------------------------------
void WorldSession::SendMascotInfo()
{
	sGU_MASCOT_INFO_EX mascot;
	sql::ResultSet* result = sDB.executes("SELECT * FROM MascotInfo WHERE CharID = '%d';", _player->GetCharacterID());
	if (result == NULL)
		return;
	if (result->rowsCount() <= 0)
	{
		delete result;
		return;
	}
	mascot.wOpCode = GU_MASCOT_INFO_EX;
	mascot.wPacketSize = sizeof(sGU_MASCOT_INFO_EX) - 2;
	mascot.PetCount = 0;
	for (int i = 0; i < result->rowsCount(); i++)
	{
		mascot.pet[mascot.PetCount].MascotID = result->getInt("MascotID");
		mascot.pet[mascot.PetCount].CurVp = result->getInt("CurVP");
		mascot.pet[mascot.PetCount].Exp = result->getInt("Exp");
		mascot.pet[mascot.PetCount].MascotID1 = result->getInt("MascotID");
		mascot.pet[mascot.PetCount].MaxVp = result->getInt("MaxVP");
		mascot.pet[mascot.PetCount].Skillcount = result->getInt("Skill_count");
		mascot.pet[mascot.PetCount].UNK = 0;
		mascot.pet[mascot.PetCount].SlotPos = result->getInt("Slot");
		mascot.pet[mascot.PetCount].Skill[0] = result->getInt("Skill1");
		mascot.pet[mascot.PetCount].Skill[1] = result->getInt("Skill2");
		mascot.pet[mascot.PetCount].Skill[2] = result->getInt("Skill3");
		mascot.pet[mascot.PetCount].Skill[3] = result->getInt("Skill4");

		mascot.PetCount++;
		if (result->next())
			continue;
		else
			break;
	}

	SendPacket((char*)&mascot, sizeof(sGU_MASCOT_INFO_EX));
	delete result;
	return;
}
//----------------------------------------
//	Send the HoiPoiMix info
//----------------------------------------
void WorldSession::SendHoiPoiMixInfo()
{
	sGU_HOIPOIMIX_ITEM_RECIPE_INFO HoiPoiMix;
	sql::ResultSet* result = sDB.executes("SELECT * FROM HoiPoiMix WHERE CharID = '%d';", _player->GetCharacterID());
	if (result == NULL)
		return;
	if (result->rowsCount() <= 0)
	{
		delete result;
		return;
	}
	HoiPoiMix.wOpCode = GU_HOIPOIMIX_ITEM_RECIPE_INFO;
	HoiPoiMix.wPacketSize = sizeof(sGU_HOIPOIMIX_ITEM_RECIPE_INFO) - 2;
	HoiPoiMix.TotalCount = result->rowsCount();
	HoiPoiMix.UNK = 0;//if change crash client 
	int size = 0;//not know why need that to load correct
	for (int i = 0; i < HoiPoiMix.TotalCount; i++)
	{
		HoiPoiMix.RecipeData[size].recipeTblidx = result->getInt("RecipeID");
		HoiPoiMix.RecipeData[size].byRecipeType = 0;

		size++;
		if (result->next())
			continue;
		else
			break;
	}
	SendPacket((char*)&HoiPoiMix, sizeof(sGU_HOIPOIMIX_ITEM_RECIPE_INFO));
	delete result;
	return;
}
//----------------------------------------
//	Send the new war fog
//----------------------------------------
void WorldSession::SendFogOfWarRes(Packet& packet)
{
	uint32 WarFogID;	
	sUG_WAR_FOG_UPDATE_REQ *req = (sUG_WAR_FOG_UPDATE_REQ *)packet.GetPacketBuffer();
	int ObjectFinnalID;

	ObjectTable *objTbl = sTBM.GetObjectTable(_player->GetWorldID());
	if (objTbl != NULL)
	{
		for (auto m_wobjRefIter = objTbl->Begin(); m_wobjRefIter != objTbl->End(); ++m_wobjRefIter)
		{
			sOBJECT_TBLDAT* pOBJECT_TBLDAT = reinterpret_cast<sOBJECT_TBLDAT*>(objTbl->FindData(m_wobjRefIter->first));
			if (pOBJECT_TBLDAT != NULL)
			{
				if (pOBJECT_TBLDAT->dwSequence == (req->hObject - 100000))
				{
					TBLIDX objectID = pOBJECT_TBLDAT->tblidx;
					sOBJECT_TBLDAT* tblData = reinterpret_cast<sOBJECT_TBLDAT*>(objTbl->FindData(objectID));
					if (tblData != NULL)
					{
						sLog.outDebug("Tblidx for Warfog %d", tblData->tblidx);
						sLog.outDebug("ContentsTblidx %d", tblData->contentsTblidx);
						ObjectFinnalID = tblData->contentsTblidx;
					}
					else
					{
						sLog.outDetail("Error, can't find the ObjectID: %d", objectID);
					}
				}
			}
		}
	}
	else
	{
		sLog.outDetail("Error, Object table is invalid");
	}


	sGU_WAR_FOG_UPDATE_RES res;

	res.wPacketSize = sizeof(sGU_WAR_FOG_UPDATE_RES) - 2;
	res.wOpCode = GU_WAR_FOG_UPDATE_RES;
	for (int i = 0; i <= _player->WarFrogcount; i++)
	{
		if (_player->WarFrogList[i] == ObjectFinnalID)
		{
			WarFogID = ObjectFinnalID;
			res.wResultCode = ResultCodes::GAME_WARFOG_ARLEADY_ADDED;
		}		
	}	
	if (ObjectFinnalID != WarFogID)
	{
		res.wResultCode = GAME_SUCCESS;
		res.handle = req->hObject;
		// add warfog to db		
		printf("IDWarFrog %d \n", req->hObject);
		
		sDB.AddNewWarFog(ObjectFinnalID, _player->GetCharacterID());
		_player->WarFrogcount += 1;
		_player->WarFrogList[_player->WarFrogcount] = ObjectFinnalID;
		
	}
	
	SendPacket((char*)&res, sizeof(sGU_WAR_FOG_UPDATE_RES));
	
}
//----------------------------------------
//	??
//----------------------------------------
void WorldSession::SendNetMarbleMemberShipNfy()
{
	sGU_ENTER_WORLD_RES res;
	res.wOpCode = GU_ENTER_WORLD_RES;
	res.wResultCode = GAME_SUCCESS;
	res.wPacketSize = sizeof(sGU_ENTER_WORLD_RES) - 2;
	SendPacket((char*)&res, sizeof(sGU_ENTER_WORLD_RES));

	sGU_NETMARBLEMEMBERIP_NFY res1;
	res1.wPacketSize = sizeof(sGU_NETMARBLEMEMBERIP_NFY) - 2;
	res1.wOpCode = GU_NETMARBLEMEMBERIP_NFY;
	SendPacket((char*)&res1, sizeof(sGU_NETMARBLEMEMBERIP_NFY));
	

	/*SendPacket((char*)contents_onoff, 272);*/
	
	sGU_SERVER_CONTENTS_ONOFF content;	
	memset(&content, 0, sizeof(sGU_SERVER_CONTENTS_ONOFF));

	content.wOpCode = GU_SERVER_CONTENTS_ONOFF;
	content.wPacketSize = sizeof(sGU_SERVER_CONTENTS_ONOFF) - 2;

	content.Dojo = 1;

	content.bDisableHoiPoiOld = 1;
	content.bDisableWeirdDissassemble = 1;

	content.bDisableOldScouter = 0x02;
	content.bDisableNewScouter = 0x02;

	content.BDungeon001_Trigger = 1;
	content.Dungeon004_Trigger = 1;
	content.Dungeon006_Trigger = 1;
	content.Dungeon007_Trigger = 1;	

	content.WZone001_NPC = 1;	
	content.MainWorld02_NPC = 1;

	content.Block_QuestType_BitFlag = 1;
	content.IDK2 = 0;
	content.IDK3 = 0;

	content.QUESTONOFF_DWC = 0;
	content.bDisableDWC = 0;

	content.byteUnknown4_5 = 0;
	
	content.byteUnknown7 = 0;
	
	content.QUESTONOFF_SKD01 = 1;
	content.bySkyUD_TriggersCount = 6;
	content.tbxObjectSkyUD[0] = 1;
	content.tbxObjectSkyUD[1] = 1;
	content.tbxObjectSkyUD[2] = 1;
	content.tbxObjectSkyUD[3] = 1;
	content.tbxObjectSkyUD[4] = 1;
	content.tbxObjectSkyUD[5] = 1;

	//content.byUnknown2[0] = INVALID_BYTE;

	content.dwCCBD_LastFloor = 150;
	content.PetSystemOldNew = 2;
	
	SendPacket((char*)&content, sizeof(sGU_SERVER_CONTENTS_ONOFF));

	BYTE server_info[] = {
		0x06, 0x00, 0x30, 0x16, 0xE8, 0x03, 0x00, 0x00
	};
	SendPacket((char*)server_info, 8);
	// old 0x06, 0x00, 0x30, 0x16, 0xE8, 0x03, 0x00, 0x00
	// glob 0x06, 0x00, 0x03, 0x00, 0xAC, 0x86, 0xF5, 0x74
}
//----------------------------------------
//	Prepare our character to enter in world, get the map insert the player in.
//----------------------------------------
void WorldSession::SendWorldEnter()
{
	sGU_AVATAR_WORLD_INFO res;
	memset(&res, 0, sizeof sGU_AVATAR_WORLD_INFO);

	res.byDojoCount = 0;
	res.wOpCode = GU_AVATAR_WORLD_INFO;
	res.wPacketSize = sizeof(sGU_AVATAR_WORLD_INFO) - 2;
	/*for (int n = 0; n < DBO_MAX_COUNT_DOJO_IN_WORLD; n++)
	{
		res.sDojoData[n].guildId = 0xffffffff;
		res.sDojoData[n].dojoTblidx = 0xffffffff;
		res.sDojoData[n].sMark.byMarkInColor = 1;
		res.sDojoData[n].sMark.byMarkInLine = 1;
		res.sDojoData[n].sMark.byMarkMain = 1;
		res.sDojoData[n].sMark.byMarkMainColor = 1;
		res.sDojoData[n].sMark.byMarkOutColor = 1;
		res.sDojoData[n].sMark.byMarkOutLine = 1;		
	}*/
	sql::ResultSet* result = sDB.executes("SELECT * FROM characters WHERE CharacterID = '%d';", _player->GetCharacterID());
	if (result == NULL)
		return;
	if (result->rowsCount() <= 0)
	{
		delete result;
		return;
	}
	//Uncomment this if lines to see the first tutorial...not working for now this method above is wrong...we need get from database - Luiz45
	if (result->getInt("IsTutorialDone") == 1)
	{
		NewbieTable* pNewBieTable = sTBM.GetNewbieTable();
		sNEWBIE_TBLDAT* pNewbieTbldat = reinterpret_cast<sNEWBIE_TBLDAT*>(pNewBieTable->GetNewbieTbldat(result->getInt("RaceID"), result->getInt("ClassID")));
		sWORLD_TBLDAT* world = (sWORLD_TBLDAT*)sTBM.GetWorldTable()->FindData(_player->GetWorldID());
		if (world == NULL)
		{
			world = (sWORLD_TBLDAT*)sTBM.GetWorldTable()->FindData(1);
		}
		/*if (world->byWorldRuleType != eGAMERULE_TYPE::GAMERULE_NORMAL)
		{
			sLog.outDebug("World rules = %u", world->byWorldRuleType);
			sLog.outDebug("World out tblidx = %d", world->outWorldTblidx);

			_player->SetWorldID(world->outWorldTblidx);
			_player->Relocate(world->outWorldLoc.x, world->outWorldLoc.y, world->outWorldLoc.z, world->outWorldDir.x, world->outWorldDir.y, world->outWorldDir.z);
			world = (sWORLD_TBLDAT*)sTBM.GetWorldTable()->FindData(world->outWorldTblidx);
			_player->SetWorldTableID(world->tblidx);
			
		}*/
		res.worldInfo.tblidx = _player->GetWorldTableID();
		res.worldInfo.worldID = _player->GetWorldID();
		res.worldInfo.hTriggerObjectOffset = HANDLE_TRIGGER_OBJECT_OFFSET;
		res.worldInfo.sRuleInfo.byRuleType = world->byWorldRuleType;
		_player->GetPosition(res.vCurLoc.x, res.vCurLoc.y, res.vCurLoc.z);
		_player->GetOriantation(res.vCurDir.x, res.vCurDir.y, res.vCurDir.z);

		sLog.outDebug("Enter in: world: %d, table: %d", _player->GetWorldID(), _player->GetWorldTableID());
	}
	else
	{
		NewbieTable* pNewBieTable = sTBM.GetNewbieTable();
		sNEWBIE_TBLDAT* pNewbieTbldat = reinterpret_cast<sNEWBIE_TBLDAT*>(pNewBieTable->GetNewbieTbldat(result->getInt("RaceID"), result->getInt("ClassID")));
		if (pNewbieTbldat == NULL)
		{
			requestToLogout = true;
			delete result;
			return;
		}
		res.worldInfo.tblidx = pNewbieTbldat->tutorialWorld;
		res.worldInfo.worldID = pNewbieTbldat->world_Id;

		res.worldInfo.hTriggerObjectOffset = HANDLE_TRIGGER_OBJECT_OFFSET;
		res.worldInfo.sRuleInfo.byRuleType = GAMERULE_TUTORIAL;
		//Hard Coded
		res.vCurLoc.x = (-1)*78.90;
		res.vCurLoc.y = 46.95;
		res.vCurLoc.z = (-1) * 168.35;
		res.vCurDir.x = (-1) * 0.95;
		res.vCurDir.y = 0;
		res.vCurDir.z = 0.30;
		_player->SetWorldID(pNewbieTbldat->world_Id);
		_player->SetWorldTableID(pNewbieTbldat->tutorialWorld);
		_player->Relocate(res.vCurLoc.x, res.vCurLoc.y, res.vCurLoc.z, res.vCurDir.x, res.vCurDir.y, res.vCurDir.z);
		sLog.outDebug("Loading tutorial map: WorldID: %u, tblidx: %u", pNewbieTbldat->world_Id, pNewbieTbldat->tutorialWorld);
		// Set in tutorial ??? to not get the other player packet ??
	}
	delete result;
	SendPacket((char*)&res, sizeof(sGU_AVATAR_WORLD_INFO));
}
void WorldSession::SendGameExit(Packet& packet)
{
	sGU_GAME_EXIT_RES res;

	res.wPacketSize = sizeof(sGU_GAME_EXIT_RES) - 2;
	res.wOpCode = GU_GAME_EXIT_RES;

	SendPacket((char*)&res, sizeof(sGU_GAME_EXIT_RES));

}
//----------------------------------------
//	Process character logout on request leave game
//----------------------------------------
void WorldSession::SendGameLeave(Packet& packet, bool goToCharacterServer)
{
	sql::ResultSet* result = sDB.executes("UPDATE characters SET IsOnline = 0 WHERE CharacterID = '%d';", _player->GetCharacterID());
	if (result != NULL)
		delete result;
	// save player, remove him from database
	if (goToCharacterServer == true)
	{
		_player->GetAttributesManager()->LoseBatle == true;
		_player->isMovingToCharServer = true;
		sDB.UpdateAccountOnline(_player->accID, 1);
		// log in to char server
		sGU_CHAR_EXIT_RES res;
		memset(&res, 0, sizeof(sGU_CHAR_EXIT_RES));

		res.wOpCode = GU_CHAR_EXIT_RES;
		res.wResultCode = GAME_SUCCESS;
		res.wPacketSize = sizeof(sGU_CHAR_EXIT_RES) - 2;

		res.byServerInfoCount = sXmlParser.GetInt("CharServerList", "Count");
		int i = 0;
		for (i = 0; i < res.byServerInfoCount; ++i)
		{
			int srv = i + 1;
			std::string fieldName = "CharServer";
			fieldName.append(std::to_string(srv));

			std::string addr = sXmlParser.GetChildStr("CharServerList", (char*)fieldName.c_str(), "IP");
			int port = sXmlParser.GetChildInt("CharServerList", (char*)fieldName.c_str(), "Port");
			res.aServerInfo[i].dwLoad = 0;
			memcpy(res.aServerInfo[i].szCharacterServerIP, addr.c_str(), MAX_LENGTH_OF_IP);
			res.aServerInfo[i].wCharacterServerPortForClient = port;
		}
		res.wPacketSize = (res.wPacketSize - (sizeof(sSERVER_INFO) * (9 - i))); // remove unused struct size (9 because we need always 1 struct size to send)
		SendPacket((char*)&res, sizeof(sGU_CHAR_EXIT_RES));
	}
	else
	{
		_player->GetAttributesManager()->LoseBatle == true;
		requestToLogout = true;
	}
}
//----------------------------------------
//	Tell our character we finish to load and send all info to get in world
//----------------------------------------
void WorldSession::SendEnterWorldComplete()
{
	sGU_ENTER_WORLD_COMPLETE res;

	res.wOpCode = GU_ENTER_WORLD_COMPLETE;
	res.wPacketSize = sizeof(sGU_ENTER_WORLD_COMPLETE) - 2;
	SendPacket((char*)&res, sizeof(sGU_ENTER_WORLD_COMPLETE));

	sql::ResultSet* result = sDB.executes("UPDATE characters SET IsOnline = 1 WHERE CharacterID = '%d';", _player->GetCharacterID());
	if (result != NULL)
		delete result;
}
//----------------------------------------
//	Send the confirmation that the player enter in the world
//----------------------------------------
void WorldSession::SendEnterWorldTeleport()
{
	sWORLD_TBLDAT *world = (sWORLD_TBLDAT*)sTBM.GetWorldTable()->FindData(_player->GetWorldID());
	if (world == NULL)
	{
		sLog.outError("Error world not found");
		requestToLogout = true;
		return;
	}
	sGU_AVATAR_WORLD_INFO res;

	res.wOpCode = GU_AVATAR_WORLD_INFO;
	res.wPacketSize = sizeof(sGU_AVATAR_WORLD_INFO) - 2;
	res.byDojoCount = 7;
	for (int n = 0; n < DBO_MAX_COUNT_DOJO_IN_WORLD; n++)
	{
		res.sDojoData[n].guildId = 0xffffffff;
		res.sDojoData[n].dojoTblidx = 0xffffffff;
	}

	res.worldInfo.tblidx = _player->GetWorldTableID();
	res.worldInfo.worldID = _player->GetWorldID();
	res.worldInfo.hTriggerObjectOffset = HANDLE_TRIGGER_OBJECT_OFFSET;	//i don't know what the fuck i'm doing
	res.worldInfo.sRuleInfo.byRuleType = world->byWorldRuleType;
	res.vCurLoc = _player->GetVectorPosition();
	res.vCurDir = _player->GetVectorOriantation();

	SendPacket((char*)&res, sizeof(sGU_AVATAR_WORLD_INFO));
}
void WorldSession::SendDangeonTeleport(HOBJECT handle, WORD Dificulty)
{
	sGU_ULTIMATE_DUNGEON_ENTER_RES res;
	sGU_AVATAR_WORLD_INFO res1;
	WorldTable *WorldTable = sTBM.GetWorldTable();
	sWORLD_TBLDAT *world = NULL;

	res.wOpCode = GU_ULTIMATE_DUNGEON_ENTER_RES;
	res.wPacketSize = sizeof(sGU_ULTIMATE_DUNGEON_ENTER_RES) - 2;
	res.wResultCode = GAME_PARTY_DUNGEON_ENTER_PARTY_FAIL;

	res1.wOpCode = GU_AVATAR_WORLD_INFO;
	res1.wPacketSize = sizeof(sGU_AVATAR_WORLD_INFO) - 2;

	res1.byDojoCount = 7;
	for (int n = 0; n < DBO_MAX_COUNT_DOJO_IN_WORLD; n++)
	{
		res1.sDojoData[n].guildId = 0xffffffff;
		res1.sDojoData[n].dojoTblidx = 0xffffffff;
	}
	/*Need Some Verification "If is in Party, if is PartyLeader, if get Level to enter,
	Dificulty; Obs: Hard need More level ex: UD1 Normal Level 22, Hard level 30"*/
	// UD1
	if (handle == 918)
	{
		printf("Handle %d \n Dificulty %d \n", handle, Dificulty);

		res.wResultCode = GAME_SUCCESS;
		world = (sWORLD_TBLDAT*)sTBM.GetWorldTable()->FindData(200000);
		res1.worldInfo.worldID = 200000;
		_player->SetWorldID(200000);
	}
	//UD2
	else if (handle == 929)
	{
		printf("Handle %d \n Dificulty %d \n", handle, Dificulty);

		res.wResultCode = GAME_SUCCESS;
		world = (sWORLD_TBLDAT*)sTBM.GetWorldTable()->FindData(500000);
		res1.worldInfo.worldID = 500000;
		_player->SetWorldID(500000);
	}
	//UD3
	else if (handle == 732)
	{
		printf("Handle %d \n Dificulty %d \n", handle, Dificulty);

		res.wResultCode = GAME_SUCCESS;
		world = (sWORLD_TBLDAT*)sTBM.GetWorldTable()->FindData(700000);
		res1.worldInfo.worldID = 700000;
		_player->SetWorldID(700000);
	}
	//UD4
	else if (handle == 556)
	{
		printf("Handle %d \n Dificulty %d \n", handle, Dificulty);

		res.wResultCode = GAME_SUCCESS;
		world = (sWORLD_TBLDAT*)sTBM.GetWorldTable()->FindData(712000);
		res1.worldInfo.worldID = 712000;
		_player->SetWorldID(712000);
	}
	//UD5
	else if (handle == 1404)
	{
		printf("Handle %d \n Dificulty %d \n", handle, Dificulty);

		res.wResultCode = GAME_SUCCESS;
		world = (sWORLD_TBLDAT*)sTBM.GetWorldTable()->FindData(715000);
		res1.worldInfo.worldID = 715000;
		_player->SetWorldID(715000);
	}
	//UD6
	else if (handle == 7)
	{
		printf("Handle %d \n Dificulty %d \n", handle, Dificulty);

		res.wResultCode = GAME_SUCCESS;
		world = (sWORLD_TBLDAT*)sTBM.GetWorldTable()->FindData(717000);
		res1.worldInfo.worldID = 717000;
		_player->SetWorldID(717000);
	}
	//BID1
	else if (handle == 43)
	{
		printf("Handle %d \n Dificulty %d \n", handle, Dificulty);

		res.wResultCode = GAME_SUCCESS;
		world = (sWORLD_TBLDAT*)sTBM.GetWorldTable()->FindData(900000);
		res1.worldInfo.worldID = 900000;
		_player->SetWorldID(900000);
	}
	//BID2
	else if (handle == 34162)
	{
		printf("Handle %d \n Dificulty %d \n", handle, Dificulty);

		res.wResultCode = GAME_SUCCESS;
		world = (sWORLD_TBLDAT*)sTBM.GetWorldTable()->FindData(900020);
		res1.worldInfo.worldID = 900020;
		_player->SetWorldID(900020);
	}
	//BID3
	else if (handle == 34161)
	{
		printf("Handle %d \n Dificulty %d \n", handle, Dificulty);

		res.wResultCode = GAME_SUCCESS;
		world = (sWORLD_TBLDAT*)sTBM.GetWorldTable()->FindData(900030);
		res1.worldInfo.worldID = 900030;
		_player->SetWorldID(900030);
	}
	//BID4
	else if (handle == 34117)
	{
		printf("Handle %d \n Dificulty %d \n", handle, Dificulty);

		res.wResultCode = GAME_SUCCESS;
		world = (sWORLD_TBLDAT*)sTBM.GetWorldTable()->FindData(900040);
		res1.worldInfo.worldID = 900040;
		_player->SetWorldID(900040);
	}
	SendPacket((char*)&res, sizeof(sGU_ULTIMATE_DUNGEON_ENTER_RES));
	if (res.wResultCode == GAME_SUCCESS && world != NULL)
	{
		res1.worldInfo.tblidx = world->tblidx;
		res1.worldInfo.sRuleInfo.byRuleType = world->byWorldRuleType;
		_player->GetState()->sCharStateDetail.sCharStateTeleporting.byTeleportType = eTELEPORT_TYPE::TELEPORT_TYPE_DUNGEON;
		res1.vCurLoc.x = world->vStart1Loc.x;
		res1.vCurLoc.y = world->vStart1Loc.y;
		res1.vCurLoc.z = world->vStart1Loc.z;
		res1.vCurDir.x = world->vStart1Dir.x;
		res1.vCurDir.y = world->vStart1Dir.y;
		res1.vCurDir.z = world->vStart1Dir.z;
		_player->SetWorldTableID(world->tblidx);
		_player->Relocate(res1.vCurLoc.x, res1.vCurLoc.y, res1.vCurLoc.z, res1.vCurDir.x, res1.vCurDir.y, res1.vCurDir.z);
		res1.worldInfo.hTriggerObjectOffset = HANDLE_TRIGGER_OBJECT_OFFSET;

		SendPacket((char*)&res1, sizeof(sGU_AVATAR_WORLD_INFO));
	}
}
//----------------------------------------
//	Tell everyone the character state changed
//----------------------------------------
void Player::UpdateState(eCHARSTATE _state)
{
	sGU_UPDATE_CHAR_STATE res;
	memset(&res, 0, sizeof sGU_UPDATE_CHAR_STATE);
	
	res.wOpCode = GU_UPDATE_CHAR_STATE;
	res.wPacketSize = sizeof(sGU_UPDATE_CHAR_STATE) - 2;

	memcpy(&res.sCharState, GetState(), sizeof sCHARSTATE);
	

	res.sCharState.sCharStateBase.byStateID = GetState()->sCharStateBase.byStateID = _state;
	res.sCharState.sCharStateBase.vCurLoc = GetState()->sCharStateBase.vCurLoc = GetVectorPosition();
	res.sCharState.sCharStateBase.vCurDir = GetState()->sCharStateBase.vCurDir = GetVectorOriantation();

	res.handle = GetHandle();

	// sLog.outDetail("Need handle correct condition flag here. UpdateCharState()");
	res.sCharState.sCharStateBase.aspectState.sAspectStateBase.byAspectStateId = GetState()->sCharStateBase.aspectState.sAspectStateBase.byAspectStateId;
	
	res.sCharState.sCharStateBase.dwConditionFlag = GetState()->sCharStateBase.dwConditionFlag;
	res.sCharState.sCharStateBase.dwStateTime = GetState()->sCharStateBase.dwStateTime;

	res.sCharState.sCharStateBase.isFighting =  GetState()->sCharStateBase.isFighting = GetIsFighting();

	
	res.sCharState.sCharStateBase.isFlying = GetState()->sCharStateBase.isFlying = GetIsFlying();

	memcpy(&res.sCharState.sCharStateBase.aspectState.sAspectStateDetail, &GetState()->sCharStateBase.aspectState.sAspectStateDetail, sizeof(sASPECTSTATE_DETAIL));
	SendPacket((char*)&res, sizeof(sGU_UPDATE_CHAR_STATE));
	SendToPlayerList((char*)&res, sizeof(sGU_UPDATE_CHAR_STATE));
}
