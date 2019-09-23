#include <GameServer.h>

#include <WorldRunnable.h>
#include <Game\Maps\MapManager.h>
#include <CliRunnable.h>
#include <World.h>
#include <mysqlconn_wrapper.h>
#include <XmlParser.h>

#include <iostream>
#include <signal.h>

void signalHandler(int signum)
{
	sDB.SetGameServerState(sXmlParser.GetInt("Server", "ID"), sXmlParser.GetInt("Server", "ChannelID"), eDBO_SERVER_STATUS::DBO_SERVER_STATUS_DOWN, 0);
	sql::ResultSet* result = sDB.executes("UPDATE account SET AccountStatus = 0 WHERE AccountStatus = 2;");
	if (result != NULL)
		delete result;
	switch (signum)
	{
		case SIGINT:
		{
			World::StopNow(SHUTDOWN_EXIT_CODE);
			break;
		}
		case SIGTERM:
		{
			World::StopNow(SHUTDOWN_EXIT_CODE);
			break;
		}
		case SIGBREAK:
		{
			World::StopNow(SHUTDOWN_EXIT_CODE);
			break;
		}
	}
	sLog.outDebug("Interrupt signal (%d) received.", signum);
}
bool GameServer::loadDataTable()
{
	sLog.outDetail("==== LOADING GAME TABLES ... ====");

	CNtlBitFlagManager flagManager;
	if (false == flagManager.Create(TableContainer::TABLE_COUNT))
	{
		return false;
	}

	TableFileNameList fileNameList;
	if (false == fileNameList.Create())
	{
		return false;
	}
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////TABLE IST//////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////// 
	/*Loadable Tables*/
	flagManager.Set(TableContainer::TABLE_PC);//Done
	flagManager.Set(TableContainer::TABLE_NEWBIE);//Done
	flagManager.Set(TableContainer::TABLE_SKILL);// 90% done
	flagManager.Set(TableContainer::TABLE_NPC_SPAWN);//done
	flagManager.Set(TableContainer::TABLE_MOB_SPAWN);//Done

	/*Unmodified Tables that load properly*/
	flagManager.Set(TableContainer::TABLE_BASIC_DROP);
	flagManager.Set(TableContainer::TABLE_LEGENDARY_DROP);
	flagManager.Set(TableContainer::TABLE_NORMAL_DROP);
	flagManager.Set(TableContainer::TABLE_SUPERIOR_DROP);
	flagManager.Set(TableContainer::TABLE_EACH_DROP);
	flagManager.Set(TableContainer::TABLE_TYPE_DROP);
	flagManager.Set(TableContainer::TABLE_EXCELLENT_DROP);

	flagManager.Set(TableContainer::TABLE_QUEST_DROP);
	flagManager.Set(TableContainer::TABLE_QUEST_PROBABILITY);
	flagManager.Set(TableContainer::TABLE_QUEST_PROBABILITY2);

	flagManager.Set(TableContainer::TABLE_DIRECTION_LINK);
	flagManager.Set(TableContainer::TABLE_SCRIPT_LINK);

	flagManager.Set(TableContainer::TABLE_VEHICLE);
	flagManager.Set(TableContainer::TABLE_ACTION);
	flagManager.Set(TableContainer::TABLE_HELP);
	flagManager.Set(TableContainer::TABLE_CHARM);
	flagManager.Set(TableContainer::TABLE_MOB_MOVE_PATTERN);
	flagManager.Set(TableContainer::TABLE_CHAT_COMMAND);
	flagManager.Set(TableContainer::TABLE_DOJO);
	flagManager.Set(TableContainer::TABLE_GAME_MANIA_TIME);
	flagManager.Set(TableContainer::TABLE_WORLD_ZONE);
	flagManager.Set(TableContainer::TABLE_MIX_MACHINE);
	flagManager.Set(TableContainer::TABLE_GUIDE_HINT);
	flagManager.Set(TableContainer::TABLE_ITEM_UPGRADE);
	flagManager.Set(TableContainer::TABLE_ITEM_RECIPE);
	flagManager.Set(TableContainer::TABLE_DYNAMIC_OBJECT);
	flagManager.Set(TableContainer::TABLE_CHATTING_FILTER);
	flagManager.Set(TableContainer::TABLE_HTB_SET);
	flagManager.Set(TableContainer::TABLE_SET_ITEM);
	flagManager.Set(TableContainer::TABLE_QUEST_ITEM);
	flagManager.Set(TableContainer::TABLE_TEXT_ALL);

	/*Tables in Progress*/
	flagManager.Set(TableContainer::TABLE_ITEM);
	flagManager.Set(TableContainer::TABLE_DRAGONBALL_REWARD);
	flagManager.Set(TableContainer::TABLE_EXP);
	flagManager.Set(TableContainer::TABLE_PORTAL);
	flagManager.Set(TableContainer::TABLE_USE_ITEM);
	flagManager.Set(TableContainer::TABLE_USE_ITEM2);
	flagManager.Set(TableContainer::TABLE_WORLD);
	flagManager.Set(TableContainer::TABLE_MOB);
	flagManager.Set(TableContainer::TABLE_NPC);
	flagManager.Set(TableContainer::TABLE_DUNGEON);
	flagManager.Set(TableContainer::TABLE_TIMEQUEST);
	flagManager.Set(TableContainer::TABLE_SYSTEM_EFFECT);

	flagManager.Set(TableContainer::TABLE_MERCHANT);	
	flagManager.Set(TableContainer::TABLE_MERCHANT2);

	flagManager.Set(TableContainer::TABLE_CHAR_TITLE);
	/*Unloadable Tables*/
	//flagManager.Set(TableContainer::TABLE_ITEM_OPTION);																								
	//flagManager.Set(TableContainer::TABLE_QUEST_TEXT_DATA);	
	flagManager.Set(TableContainer::TABLE_OBJECT);
	flagManager.Set(TableContainer::TABLE_HLS_ITEM);
	flagManager.Set(TableContainer::TABLE_WORLD_MAP);			
	//flagManager.Set(TableContainer::TABLE_LAND_MARK);									
	//flagManager.Set(TableContainer::TABLE_DRAGONBALL);					
	//flagManager.Set(TableContainer::TABLE_BUDOKAI);		fail	
	//flagManager.Set(TableContainer::TABLE_RANKBATTLE);			
	//flagManager.Set(TableContainer::TABLE_SPEECH);												
	//flagManager.Set(TableContainer::TABLE_FORMULA);	
	flagManager.Set(TableContainer::TABLE_QUEST_REWARD);
	//flagManager.Set(TableContainer::TABLE_QUEST_NARRATION);

	flagManager.Set(TableContainer::TABLE_CASHITEM_TABLE);


	/////////////////////////////////////////////////////////////////////////////////////////////////////////// 
	///////////////////////////////////TABLE LOADLIST//////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////  
	/*Loadable Tables*/
	fileNameList.SetFileName(TableContainer::TABLE_PC,						"Table_PC_Data");//structure Done
	fileNameList.SetFileName(TableContainer::TABLE_NEWBIE,					"Table_Newbie_Data");//structure Done
	fileNameList.SetFileName(TableContainer::TABLE_SKILL,					"Table_Skill_Data");//structure Done
	fileNameList.SetFileName(TableContainer::TABLE_VEHICLE,					"Table_Vehicle_Data");//structure Done
	fileNameList.SetFileName(TableContainer::TABLE_QUEST_REWARD,			"Table_Quest_Reward_Data");//structure Done
	fileNameList.SetFileName(TableContainer::TABLE_ITEM,					"Table_Item_Data");//structure Done
	fileNameList.SetFileName(TableContainer::TABLE_CASHITEM_TABLE,			"o_table_item_data");//structure Done
	fileNameList.SetFileName(TableContainer::TABLE_DRAGONBALL_REWARD,		"Table_DB_Reward_Data");//structure Done
	fileNameList.SetFileName(TableContainer::TABLE_EXP,						"table_exp_data");//structure Done

	/*Unmodified Tables that load properly*/
	fileNameList.SetFileName(TableContainer::TABLE_BASIC_DROP,				"table_basic_drop_data");
	fileNameList.SetFileName(TableContainer::TABLE_NORMAL_DROP,				"table_normal_drop_data");
	fileNameList.SetFileName(TableContainer::TABLE_SUPERIOR_DROP,			"table_superior_drop_data");
	fileNameList.SetFileName(TableContainer::TABLE_EXCELLENT_DROP,			"table_excellent_drop_data");
	fileNameList.SetFileName(TableContainer::TABLE_LEGENDARY_DROP,			"table_legendary_drop_data");
	fileNameList.SetFileName(TableContainer::TABLE_QUEST_DROP,				"table_quest_drop_data");
	fileNameList.SetFileName(TableContainer::TABLE_TYPE_DROP,				"table_type_drop_data");
	fileNameList.SetFileName(TableContainer::TABLE_EACH_DROP,				"table_each_drop_data");

	fileNameList.SetFileName(TableContainer::TABLE_QUEST_PROBABILITY,		"table_quest_probability_data");
	fileNameList.SetFileName(TableContainer::TABLE_QUEST_PROBABILITY2,		"o_table_quest_probability_data");
	fileNameList.SetFileName(TableContainer::TABLE_SCRIPT_LINK,				"Table_Script_Link_Data");
	fileNameList.SetFileName(TableContainer::TABLE_DIRECTION_LINK,			"Table_Direction_Link_Data");

	
	fileNameList.SetFileName(TableContainer::TABLE_ACTION,					"Table_Action_Data");
	fileNameList.SetFileName(TableContainer::TABLE_HELP,					"Table_Help_Data");
	fileNameList.SetFileName(TableContainer::TABLE_CHARM,					"Table_Charm_Data");
	fileNameList.SetFileName(TableContainer::TABLE_MOB_MOVE_PATTERN,		"Table_Mob_Move_Pattern_Data");
	fileNameList.SetFileName(TableContainer::TABLE_CHAT_COMMAND,			"Table_Chat_Command_Data");
	fileNameList.SetFileName(TableContainer::TABLE_DOJO,					"Table_Dojo_Data");
	fileNameList.SetFileName(TableContainer::TABLE_GAME_MANIA_TIME,			"Table_GameManiaTime_Data");
	fileNameList.SetFileName(TableContainer::TABLE_WORLD_ZONE,				"Table_World_Zone_Data");
	fileNameList.SetFileName(TableContainer::TABLE_MIX_MACHINE,				"Table_Item_Mix_Machine_Data");
	fileNameList.SetFileName(TableContainer::TABLE_GUIDE_HINT,				"Table_Guide_Hint_Data");
	fileNameList.SetFileName(TableContainer::TABLE_ITEM_UPGRADE,			"Table_Item_Upgrade_Value");//
	fileNameList.SetFileName(TableContainer::TABLE_ITEM_RECIPE,				"Table_Item_Recipe_Data");
	fileNameList.SetFileName(TableContainer::TABLE_DYNAMIC_OBJECT,			"Table_Dynamic_Object_Data");
	fileNameList.SetFileName(TableContainer::TABLE_CHATTING_FILTER,			"Table_Chatting_Filter_Data");
	fileNameList.SetFileName(TableContainer::TABLE_HTB_SET,					"Table_HTB_Set_Data");
	fileNameList.SetFileName(TableContainer::TABLE_SET_ITEM,				"Table_Set_Item_Data");
	fileNameList.SetFileName(TableContainer::TABLE_QUEST_ITEM,				"Table_Quest_Item_Data");
	fileNameList.SetFileName(TableContainer::TABLE_TEXT_ALL,				"Table_Text_All_Data");
	fileNameList.SetFileName(TableContainer::TABLE_DUNGEON,					"Table_Dungeon_Data");

	/*Tables in progress
	* If tables are here they load but don't have correct structures.
	* Just a correct size.
	*/
	
	
	fileNameList.SetFileName(TableContainer::TABLE_PORTAL,					"Table_Portal_Data");
	fileNameList.SetFileName(TableContainer::TABLE_USE_ITEM,				"Table_Use_Item_Data");
	fileNameList.SetFileName(TableContainer::TABLE_USE_ITEM2,				"o_table_use_item_data");
	fileNameList.SetFileName(TableContainer::TABLE_WORLD,					"Table_World_Data");
	fileNameList.SetFileName(TableContainer::TABLE_MOB,						"Table_MOB_Data");
	fileNameList.SetFileName(TableContainer::TABLE_NPC,						"Table_NPC_Data");
	fileNameList.SetFileName(TableContainer::TABLE_SYSTEM_EFFECT,			"table_system_effect_data");
	fileNameList.SetFileName(TableContainer::TABLE_TIMEQUEST,				"Table_TMQ_Data");
	fileNameList.SetFileName(TableContainer::TABLE_CHAR_TITLE,				"table_chartitle_data");
	
	/*Unloadable Tables*/
	//
	//fileNameList.SetFileName(TableContainer::TABLE_FORMULA,				"TD_Formula");//structure need
	fileNameList.SetFileName(TableContainer::TABLE_WORLD_MAP,				"Table_Worldmap_Data");//structure need
	//fileNameList.SetFileName(TableContainer::TABLE_SPEECH,				"Table_NPC_Speech_Data");//structure need
	//fileNameList.SetFileName(TableContainer::TABLE_ITEM_OPTION,			"Table_Item_Option_Data");	//structure need
	//fileNameList.SetFileName(TableContainer::TABLE_QUEST_TEXT_DATA,		"Table_Quest_Text_Data");//fail
	fileNameList.SetFileName(TableContainer::TABLE_OBJECT,					"Table_Object");//structure need
	//fileNameList.SetFileName(TableContainer::TABLE_LAND_MARK,				"Table_Landmark_Data");/structure need
	//fileNameList.SetFileName(TableContainer::TABLE_BUDOKAI,				"Table_Tenkaichibudokai_Data");//fail
	//fileNameList.SetFileName(TableContainer::TABLE_RANKBATTLE,			"Table_RankBattle_Data");//structure need
	//fileNameList.SetFileName(TableContainer::TABLE_SPEECH,				"Table_NPC_Speech_Data");//structure need
	//fileNameList.SetFileName(TableContainer::TABLE_QUEST_NARRATION,		"Table_Quest_Narration_Data");//structure need	
	//fileNameList.SetFileName(TableContainer::TABLE_DRAGONBALL,			"Table_Dragon_Ball_Data");//structure need

	fileNameList.SetFileName(TableContainer::TABLE_MERCHANT,				"Table_Merchant_Data");
	fileNameList.SetFileName(TableContainer::TABLE_MERCHANT2,				"o_table_merchant_data");
	fileNameList.SetFileName(TableContainer::TABLE_HLS_ITEM,				"table_hls_item_data"); 
	
	/*
	world_tablx
	id	name
	1	DBO_Main_World
	2	DBO_Dungeon_001
	3	DBO_Dungeon_002
	4	DBO_Dungeon_003
	5	DBO_Town_001
	6	DBO_Dungeon_004
	7	DBO_Dungeon_005
	9	DBO_Dungeon_006
	10	DBO_Dungeon_007
	11	DBO_SZone_001
	12	DBO_SZone_002
	13	DBO_Dungeon_ETC
	14	DBO_WZone_001
	15	DBO_Main_World_02
	100	DBO_Budoh_001
	101	DBO_Budoh_001
	102	DBO_Budoh_001
	103	DBO_Budoh_001
	104	DBO_Budoh_001
	200	DBO_Budoh_001
	500	DBO_Dojo_001
	501	DBO_Dojo_001
	502	DBO_Dojo_001
	503	DBO_Dojo_001
	504	DBO_Dojo_001
	505	DBO_Dojo_001
	506	DBO_Dojo_001
	9999	DBO_Start_001
	10000	DBO_Dungeon_000
	11000	DBO_Quest_001
	12000	DBO_Battle_001
	13000	DBO_Battle_001
	28000	DBO_Quest_002
	30000	DBO_Budoh_002
	31000	DBO_Budoh_003
	32000	DBO_Budoh_003
	40000	DBO_Budoh_002
	41000	DBO_Budoh_003
	42000	DBO_Budoh_003
	43000	DBO_Battle_002
	44000	DBO_Battle_002
	45000	DBO_Battle_003
	46000	DBO_Battle_003
	60000	DBO_Quest_001
	70000	DBO_Quest_002
	80000	DBO_Quest_003
	90000	DBO_Dungeon_001
	100000	DBO_Quest_003
	110000	DBO_Dungeon_001
	120000	DBO_TLQ_001
	130000	DBO_Quest_004
	140000	DBO_Quest_004
	150000	DBO_TLQ_001
	160000	DBO_TLQ_001
	170000	DBO_TLQ_002
	180000	DBO_TLQ_002
	190000	DBO_TLQ_002
	191000	DBO_Quest_001
	192000	DBO_Quest_002
	193000	DBO_Quest_003
	195000	DBO_Quest_005
	196000	DBO_Quest_006
	197000	DBO_Quest_007
	198000	DBO_Quest_005
	199000	DBO_Quest_006
	200000	DBO_PDungeon_001
	210000	DBO_DWC_001
	211000	DBO_DWC_001
	212000	DBO_DWC_001
	213000	DBO_DWC_001
	300000	DBO_PDungeon_001
	310000	DBO_PDungeon_001
	400000	DBO_TLQ_003
	410000	DBO_TLQ_003
	420000	DBO_TLQ_003
	430000	DBO_TEST
	500000	DBO_PDungeon_002
	510000	DBO_SKDungeon_001
	511000	DBO_SKDungeon_001
	512000	DBO_SKDungeon_001
	600000	DBO_PDungeon_002
	610000	DBO_PDungeon_002
	700000	DBO_PDungeon_003
	710000	DBO_PDungeon_003
	712000	DBO_PDungeon_004
	713000	DBO_PDungeon_004
	715000	DBO_PDungeon_005
	717000	DBO_PDungeon_006
	800000	DBO_Town_002
	801000	DBO_Town_003
	802000	DBO_Town_003
	803000	DBO_Town_003
	804000	DBO_Town_003
	805000	DBO_Town_003
	806000	DBO_Town_003
	807000	DBO_Town_003
	808000	DBO_Town_003
	809000	DBO_Town_003
	810000	DBO_Town_003
	811000	DBO_Town_003
	812000	DBO_Town_003
	900000	DBO_BDungeon_001
	900020	DBO_BDungeon_002
	900030	DBO_BDungeon_003
	900040	DBO_BDungeon_004
	910000	DBO_CDungeon_001
	*/
	std::string path = sXmlParser.GetStr("GameData", "Path");
	bool bResult = sTBM.Create(flagManager, (char*)path.c_str(), &fileNameList, eLOADING_METHOD::LOADING_METHOD_BINARY, GetACP(), NULL);
	if (bResult != false)
	{
		// If got Problem with Handle Worong Load World Here

		if (sMapMgr.CreateMap(1) == NULL) // create world map
		{
			sLog.outError("Failed to create world map: 1");
			return false;
		}
		if (sMapMgr.CreateMap(15) == NULL) // create world map
		{
			sLog.outError("Failed to create world map: 1");
			return false;
		}
		
		//used to work in Rdf strutures
		MobTable * dat = sTBM.GetMobTable();
		sMOB_TBLDAT * tbldat = reinterpret_cast<sMOB_TBLDAT*>(dat->FindData(1211101));
		if (tbldat)
		{

			printf("bValidity_Able %d \n ", tbldat->bValidity_Able);
			printf("tblidx %d \n ", tbldat->tblidx);
			printf("Name %d \n ", tbldat->Name);
			printf("byLevel %d \n ", tbldat->byLevel);		
			printf("fDrop_Exp_Rate %d \n ", tbldat->fDrop_Exp_Rate);
			printf("fDrop_Zenny_Rate %d \n ", tbldat->fDrop_Zenny_Rate);						
			printf("notknow %f \n ", tbldat->notknow);
					
	//	printf("burnDefense %d \n ", tbldat->NextID);
			
		}
		for (auto it = sTBM.GetWorldMapTable()->Begin(); it != sTBM.GetWorldMapTable()->End(); it++)
		{
			sWORLD_MAP_TBLDAT* tbldat = (sWORLD_MAP_TBLDAT*)it->second;
			if (tbldat)
			{				
				printf("tblidx %d \n ", tbldat->tblidx);			
				//printf("Worldmap_Name %d \n ", tbldat->Worldmap_Name);
				delete tbldat;
			}
		}
	}
	return bResult;
}
bool GameServer::ConnectToDatabase()
{
	std::string user, password, host, db;

	user = sXmlParser.GetStr("MySQL", "User");
	password = sXmlParser.GetStr("MySQL", "Password");
	host = sXmlParser.GetStr("MySQL", "Host");
	db = sXmlParser.GetStr("MySQL", "Database");

	sDB.setInfos(user, password, host, db);
	if (sDB.connect() == false)
		return false;
	sDB.switchDb(db);
	sLog.outDetail("Database connection established.");

	return true;
}
int GameServer::Run()
{
	

	signal(SIGINT, signalHandler);
	signal(SIGABRT, signalHandler);
	signal(SIGFPE, signalHandler);
	signal(SIGILL, signalHandler);
	signal(SIGSEGV, signalHandler);
	signal(SIGTERM, signalHandler);
	signal(SIGBREAK, signalHandler);

	std::cout << blue << "\n\n" << std::endl;
	std::cout << "\t     ____                              ____        _ _ " << std::endl;
	std::cout << "\t    |  _ \\ _ __ __ _  __ _  ___  _ __ | __ )  __ _| | |" << std::endl;
	std::cout << "\t    | | | | '__/ _` |/ _` |/ _ \\| '_ \\|  _ \\ / _` | | |" << std::endl;
	std::cout << "\t    | |_| | | | (_| | (_| | (_) | | | | |_) | (_| | | |" << std::endl;
	std::cout << "\t    |____/|_|  \\__,_|\\__, |\\___/|_| |_|____/ \\__,_|_|_|" << std::endl;
	std::cout << "\t                     |___/                             " << std::endl;
	std::cout << yellow << "\t   	           Baticueva 2019					\n\n" << white << std::endl;
	sLog.outString("Using configuration file 'GameServer.xml'.");
	sLog.outString("Using Boost: %s", BOOST_LIB_VERSION);

	if (sXmlParser.loadFile("GameServer") == false)
		return 1;
	sLog.SetLogLevel((LogLevel)sXmlParser.GetInt("LogLevel", "Value"));
	if (ConnectToDatabase() == false)
	{
		sLog.outError("Database connection failed, exiting...");
		return 1;
	}
	if (loadDataTable() == false)
	{
		sLog.outError("Table data unsucessfully loaded, exiting...");
		system("PAUSE");
		return 1;
	}
	_ServerID = sXmlParser.GetInt("Server", "ID");
	_ChannelID = sXmlParser.GetInt("Server", "ChannelID");
	AKCore::Thread world_thread(new WorldRunnable);
	AKCore::Thread* cliThread = nullptr;

	world_thread.setPriority(AKCore::Priority_Highest);
	sDB.SetGameServerState(_ServerID, _ChannelID, eDBO_SERVER_STATUS::DBO_SERVER_STATUS_UP, 0);
	{
		network = new Listener<GameSocket>(sXmlParser.GetInt("Server", "Port"), sXmlParser.GetInt("ServerWorker", "Value"));
		sLog.outString("GameServer: ServerID: %d, ChannelID: %d:", _ServerID, _ChannelID);
		sLog.outString("Started on port: [%d]", sXmlParser.GetInt("Server", "Port"));
		/// ONCE NETWORK IS DONE, START THE INPUT THREAD
		cliThread = new AKCore::Thread(new CliRunnable);
		while (!World::IsStopped())
		{
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
	}
	// when the main thread closes the singletons get unloaded
	// since worldrunnable uses them, it will crash if unloaded after master
	world_thread.wait();
	///- Clean account database before leaving
	sLog.outError("must do thing with account - character database here");
	//clearOnlineAccounts();
	if (cliThread)
	{
		INPUT_RECORD b[5];
		HANDLE hStdIn = GetStdHandle(STD_INPUT_HANDLE);
		b[0].EventType = KEY_EVENT;
		b[0].Event.KeyEvent.bKeyDown = TRUE;
		b[0].Event.KeyEvent.uChar.AsciiChar = 'X';
		b[0].Event.KeyEvent.wVirtualKeyCode = 'X';
		b[0].Event.KeyEvent.wRepeatCount = 1;

		b[1].EventType = KEY_EVENT;
		b[1].Event.KeyEvent.bKeyDown = FALSE;
		b[1].Event.KeyEvent.uChar.AsciiChar = 'X';
		b[1].Event.KeyEvent.wVirtualKeyCode = 'X';
		b[1].Event.KeyEvent.wRepeatCount = 1;

		b[2].EventType = KEY_EVENT;
		b[2].Event.KeyEvent.bKeyDown = TRUE;
		b[2].Event.KeyEvent.dwControlKeyState = 0;
		b[2].Event.KeyEvent.uChar.AsciiChar = '\r';
		b[2].Event.KeyEvent.wVirtualKeyCode = VK_RETURN;
		b[2].Event.KeyEvent.wRepeatCount = 1;
		b[2].Event.KeyEvent.wVirtualScanCode = 0x1c;

		b[3].EventType = KEY_EVENT;
		b[3].Event.KeyEvent.bKeyDown = FALSE;
		b[3].Event.KeyEvent.dwControlKeyState = 0;
		b[3].Event.KeyEvent.uChar.AsciiChar = '\r';
		b[3].Event.KeyEvent.wVirtualKeyCode = VK_RETURN;
		b[3].Event.KeyEvent.wVirtualScanCode = 0x1c;
		b[3].Event.KeyEvent.wRepeatCount = 1;
		DWORD numb;
		BOOL ret = WriteConsoleInput(hStdIn, b, 4, &numb);

		cliThread->wait();
		delete cliThread;
	}
	delete network;
	sLog.outString("Deleting table...");
	sTBM.Destroy();
	sLog.outString("Halting process...");
	return 0;
}