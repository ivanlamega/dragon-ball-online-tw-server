#include "NtlString.h"
#include "NtlSharedCommon.h"
#include "NtlCharacter.h"
#include "NtlVector.h"
enum GENERAL_LOG
{
	PRINT_APP = 2,
};
enum GENERAL_SESSION
{
	SESSION_CLIENT,
	SESSION_SERVER_ACTIVE,
	SESSION_MASTER_SERVER,
	SESSION_OPERATING_SERVER,
	SESSION_QUERY_SERVER,
	SESSION_AUTH_SERVER,
	SESSION_CHAR_SERVER,
	SESSION_COMMUNITY_SERVER,
	SESSION_GAME_SERVER,
	SESSION_NPC_SERVER,
	SESSION_LOG_SERVER,
	SESSION_SERVER_AGENT_SERVER,
	SESSION_SERVER_AGENT_CONTROLLER_SERVER,
	SESSION_SYSTEM_TOOL_SERVER,
	SESSION_GAME_REPORT_SERVER,
	SESSION_BOT_MASTER_SERVER,
	SESSION_BOT_AGENT_SERVER
};
struct sSERVERCONFIG
{
	//Auth
	CNtlString		strAuthServerIP;
	WORD			wAuthServerPort;
	//Char
	CNtlString		strCharServerIP;
	WORD			wCharServerPort;
	//Community
	CNtlString		strCommunityServerIP;
	WORD			wCommunityServerPort;
	//Game
	CNtlString		strGameServerIP;
	WORD			wGameServerPort;
	//GameReport
	CNtlString		strGameReportServerIP;
	WORD			wGameReportServerPort;
	//Log
	CNtlString		strLogServerIP;
	WORD			wLogServerPort;
	//Server Agent
	CNtlString		strServerAgentServerIP;
	WORD			wServerAgentServerPort;
	//Server Controller
	CNtlString		strServerAgentControllerServerIP;
	WORD			wServerAgentControllerServerPort;
	//System tool
	CNtlString		strSystemToolServerIP;
	WORD			wSystemToolServerPort;
	//Master
	CNtlString		strMasterServerIP;
	WORD			wMasterServerPort;
	//NPC
	CNtlString		strNpcServerIP;
	WORD			wNpcServerPort;
	//Operating
	CNtlString		strOperatingServerIP;
	WORD			wOperatingServerPort;
	//Query
	CNtlString		strQueryServerIP;
	WORD			wQueryServerPort;
	//Bot Agent
	CNtlString		strBotAgentIP;
	WORD			wBotAgentPort;
	//Bot Master
	CNtlString		strBotMasterIP;
	WORD			wBotMasterPort;
	//Database - Is ODBC then its ok
	CNtlString		strDatabaseDSN;
	//WORD			wDatabasePort;
	CNtlString		strDatabaseUsername;
	CNtlString		strDatabasePassword;
	CNtlString		strDatabaseName;
};

#pragma pack(2)
//Used in NPC Server
struct sNPC_FULLDATA
{
	sVECTOR3 vSpawnLoc;
	sVECTOR3 vSpawnDir;	
	BYTE	 byAspectID;
	bool	 bFightMode;
	TBLIDX	 worldId;
	HOBJECT	 hHandler;
	union 
	{
		sNPC_BRIEF sNpcData;
	};	
};

struct sMOB_FULLDATA
{
	sVECTOR3 vSpawnLoc;
	sVECTOR3 vSpawnDir;
	BYTE	 byAspectID;
	bool	 bFightMode;
	TBLIDX	 worldId;
	HOBJECT  hHandler;
	union
	{
		sMOB_BRIEF sMobData;
	};
};
//Used in community server
struct sCHAR_GAME_INFO
{
	ACCOUNTID			accountId;
	CHARACTERID			charId;
	HOBJECT				hHandle;
	BYTE				byRace;
	BYTE				byClass;
	BYTE				byLevel;
	DWORD				dwReputation;
	WORLDID				worldId;
	sVECTOR3			vCurrentPosition;
	WCHAR				awchName[NTL_MAX_SIZE_CHAR_NAME_UNICODE + 1];
	GUILDID				guildId;
	DWORD				dwPunishBitFlag;
	GMGROUPID			gmGroupId;
	TBLIDX				mapNameTblidx;
	WCHAR				awchUserID[NTL_MAX_SIZE_USERID_UNICODE + 1];		// User ID
};

