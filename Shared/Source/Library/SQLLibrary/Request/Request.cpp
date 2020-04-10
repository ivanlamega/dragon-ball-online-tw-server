#include <mysqlconn_wrapper.h>
#include <Logger.h>
#include <Packet/Char/PacketCU.h>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <list>

bool has_special_char(std::string const &str) {
	return std::find_if(str.begin(), str.end(),
		[](char ch) { return !(isalnum(ch) || ch == '_'); }) != str.end();
}


int MySQLConnWrapper::GetGuildID(int charId)
{
	int result = 0;
	//Get GUILD ID
	sql::ResultSet* Query = executes("SELECT GuildID, Name from characters WHERE CharacterID = '%d' ", charId);

	//There was no Character found in database. Fail
	if (Query && Query->rowsCount() == 0)
	{
		delete Query;
		return 0;
	}

	//Check for that character being in a guild now. If not continue on
	else if (Query && Query->getInt("GuildID") > 0)
	{
		result = Query->getInt("GuildID");
		delete Query;
		return result;
		/*charName = result->getString("Name");
		sql::ResultSet* checkGuildRes = executes("SELECT * from Guilds WHERE GuildName = '%s' ", guildName);
		//Guild exists with this username. Throw the code.
		if (checkGuildRes && checkGuildRes->rowsCount() != 0)
		{
			retcode = GAME_GUILD_SAME_GUILD_NAME_EXIST;
			delete checkGuildRes;
			return retcode;
		}
		else
		{
			sLog.outDebug("Guilds with the same name dont exist Continue and insert");
			sql::ResultSet* createGuildRes = executes("INSERT INTO guilds (GuildName, GuildMasterName, GuildMaster) VALUES('%s', '%s', '%d')", guildName, charName, charId);
			sLog.outDebug("Guild Created. Get the guild info now");
			sql::ResultSet* res = executes("Select * from guilds where GuildMasterName = '%s'", charName);
			int guildId = res->getInt("GuildID");
			sql::ResultSet* setGuildRes = executes("UPDATE characters SET GuildID = %d WHERE CharacterID = %d", guildId, charId);
			sql::ResultSet* setMembersRes = executes("INSERT INTO guild_members (GuildID, MemberID, MemberName, is_guildmaster) VALUES ('%d', '%d', '%s', '1')", guildId, charId, charName);
			retcode = GAME_SUCCESS;
			return retcode;
		}
		*/
	}
	else
	{
		return result;
	}
}


