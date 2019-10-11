#ifndef	__MYSQLCONN_WRAPPER__H
# define __MYSQLCONN_WRAPPER__H

#pragma once

#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <mutex>
#include <ResultCode.h>
#include "../../../NtlBaseLib/TableAll.h"
#include <Singleton.h>

#include <cstdarg>

using namespace std;

#define MAX_QUERY_LEN   (32*1024)
struct sCU_CHARACTER_INFO;

class MySQLConnWrapper
{
public:
	/* Your MySQL server settings */
	MySQLConnWrapper();
	~MySQLConnWrapper();
	void manageException(sql::SQLException& e);
	bool connect();
	void Ping();
	bool switchDb(const string& db_name);
	sql::ResultSet* executes(const char* format, ...);
	/*
	username , password , host , db
	*/
	void setInfos(string, string, string, string);
	// REQUEST
	ResultCodes CreateAccount(const char* username, const char* password);
	ResultCodes ValidateLoginRequest(char *username, char* password, int accid);
	int GetAccountID(char* username, char* password);
	int GetLastServerID(int accid);
	bool GetIsGameMaster(int accid);
	void GetDBAccCharListData(sCU_CHARACTER_INFO* outdata, int accid, int serverid);
	void DBUpdateLastServer(int accid, int srvid);
	void UpdateAccountIP(char*ip, int accid);
	void UpdateMacAddress(char* byMac, int accid);
	ResultCodes Confirm_IP_MAC(int accid, char*ip);
	ResultCodes checkUsedName(char* Name);
	void UpdateAccountOnline(int AccountID, int isLoggingID);
	ResultCodes DeleteCharacter(int accId, int charId);
	void VerifyCharacterToDelete(int accid);
	ResultCodes CancelDeleteCharacterPending(CHARACTERID charid);
	int GetAmountOfCharacter(int accid, int servid);
	ResultCodes CharacterRename(int charid, char* newName);
	void SetGameServerState(int serverID, int chanID, int online, int population);
	// GAME
	void UpdateQuickSlots(TBLIDX id, SLOTID slotID, CHARACTERID characterID);
	bool CheckIfItemCanGoHere(CHARACTERID CharID, BYTE Place, BYTE Pos);
	void UpdateItemPosAndPlace(TBLIDX ItemID, BYTE Place, BYTE Pos);
	void LearnSkill(TBLIDX skillID, CHARACTERID characterID, TBLIDX slotID);
	void AddItem(TBLIDX itemID, CHARACTERID characterID, int place, int pose, int count, int rank, int durability,int grade);
	void SaveQuickTeleport(CHARACTERID characterID, BYTE TeleportID, DWORD WorldID, float Loc_x, float Loc_y, float Loc_z, WORD Year, BYTE Moch, BYTE Day, BYTE Hour, BYTE Minute, BYTE Secound, DWORD MapTBLIDX);
	//Cash
	void AddCashItem(TBLIDX itemID, CHARACTERID characterID, int byStackCount, int Handle);
	///////////
	//Title
	void AddTitle( CHARACTERID characterID, TBLIDX TitleID);
	void UpdateSPPoint(int point, CHARACTERID id);
	void UpdateSkill(TBLIDX NewskillID, CHARACTERID characterID, TBLIDX skillID);
	void UpdatePlayerLevel(int _level, CHARACTERID CharID, int _exp);
	void AddNewPortal(CHARACTERID charid, PORTALID portalid);
	bool CheckIfMailAway(CHARACTERID charID);
	bool HowMuchMail(CHARACTERID charID);
	bool LoadAllMail(CHARACTERID charID);
	void AddMail(CHARACTERID CharID, int byDay, int byMailType, int byTextSize, char* wszText, char* wszTargetName, char* wszFromName, int bIsAccept, int bIsLock, int bIsRead);
	void DelMail(MAILID mailID);
	void AddNewBind(CHARACTERID charid, WORLDID worldid, TBLIDX bindID);
	void AddNewWarFog(HOBJECT id, CHARACTERID charid);
	void SavePlayerPositionAndWorldID(sVECTOR3 position, sVECTOR3 direction, WORLDID w_id, WORLDID w_tblidx_id, CHARACTERID charid);
	void SavePlayerLife(int CurLP, int CurEP, CHARACTERID charid);
	void SaveTitleMarket(int TitleMarket, CHARACTERID charid);
	void SavePlayerWagguCoin(int WagguPoint, CHARACTERID charid);
	void SavePlayerCashPoit(int Cash, CHARACTERID charid);
	void SavePlayerZenny(int zenny, CHARACTERID charid);
	void SavePlayerExp(int exp, CHARACTERID charid);

	//Friend
	/** Convert from wchar to char */
	inline void wcharToChar(const wchar_t * src, char *dst, const unsigned int & srcSize) {


		//wcstombs(dst, src, srcSize);

		size_t   charsConverted;
		wcstombs_s(&charsConverted, dst, (float)(srcSize / sizeof(wchar_t)), src, srcSize);
	}

	unsigned int GetFriendIdByName(std::string charName);
	void AddFriendToList(CHARACTERID ownerId, CHARACTERID friendId);
	BYTE GetFriendList(CHARACTERID charID, sFRIEND_FULL_INFO * friends);
private:
	string host;
	string user;
	string password;
	string dbmmoDB;

	sql::Driver* driver;
	sql::Connection* con;

	std::mutex m_mutex;
};

#define sDB AKCore::Singleton<MySQLConnWrapper>::Instance()

#endif /*__MYSQLCONN_WRAPPER__H*/