typedef std::map<TBLIDX, sNPC_FULLDATA*> NPC_LIST;
typedef std::map<TBLIDX, sNPC_FULLDATA*>::iterator NPC_LIST_IT;

typedef std::map<TBLIDX, sMOB_FULLDATA*> MOB_LIST;
typedef std::map<TBLIDX, sMOB_FULLDATA*>::iterator MOB_LIST_IT;

typedef std::multimap<HOBJECT, HOBJECT> SPAWNMAP;
typedef SPAWNMAP::iterator SPAWNMAP_IT;

typedef std::map<HSESSION, sCHAR_GAME_INFO> PLAYERS_LIST;
typedef std::map<HSESSION, sCHAR_GAME_INFO>::iterator PLAYERS_IT;

typedef std::map<DWORD, CHARACTERID>	PARTY_MEMBERS;
typedef std::map<DWORD, CHARACTERID>::iterator PARTY_MEMBER_IT;

typedef std::map<DWORD, sCHAR_GAME_INFO>	GUILD_MEMBERS;
typedef std::map<DWORD, sCHAR_GAME_INFO>::iterator GUILD_MEMBER_IT;

typedef std::map<PARTYID, PARTY_MEMBERS> PARTY_LIST;
typedef std::map<PARTYID, PARTY_MEMBERS>::iterator PARTY_IT;

typedef std::map<GUILDID, GUILD_MEMBERS> GUILD_LIST;
typedef std::map<GUILDID, GUILD_MEMBERS>::iterator GUILD_LIST_IT;