void MySQLConnWrapper::UpdateAccountOnline(int AccountID, int isLoggingID)
{
	sql::ResultSet* result = executes("UPDATE `account` SET `AccountStatus` = '%d' WHERE `AccountID` = '%d';", isLoggingID, AccountID);
	if (result)
	{
		delete result;
	}
}
ResultCodes MySQLConnWrapper::CreateAccount(const char* username, const char* password)
{
	/// prevent mysql injection
	if (has_special_char(username) == true || has_special_char(password) == true)
		return AUTH_DB_FAIL;
	sql::ResultSet* result = executes("SELECT `UserName` FROM `account` WHERE `UserName` = '%s';", username);
	if (result)
	{
		if (result->rowsCount() != 0)
		{
			delete result;
			return AUTH_USER_EXIST;
		}
		delete result;
	}
	result = executes("INSERT INTO account (`UserName`, `UserPassword`) VALUES('%s','%s');", username, password);
	if (result)
	{
		if (result->rowInserted() != 0)
		{
			delete result;
			return RESULT_SUCCESS;
		}
		delete result;
	}
	return AUTH_USER_EXIST;
}
ResultCodes MySQLConnWrapper::ValidateLoginRequest(char *username, char* password, int accid)
{
	/// prevent mysql injection
	if (has_special_char(username) == true || has_special_char(password) == true)
		return AUTH_DB_FAIL;
	sql::ResultSet* result = executes("SELECT `AccountID` FROM `account` WHERE `UserName` = '%s';", username);
	if (result && result->rowsCount() == 0)
	{
		delete result;
		return AUTH_USER_NOT_FOUND;
	}
	else if (result && result->rowsCount() != 0)
	{
		result = executes("SELECT * FROM `account` WHERE `UserName` = '%s' AND `UserPassword` = '%s'", username, password);
		if (result == NULL)
			return AUTH_DB_FAIL;
		if (result->rowsCount() == 0)
		{
			delete result;
			return AUTH_WRONG_PASSWORD;
		}
		if (result->getInt("AccountStatus") != 0)
		{
			delete result;
			return AUTH_USER_EXIST_IN_CHARACTER_SERVER;
		}
		else
		{
			if (result->getInt("IsBanned") == 0)
			{
				delete result;
				return AUTH_SUCCESS;
			}
			else
			{
				delete result;
				return AUTH_USER_TEMPORARY_BLOCK;
			}
		}
	}
	if (result != NULL)
		delete result;
	return AUTH_DB_FAIL;
}
int MySQLConnWrapper::GetAccountID(char* username, char* password)
{
	/// prevent mysql injection
	if (has_special_char(username) == true || has_special_char(password) == true)
		return AUTH_DB_FAIL;
	int val = -1;

	sql::ResultSet* result = executes("SELECT `AccountID` FROM `account` WHERE `userName` = '%s' AND `UserPassword` = '%s';", username, password);
	if (result)
	{
		if (result->rowsCount() > 0)
		{
			val = result->getInt("AccountID");
		}
		delete result;
		return val;
	}
	return val;
}
int MySQLConnWrapper::GetLastServerID(int accid)
{
	int val = 0xFF;

	sql::ResultSet* result = executes("SELECT `LastServerID` FROM `account` WHERE `AccountID` = '%d';", accid);
	if (result)
	{
		if (result->rowsCount() > 0)
		{
			val = result->getInt("LastServerID");
		}
		delete result;
		return val;
	}
	return 0xFF;
}
bool MySQLConnWrapper::GetIsGameMaster(int accid)
{
	bool val = false;

	sql::ResultSet* result = executes("SELECT `IsGM` FROM `account` WHERE `AccountID` = '%d';", accid);
	if (result)
	{
		if (result->rowsCount() > 0)
		{
			val = result->getBoolean("IsGM");
		}
		delete result;
		return val;
	}
	return val;
}
void MySQLConnWrapper::DBUpdateLastServer(int accid, int servid)
{
	sql::ResultSet* result = executes("UPDATE `account` SET `LastServerID` = '%d' WHERE `AccountID` = '%d';", servid, accid);
	if (result)
	{
		delete result;
	}
}
void MySQLConnWrapper::UpdateAccountIP(char*ip, int accid)
{
	sql::ResultSet* result = executes("UPDATE `account` SET `ip` = '%s' WHERE `AccountID` = '%d';", ip, accid);
	if (result)
	{
		delete result;
	}
}
ResultCodes MySQLConnWrapper::Confirm_IP_MAC(int accid, char*ip)
{
	/*prepare("SELECT `ip` FROM `account` WHERE AccountID = ?;");
	setInt(1, accid);
	execute();
	fetch();

	std::string oldIp = getString("ip");

	/// is our first connection to server ?
	if (oldIp == "")
	{
		UpdateAccountIP(ip, accid);
		oldIp = ip;
	}

	/// verify old data
	if (oldIp.c_str() == ip) /// ok*/
	{
		return ResultCodes::AUTH_SUCCESS;
	}
	//return ResultCodes::AUTH_INVALID_CJI_KOR_COOKIE; /// no exist result for mismatch ip
}
void MySQLConnWrapper::UpdateMacAddress(char* byMac, int accid)
{
	
}
void MySQLConnWrapper::GetDBAccCharListData(sCU_CHARACTER_INFO* outdata, int accid, int serverid)
{
	outdata->wOpCode = CU_CHARACTER_INFO;
	outdata->wPacketSize = sizeof(sCU_CHARACTER_INFO) - 2;
	outdata->byCount = 0;

	sql::ResultSet* result = executes("SELECT * FROM `characters` WHERE `AccountID`= '%d' AND `ServerID`= '%d' LIMIT 8;", accid, serverid);
	if (result)
	{
		outdata->byCount = result->rowsCount();
		delete result;
	}
	sLog.outDebug("Account: %d, num characters: %d", accid, outdata->byCount);
}
ResultCodes MySQLConnWrapper::checkUsedName(char* Name)
{
	/// prevent mysql injection
	if (has_special_char(Name) == true)
		return CHARACTER_DB_QUERY_FAIL;
	sql::ResultSet* result = executes("SELECT * FROM `characters` WHERE `Name` = '%s';", Name);
	if (result && result->rowsCount() == 0)
	{
		delete result;
		return CHARACTER_SUCCESS;
	}
	else
	{
		if (result != NULL)
			delete result;
		return CHARACTER_SAMENAME_EXIST;
	}
	if (result != NULL)
		delete result;
	return CHARACTER_DB_QUERY_FAIL;
}
ResultCodes MySQLConnWrapper::DeleteCharacter(int accId, int charId)
{
	// CHECK IF GUILD OWNER !!!!! /\

	// Char db
	sql::ResultSet* result = executes("DELETE FROM `characters` WHERE `AccountID`= '%d' AND `CharacterID`= '%d';", accId, charId);
	if (result)
	{
		if (result->rowDeleted() == 0)
		{
			sLog.outError("Error while removing character, Account: %d, CharacterID: %d", accId, charId);
			delete result;
			return ResultCodes::CHARACTER_DELETE_CHAR_FAIL;
		}
	}
	result = executes("DELETE FROM `quickslot` WHERE `charId`= '%d';", charId);
	if (result)
	{
		if (result->rowDeleted() == 0)
		{
			delete result;
			sLog.outError("Error while removing character quickslot, Account: %d, CharacterID: %d", accId, charId);
			return ResultCodes::CHARACTER_DELETE_CHAR_FAIL;
		}
	}
	result = executes("DELETE FROM `skills` WHERE `owner_id`= '%d';", charId);
	if (result)
	{
		if (result->rowDeleted() == 0)
		{
			delete result;
			sLog.outError("Error while removing character skills, Account: %d, CharacterID: %d", accId, charId);
			return ResultCodes::CHARACTER_DELETE_CHAR_FAIL;
		}
	}
	result = executes("DELETE FROM `items` WHERE `owner_id`= '%d';", charId);
	if (result)
	{
		if (result->rowDeleted() == 0)
		{
			delete result;
			sLog.outError("Error while removing character items, Account: %d, CharacterID: %d", accId, charId);
			return ResultCodes::CHARACTER_DELETE_CHAR_FAIL;
		}
	}
	result = executes("DELETE FROM `portals` WHERE `CharacterID` = '%d';", charId);
	if (result)
	{
		if (result->rowDeleted() == 0)
		{
			delete result;
			sLog.outError("Error while removing character portals, Account: %d, CharacterID: %d", accId, charId);
			return ResultCodes::CHARACTER_DELETE_CHAR_FAIL;
		}
	}
	result = executes("DELETE FROM `bind` WHERE `CharacterID` = '%d';", charId);
	if (result)
	{
		if (result->rowDeleted() == 0)
		{
			delete result;
			sLog.outError("Error while removing character bind, Account: %d, CharacterID: %d", accId, charId);
			return ResultCodes::CHARACTER_DELETE_CHAR_FAIL;
		}
	}
	sLog.outDetail("Character have been deleted: Account: %d, CharacterID: %d", accId, charId);
	if (result != NULL)
		delete result;
	return ResultCodes::CHARACTER_SUCCESS;
}
void MySQLConnWrapper::VerifyCharacterToDelete(int accid)
{
	std::list<int> characterToDelete;
	time_t startedAt;
	time(&startedAt);
	sql::ResultSet* result = executes("SELECT * FROM `characters` WHERE `AccountID` = '%d';", accid);
	if (result && result->rowsCount() > 0)
	{
		while (true)
		{
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
					double diff = difftime(timeNow, deletedAtDate) / 60 / 60; // in hour

					if (diff >= 1) // more than a hour past so delete the character
					{
						characterToDelete.push_back(result->getInt("CharacterID"));
					}
				}
			}
			if (result->next())
				continue;
			else
				break;
		}
	}
	if (result)
		delete result;
	for (std::list<int>::iterator it = characterToDelete.begin(); it != characterToDelete.end(); ++it)
	{
		DeleteCharacter(accid, *it);
	}
}
ResultCodes MySQLConnWrapper::CancelDeleteCharacterPending(CHARACTERID charid)
{
	sql::ResultSet* result = executes("SELECT * FROM `characters` WHERE `CharacterID` = '%d';", charid);
	if (result)
	{
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
				double diff = difftime(timeNow, deletedAtDate) / 60 / 60; // in hour

				if (diff < 1) // less than a hour past so cancel the deletion
				{
					result = executes("UPDATE `characters` SET `deletionStartedAt` = '%s' WHERE `CharacterID` = '%d' LIMIT 1;", "NULL", charid);
					sLog.outDetail("Character have been restored: CharacterID: %d", charid);
					if (result != NULL)
						delete result;
					return ResultCodes::CHARACTER_SUCCESS;
				}
			}
			delete result;
			return ResultCodes::CHARACTER_FAIL;
		}
	}
	return ResultCodes::CHARACTER_DB_QUERY_FAIL;
}
int MySQLConnWrapper::GetAmountOfCharacter(int accid, int servid)
{
	sql::ResultSet* result = executes("SELECT * FROM `characters` WHERE `AccountID`= '%d' AND `ServerID`= '%d' LIMIT 8;", accid, servid);
	if (result)
	{
		int val = result->rowsCount();
		delete result;
		return val;
	}
	return 0;
}
ResultCodes MySQLConnWrapper::CharacterRename(int charid, char* newName)
{
	/// prevent mysql injection
	if (has_special_char(newName) == true)
		return CHARACTER_DB_QUERY_FAIL;
	if (checkUsedName(newName) != CHARACTER_SUCCESS)
	{
		return CHARACTER_SAMENAME_EXIST;
	}
	sql::ResultSet* result = executes("UPDATE `characters` SET `Name` = '%s', `IsToRename` = 0 WHERE `CharacterID` = '%d';", newName, charid);
	if (result)
	{
		delete result;
	}
	return CHARACTER_SUCCESS;
}
void MySQLConnWrapper::SetGameServerState(int serverID, int chanID, int online, int population)
{
	sql::ResultSet* result = executes("UPDATE `realmlist` SET `realmflags` = '%d', `population` = '%d' WHERE `ServerID` = '%d' AND `ChannelID` = '%d';", online, population, serverID, chanID);
	if (result)
	{
		delete result;
	}
}
void MySQLConnWrapper::AddNewPortal(CHARACTERID charid, PORTALID portalid)
{
	sql::ResultSet* result = executes("INSERT INTO portals (`CharacterID`, `PortalID`) VALUES('%d','%d');", charid, portalid);
	if (result)
	{
		delete result;
	}
}
#pragma region SANGAWKU_PACKETS
bool MySQLConnWrapper::CheckIfMailAway(CHARACTERID charID)
{
	bool val = false;

	sql::ResultSet* result = executes("SELECT `MailIsAway` FROM `characters` WHERE `CharacterID` = '%d';", charID);
	if (result)
	{
		if (result->rowsCount() > 0)
		{
			val = result->getBoolean("MailIsAway");
		}
		delete result;
		return val;
	}
	return val;
}

