#include <CharSocket.h>
#include <Logger.h>
#include <stdio.h>
#include <cstdio>
#include <Opcodes.h>
#include <Encryptation.h>
#include <mysqlconn_wrapper.h>
#include <XmlParser2/XmlParser2.h>
#include <Packet\Char\PacketUC.h>
#include <Packet\Char\PacketCU.h>

bool IsLetters(std::string input)
{
	for (int i = 0; i < input.size(); i++)
	{
		int uppercaseChar = toupper(input[i]); //Convert character to upper case version of character
		if (uppercaseChar < 'A' || uppercaseChar > 'Z') //If character is not A-Z
		{
			return false;
		}
	}
	//At this point, we have gone through every character and checked it.
	return true; //Return true since every character had to be A-Z
}

bool CharSocket::GetLoginRequest(Packet &packet)
{
	sUC_LOGIN_REQ* req = (sUC_LOGIN_REQ*)packet.GetPacketData();
	sCU_LOGIN_RES res;
	::memset(&res, 0, sizeof(sCU_LOGIN_RES));

	res.wPacketSize = sizeof(sCU_LOGIN_RES) - 2;
	res.wOpCode = Opcodes::CU_LOGIN_RES;

	res.dwRaceAllowedFlag = 255;
	res.lastServerFarmId = req->serverID;
	res.wResultCode = ResultCodes::CHARACTER_SUCCESS;
	res.LastChannelID = 1;
	res.unk[0] = 0;
	res.unk[1] = 1;
	res.unk[2] = 0;
	
	// storing data
	AccountID = req->accountId;
	ServerID = req->serverID;

	Write((char*)&res, sizeof(sCU_LOGIN_RES));
	return true;
}
bool CharSocket::GetCharacterServerList(Packet &packet, bool one)
{
	sCU_SERVER_FARM_INFO sinfo;
	::memset(&sinfo, 0, sizeof(sCU_SERVER_FARM_INFO));

	sinfo.wPacketSize = sizeof(sCU_SERVER_FARM_INFO) - 2;
	sinfo.wOpCode = CU_SERVER_FARM_INFO;
	sql::ResultSet* result = sDB.executes("SELECT * from `realmlist` WHERE `ServerID` = '%d';", sinfo.serverFarmInfo.serverFarmId + 1);
	if (result == NULL)
		return false;
	for (int i = 0; i < sXmlParser.GetInt("ServerCount", "value"); i++)
	{
		char snode[20];
		sprintf_s(snode, "Server%d", i + 1);
		sinfo.serverFarmInfo.serverFarmId = i;
		
		memcpy(sinfo.serverFarmInfo.wszGameServerFarmName, charToWChar(sXmlParser.GetStr(snode, "Name").c_str()), MAX_SIZE_SERVER_FARM_NAME_UNICODE);
		
		sinfo.serverFarmInfo.dwLoad = result->getInt("population") / 2;
		sinfo.serverFarmInfo.dwMaxLoad = sXmlParser.GetInt(snode, "MaxLoad");
		isGameMaster = static_cast<bool>(sDB.GetIsGameMaster(AccountID));
		if (sXmlParser.GetInt(snode, "Private") == 1)
		{
			if (isGameMaster == false)
			{
				sinfo.serverFarmInfo.byServerStatus = DBO_SERVER_STATUS_LOCKED;
			}
			else
			{
				sinfo.serverFarmInfo.byServerStatus = DBO_SERVER_STATUS_UP;
			}
		}
		else
		{
			sinfo.serverFarmInfo.byServerStatus = DBO_SERVER_STATUS_UP;
		}

		Write((char*)&sinfo, sizeof(sCU_SERVER_FARM_INFO));
	}

	//if (one)
	{
		sCU_CHARACTER_SERVERLIST_ONE_RES slone;
		::memset(&slone, 0, sizeof(sCU_CHARACTER_SERVERLIST_ONE_RES));

		slone.wPacketSize = sizeof(sCU_CHARACTER_SERVERLIST_ONE_RES) - 2;
		slone.wOpCode = CU_CHARACTER_SERVERLIST_ONE_RES;
		slone.wResultCode = CHARACTER_SUCCESS;

		Write((char*)&slone, sizeof(sCU_CHARACTER_SERVERLIST_ONE_RES));
	}
	//else
	{
		sCU_CHARACTER_SERVERLIST_RES slres;
		::memset(&slres, 0, sizeof(slres));

		slres.wPacketSize = sizeof(sCU_CHARACTER_SERVERLIST_RES) - 2;
		slres.wOpCode = CU_CHARACTER_SERVERLIST_RES;
		slres.wResultCode = CHARACTER_SUCCESS;

		Write((char*)&slres, sizeof(sCU_CHARACTER_SERVERLIST_RES));
	}
	return true;
}
void CharSocket::SendCharacterList()
{
	sCU_CHARACTER_INFO cinfo;
	::memset(&cinfo, 0, sizeof(sCU_CHARACTER_INFO));

	cinfo.wPacketSize = sizeof(sCU_CHARACTER_INFO) - 2;

	sDB.VerifyCharacterToDelete(AccountID);

	sDB.GetDBAccCharListData(&cinfo, AccountID, ServerID);
	cinfo.wOpCode = CU_CHARACTER_INFO;

	sql::ResultSet* result = sDB.executes("SELECT * FROM characters WHERE AccountID = '%d' AND ServerID = '%d';", AccountID, ServerID);
	if (result == NULL)
		return;
	if (result->rowsCount() <= 0)
	{
		delete result;
		return;
	}
	for (int i = 0; i < cinfo.byCount; i++)
	{
		wcscpy_s(cinfo.sPcData[i].awchName, MAX_SIZE_CHAR_NAME_UNICODE + 1, charToWChar(result->getString("Name").c_str()));
		cinfo.sPcData[i].charId = result->getInt("CharacterID");
		cinfo.sPcData[i].byRace = result->getInt("RaceID");
		cinfo.sPcData[i].byClass = result->getInt("ClassID");
		cinfo.sPcData[i].bIsAdult = result->getBoolean("IsAdult");
		cinfo.sPcData[i].byGender = result->getInt("GenderID");
		cinfo.sPcData[i].byFace = result->getInt("FaceID");
		cinfo.sPcData[i].byHair = result->getInt("HairID");
		cinfo.sPcData[i].byHairColor = result->getInt("HairColorID");
		cinfo.sPcData[i].bySkinColor = result->getInt("SkinColorID");
		cinfo.sPcData[i].byLevel = result->getInt("CurrentLevel");
		cinfo.sPcData[i].bTutorialFlag = result->getBoolean("IsTutorialDone");
		cinfo.sPcData[i].bNeedNameChange = result->getBoolean("IsToRename");
		cinfo.sPcData[i].dwMoney = result->getInt("ZennyInventory");
		cinfo.sPcData[i].dwMoneyBank = result->getInt("ZennyBank");
		cinfo.sPcData[i].worldId = result->getInt("WorldID");
		cinfo.sPcData[i].worldTblidx = result->getInt("WorldTableID");
		cinfo.sPcData[i].dwMapInfoIndex = result->getInt("MapInfoID");

		std::string deletedAt = result->getString("deletionStartedAt");
		if (deletedAt != "" && deletedAt != "NULL")
		{
			boost::posix_time::ptime t(boost::posix_time::time_from_string(deletedAt));
			tm pt_tm = to_tm(t); // cast struct to time_t
			if (t.is_not_a_date_time() == false)
			{
				time_t deletedAtDate = mktime(&pt_tm);
				time_t timeNow;
				time(&timeNow);
				long long diff = 3600000 - ((timeNow - deletedAtDate) * 1000); // get time left before delete the character
				cinfo.asDelData[i].charId = cinfo.sPcData[i].charId;
				if (diff <= 0)
					cinfo.asDelData[i].dwPastTick = 0;
				else
					cinfo.asDelData[i].dwPastTick = static_cast<DWORD>(diff);
			}
		}
		else
			cinfo.asDelData[i].charId = INVALID_CHARACTERID;
		result->next();
		sLog.outDebug("Getting information for characters: %d", cinfo.sPcData[i].charId);
	}
	delete result;
	for (int i = 0; i < cinfo.byCount; i++)
	{
		for (int x = 0; x < EQUIP_SLOT_TYPE_COUNT; x++)
		{
			result = sDB.executes("SELECT * FROM items WHERE place=7 AND pos='%d' AND owner_id='%d';", x, cinfo.sPcData[i].charId);
			if (result == NULL)
				return;
			if (result->rowsCount() == 0)
			{
				cinfo.sPcData[i].sItem[x].tblidx = INVALID_TBLIDX;
			}
			else
			{
				cinfo.sPcData[i].sItem[x].tblidx = result->getInt("tblidx");
				cinfo.sPcData[i].sItem[x].byBattleAttribute = result->getInt("battleAttribute");
				cinfo.sPcData[i].sItem[x].byGrade = result->getInt("grade");
				cinfo.sPcData[i].sItem[x].byRank = result->getInt("rank");
			}
			delete result;
		}
	}
	Write((char*)&cinfo, sizeof(sCU_CHARACTER_INFO));
}
bool CharSocket::GetCharacterLoad(Packet &packet)
{
	sUC_CHARACTER_LOAD_REQ* req = (sUC_CHARACTER_LOAD_REQ*)packet.GetPacketData();
	sDB.DBUpdateLastServer(req->accountId, req->serverFarmId);
	sCU_SERVER_CHANNEL_INFO cninfo;
	::memset(&cninfo, 0, sizeof(sCU_SERVER_CHANNEL_INFO));

	cninfo.wPacketSize = sizeof(sCU_SERVER_CHANNEL_INFO) - 2;
	cninfo.wOpCode = CU_SERVER_CHANNEL_INFO;

	ServerID = req->serverFarmId; // store the new serverID to get only the data related to it.

	char snode[20];
	sprintf_s(snode, "Server%d", req->serverFarmId + 1);
	cninfo.byCount = sXmlParser.GetInt(snode, "Count");

	sql::ResultSet* result = sDB.executes("SELECT * from `realmlist` WHERE `ServerID` = '%d';", req->serverFarmId + 1);
	if (result == NULL)
		return false;
	if (result->rowsCount() == cninfo.byCount)
	{
		int i = 0;
		while (true)
		{
			cninfo.serverChannelInfo[i].bIsVisible = true;
			cninfo.serverChannelInfo[i].byServerStatus = (eDBO_SERVER_STATUS)result->getInt("realmflags");
			cninfo.serverChannelInfo[i].byServerChannelIndex = i;
			cninfo.serverChannelInfo[i].dwLoad = result->getInt("population") / 2;// "0-50 - free" "50-80 Normal" "80-99 Ocuped"  "100  full" 
			cninfo.serverChannelInfo[i].dwMaxLoad = sXmlParser.GetInt(snode, "MaxLoad");
			cninfo.serverChannelInfo[i].serverFarmId = req->serverFarmId;
			cninfo.serverChannelInfo[i].is_pvpdb = result->getInt("IsEvent");
			i++;
			if (result->next())
				continue;
			else
				break;
		}
		delete result;
	}
	Write((char*)&cninfo, sizeof(sCU_SERVER_CHANNEL_INFO));

	SendCharacterList(); // SEND THE CURRENT CHARACTER LIST

	sCU_CHARACTER_LOAD_RES clres;
	::memset(&clres, 0, sizeof(sCU_CHARACTER_LOAD_RES));

	clres.wPacketSize = sizeof(sCU_CHARACTER_LOAD_RES) - 2;
	clres.wOpCode = CU_CHARACTER_LOAD_RES;
	clres.wResultCode = CHARACTER_SUCCESS;
	clres.ServerID = req->serverFarmId;
	clres.OpenCharSlots = MAX_COUNT_USER_CHAR_SLOT;
	clres.VipCharSlot = 0;

	Write((char*)&clres, sizeof(sCU_CHARACTER_LOAD_RES));
	return true;
}
bool CharSocket::GetCreateCharactersRequest(Packet &packet)
{
	sUC_CHARACTER_ADD_REQ* data = (sUC_CHARACTER_ADD_REQ*)packet.GetPacketData();
	sCU_CHARACTER_ADD_RES res;
	::memset(&res, 0, sizeof(res));

	wcstombs(username, data->awchCharName, MAX_SIZE_USERID_UNICODE + 1);
	if (sDB.GetAmountOfCharacter(AccountID, ServerID) < MAX_COUNT_USER_CHAR_SLOT)
	{
		if (sDB.checkUsedName(username) == ResultCodes::CHARACTER_SUCCESS)
		{
			if (IsLetters(username) == true)
			{
				res.wResultCode = CHARACTER_SUCCESS;
			}
			else
				res.wResultCode = CHARACTER_CREATE_VALUE_FAIL;
		}
		else
			res.wResultCode = CHARACTER_CREATE_VALUE_FAIL;
	}
	else
		res.wResultCode = CHARACTER_COUNT_OVER;

	res.wOpCode = CU_CHARACTER_ADD_RES;
	res.wPacketSize = sizeof(sCU_CHARACTER_ADD_RES) - 2;

	if (res.wResultCode == CHARACTER_SUCCESS)
	{
		wcscpy_s(res.sPcDataSummary.awchName, MAX_SIZE_CHAR_NAME_UNICODE + 1, charToWChar(username));
		res.sPcDataSummary.byRace = data->byRace;
		res.sPcDataSummary.byClass = data->byClass;
		res.sPcDataSummary.bIsAdult = false;
		res.sPcDataSummary.byGender = data->byGender;
		res.sPcDataSummary.byFace = data->byFace;
		res.sPcDataSummary.byHair = data->byHair;
		res.sPcDataSummary.byHairColor = data->byHairColor;
		res.sPcDataSummary.bySkinColor = data->bySkinColor;
		res.sPcDataSummary.byLevel = 1;
		res.sPcDataSummary.dwMoney = 0;
		res.sPcDataSummary.dwMoneyBank = 0;
		res.sPcDataSummary.bTutorialFlag = true;
		res.sPcDataSummary.bNeedNameChange = false;

		res.unknown = 1;

		res.sPcDataSummary.sDogi.byDojoColor = 255;
		res.sPcDataSummary.sDogi.byGuildColor = 255;
		res.sPcDataSummary.sDogi.byType = 255;
		res.sPcDataSummary.sDogi.guildId = INVALID_TBLIDX;
		res.sPcDataSummary.sMarking.dwCode = 255;
		res.sPcDataSummary.dwMapInfoIndex = INVALID_TBLIDX;
		res.sPcDataSummary.worldId = 1;
		res.sPcDataSummary.worldTblidx = INVALID_TBLIDX;
		res.sPcDataSummary.fPositionX = 0;
		res.sPcDataSummary.fPositionY = 0;
		res.sPcDataSummary.fPositionZ = 0;

		//res.sPcDataSummary.wUnknow1 = 65535;
		//for (int x = 0; x < 6; x++)
		//{
			//res.sPcDataSummary.abyUnknow2[x] = 255;
		//}

		res.sPcDataSummary.charId = AddCharacters(res.sPcDataSummary);
		if (res.sPcDataSummary.charId == -1)
			res.wResultCode = CHARACTER_FAIL;
		else
		{
			for (int x = 0; x < EQUIP_SLOT_TYPE_COUNT; x++)
			{
				sql::ResultSet* result = sDB.executes("SELECT * FROM items WHERE place=7 AND pos = '%d' AND owner_id  = '%d';", x, res.sPcDataSummary.charId);
				if (result == NULL)
					return false;
				if (result->rowsCount() == 0)
				{
					res.sPcDataSummary.sItem[x].tblidx = INVALID_TBLIDX;
				}
				else
				{
					res.sPcDataSummary.sItem[x].tblidx = result->getInt("tblidx");
					res.sPcDataSummary.sItem[x].byBattleAttribute = result->getInt("battleAttribute");
					res.sPcDataSummary.sItem[x].byGrade = result->getInt("grade");
					res.sPcDataSummary.sItem[x].byRank = result->getInt("rank");
				}
				delete result;
			}
		}
	}
	Write((char*)&res, sizeof(sCU_CHARACTER_ADD_RES));
	return true;
}
bool CharSocket::GetCharactersDeleteRequest(Packet &packet)
{
	sUC_CHARACTER_DEL_REQ *req = (sUC_CHARACTER_DEL_REQ*)packet.GetPacketData();
	sCU_CHARACTER_DEL_RES res;
	::memset(&res, 0, sizeof(sCU_CHARACTER_DEL_RES));

	res.wOpCode = CU_CHARACTER_DEL_RES;
	res.wPacketSize = sizeof(sCU_CHARACTER_DEL_RES) - 2;
	
	res.charId = req->charId;

	time_t rawtime;
	struct tm * timeinfo = new struct tm;
	char buffer[80];
	time(&rawtime);
	localtime_s(timeinfo, &rawtime);
	strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);

	sql::ResultSet* result = sDB.executes("UPDATE characters SET `deletionStartedAt` = '%s' WHERE `CharacterID` = '%d' LIMIT 1;", buffer, req->charId);
	if (result != NULL)
		delete result;
	res.wResultCode = CHARACTER_SUCCESS;

	Write((char*)&res, sizeof(sCU_CHARACTER_DEL_RES));
	delete timeinfo;
	return true;
}
bool CharSocket::SendCharacterExit(Packet &packet)
{
	sCU_CHARACTER_EXIT_RES res;
	::memset(&res, 0, sizeof(sCU_CHARACTER_EXIT_RES));

	res.wOpCode = CU_CHARACTER_EXIT_RES;
	res.wPacketSize = sizeof(sCU_CHARACTER_EXIT_RES) - 2;
	res.wResultCode = GAME_SUCCESS;

	Write((char*)&res, sizeof(sCU_CHARACTER_EXIT_RES));

	return true;
}
bool CharSocket::SendCancelCharacterDeleteRequest(Packet &packet)
{
	sUC_CHARACTER_DEL_CANCEL_REQ *req = (sUC_CHARACTER_DEL_CANCEL_REQ*)packet.GetPacketData();
	sCU_CHARACTER_DEL_CANCEL_RES res;
	::memset(&res, 0, sizeof(sCU_CHARACTER_DEL_CANCEL_RES));

	res.wOpCode = CU_CHARACTER_DEL_CANCEL_RES;
	res.wPacketSize = sizeof(sCU_CHARACTER_DEL_CANCEL_RES) - 2;
	res.wResultCode = sDB.CancelDeleteCharacterPending(req->charId);
	res.charId = req->charId;
	Write((char*)&res, sizeof(sCU_CHARACTER_DEL_CANCEL_RES));
	return true;
}
bool CharSocket::SendCharSelect(Packet &packet)
{
	sUC_CHARACTER_SELECT_REQ * req = (sUC_CHARACTER_SELECT_REQ*)packet.GetPacketData();
	sCU_CHARACTER_SELECT_RES res;

	res.wOpCode = CU_CHARACTER_SELECT_RES;
	res.wPacketSize = sizeof(sCU_CHARACTER_SELECT_RES) - 2;

	char channelSelected[20];
	char serverSelected[20];
	sprintf_s(serverSelected, "Server%u", ServerID + 1);
	sprintf_s(channelSelected, "Channel%u", req->byServerChannelIndex + 1);
	memcpy(res.szGameServerIP, sXmlParser.GetChildStr(serverSelected, channelSelected, "IP").c_str(), MAX_LENGTH_OF_IP);
	res.wGameServerPortForClient = sXmlParser.GetChildInt(serverSelected, channelSelected, "Port");
	res.charId = req->charId;
	res.wResultCode = CHARACTER_SUCCESS;
	strcpy_s((char*)res.abyAuthKey, MAX_SIZE_AUTH_KEY, "Dbo");

	Write((char*)&res, sizeof(sCU_CHARACTER_SELECT_RES));

	return true;
}
bool CharSocket::SendConnectWaitCheck(Packet& packet)
{
	sCU_CONNECT_WAIT_CHECK_RES res;

	res.wPacketSize = sizeof(sCU_CONNECT_WAIT_CHECK_RES) - 2;
	res.wOpCode = CU_CONNECT_WAIT_CHECK_RES;
	res.wResultCode = GAME_SUCCESS;
	
	Write((char*)&res, sizeof(sCU_CONNECT_WAIT_CHECK_RES));
	
	sCU_CONNECT_WAIT_COUNT_NFY res2;

	res2.wPacketSize = sizeof(sCU_CONNECT_WAIT_COUNT_NFY) - 2;
	res2.wOpCode = CU_CONNECT_WAIT_COUNT_NFY;
	res2.dwCountWaiting = 0; /// How many players are in queue?

	Write((char*)&res2, sizeof(sCU_CONNECT_WAIT_COUNT_NFY));

	return true;
}
bool CharSocket::SendCharacterRename(Packet &packet)
{
	sUC_CHARACTER_RENAME_REQ * req = (sUC_CHARACTER_RENAME_REQ*)packet.GetPacketData();
	sCU_CHARACTER_RENAME_RES res;
	char	nameRequest[MAX_SIZE_USERID_UNICODE + 1];
	
	wcstombs(nameRequest, req->awchCharName, MAX_SIZE_USERID_UNICODE + 1);
	res.wPacketSize = sizeof(sCU_CHARACTER_RENAME_RES) - 2;
	res.wOpCode = CU_CHARACTER_RENAME_RES;
	res.charId = req->charId;
	res.wResultCode = sDB.CharacterRename(req->charId, nameRequest);
	if (res.wResultCode == CHARACTER_SUCCESS)
	{
		memcpy(username, nameRequest, MAX_SIZE_USERID_UNICODE + 1);
	}
	Write((char*)&res, sizeof(sCU_CHARACTER_RENAME_RES));
	return true;
}
bool CharSocket::HaveToSendOneServer()
{
	sql::ResultSet* result = sDB.executes("SELECT AccountStatus FROM account WHERE accountid = '%d';", AccountID);
	if (result == NULL)
		return false;
	if (result->rowsCount() <= 0)
	{
		delete result;
		return false;
	}
	int status = result->getInt("AccountStatus");
	delete result;
	if (status != 2)
	{
		return true;
	}
	return false;
}
bool CharSocket::_ProcessCharPacket(Packet& packet, WORD wOpCode)
{
	switch (wOpCode)
	{
		case UC_LOGIN_REQ:
		{
			sLog.outDebug("~~~~~~~~~ UC_LOGIN_REQ ~~~~~~~~~");
			return GetLoginRequest(packet);
		}
		case UC_CHARACTER_SERVERLIST_REQ:
		{
			sLog.outDebug("~~~~~~~~~ UC_CHARACTER_SERVERLIST_REQ ~~~~~~~~~");
			return GetCharacterServerList(packet, false);
		}
		case UC_CHARACTER_SERVERLIST_ONE_REQ:
		{
			sLog.outDebug("~~~~~~~~~ UC_CHARACTER_SERVERLIST_ONE_REQ ~~~~~~~~~");
			return GetCharacterServerList(packet, true);
		}
		case UC_CHARACTER_ADD_REQ:
		{
			sLog.outDebug("~~~~~~~~~ UC_CHARACTER_ADD_REQ ~~~~~~~~~");
			return GetCreateCharactersRequest(packet);
		}
		case UC_CHARACTER_DEL_REQ:
		{
			sLog.outDebug("~~~~~~~~~ UC_CHARACTER_DEL_REQ ~~~~~~~~~");
			return GetCharactersDeleteRequest(packet);
		}
		case UC_CHARACTER_SELECT_REQ:
		{
			sLog.outDebug("~~~~~~~~~ UC_CHARACTER_SELECT_REQ ~~~~~~~~~");
			return SendCharSelect(packet);
		}
		case UC_CHARACTER_EXIT_REQ:
		{
			sLog.outDebug("~~~~~~~~~ UC_CHARACTER_EXIT_REQ ~~~~~~~~~");
			return SendCharacterExit(packet);
		}
		case UC_CHARACTER_LOAD_REQ:
		{
			sLog.outDebug("~~~~~~~~~ UC_CHARACTER_LOAD_REQ ~~~~~~~~~");
			return GetCharacterLoad(packet);
		}
		case UC_CHARACTER_DEL_CANCEL_REQ:
		{
			sLog.outDebug("~~~~~~~~~ UC_CHARACTER_DEL_CANCEL_REQ ~~~~~~~~~");
			return SendCancelCharacterDeleteRequest(packet);
		}
		case UC_CONNECT_WAIT_CHECK_REQ:
		{
			sLog.outDebug("~~~~~~~~~ UC_CONNECT_WAIT_CHECK_REQ ~~~~~~~~~");
			return SendConnectWaitCheck(packet);
		}
		case UC_CONNECT_WAIT_CANCEL_REQ:
		{
			sLog.outDebug("~~~~~~~~~ UC_CONNECT_WAIT_CANCEL_REQ ~~~~~~~~~");
			break;
		}
		case UC_CHARACTER_RENAME_REQ:
		{
			sLog.outDebug("~~~~~~~~~ UC_CHARACTER_RENAME_REQ ~~~~~~~~~");
			return SendCharacterRename(packet);
		}
		case UC_CASHITEM_HLSHOP_REFRESH_REQ:
		{
			sLog.outDebug("~~~~~~~~~ UC_CASHITEM_HLSHOP_REFRESH_REQ ~~~~~~~~~");
			return true;
			break;
		}
		case UC_CASHITEM_BUY_REQ:
		{
			sLog.outDebug("~~~~~~~~~ UC_CASHITEM_BUY_REQ ~~~~~~~~~");
			break;
		}
		case UC_CHAR_SERVERLIST_REQ:
		{
			sLog.outDebug("~~~~~~~~~ UC_CHAR_SERVERLIST_REQ ~~~~~~~~~");
			return GetCharacterServerList(packet, HaveToSendOneServer()); // will send the all list and the client will connect to the last connected server
		}
		default:
		{
			sLog.outError("Packet_[%u] Unknow", wOpCode);
			return false;
		}
	}
	return false;
}
int CharSocket::AddCharacters(sPC_SUMMARY data)
{
	NewbieTable* pNewBieTable = sTBM.GetNewbieTable();
	sNEWBIE_TBLDAT* pNewbieTbldat = reinterpret_cast<sNEWBIE_TBLDAT*>(pNewBieTable->GetNewbieTbldat(data.byRace, data.byClass));

	if (pNewbieTbldat != NULL);
	else
	{
		sLog.outError("Error, Account: %d try to create invalid class / race [%d][%d] from ip: %s", AccountID, data.byClass, data.byRace, m_address);
		return -1;
	}

	int charid = -1;
	sql::ResultSet* result = sDB.executes("INSERT INTO characters (AccountID, Name, ServerID, RaceID, ClassID, GenderID, FaceID, HairID, HairColorID, SkinColorID, GuildID) VALUES ('%d', '%s', '%d', '%d', '%d', '%d', '%d', '%d', '%d', '%d', '%d');",
		AccountID, username, ServerID, data.byRace, data.byClass, data.byGender, data.byFace, data.byHair, data.byHairColor, data.bySkinColor, 0);
	if (result != NULL)
		delete result;
	result = sDB.executes("SELECT `CharacterID` from `characters` WHERE `Name` = '%s' AND `AccountID` = '%d';",
		username, AccountID);
	if (result == NULL)
		return -1;
	if (result->rowsCount() == 0)
		return -1;
	charid = result->getInt("CharacterID");
	delete result;

	// BASE ATTRIBUTE
	sPC_TBLDAT* newb = (sPC_TBLDAT*)sTBM.GetPcTable()->GetPcTbldat(data.byRace, data.byClass, data.byGender);
	if (newb == NULL)
		return false;
	// LP Calculation
	DWORD BasicLife = newb->wBasic_LP + static_cast<DWORD>(newb->byLevel_Up_LP * 1);
	WORD LevelCon = newb->byCon + static_cast<WORD>(newb->fLevel_Up_Con * 1);
	float ConByPoint = 81.6; // 1con = 85 old tw
	DWORD LP = BasicLife + static_cast<DWORD>(LevelCon * ConByPoint);

	//EP Calculation
	WORD BasicEnergy = newb->wBasic_EP + (newb->byLevel_Up_EP * 1);
	WORD LevelEng = newb->byEng + static_cast<WORD>(newb->fLevel_Up_Eng * 1);
	float EngByPoint = 56; // 1Eng = 45 ep old tw
	WORD EP = BasicEnergy + static_cast<WORD>(LevelEng * EngByPoint);
	result = sDB.executes("INSERT INTO characters_attributes (`CharacterID`, `CurLP`, `CurEP`, `CurRP`) VALUES ('%d', '%d', '%d', '%d');",
		charid, LP, EP, 0);
	if (result != NULL)
		delete result;
	// QUICK SLOT
	result = sDB.executes("INSERT INTO quickslot (`charId`) VALUES ( '%d' );",
		charid);
	if (result != NULL)
		delete result;
	// PORTALS
	PortalTable* pPortalTbl = sTBM.GetPortalTable();
	sDB.AddNewPortal(charid, pPortalTbl->FindData(pNewbieTbldat->defaultPortalTblidx)->tblidx);
	sDB.AddNewPortal(charid, pPortalTbl->FindData(pNewbieTbldat->defaultPortalTblidx1)->tblidx);
	sDB.AddNewPortal(charid, pPortalTbl->FindData(pNewbieTbldat->defaultPortalTblidx2)->tblidx);
	// BASE ITEM
	for (int i = 0; i < 10; i++)
	{		
		if (pNewbieTbldat->aitem_Tblidx[i] != -1)
		{
			sizeof(sITEM_TBLDAT);
			sITEM_TBLDAT* item = (sITEM_TBLDAT*)sTBM.GetItemTable()->FindData(pNewbieTbldat->aitem_Tblidx[i]);
			if (item == NULL)
			{
				item = (sCASHITEM_TBLDAT*)sTBM.GetCashItemTable()->FindData(pNewbieTbldat->aitem_Tblidx[i]);
			}
			if (item != NULL)
			{
				eEQUIP_TYPE eType = (eEQUIP_TYPE)item->eEquipType;

				if (eType == eEQUIP_TYPE::EQUIP_TYPE_ARMOR || eType == eEQUIP_TYPE::EQUIP_TYPE_MAIN_WEAPON || eType == eEQUIP_TYPE::EQUIP_TYPE_SUB_WEAPON
				|| eType == eEQUIP_TYPE::EQUIP_TYPE_SCOUTER)
				{
					sDB.AddItem(pNewbieTbldat->aitem_Tblidx[i], charid, int(CONTAINER_TYPE_EQUIP), pNewbieTbldat->abyPos[i], 1, item->eRank, item->byDurability, 0, INVALID_TBLIDX, INVALID_TBLIDX, INVALID_TBLIDX, INVALID_TBLIDX, INVALID_TBLIDX, INVALID_TBLIDX, INVALID_TBLIDX, INVALID_TBLIDX, INVALID_TBLIDX, INVALID_TBLIDX, INVALID_TBLIDX, INVALID_TBLIDX);
				}
				else
				{
					if (item->eItemType == eITEM_TYPE::ITEM_TYPE_NETPYSTORE)
					{
						//NetPyStore
						sDB.AddItem(pNewbieTbldat->aitem_Tblidx[i], charid, int(CONTAINER_TYPE_BAGSLOT), int(CONTAINER_TYPE_NETPYSTORE), 1, item->eRank, item->byDurability, 0, INVALID_TBLIDX, INVALID_TBLIDX, INVALID_TBLIDX, INVALID_TBLIDX, INVALID_TBLIDX, INVALID_TBLIDX, INVALID_TBLIDX, INVALID_TBLIDX, INVALID_TBLIDX, INVALID_TBLIDX, INVALID_TBLIDX, INVALID_TBLIDX);
					}
					else if (item->eItemType == eITEM_TYPE::ITEM_TYPE_WAREHOUSE)
					{
						//Bank Bag 
						sDB.AddItem(pNewbieTbldat->aitem_Tblidx[i], charid, int(CONTAINER_TYPE_BANKSLOT), int(CONTAINER_TYPE_BAGSLOT), 1, item->eRank, item->byDurability, 0, INVALID_TBLIDX, INVALID_TBLIDX, INVALID_TBLIDX, INVALID_TBLIDX, INVALID_TBLIDX, INVALID_TBLIDX, INVALID_TBLIDX, INVALID_TBLIDX, INVALID_TBLIDX, INVALID_TBLIDX, INVALID_TBLIDX, INVALID_TBLIDX);
					}
					else if (item->eItemType == eITEM_TYPE::ITEM_TYPE_GAMBLE)
					{
						printf("Item ID = %d \n", pNewbieTbldat->aitem_Tblidx[i]);
						// Popo Gift Box
						sDB.AddItem(pNewbieTbldat->aitem_Tblidx[i], charid, int(CONTAINER_TYPE_BAG1), int(BAGSLOT_POSITION_BAGSLOT_POSITION_0), 1, item->eRank, item->byDurability, 0, INVALID_TBLIDX, INVALID_TBLIDX, INVALID_TBLIDX, INVALID_TBLIDX, INVALID_TBLIDX, INVALID_TBLIDX, INVALID_TBLIDX, INVALID_TBLIDX, INVALID_TBLIDX, INVALID_TBLIDX, INVALID_TBLIDX, INVALID_TBLIDX);
					}
					else if (item->eItemType == eITEM_TYPE::ITEM_TYPE_BAG)
					{
						sDB.AddItem(pNewbieTbldat->aitem_Tblidx[i], charid, int(CONTAINER_TYPE_BAGSLOT), int(BAGSLOT_POSITION_BAGSLOT_POSITION_0), 1, item->eRank, item->byDurability, 0, INVALID_TBLIDX, INVALID_TBLIDX, INVALID_TBLIDX, INVALID_TBLIDX, INVALID_TBLIDX, INVALID_TBLIDX, INVALID_TBLIDX, INVALID_TBLIDX, INVALID_TBLIDX, INVALID_TBLIDX, INVALID_TBLIDX, INVALID_TBLIDX);
						sDB.AddItem(pNewbieTbldat->aitem_Tblidx[i], charid, int(CONTAINER_TYPE_BAGSLOT), int(BAGSLOT_POSITION_BAGSLOT_POSITION_NETPYSTORE), 1, item->eRank, item->byDurability, 0, INVALID_TBLIDX, INVALID_TBLIDX, INVALID_TBLIDX, INVALID_TBLIDX, INVALID_TBLIDX, INVALID_TBLIDX, INVALID_TBLIDX, INVALID_TBLIDX, INVALID_TBLIDX, INVALID_TBLIDX, INVALID_TBLIDX, INVALID_TBLIDX);
					}
				}
			}
		}
	}
	// BASE SKILL
	for (int i = 0; i < 7; i++)
	{
		if (pNewbieTbldat->aSkillTblidx[i] != -1)
		{
			sDB.LearnSkill(pNewbieTbldat->aSkillTblidx[i], charid, i + 1);
		}
	}
	// SPAWN LOCATION
	result = sDB.executes("UPDATE characters SET `Position_X` = '%f', `Position_Y` = '%f', `Position_Z` = '%f' WHERE `CharacterID` = '%d' LIMIT 1;",
		pNewbieTbldat->vSpawn_Loc.x, pNewbieTbldat->vSpawn_Loc.y, pNewbieTbldat->vSpawn_Loc.z, charid);
	if (result != NULL)
		delete result;
	// BASE BIND
	sDB.AddNewBind(charid, 1, 6); // kokkara village
	// GAMEMASTER
	if (isGameMaster == true)
	{
		result = sDB.executes("UPDATE characters SET `IsGameMaster` = '%d' WHERE `CharacterID` = '%d' LIMIT 1;",
			isGameMaster, charid);
		if (result != NULL)
			delete result;
	}

	// Add Custom Initial Level For Each Server
	if (ServerID == 0)
	{
		result = sDB.executes("UPDATE characters SET `CurrentLevel` = '70' WHERE `CharacterID` = '%d' LIMIT 1;",
			 charid);
		if (result != NULL)
			delete result;
	}

	if (ServerID == 1)
	{
		result = sDB.executes("UPDATE characters SET `CurrentLevel` = '1' WHERE `CharacterID` = '%d' LIMIT 1;",
			 charid);
		if (result != NULL)
			delete result;
	}
	return charid;
}