//////////////////////////////////////////////////////QUERY SERVER/////////////////////////////////////////////////////////////////////////////
const DWORD					MAX_NUMOF_QUERY_GAME_CLIENT = 50;
const DWORD					MAX_NUMOF_QUERY_SERVER = 5;
const DWORD					MAX_NUMOF_QUERY_SESSION = MAX_NUMOF_QUERY_GAME_CLIENT + MAX_NUMOF_QUERY_SERVER;
const unsigned int			MAX_SIZE_USER_ID = 12;
const unsigned int			MAX_SIZE_USER_PW = 12;
//Querys available
enum SQL_ID
{
	SP_AccountSelect = 0,
	SP_BuffListCreate,
	SP_BuffListUpdate,
	SP_BuffListDelete,
	SP_BuffListSelect,
	SP_CharacterCreate,
	SP_CharacterUpdate,
	SP_CharacterSelect,
	SP_CharacterSelectByID,
	SP_CharacterOnline,
	SP_CharacterMaxID,
	SP_HTBSkillSelect,
	SP_HTBSkillInsert,
	SP_HTBSkillUpdate,
	SP_InventorySelect,
	SP_InventoryCreate,
	SP_InventoryInsertItem,
	SP_InventoryDeleteItem,
	SP_InventoryItemMove,
	SP_SkillsSelect,
	SP_SkillsSelectAll,
	SP_SkillsInsert,
	SP_SkillsMaxSlotByChar,
	SP_SkillsDelete,
	SP_SkillsUpdate,
	SP_QuickSlotSelect,
	SP_QuickSlotCreate,
	SP_QuickSlotUpdate,
	SP_QuickSlotDelete,
	SP_WarFogInsert,
	SP_WarFogSelect,	
	SP_WarFogUpdate,
	MAX_SQL_ID
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////MASTER SERVER////////////////////////////////////////////////////////////////////////////
const DWORD					MAX_NUMOF_MASTER_GAME_CLIENT = 50;
const DWORD					MAX_NUMOF_MASTER_SERVER = 5;
const DWORD					MAX_NUMOF_MASTER_SESSION = MAX_NUMOF_MASTER_GAME_CLIENT + MAX_NUMOF_MASTER_SERVER;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////AUTH SERVER//////////////////////////////////////////////////////////////////////////////
const DWORD					MAX_NUMOF_AUTH_GAME_CLIENT = 50;
const DWORD					MAX_NUMOF_AUTH_SERVER = 5;
const DWORD					MAX_NUMOF_AUTH_SESSION = MAX_NUMOF_AUTH_GAME_CLIENT + MAX_NUMOF_AUTH_SERVER;
typedef std::map<WCHAR*, HSESSION> AUTH_CLIENT_SESSION;
typedef std::map<WCHAR*, HSESSION>::iterator AUTH_CLIENT_IT;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////CHAR SERVER//////////////////////////////////////////////////////////////////////////////
const DWORD					MAX_NUMOF_CHAR_GAME_CLIENT = 50;
const DWORD					MAX_NUMOF_CHAR_SERVER = 5;
const DWORD					MAX_NUMOF_CHAR_SESSION = MAX_NUMOF_CHAR_GAME_CLIENT + MAX_NUMOF_CHAR_SERVER;
typedef std::map<ACCOUNTID, HSESSION> CHAR_CLIENT_SESSION;
typedef std::map<ACCOUNTID, HSESSION>::iterator CHAR_CLIENT_IT;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////COMMUNITY SERVER/////////////////////////////////////////////////////////////////////////
const DWORD					MAX_NUMOF_COMMUNITY_GAME_CLIENT = 50;
const DWORD					MAX_NUMOF_COMMUNITY_SERVER = 5;
const DWORD					MAX_NUMOF_COMMUNITY_SESSION = MAX_NUMOF_COMMUNITY_GAME_CLIENT + MAX_NUMOF_COMMUNITY_SERVER;
typedef std::map<ACCOUNTID, HSESSION> COMMUNITY_CLIENT_SESSION;
typedef std::map<ACCOUNTID, HSESSION>::iterator COMMUNITY_CLIENT_IT;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////GAME SERVER//////////////////////////////////////////////////////////////////////////////
const DWORD					MAX_NUMOF_GAME_GAME_CLIENT = 50;
const DWORD					MAX_NUMOF_GAME_SERVER = 5;
const DWORD					MAX_NUMOF_GAME_SESSION = MAX_NUMOF_GAME_GAME_CLIENT + MAX_NUMOF_GAME_SERVER;
typedef std::map<CHARACTERID, HSESSION> GAME_CLIENT_SESSION;
typedef std::map<CHARACTERID, HSESSION>::iterator GAME_CLIENT_IT;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////BOT AGENT SERVER/////////////////////////////////////////////////////////////////////////
const DWORD					MAX_NUMOF_BA_GAME_CLIENT = 50;
const DWORD					MAX_NUMOF_BA_SERVER = 5;
const DWORD					MAX_NUMOF_BA_SESSION = MAX_NUMOF_BA_GAME_CLIENT + MAX_NUMOF_BA_SERVER;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////BOT MASTER SERVER////////////////////////////////////////////////////////////////////////
const DWORD					MAX_NUMOF_BM_GAME_CLIENT = 50;
const DWORD					MAX_NUMOF_BM_SERVER = 5;
const DWORD					MAX_NUMOF_BM_SESSION = MAX_NUMOF_BM_GAME_CLIENT + MAX_NUMOF_BM_SERVER;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////NPC SERVER///////////////////////////////////////////////////////////////////////////////
const DWORD					MAX_NUMOF_NPC_GAME_CLIENT = 50;
const DWORD					MAX_NUMOF_NPC_SERVER = 5;
const DWORD					MAX_NUMOF_NPC_SESSION = MAX_NUMOF_NPC_GAME_CLIENT + MAX_NUMOF_NPC_SERVER;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