bool MySQLConnWrapper::HowMuchMail(CHARACTERID charID)
{
		sql::ResultSet* result = executes("SELECT `*` FROM `mail` WHERE `CharacterID` = '%';", charID);
	if (result && result->rowsCount() > 0)
	{

	}
}
ResultCodes MySQLConnWrapper::CreateGuild(char *guildName, int charId)
{
	ResultCodes retcode = GAME_FAIL;
	
	string charName;
	sql::ResultSet* result = executes("SELECT GuildID, Name from characters WHERE CharacterID = '%d' ", charId);

	//There was no Character found in database. Fail
	if (result && result->rowsCount() == 0)
	{
		delete result;
		return retcode;
	}
	//Check for that character being in a guild now. If not continue on
	else if (result && result->getInt("GuildID") == 0)
	{
		charName = result->getString("Name");
		sql::ResultSet* checkGuildRes = executes("SELECT * from Guilds WHERE GuildName = '%s' ", guildName);
		//Guild exists with this username. Throw the code. 
		if (checkGuildRes && checkGuildRes->rowsCount() != 0)
		{
			retcode = GAME_GUILD_SAME_GUILD_NAME_EXIST;
			delete checkGuildRes;
			return retcode;
		}
		else
		{
			sLog.outDebug("Guilds with the same name dont exist Continue and insert");
			sql::ResultSet* createGuildRes = executes("INSERT INTO guilds (GuildName, GuildMasterName, GuildMaster) VALUES('%s', '%s', '%d')", guildName, charName, charId);
			sLog.outDebug("Guild Created. Get the guild info now");
			sql::ResultSet* res = executes("Select * from guilds where GuildMasterName = '%s'", charName);
			int guildId = res->getInt("GuildID");
			sql::ResultSet* setGuildRes = executes("UPDATE characters SET GuildID = %d WHERE CharacterID = %d", guildId, charId);
			sql::ResultSet* setMembersRes = executes("INSERT INTO guild_members (GuildID, MemberID, MemberName, is_guildmaster) VALUES ('%d', '%d', '%s', '1')", guildId, charId, charName);
			retcode = GAME_SUCCESS;
			return retcode;
		}

	}
	else
	{
		return retcode;
	}
}
bool MySQLConnWrapper::LoadAllMail(CHARACTERID charID)
{
	sql::ResultSet* result = executes("SELECT `*` FROM `mail` WHERE `CharacterID` = '%';", charID);
	if (result && result->rowsCount() > 0)
	{

	}
}
#pragma endregion END_SANGAWKU