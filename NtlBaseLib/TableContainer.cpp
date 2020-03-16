#include "stdafx.h"
#include "TableContainer.h"
#include "TableFileNameList.h"

#include "ExpTable.h"
#include "HelpTable.h"
#include "MerchantTable.h"
#include "MerchantTable2.h"
#include "MobTable.h"
#include "NewbieTable.h"
#include "NPCTable.h"
#include "PCTable.h"
#include "StatusTransformTable.h"
#include "GameManiaTimeTable.h"
#include "GuideHintTable.h"

#include "BasicDropTable.h"
#include "ItemOptionTable.h"
#include "ItemTable.h"
#include "NormalDropTable.h"
#include "LegendaryDropTable.h"
#include "SuperiorDropTable.h"
#include "UseItemTable.h"
#include "UseItemTable2.h"
#include "SetItemTable.h"
#include "EachDropTable.h"
#include "TypeDropTable.h"
#include "ExcellentDropTable.h"

#include "DragonBallTable.h"
#include "DragonBallRewardTable.h"

#include "ActionTable.h"
#include "ChatCommandTable.h"
#include "DirectionLinkTable.h"
#include "FormulaTable.h"
#include "ItemEnchantTable.h"

#include "CharmTable.h"

#include "QuestDropTable.h"
#include "QuestItemTable.h"
#include "QuestProbabilityTable.h"
#include "QuestProbabilityTable2.h"
#include "QuestTextDataTable.h"
#include "QuestRewardTable.h"
#include "QuestRewardSelectTable.h"

#include "HTBSetTable.h"
#include "SkillTable.h"
#include "SystemEffectTable.h"

#include "TextAllTable.h"
#include "ChattingFilterTable.h"
#include "TextServerTable.h"

#include "ObjectTable.h"
#include "SpawnTable.h"
#include "WorldTable.h"
#include "WorldZoneTable.h"
#include "WorldMapTable.h"
#include "LandMarkTable.h"
#include "WorldPathTable.h"
#include "WorldPlayTable.h"
#include "PortalTable.h"
#include "NpcSpeechTable.h"

#include "TimeQuestTable.h"
#include "RankBattleTable.h"
#include "BudokaiTable.h"
#include "ScriptLinkTable.h"
#include "DungeonTable.h"

#include "QuestNarrationTable.h"

#include "VehicleTable.h"

#include "ItemRecipeTable.h"
#include "ItemRecipeTable2.h"

#include "DynamicObjectTable.h"
#include "MobMovePatternTable.h"

#include "DojoTable.h"
#include "ItemUpgradeTable.h"
#include "ItemMixMachineTable.h"

#include "HLSItemTable.h"
#include "HLSMerchantTable.h"
#include "CharTitleTable.h"
#include "CashItemTable.h"
#include "FileSerializer.h"
#include "NtlStringHandler.h"
#include "NtlBitFlagManager.h"

#include <Logger.h>

#define DBO_CREATE_TABLE(table_class_name, serializer, file_name_without_extension, table_pointer_variable, table_call_back)		\
		{																											\
		if (NULL != table_pointer_variable)																		\
				{																										\
			Table::CallErrorCallbackFunction("The table is already created.(Table : %s)", #table_class_name);	\
			delete table_pointer_variable;																		\
				}																										\
		table_class_name* pTable = new table_class_name;														\
		if (NULL == pTable)																						\
				{																										\
			Table::CallErrorCallbackFunction("new operation failed.(Table : %s)", #table_class_name);			\
			sLog.outError("new operation failed.(Table : %s)", #table_class_name);								\
			Destroy();																							\
			return false;																						\
				}																										\
		if (false == pTable->Create(m_dwCodePage))																\
				{																										\
			Table::CallErrorCallbackFunction("%s::Create() failed.(Table : %s)", #table_class_name);			\
			delete pTable;																						\
																												\
			sLog.outError("%s::Create() failed.(Table : %s)", #table_class_name);								\
			Destroy();																							\
			return false;																						\
				}																										\
		if (NULL == table_call_back)																			\
				{																										\
			if (false == InitializeTable(pTable, serializer, file_name_without_extension, table_call_back))		\
						{																									\
				Table::CallErrorCallbackFunction("InitializeTable() failed.(Table : %s)", #table_class_name);	\
				delete pTable;																					\
																												\
				sLog.outError("InitializeTable() failed.(Table : %s) false == InitializeTable", #table_class_name);								\
				Destroy();																						\
				return false;																					\
						}																									\
				}																										\
				else																									\
				{																										\
			if (false == InitializePackTable(pTable, serializer, file_name_without_extension, table_call_back))	\
						{																									\
				Table::CallErrorCallbackFunction("InitializeTable() failed.(Table : %s)", #table_class_name);	\
				delete pTable;																					\
																												\
				sLog.outError("InitializeTable() failed.(Table : %s) false == InitializePackTable", #table_class_name);								\
				Destroy();																						\
				return false;																					\
						}																									\
				}																										\
		table_pointer_variable = pTable;																		\
		}																											\

#define DBO_RELOAD_TABLE(table_class_name, serializer, file_name_without_extension, table_pointer_variable)		\
		{																											\
		if (NULL == table_pointer_variable)																		\
				{																										\
			Table::CallErrorCallbackFunction("The table is not created.(Table : %s)", #table_class_name);		\
			return false;																						\
				}																										\
		if ( false == ReloadTable( table_pointer_variable, serializer, file_name_without_extension ) )			\
				{																										\
			Table::CallErrorCallbackFunction("%s::ReloadTable() failed.(Table : %s)", #table_class_name);		\
			return false;																						\
				}																										\
		}

#define DBO_CREATE_AND_REGISTER_TABLE(table_class_name, serializer, file_name_without_extension, table_map, tblidx, table_call_back)		\
		{																													\
		table_class_name* pNewTable = NULL;																				\
		DBO_CREATE_TABLE(table_class_name, serializer, file_name_without_extension, pNewTable, table_call_back);							\
																														\
		if (false == table_map.insert(std::pair<TBLIDX, table_class_name*>(tblidx, pNewTable)).second)					\
				{																												\
			_ASSERTE( !"table_map.insert Fail");																		\
			delete pNewTable;																							\
																														\
			Destroy();																									\
			return false;																								\
				}																												\
		}

#define DBO_EXPORT_TABLE(table_object_pointer, serializer, file_name_without_extension, need_to_encrypt)		\
		{																											\
		serializer.Refresh();																					\
																												\
		std::wstring wstrFullPath;																				\
																												\
		wstrFullPath = m_wstrPath;																				\
		wstrFullPath += L"\\";																					\
		wstrFullPath += file_name_without_extension;															\
		if (false == need_to_encrypt)																			\
				{																										\
			wstrFullPath += L".rdf";																			\
																												\
			table_object_pointer->SaveToBinary(serializer);														\
																												\
			serializer.SaveFile((WCHAR*)(wstrFullPath.c_str()), false);											\
				}																										\
				else																									\
				{																										\
			wstrFullPath += L".edf";																			\
																												\
			FileSerializer dataSerializer;																	\
			table_object_pointer->SaveToBinary(dataSerializer);													\
																												\
			int nDataSize = dataSerializer.GetDataSize();														\
			serializer << nDataSize;																			\
			serializer.In(dataSerializer.GetData(), nDataSize);													\
																												\
			serializer.SaveFile((WCHAR*)(wstrFullPath.c_str()), true, L"KEY_FOR_GAME_DATA_TABLE");				\
				}																										\
		}

#define DBO_EXPORT_REGISTERED_TABLE(table_class_name, serializer, file_name_without_extension, need_to_encrypt, table_map, tblidx)		\
		{																																	\
		std::map<TBLIDX, table_class_name*>::iterator iter;																				\
		iter = table_map.find(tblidx);																									\
																																		\
		if (table_map.end() != iter)																									\
				{																																\
			table_class_name* pTable = iter->second;																					\
			if (NULL != pTable)																											\
						{																															\
				DBO_EXPORT_TABLE(pTable, serializer, file_name_without_extension, need_to_encrypt);										\
						}																															\
				}																																\
		}

TableContainer::TableContainer()
{
	Init();
}

TableContainer::~TableContainer()
{
	Destroy();
}

void TableContainer::Init()
{
	m_pExpTable = NULL;
	m_pHelpTable = NULL;
	m_pMerchantTable = NULL;
	m_pMerchantTable2 = NULL;
	m_pMobTable = NULL;
	m_pNewbieTable = NULL;
	m_pNpcTable = NULL;
	m_pPcTable = NULL;
	m_pStatusTransformTable = NULL;
	m_pGameManiaTimeTable = NULL;
	m_pGuideHintTable = NULL;

	m_pBasicDropTable = NULL;
	m_pItemOptionTable = NULL;
	m_pItemTable = NULL;

	m_pNormalDropTable = NULL;
	m_pLegendaryDropTable = NULL;
	m_pSuperiorDropTable = NULL;
	m_pUseItemTable = NULL;
	m_pUseItemTable2 = NULL;
	m_pSetItemTable = NULL;

	m_pDragonBallTable = NULL;
	m_pDragonBallRewardTable = NULL;

	m_pActionTable = NULL;
	m_pChatCommandTable = NULL;
	m_pDirectionLinkTable = NULL;
	m_pFormulaTable = NULL;

	m_pCharmTable = NULL;

	m_pQuestDropTable = NULL;
	m_pQuestItemTable = NULL;
	m_pQuestProbalityTable = NULL;
	m_pQuestProbalityTable2 = NULL;
	m_pQuestTextDataTable = NULL;
	m_pQuestRewardTable = NULL;
	m_pQuestRewardSelectTable = NULL;

	m_pHTBSetTable = NULL;
	m_pSkillTable = NULL;
	m_pSystemEffectTable = NULL;

	m_pTextAllTable = NULL;
	m_pChattingFilterTable = NULL;
	m_pTextServerTable = NULL;

	m_mapObjectTable.clear();
	m_mapNpcSpawnTable.clear();
	m_mapMobSpawnTable.clear();
	m_pWorldTable = NULL;
	m_pWorldZoneTable = NULL;
	m_pWorldPlayTable = NULL;

	m_pWorldMapTable = NULL;
	m_pLandMarkTable = NULL;

	m_pTimeQuestTable = NULL;
	m_pRankBattleTable = NULL;
	m_pBudokaiTable = NULL;

	m_pWorldPathTable = NULL;

	m_pPortalTable = NULL;

	m_pNpcSpeechTable = NULL;

	m_pEachDropTable = NULL;
	m_pTypeDropTable = NULL;

	m_pScriptLinkTable = NULL;
	m_pExcellentDropTable = NULL;
	m_pDungeonTable = NULL;

	m_pQuestNarrationTable = NULL;

	m_pVehicleTable = NULL;

	m_pItemRecipeTable = NULL;
	m_pItemRecipeTable2 = NULL;

	m_pDynamicObjectTable = NULL;

	m_pMobMovePatternTable = NULL;

	m_pDojoTable = NULL;

	m_pItemUpgradeTable = NULL;

	m_pItemMixMachineTable = NULL;

	m_pHLSItemTable = NULL;
	m_pHLSMerchantTable = NULL;
	m_pCharmTable = NULL;
	m_pCharTitleTable = NULL;
	m_pCashItemTable = NULL;

}

bool TableContainer::Create(CNtlBitFlagManager& rTableFlag, char* pszPath, TableFileNameList* pFileNameList, eLOADING_METHOD eLoadingMethod, DWORD dwCodePage, ICallBack* pCall)
{
	WCHAR* pwszPath = MB2WC(pszPath);
	if (NULL == pwszPath)
	{
		return false;
	}

	bool bResult = Create(rTableFlag, pwszPath, pFileNameList, eLoadingMethod, dwCodePage, pCall);

	CleanUpHeapStringW(pwszPath);

	return bResult;
}

void TableContainer::SetPath(char* pszPath)
{
	WCHAR* pwszPath = MB2WC(pszPath);
	if (NULL == pwszPath)
	{
		return;
	}
	SetPath(pwszPath);
	CleanUpHeapStringW(pwszPath);
}

bool TableContainer::Create(CNtlBitFlagManager& rTableFlag, WCHAR* pwszPath, TableFileNameList* pFileNameList, eLOADING_METHOD eLoadingMethod, DWORD dwCodePage, ICallBack* pCall)
{
	m_wstrPath = pwszPath;
	m_eLoadingMethod = eLoadingMethod;
	m_dwCodePage = dwCodePage;

	FileSerializer serializer;

	//--------------------------------------------------------------------------------
	// Character
	//--------------------------------------------------------------------------------
	if (false != rTableFlag.IsSet(TABLE_EXP))
	{
		DBO_CREATE_TABLE(ExpTable, serializer, pFileNameList->GetFileNameW(TABLE_EXP), m_pExpTable, pCall);
	}
	if (false != rTableFlag.IsSet(TABLE_HELP))
	{
		DBO_CREATE_TABLE(HelpTable, serializer, pFileNameList->GetFileNameW(TABLE_HELP), m_pHelpTable, pCall);
	}
	if (false != rTableFlag.IsSet(TABLE_MERCHANT))
	{
		DBO_CREATE_TABLE(MerchantTable, serializer, pFileNameList->GetFileNameW(TABLE_MERCHANT), m_pMerchantTable, pCall);
	}
	if (false != rTableFlag.IsSet(TABLE_MERCHANT2))
	{
		DBO_CREATE_TABLE(MerchantTable2, serializer, pFileNameList->GetFileNameW(TABLE_MERCHANT2), m_pMerchantTable2, pCall);
	}
	if (false != rTableFlag.IsSet(TABLE_MOB))
	{
		DBO_CREATE_TABLE(MobTable, serializer, pFileNameList->GetFileNameW(TABLE_MOB), m_pMobTable, pCall);
	}
	if (false != rTableFlag.IsSet(TABLE_NEWBIE))
	{
		DBO_CREATE_TABLE(NewbieTable, serializer, pFileNameList->GetFileNameW(TABLE_NEWBIE), m_pNewbieTable, pCall);
	}
	if (false != rTableFlag.IsSet(TABLE_NPC))
	{
		DBO_CREATE_TABLE(NPCTable, serializer, pFileNameList->GetFileNameW(TABLE_NPC), m_pNpcTable, pCall);
	}
	if (false != rTableFlag.IsSet(TABLE_PC))
	{
		DBO_CREATE_TABLE(PCTable, serializer, pFileNameList->GetFileNameW(TABLE_PC), m_pPcTable, pCall);
	}
	if (false != rTableFlag.IsSet(TABLE_STATUS_TRANSFORM))
	{
		DBO_CREATE_TABLE(StatusTransformTable, serializer, pFileNameList->GetFileNameW(TABLE_STATUS_TRANSFORM), m_pStatusTransformTable, pCall);
	}
	if (false != rTableFlag.IsSet(TABLE_GAME_MANIA_TIME))
	{
		DBO_CREATE_TABLE(GameManiaTimeTable, serializer, pFileNameList->GetFileNameW(TABLE_GAME_MANIA_TIME), m_pGameManiaTimeTable, pCall);
	}
	if (false != rTableFlag.IsSet(TABLE_GUIDE_HINT))
	{
		DBO_CREATE_TABLE(GuideHintTable, serializer, pFileNameList->GetFileNameW(TABLE_GUIDE_HINT), m_pGuideHintTable, pCall);
	}
	//--------------------------------------------------------------------------------

	//--------------------------------------------------------------------------------
	// Item
	//--------------------------------------------------------------------------------
	if (false != rTableFlag.IsSet(TABLE_BASIC_DROP))
	{
		DBO_CREATE_TABLE(BasicDropTable, serializer, pFileNameList->GetFileNameW(TABLE_BASIC_DROP), m_pBasicDropTable, pCall);
	}
	if (false != rTableFlag.IsSet(TABLE_ITEM_OPTION))
	{
		DBO_CREATE_TABLE(ItemOptionTable, serializer, pFileNameList->GetFileNameW(TABLE_ITEM_OPTION), m_pItemOptionTable, pCall);
	}
	if (false != rTableFlag.IsSet(TABLE_ITEM))
	{
		DBO_CREATE_TABLE(ItemTable, serializer, pFileNameList->GetFileNameW(TABLE_ITEM), m_pItemTable, pCall);
	}
	if (false != rTableFlag.IsSet(TABLE_NORMAL_DROP))
	{
		DBO_CREATE_TABLE(NormalDropTable, serializer, pFileNameList->GetFileNameW(TABLE_NORMAL_DROP), m_pNormalDropTable, pCall);
	}
	if (false != rTableFlag.IsSet(TABLE_LEGENDARY_DROP))
	{
		DBO_CREATE_TABLE(LegendaryDropTable, serializer, pFileNameList->GetFileNameW(TABLE_LEGENDARY_DROP), m_pLegendaryDropTable, pCall);
	}
	if (false != rTableFlag.IsSet(TABLE_SUPERIOR_DROP))
	{
		DBO_CREATE_TABLE(SuperiorDropTable, serializer, pFileNameList->GetFileNameW(TABLE_SUPERIOR_DROP), m_pSuperiorDropTable, pCall);
	}
	if (false != rTableFlag.IsSet(TABLE_EACH_DROP))
	{
		DBO_CREATE_TABLE(EachDropTable, serializer, pFileNameList->GetFileNameW(TABLE_EACH_DROP), m_pEachDropTable, pCall);
	}
	if (false != rTableFlag.IsSet(TABLE_TYPE_DROP))
	{
		DBO_CREATE_TABLE(TypeDropTable, serializer, pFileNameList->GetFileNameW(TABLE_TYPE_DROP), m_pTypeDropTable, pCall);
	}
	if (false != rTableFlag.IsSet(TABLE_USE_ITEM))
	{
		DBO_CREATE_TABLE(UseItemTable, serializer, pFileNameList->GetFileNameW(TABLE_USE_ITEM), m_pUseItemTable, pCall);
	}
	if (false != rTableFlag.IsSet(TABLE_USE_ITEM2))
	{
		DBO_CREATE_TABLE(UseItemTable2, serializer, pFileNameList->GetFileNameW(TABLE_USE_ITEM2), m_pUseItemTable2, pCall);
	}
	if (false != rTableFlag.IsSet(TABLE_SET_ITEM))
	{
		DBO_CREATE_TABLE(SetItemTable, serializer, pFileNameList->GetFileNameW(TABLE_SET_ITEM), m_pSetItemTable, pCall);
	}
	if (false != rTableFlag.IsSet(TABLE_DRAGONBALL))
	{
		DBO_CREATE_TABLE(DragonBallTable, serializer, pFileNameList->GetFileNameW(TABLE_DRAGONBALL), m_pDragonBallTable, pCall);
	}
	if (false != rTableFlag.IsSet(TABLE_DRAGONBALL_REWARD))
	{
		DBO_CREATE_TABLE(DragonBallRewardTable, serializer, pFileNameList->GetFileNameW(TABLE_DRAGONBALL_REWARD), m_pDragonBallRewardTable, pCall);
	}
	if (false != rTableFlag.IsSet(TABLE_EXCELLENT_DROP))
	{
		DBO_CREATE_TABLE(ExcellentDropTable, serializer, pFileNameList->GetFileNameW(TABLE_EXCELLENT_DROP), m_pExcellentDropTable, pCall);
	}
	//--------------------------------------------------------------------------------

	//--------------------------------------------------------------------------------
	// Misc
	//--------------------------------------------------------------------------------
	if (false != rTableFlag.IsSet(TABLE_ACTION))
	{
		DBO_CREATE_TABLE(ActionTable, serializer, pFileNameList->GetFileNameW(TABLE_ACTION), m_pActionTable, pCall);
	}
	if (false != rTableFlag.IsSet(TABLE_CHAT_COMMAND))
	{
		DBO_CREATE_TABLE(ChatCommandTable, serializer, pFileNameList->GetFileNameW(TABLE_CHAT_COMMAND), m_pChatCommandTable, pCall);
	}
	if (false != rTableFlag.IsSet(TABLE_DIRECTION_LINK))
	{
		DBO_CREATE_TABLE(DirectionLinkTable, serializer, pFileNameList->GetFileNameW(TABLE_DIRECTION_LINK), m_pDirectionLinkTable, pCall);
	}
	if (false != rTableFlag.IsSet(TABLE_FORMULA))
	{
		DBO_CREATE_TABLE(FormulaTable, serializer, pFileNameList->GetFileNameW(TABLE_FORMULA), m_pFormulaTable, pCall);
	}
	if (false != rTableFlag.IsSet(TABLE_ITEM_ENCHANT))
	{
		DBO_CREATE_TABLE(ItemEnchantTable, serializer, pFileNameList->GetFileNameW(TABLE_ITEM_ENCHANT), m_pItemEnchantTable, pCall);
	}
	//--------------------------------------------------------------------------------

	//--------------------------------------------------------------------------------
	// Party
	//--------------------------------------------------------------------------------
	if (false != rTableFlag.IsSet(TABLE_CHARM))
	{
		DBO_CREATE_TABLE(CharmTable, serializer, pFileNameList->GetFileNameW(TABLE_CHARM), m_pCharmTable, pCall);
	}
	//--------------------------------------------------------------------------------

	//--------------------------------------------------------------------------------
	// Quest
	//--------------------------------------------------------------------------------
	if (false != rTableFlag.IsSet(TABLE_QUEST_DROP))
	{
		DBO_CREATE_TABLE(QuestDropTable, serializer, pFileNameList->GetFileNameW(TABLE_QUEST_DROP), m_pQuestDropTable, pCall);
	}
	if (false != rTableFlag.IsSet(TABLE_QUEST_ITEM))
	{
		DBO_CREATE_TABLE(QuestItemTable, serializer, pFileNameList->GetFileNameW(TABLE_QUEST_ITEM), m_pQuestItemTable, pCall);
	}
	if (false != rTableFlag.IsSet(TABLE_QUEST_PROBABILITY))
	{
		DBO_CREATE_TABLE(QuestProbabilityTable, serializer, pFileNameList->GetFileNameW(TABLE_QUEST_PROBABILITY), m_pQuestProbalityTable, pCall);
	}
	if (false != rTableFlag.IsSet(TABLE_QUEST_PROBABILITY2))
	{
		DBO_CREATE_TABLE(QuestProbabilityTable2, serializer, pFileNameList->GetFileNameW(TABLE_QUEST_PROBABILITY2), m_pQuestProbalityTable2, pCall);
	}
	if (false != rTableFlag.IsSet(TABLE_QUEST_TEXT_DATA))
	{
		DBO_CREATE_TABLE(QuestTextDataTable, serializer, pFileNameList->GetFileNameW(TABLE_QUEST_TEXT_DATA), m_pQuestTextDataTable, pCall);
	}
	if (false != rTableFlag.IsSet(TABLE_QUEST_REWARD))
	{
		DBO_CREATE_TABLE(QuestRewardTable, serializer, pFileNameList->GetFileNameW(TABLE_QUEST_REWARD), m_pQuestRewardTable, pCall);
	}
	if (false != rTableFlag.IsSet(TABLE_QUEST_REWARD_SELECT))
	{
		DBO_CREATE_TABLE(QuestRewardSelectTable, serializer, pFileNameList->GetFileNameW(TABLE_QUEST_REWARD_SELECT), m_pQuestRewardSelectTable, pCall);
	}
	//--------------------------------------------------------------------------------

	//--------------------------------------------------------------------------------
	// Skill
	//--------------------------------------------------------------------------------
	if (false != rTableFlag.IsSet(TABLE_HTB_SET))
	{
		DBO_CREATE_TABLE(HTBSetTable, serializer, pFileNameList->GetFileNameW(TABLE_HTB_SET), m_pHTBSetTable, pCall);
	}
	if (false != rTableFlag.IsSet(TABLE_SKILL))
	{
		DBO_CREATE_TABLE(SkillTable, serializer, pFileNameList->GetFileNameW(TABLE_SKILL), m_pSkillTable, pCall);
		if (m_pSkillTable == NULL)
			sLog.outError("Error loading: m_pSkillTable");
	}
	if (false != rTableFlag.IsSet(TABLE_SYSTEM_EFFECT))
	{
		DBO_CREATE_TABLE(SystemEffectTable, serializer, pFileNameList->GetFileNameW(TABLE_SYSTEM_EFFECT), m_pSystemEffectTable, pCall);
	}
	//--------------------------------------------------------------------------------

	//--------------------------------------------------------------------------------
	// Text
	//--------------------------------------------------------------------------------
	if (false != rTableFlag.IsSet(TABLE_TEXT_ALL))
	{
		DBO_CREATE_TABLE(TextAllTable, serializer, pFileNameList->GetFileNameW(TABLE_TEXT_ALL), m_pTextAllTable, pCall);
	}
	if (false != rTableFlag.IsSet(TABLE_CHATTING_FILTER))
	{
		DBO_CREATE_TABLE(ChattingFilterTable, serializer, pFileNameList->GetFileNameW(TABLE_CHATTING_FILTER), m_pChattingFilterTable, pCall);
	}
	if (false != rTableFlag.IsSet(TABLE_TEXT_SERVER))
	{
		DBO_CREATE_TABLE(TextServerTable, serializer, pFileNameList->GetFileNameW(TABLE_TEXT_SERVER), m_pTextServerTable, pCall);
	}
	//--------------------------------------------------------------------------------

	//--------------------------------------------------------------------------------
	// World
	//--------------------------------------------------------------------------------
	if (false != rTableFlag.IsSet(TABLE_WORLD))
	{
		DBO_CREATE_TABLE(WorldTable, serializer, pFileNameList->GetFileNameW(TABLE_WORLD), m_pWorldTable, pCall);
	}
	if (false != rTableFlag.IsSet(TABLE_WORLD_ZONE))
	{
		DBO_CREATE_TABLE(WorldZoneTable, serializer, pFileNameList->GetFileNameW(TABLE_WORLD_ZONE), m_pWorldZoneTable, pCall);
	}
	if (false != rTableFlag.IsSet(TABLE_WORLD_PLAY))
	{
		DBO_CREATE_TABLE(WorldPlayTable, serializer, pFileNameList->GetFileNameW(TABLE_WORLD_PLAY), m_pWorldPlayTable, pCall);
	}
	if (false != rTableFlag.IsSet(TABLE_OBJECT))
	{
		for (Table::TABLEIT iter = m_pWorldTable->Begin(); m_pWorldTable->End() != iter; iter++)
		{
			sWORLD_TBLDAT* pWorldTableData = (sWORLD_TBLDAT*)(iter->second);

			DBO_CREATE_AND_REGISTER_TABLE(ObjectTable, serializer, pWorldTableData->wszObjSpawn_Table_Name, m_mapObjectTable, pWorldTableData->tblidx, pCall);
		}
	}
	if (false != rTableFlag.IsSet(TABLE_NPC_SPAWN))
	{
		for (Table::TABLEIT iter = m_pWorldTable->Begin(); m_pWorldTable->End() != iter; iter++)
		{
			sWORLD_TBLDAT* pWorldTableData = (sWORLD_TBLDAT*)(iter->second);

			DBO_CREATE_AND_REGISTER_TABLE(SpawnTable, serializer, pWorldTableData->wszNpcSpawn_Table_Name, m_mapNpcSpawnTable, pWorldTableData->tblidx, pCall);
		}
	}
	if (false != rTableFlag.IsSet(TABLE_MOB_SPAWN))
	{
		for (Table::TABLEIT iter = m_pWorldTable->Begin(); m_pWorldTable->End() != iter; iter++)
		{
			sWORLD_TBLDAT* pWorldTableData = (sWORLD_TBLDAT*)(iter->second);

			DBO_CREATE_AND_REGISTER_TABLE(SpawnTable, serializer, pWorldTableData->wszMobSpawn_Table_Name, m_mapMobSpawnTable, pWorldTableData->tblidx, pCall);
		}
	}
	if (false != rTableFlag.IsSet(TABLE_WORLD_MAP))
	{
		DBO_CREATE_TABLE(WorldMapTable, serializer, pFileNameList->GetFileNameW(TABLE_WORLD_MAP), m_pWorldMapTable, pCall);
	}
	if (false != rTableFlag.IsSet(TABLE_LAND_MARK))
	{
		DBO_CREATE_TABLE(LandMarkTable, serializer, pFileNameList->GetFileNameW(TABLE_LAND_MARK), m_pLandMarkTable, pCall);
	}

	//--------------------------------------------------------------------------------
	// 
	//--------------------------------------------------------------------------------
	if (false != rTableFlag.IsSet(TABLE_TIMEQUEST))
	{
		DBO_CREATE_TABLE(TimeQuestTable, serializer, pFileNameList->GetFileNameW(TABLE_TIMEQUEST), m_pTimeQuestTable, pCall);
	}

	if (false != rTableFlag.IsSet(TABLE_RANKBATTLE))
	{
		DBO_CREATE_TABLE(RankBattleTable, serializer, pFileNameList->GetFileNameW(TABLE_RANKBATTLE), m_pRankBattleTable, pCall);
	}

	if (false != rTableFlag.IsSet(TABLE_BUDOKAI))
	{
		DBO_CREATE_TABLE(BudokaiTable, serializer, pFileNameList->GetFileNameW(TABLE_BUDOKAI), m_pBudokaiTable, pCall);
	}

	if (false != rTableFlag.IsSet(TABLE_PASS_POINT))
	{
		if (NULL == m_pWorldTable)
		{
			Destroy();
			return false;
		}

		WorldPathTable * pTable = new WorldPathTable;
		if (NULL == pTable)
		{
			Destroy();
			return false;
		}

		if (false == pTable->Create(pFileNameList->GetFileName(TABLE_PASS_POINT)))
		{
			delete pTable;
			pTable = NULL;

			Destroy();
			return false;
		}


		for (Table::TABLEIT iter = m_pWorldTable->Begin(); m_pWorldTable->End() != iter; iter++)
		{
			sWORLD_TBLDAT * pWorldTableData = (sWORLD_TBLDAT*)(iter->second);

			if (false == pTable->CreateWorldPath(pWorldTableData->tblidx, pWorldTableData->szName))
			{
				//delete pTable;
				//pTable = NULL;

				//Destroy();
				//return false;
			}
		}

		m_pWorldPathTable = pTable;
	}

	//--------------------------------------------------------------------------------

	if (false != rTableFlag.IsSet(TABLE_PORTAL))
	{
		DBO_CREATE_TABLE(PortalTable, serializer, pFileNameList->GetFileNameW(TABLE_PORTAL), m_pPortalTable, pCall);
	}

	if (false != rTableFlag.IsSet(TABLE_SPEECH))
	{
		DBO_CREATE_TABLE(NpcSpeechTable, serializer, pFileNameList->GetFileNameW(TABLE_SPEECH), m_pNpcSpeechTable, pCall);
	}

	if (false != rTableFlag.IsSet(TABLE_SCRIPT_LINK))
	{
		DBO_CREATE_TABLE(ScriptLinkTable, serializer, pFileNameList->GetFileNameW(TABLE_SCRIPT_LINK), m_pScriptLinkTable, pCall);
	}

	if (false != rTableFlag.IsSet(TABLE_DUNGEON))
	{
		DBO_CREATE_TABLE(DungeonTable, serializer, pFileNameList->GetFileNameW(TABLE_DUNGEON), m_pDungeonTable, pCall);
	}

	if (false != rTableFlag.IsSet(TABLE_QUEST_NARRATION))
	{
		DBO_CREATE_TABLE(QuestNarrationTable, serializer, pFileNameList->GetFileNameW(TABLE_QUEST_NARRATION), m_pQuestNarrationTable, pCall);
	}

	if (false != rTableFlag.IsSet(TABLE_VEHICLE))
	{
		DBO_CREATE_TABLE(VehicleTable, serializer, pFileNameList->GetFileNameW(TABLE_VEHICLE), m_pVehicleTable, pCall);
	}

	if (false != rTableFlag.IsSet(TABLE_ITEM_RECIPE))
	{
		DBO_CREATE_TABLE(ItemRecipeTable, serializer, pFileNameList->GetFileNameW(TABLE_ITEM_RECIPE), m_pItemRecipeTable, pCall);
	}
	if (false != rTableFlag.IsSet(TABLE_ITEM_RECIPE2))
	{
		DBO_CREATE_TABLE(ItemRecipeTable2, serializer, pFileNameList->GetFileNameW(TABLE_ITEM_RECIPE2), m_pItemRecipeTable2, pCall);
	}
	if (false != rTableFlag.IsSet(TABLE_DYNAMIC_OBJECT))
	{
		DBO_CREATE_TABLE(DynamicObjectTable, serializer, pFileNameList->GetFileNameW(TABLE_DYNAMIC_OBJECT), m_pDynamicObjectTable, pCall);
	}

	if (false != rTableFlag.IsSet(TABLE_MOB_MOVE_PATTERN))
	{
		DBO_CREATE_TABLE(MobMovePatternTable, serializer, pFileNameList->GetFileNameW(TABLE_MOB_MOVE_PATTERN), m_pMobMovePatternTable, pCall);
	}

	if (false != rTableFlag.IsSet(TABLE_DOJO))
	{
		DBO_CREATE_TABLE(DojoTable, serializer, pFileNameList->GetFileNameW(TABLE_DOJO), m_pDojoTable, pCall);
	}

	if (false != rTableFlag.IsSet(TABLE_ITEM_UPGRADE))
	{
		DBO_CREATE_TABLE(ItemUpgradeTable, serializer, pFileNameList->GetFileNameW(TABLE_ITEM_UPGRADE), m_pItemUpgradeTable, pCall);
	}

	if (false != rTableFlag.IsSet(TABLE_MIX_MACHINE))
	{
		DBO_CREATE_TABLE(ItemMixMachineTable, serializer, pFileNameList->GetFileNameW(TABLE_MIX_MACHINE), m_pItemMixMachineTable, pCall);
	}

	if (false != rTableFlag.IsSet(TABLE_HLS_MERCHANT))
	{
		DBO_CREATE_TABLE(HLSMerchantTable, serializer, pFileNameList->GetFileNameW(TABLE_HLS_MERCHANT), m_pHLSMerchantTable, pCall);
	}

	if (false != rTableFlag.IsSet(TABLE_HLS_ITEM))
	{
		DBO_CREATE_TABLE(HLSItemTable, serializer, pFileNameList->GetFileNameW(TABLE_HLS_ITEM), m_pHLSItemTable, pCall);
	}
	if (false != rTableFlag.IsSet(TABLE_CHAR_TITLE))
	{
		DBO_CREATE_TABLE(CharTitleTable, serializer, pFileNameList->GetFileNameW(TABLE_CHAR_TITLE), m_pCharTitleTable, pCall);
	}
	if (false != rTableFlag.IsSet(TABLE_CASHITEM_TABLE))
	{
		DBO_CREATE_TABLE(CashItemTable, serializer, pFileNameList->GetFileNameW(TABLE_CASHITEM_TABLE), m_pCashItemTable, pCall);
	}

	return true;
}

void TableContainer::Destroy()
{
	m_wstrPath.clear();
	m_eLoadingMethod = LOADING_METHOD_INVALID;
	m_dwCodePage = 0;

	//--------------------------------------------------------------------------------
	// Character
	//--------------------------------------------------------------------------------
	if (NULL != m_pExpTable)
	{
		delete m_pExpTable;
		m_pExpTable = NULL;
	}
	if (NULL != m_pHelpTable)
	{
		delete m_pHelpTable;
		m_pHelpTable = NULL;
	}
	if (NULL != m_pMerchantTable)
	{
		delete m_pMerchantTable;
		m_pMerchantTable = NULL;
	}
	if (NULL != m_pMerchantTable2)
	{
		delete m_pMerchantTable2;
		m_pMerchantTable2 = NULL;
	}
	if (NULL != m_pMobTable)
	{
		delete m_pMobTable;
		m_pMobTable = NULL;
	}
	if (NULL != m_pNewbieTable)
	{
		delete m_pNewbieTable;
		m_pNewbieTable = NULL;
	}
	if (NULL != m_pNpcTable)
	{
		delete m_pNpcTable;
		m_pNpcTable = NULL;
	}
	if (NULL != m_pPcTable)
	{
		delete m_pPcTable;
		m_pPcTable = NULL;
	}
	if (NULL != m_pStatusTransformTable)
	{
		delete m_pStatusTransformTable;
		m_pStatusTransformTable = NULL;
	}
	if (NULL != m_pGameManiaTimeTable)
	{
		delete m_pGameManiaTimeTable;
		m_pGameManiaTimeTable = NULL;
	}
	if (NULL != m_pGuideHintTable)
	{
		delete m_pGuideHintTable;
		m_pGuideHintTable = NULL;
	}
	//--------------------------------------------------------------------------------

	//--------------------------------------------------------------------------------
	// Item
	//--------------------------------------------------------------------------------
	if (NULL != m_pBasicDropTable)
	{
		delete m_pBasicDropTable;
		m_pBasicDropTable = NULL;
	}
	if (NULL != m_pItemOptionTable)
	{
		delete m_pItemOptionTable;
		m_pItemOptionTable = NULL;
	}
	if (NULL != m_pItemTable)
	{
		delete m_pItemTable;
		m_pItemTable = NULL;
	}
	if (NULL != m_pNormalDropTable)
	{
		delete m_pNormalDropTable;
		m_pNormalDropTable = NULL;
	}
	if (NULL != m_pLegendaryDropTable)
	{
		delete m_pLegendaryDropTable;
		m_pLegendaryDropTable = NULL;
	}
	if (NULL != m_pSuperiorDropTable)
	{
		delete m_pSuperiorDropTable;
		m_pSuperiorDropTable = NULL;
	}
	if (NULL != m_pEachDropTable)
	{
		delete m_pEachDropTable;
		m_pEachDropTable = NULL;
	}
	if (NULL != m_pTypeDropTable)
	{
		delete m_pTypeDropTable;
		m_pTypeDropTable = NULL;
	}
	if (NULL != m_pUseItemTable)
	{
		delete m_pUseItemTable;
		m_pUseItemTable = NULL;
	}
	if (NULL != m_pUseItemTable2)
	{
		delete m_pUseItemTable2;
		m_pUseItemTable2 = NULL;
	}
	if (NULL != m_pSetItemTable)
	{
		delete m_pSetItemTable;
		m_pSetItemTable = NULL;
	}
	if (NULL != m_pDragonBallTable)
	{
		delete m_pDragonBallTable;
		m_pDragonBallTable = NULL;
	}
	if (NULL != m_pDragonBallRewardTable)
	{
		delete m_pDragonBallRewardTable;
		m_pDragonBallRewardTable = NULL;
	}
	if (NULL != m_pExcellentDropTable)
	{
		delete m_pExcellentDropTable;
		m_pExcellentDropTable = NULL;
	}

	//--------------------------------------------------------------------------------

	//--------------------------------------------------------------------------------
	// Misc
	//--------------------------------------------------------------------------------
	if (NULL != m_pActionTable)
	{
		delete m_pActionTable;
		m_pActionTable = NULL;
	}
	if (NULL != m_pChatCommandTable)
	{
		delete m_pChatCommandTable;
		m_pChatCommandTable = NULL;
	}
	if (NULL != m_pDirectionLinkTable)
	{
		delete m_pDirectionLinkTable;
		m_pDirectionLinkTable = NULL;
	}
	if (NULL != m_pFormulaTable)
	{
		delete m_pFormulaTable;
		m_pFormulaTable = NULL;
	}
	//--------------------------------------------------------------------------------

	//--------------------------------------------------------------------------------
	// Party
	//--------------------------------------------------------------------------------
	if (NULL != m_pCharmTable)
	{
		delete m_pCharmTable;
		m_pCharmTable = NULL;
	}
	//--------------------------------------------------------------------------------

	//--------------------------------------------------------------------------------
	// Quest
	//--------------------------------------------------------------------------------
	if (NULL != m_pQuestDropTable)
	{
		delete m_pQuestDropTable;
		m_pQuestDropTable = NULL;
	}
	if (NULL != m_pQuestItemTable)
	{
		delete m_pQuestItemTable;
		m_pQuestItemTable = NULL;
	}
	if (NULL != m_pQuestProbalityTable)
	{
		delete m_pQuestProbalityTable;
		m_pQuestProbalityTable = NULL;
	}
	if (NULL != m_pQuestProbalityTable2)
	{
		delete m_pQuestProbalityTable2;
		m_pQuestProbalityTable2 = NULL;
	}
	if (NULL != m_pQuestTextDataTable)
	{
		delete m_pQuestTextDataTable;
		m_pQuestTextDataTable = NULL;
	}
	if (NULL != m_pQuestRewardTable)
	{
		delete m_pQuestRewardTable;
		m_pQuestRewardTable = NULL;
	}
	if (NULL != m_pQuestRewardSelectTable)
	{
		delete m_pQuestRewardSelectTable;
		m_pQuestRewardSelectTable = NULL;
	}
	//--------------------------------------------------------------------------------

	//--------------------------------------------------------------------------------
	// Skill
	//--------------------------------------------------------------------------------
	if (NULL != m_pHTBSetTable)
	{
		delete m_pHTBSetTable;
		m_pHTBSetTable = NULL;
	}
	if (NULL != m_pSkillTable)
	{
		delete m_pSkillTable;
		m_pSkillTable = NULL;
	}
	if (NULL != m_pSystemEffectTable)
	{
		delete m_pSystemEffectTable;
		m_pSystemEffectTable = NULL;
	}
	//--------------------------------------------------------------------------------

	//--------------------------------------------------------------------------------
	// Text
	//--------------------------------------------------------------------------------
	if (NULL != m_pTextAllTable)
	{
		delete m_pTextAllTable;
		m_pTextAllTable = NULL;
	}
	if (NULL != m_pChattingFilterTable)
	{
		delete m_pChattingFilterTable;
		m_pChattingFilterTable = NULL;
	}
	if (NULL != m_pTextServerTable)
	{
		delete m_pTextServerTable;
		m_pTextServerTable = NULL;
	}
	//--------------------------------------------------------------------------------

	//--------------------------------------------------------------------------------
	// World
	//--------------------------------------------------------------------------------
	if (NULL != m_pWorldPathTable)
	{
		delete m_pWorldPathTable;
		m_pWorldPathTable = NULL;
	}
	if (NULL != m_pWorldTable)
	{
		delete m_pWorldTable;
		m_pWorldTable = NULL;
	}
	if (NULL != m_pWorldZoneTable)
	{
		delete m_pWorldZoneTable;
		m_pWorldZoneTable = NULL;
	}

	for (OBJTABLEIT it = m_mapObjectTable.begin(); it != m_mapObjectTable.end(); it++)
	{
		delete it->second;
	}
	m_mapObjectTable.clear();

	for (SPAWNTABLEIT it = m_mapNpcSpawnTable.begin(); it != m_mapNpcSpawnTable.end(); it++)
	{
		delete it->second;
	}
	m_mapNpcSpawnTable.clear();

	for (SPAWNTABLEIT it = m_mapMobSpawnTable.begin(); it != m_mapMobSpawnTable.end(); it++)
	{
		delete it->second;
	}
	m_mapMobSpawnTable.clear();

	if (NULL != m_pWorldMapTable)
	{
		delete m_pWorldMapTable;
		m_pWorldMapTable = NULL;
	}
	if (NULL != m_pLandMarkTable)
	{
		delete m_pLandMarkTable;
		m_pLandMarkTable = NULL;
	}
	if (NULL != m_pWorldPlayTable)
	{
		delete m_pWorldPlayTable;
		m_pWorldPlayTable = NULL;
	}
	//--------------------------------------------------------------------------------


	//--------------------------------------------------------------------------------
	// Rule
	//--------------------------------------------------------------------------------
	if (NULL != m_pTimeQuestTable)
	{
		delete m_pTimeQuestTable;
		m_pTimeQuestTable = NULL;
	}

	if (NULL != m_pRankBattleTable)
	{
		delete m_pRankBattleTable;
		m_pRankBattleTable = NULL;
	}

	if (NULL != m_pBudokaiTable)
	{
		delete m_pBudokaiTable;
		m_pBudokaiTable = NULL;
	}

	if (NULL != m_pDungeonTable)
	{
		delete m_pDungeonTable;
		m_pDungeonTable = NULL;
	}
	//--------------------------------------------------------------------------------
	if (NULL != m_pPortalTable)
	{
		delete m_pPortalTable;
		m_pPortalTable = NULL;
	}
	//--------------------------------------------------------------------------------
	if (NULL != m_pNpcSpeechTable)
	{
		delete m_pNpcSpeechTable;
		m_pNpcSpeechTable = NULL;
	}
	//--------------------------------------------------------------------------------
	if (NULL != m_pScriptLinkTable)
	{
		delete m_pScriptLinkTable;
		m_pScriptLinkTable = NULL;
	}
	//--------------------------------------------------------------------------------
	if (NULL != m_pQuestNarrationTable)
	{
		delete m_pQuestNarrationTable;
		m_pQuestNarrationTable = NULL;
	}
	//--------------------------------------------------------------------------------
	if (NULL != m_pVehicleTable)
	{
		delete m_pVehicleTable;
		m_pVehicleTable = NULL;
	}
	//--------------------------------------------------------------------------------
	if (NULL != m_pItemRecipeTable)
	{
		delete m_pItemRecipeTable;
		m_pItemRecipeTable = NULL;
	}
	//--------------------------------------------------------------------------------
	if (NULL != m_pItemRecipeTable2)
	{
		delete m_pItemRecipeTable2;
		m_pItemRecipeTable2 = NULL;
	}
	//--------------------------------------------------------------------------------
	if (NULL != m_pDynamicObjectTable)
	{
		delete m_pDynamicObjectTable;
		m_pDynamicObjectTable = NULL;
	}
	//--------------------------------------------------------------------------------
	if (NULL != m_pMobMovePatternTable)
	{
		delete m_pMobMovePatternTable;
		m_pMobMovePatternTable = NULL;
	}
	//--------------------------------------------------------------------------------
	if (NULL != m_pDojoTable)
	{
		delete m_pDojoTable;
		m_pDojoTable = NULL;
	}
	//--------------------------------------------------------------------------------
	if (NULL != m_pItemUpgradeTable)
	{
		delete m_pItemUpgradeTable;
		m_pItemUpgradeTable = NULL;
	}
	//--------------------------------------------------------------------------------
	if (NULL != m_pItemMixMachineTable)
	{
		delete m_pItemMixMachineTable;
		m_pItemMixMachineTable = NULL;
	}
	//--------------------------------------------------------------------------------
	if (NULL != m_pHLSMerchantTable)
	{
		delete m_pHLSMerchantTable;
		m_pHLSMerchantTable = NULL;
	}
	//--------------------------------------------------------------------------------
	if (NULL != m_pHLSItemTable)
	{
		delete m_pHLSItemTable;
		m_pHLSItemTable = NULL;
	}
	//--------------------------------------------------------------------------------	
	//--------------------------------------------------------------------------------
	if (NULL != m_pCharTitleTable)
	{
		delete m_pCharTitleTable;
		m_pCharTitleTable = NULL;
	}
	//--------------------------------------------------------------------------------	
	//--------------------------------------------------------------------------------
	if (NULL != m_pCashItemTable)
	{
		delete m_pCashItemTable;
		m_pCashItemTable = NULL;
	}
	//--------------------------------------------------------------------------------	

}

bool TableContainer::Reload(CNtlBitFlagManager& rTableFlag, TableFileNameList* pFileNameList)
{
	FileSerializer serializer;

	// Mob
	if (false != rTableFlag.IsSet(TABLE_MOB))
	{
		DBO_RELOAD_TABLE(NPCTable, serializer, pFileNameList->GetFileNameW(TABLE_MOB), m_pMobTable);
	}

	// Npc
	if (false != rTableFlag.IsSet(TABLE_NPC))
	{
		DBO_RELOAD_TABLE(NPCTable, serializer, pFileNameList->GetFileNameW(TABLE_NPC), m_pNpcTable);
	}

	// Item
	if (false != rTableFlag.IsSet(TABLE_ITEM))
	{
		DBO_RELOAD_TABLE(ItemTable, serializer, pFileNameList->GetFileNameW(TABLE_ITEM), m_pItemTable);
	}

	// ItemOption
	if (false != rTableFlag.IsSet(TABLE_ITEM_OPTION))
	{
		DBO_RELOAD_TABLE(ItemOptionTable, serializer, pFileNameList->GetFileNameW(TABLE_ITEM_OPTION), m_pItemOptionTable);
	}

	// UseItem
	if (false != rTableFlag.IsSet(TABLE_ITEM_OPTION))
	{
		DBO_RELOAD_TABLE(UseItemTable, serializer, pFileNameList->GetFileNameW(TABLE_USE_ITEM), m_pUseItemTable);
	}

	// SetItem
	if (false != rTableFlag.IsSet(TABLE_SET_ITEM))
	{
		DBO_RELOAD_TABLE(SetItemTable, serializer, pFileNameList->GetFileNameW(TABLE_SET_ITEM), m_pSetItemTable);
	}

	// Merchant
	if (false != rTableFlag.IsSet(TABLE_MERCHANT))
	{
		DBO_RELOAD_TABLE(MerchantTable, serializer, pFileNameList->GetFileNameW(TABLE_MERCHANT), m_pMerchantTable);
	}
	if (false != rTableFlag.IsSet(TABLE_MERCHANT2))
	{
		DBO_RELOAD_TABLE(MerchantTable2, serializer, pFileNameList->GetFileNameW(TABLE_MERCHANT2), m_pMerchantTable2);
	}
	// BasicDrop
	if (false != rTableFlag.IsSet(TABLE_BASIC_DROP))
	{
		DBO_RELOAD_TABLE(BasicDropTable, serializer, pFileNameList->GetFileNameW(TABLE_BASIC_DROP), m_pBasicDropTable);
	}

	// EachDrop
	if (false != rTableFlag.IsSet(TABLE_EACH_DROP))
	{
		DBO_RELOAD_TABLE(EachDropTable, serializer, pFileNameList->GetFileNameW(TABLE_EACH_DROP), m_pEachDropTable);
	}

	// NormalDrop
	if (false != rTableFlag.IsSet(TABLE_NORMAL_DROP))
	{
		DBO_RELOAD_TABLE(NormalDropTable, serializer, pFileNameList->GetFileNameW(TABLE_NORMAL_DROP), m_pNormalDropTable);
	}

	// LegendaryDrop
	if (false != rTableFlag.IsSet(TABLE_LEGENDARY_DROP))
	{
		DBO_RELOAD_TABLE(LegendaryDropTable, serializer, pFileNameList->GetFileNameW(TABLE_LEGENDARY_DROP), m_pLegendaryDropTable);
	}

	// SuperiorDrop
	if (false != rTableFlag.IsSet(TABLE_SUPERIOR_DROP))
	{
		DBO_RELOAD_TABLE(SuperiorDropTable, serializer, pFileNameList->GetFileNameW(TABLE_SUPERIOR_DROP), m_pSuperiorDropTable);
	}

	// ExcellentDrop
	if (false != rTableFlag.IsSet(TABLE_NORMAL_DROP))
	{
		DBO_RELOAD_TABLE(ExcellentDropTable, serializer, pFileNameList->GetFileNameW(TABLE_EXCELLENT_DROP), m_pExcellentDropTable);
	}

	// Skill
	if (false != rTableFlag.IsSet(TABLE_SKILL))
	{
		DBO_RELOAD_TABLE(SkillTable, serializer, pFileNameList->GetFileNameW(TABLE_SKILL), m_pSkillTable);
	}

	// Object
	if (false != rTableFlag.IsSet(TABLE_OBJECT))
	{
		for (Table::TABLEIT iter = m_pWorldTable->Begin(); m_pWorldTable->End() != iter; iter++)
		{
			sWORLD_TBLDAT * pWorldTableData = (sWORLD_TBLDAT*)iter->second;

			ObjectTable * pObjectTable = GetObjectTable(pWorldTableData->tblidx);
			if (pObjectTable)
			{
				DBO_RELOAD_TABLE(ObjectTable, serializer, pWorldTableData->wszObjSpawn_Table_Name, pObjectTable);
			}
		}
	}


	// DirectionLienk
	if (false != rTableFlag.IsSet(TABLE_DIRECTION_LINK))
	{
		DBO_RELOAD_TABLE(DirectionLinkTable, serializer, pFileNameList->GetFileNameW(TABLE_DIRECTION_LINK), m_pDirectionLinkTable);
	}

	// Formula
	if (false != rTableFlag.IsSet(TABLE_FORMULA))
	{
		DBO_RELOAD_TABLE(FormulaTable, serializer, pFileNameList->GetFileNameW(TABLE_FORMULA), m_pFormulaTable);
	}

	if (false != rTableFlag.IsSet(TABLE_ITEM_ENCHANT))
	{
		DBO_RELOAD_TABLE(ItemEnchantTable, serializer, pFileNameList->GetFileNameW(TABLE_ITEM_ENCHANT), m_pItemEnchantTable);
	}

	if (false != rTableFlag.IsSet(TABLE_SCRIPT_LINK))
	{
		DBO_RELOAD_TABLE(ScriptLinkTable, serializer, pFileNameList->GetFileNameW(TABLE_SCRIPT_LINK), m_pScriptLinkTable);
	}

	if (false != rTableFlag.IsSet(TABLE_DUNGEON))
	{
		DBO_RELOAD_TABLE(DungeonTable, serializer, pFileNameList->GetFileNameW(TABLE_DUNGEON), m_pDungeonTable);
	}

	if (false != rTableFlag.IsSet(TABLE_QUEST_NARRATION))
	{
		DBO_RELOAD_TABLE(QuestNarrationTable, serializer, pFileNameList->GetFileNameW(TABLE_QUEST_NARRATION), m_pQuestNarrationTable);
	}

	if (false != rTableFlag.IsSet(TABLE_VEHICLE))
	{
		DBO_RELOAD_TABLE(VehicleTable, serializer, pFileNameList->GetFileNameW(TABLE_VEHICLE), m_pVehicleTable);
	}

	if (false != rTableFlag.IsSet(TABLE_ITEM_RECIPE))
	{
		DBO_RELOAD_TABLE(ItemRecipeTable, serializer, pFileNameList->GetFileNameW(TABLE_ITEM_RECIPE), m_pItemRecipeTable);
	}

	if (false != rTableFlag.IsSet(TABLE_ITEM_RECIPE2))
	{
		DBO_RELOAD_TABLE(ItemRecipeTable2, serializer, pFileNameList->GetFileNameW(TABLE_ITEM_RECIPE2), m_pItemRecipeTable2);
	}

	if (false != rTableFlag.IsSet(TABLE_DYNAMIC_OBJECT))
	{
		DBO_RELOAD_TABLE(DynamicObjectTable, serializer, pFileNameList->GetFileNameW(TABLE_DYNAMIC_OBJECT), m_pDynamicObjectTable);
	}

	if (false != rTableFlag.IsSet(TABLE_MOB_MOVE_PATTERN))
	{
		DBO_RELOAD_TABLE(MobMovePatternTable, serializer, pFileNameList->GetFileNameW(TABLE_MOB_MOVE_PATTERN), m_pMobMovePatternTable);
	}

	if (false != rTableFlag.IsSet(TABLE_DOJO))
	{
		DBO_RELOAD_TABLE(DojoTable, serializer, pFileNameList->GetFileNameW(TABLE_DOJO), m_pDojoTable);
	}

	if (false != rTableFlag.IsSet(TABLE_WORLD_MAP))
	{
		DBO_RELOAD_TABLE(WorldMapTable, serializer, pFileNameList->GetFileNameW(TABLE_WORLD_MAP), m_pWorldMapTable);
	}

	if (false != rTableFlag.IsSet(TABLE_LAND_MARK))
	{
		DBO_RELOAD_TABLE(LandMarkTable, serializer, pFileNameList->GetFileNameW(TABLE_LAND_MARK), m_pLandMarkTable);
	}

	if (false != rTableFlag.IsSet(TABLE_ITEM_UPGRADE))
	{
		DBO_RELOAD_TABLE(ItemUpgradeTable, serializer, pFileNameList->GetFileNameW(TABLE_ITEM_UPGRADE), m_pItemUpgradeTable);
	}

	if (false != rTableFlag.IsSet(TABLE_MIX_MACHINE))
	{
		DBO_RELOAD_TABLE(ItemMixMachineTable, serializer, pFileNameList->GetFileNameW(TABLE_MIX_MACHINE), m_pItemMixMachineTable);
	}

	if (false != rTableFlag.IsSet(TABLE_HLS_MERCHANT))
	{
		DBO_RELOAD_TABLE(HLSMerchantTable, serializer, pFileNameList->GetFileNameW(TABLE_HLS_MERCHANT), m_pHLSMerchantTable);
	}

	if (false != rTableFlag.IsSet(TABLE_HLS_ITEM))
	{
		DBO_RELOAD_TABLE(HLSItemTable, serializer, pFileNameList->GetFileNameW(TABLE_HLS_ITEM), m_pHLSItemTable);
	}

	if (false != rTableFlag.IsSet(TABLE_CHAR_TITLE))
	{
		DBO_RELOAD_TABLE(CharTitleTable, serializer, pFileNameList->GetFileNameW(TABLE_CHAR_TITLE), m_pCharTitleTable);
	}
	if (false != rTableFlag.IsSet(TABLE_CASHITEM_TABLE))
	{
		DBO_RELOAD_TABLE(CashItemTable, serializer, pFileNameList->GetFileNameW(TABLE_CASHITEM_TABLE), m_pCashItemTable);
	}
	if (false != rTableFlag.IsSet(TABLE_QUEST_PROBABILITY))
	{
		DBO_RELOAD_TABLE(QuestProbabilityTable, serializer, pFileNameList->GetFileNameW(TABLE_QUEST_PROBABILITY), m_pQuestProbalityTable);
	}
	if (false != rTableFlag.IsSet(TABLE_QUEST_PROBABILITY2))
	{
		DBO_RELOAD_TABLE(QuestProbabilityTable2, serializer, pFileNameList->GetFileNameW(TABLE_QUEST_PROBABILITY2), m_pQuestProbalityTable2);
	}
	if (false != rTableFlag.IsSet(TABLE_USE_ITEM))
	{
		DBO_RELOAD_TABLE(UseItemTable, serializer, pFileNameList->GetFileNameW(TABLE_USE_ITEM), m_pUseItemTable);
	}
	if (false != rTableFlag.IsSet(TABLE_USE_ITEM2))
	{
		DBO_RELOAD_TABLE(UseItemTable2, serializer, pFileNameList->GetFileNameW(TABLE_USE_ITEM2), m_pUseItemTable2);
	}
	return true;
}

bool TableContainer::SaveToFile(CNtlBitFlagManager& rTableFlag, TableFileNameList* pFileNameList, bool bNeedToEncrypt)
{
	FileSerializer serializer;

	//--------------------------------------------------------------------------------
	// Character
	//--------------------------------------------------------------------------------
	if (false != rTableFlag.IsSet(TABLE_EXP))
	{
		DBO_EXPORT_TABLE(m_pExpTable, serializer, pFileNameList->GetFileNameW(TABLE_EXP), bNeedToEncrypt);
	}
	if (false != rTableFlag.IsSet(TABLE_HELP))
	{
		DBO_EXPORT_TABLE(m_pHelpTable, serializer, pFileNameList->GetFileNameW(TABLE_HELP), bNeedToEncrypt);
	}
	if (false != rTableFlag.IsSet(TABLE_MERCHANT))
	{
		DBO_EXPORT_TABLE(m_pMerchantTable, serializer, pFileNameList->GetFileNameW(TABLE_MERCHANT), bNeedToEncrypt);
	}
	if (false != rTableFlag.IsSet(TABLE_MERCHANT2))
	{
		DBO_EXPORT_TABLE(m_pMerchantTable2, serializer, pFileNameList->GetFileNameW(TABLE_MERCHANT2), bNeedToEncrypt);
	}
	if (false != rTableFlag.IsSet(TABLE_MOB))
	{
		DBO_EXPORT_TABLE(m_pMobTable, serializer, pFileNameList->GetFileNameW(TABLE_MOB), bNeedToEncrypt);
	}
	if (false != rTableFlag.IsSet(TABLE_NEWBIE))
	{
		DBO_EXPORT_TABLE(m_pNewbieTable, serializer, pFileNameList->GetFileNameW(TABLE_NEWBIE), bNeedToEncrypt);
	}
	if (false != rTableFlag.IsSet(TABLE_NPC))
	{
		DBO_EXPORT_TABLE(m_pNpcTable, serializer, pFileNameList->GetFileNameW(TABLE_NPC), bNeedToEncrypt);
	}
	if (false != rTableFlag.IsSet(TABLE_PC))
	{
		DBO_EXPORT_TABLE(m_pPcTable, serializer, pFileNameList->GetFileNameW(TABLE_PC), bNeedToEncrypt);
	}
	if (false != rTableFlag.IsSet(TABLE_STATUS_TRANSFORM))
	{
		DBO_EXPORT_TABLE(m_pStatusTransformTable, serializer, pFileNameList->GetFileNameW(TABLE_STATUS_TRANSFORM), bNeedToEncrypt);
	}
	if (false != rTableFlag.IsSet(TABLE_GAME_MANIA_TIME))
	{
		DBO_EXPORT_TABLE(m_pGameManiaTimeTable, serializer, pFileNameList->GetFileNameW(TABLE_GAME_MANIA_TIME), bNeedToEncrypt);
	}
	if (false != rTableFlag.IsSet(TABLE_GUIDE_HINT))
	{
		DBO_EXPORT_TABLE(m_pGuideHintTable, serializer, pFileNameList->GetFileNameW(TABLE_GUIDE_HINT), bNeedToEncrypt);
	}
	//--------------------------------------------------------------------------------

	//--------------------------------------------------------------------------------
	// Item
	//--------------------------------------------------------------------------------
	if (false != rTableFlag.IsSet(TABLE_BASIC_DROP))
	{
		DBO_EXPORT_TABLE(m_pBasicDropTable, serializer, pFileNameList->GetFileNameW(TABLE_BASIC_DROP), bNeedToEncrypt);
	}
	if (false != rTableFlag.IsSet(TABLE_ITEM_OPTION))
	{
		DBO_EXPORT_TABLE(m_pItemOptionTable, serializer, pFileNameList->GetFileNameW(TABLE_ITEM_OPTION), bNeedToEncrypt);
	}
	if (false != rTableFlag.IsSet(TABLE_ITEM))
	{
		DBO_EXPORT_TABLE(m_pItemTable, serializer, pFileNameList->GetFileNameW(TABLE_ITEM), bNeedToEncrypt);
	}
	if (false != rTableFlag.IsSet(TABLE_NORMAL_DROP))
	{
		DBO_EXPORT_TABLE(m_pNormalDropTable, serializer, pFileNameList->GetFileNameW(TABLE_NORMAL_DROP), bNeedToEncrypt);
	}
	if (false != rTableFlag.IsSet(TABLE_LEGENDARY_DROP))
	{
		DBO_EXPORT_TABLE(m_pLegendaryDropTable, serializer, pFileNameList->GetFileNameW(TABLE_LEGENDARY_DROP), bNeedToEncrypt);
	}
	if (false != rTableFlag.IsSet(TABLE_SUPERIOR_DROP))
	{
		DBO_EXPORT_TABLE(m_pSuperiorDropTable, serializer, pFileNameList->GetFileNameW(TABLE_SUPERIOR_DROP), bNeedToEncrypt);
	}
	if (false != rTableFlag.IsSet(TABLE_EACH_DROP))
	{
		DBO_EXPORT_TABLE(m_pEachDropTable, serializer, pFileNameList->GetFileNameW(TABLE_EACH_DROP), bNeedToEncrypt);
	}
	if (false != rTableFlag.IsSet(TABLE_TYPE_DROP))
	{
		DBO_EXPORT_TABLE(m_pTypeDropTable, serializer, pFileNameList->GetFileNameW(TABLE_TYPE_DROP), bNeedToEncrypt);
	}
	if (false != rTableFlag.IsSet(TABLE_USE_ITEM))
	{
		DBO_EXPORT_TABLE(m_pUseItemTable, serializer, pFileNameList->GetFileNameW(TABLE_USE_ITEM), bNeedToEncrypt);
	}
	if (false != rTableFlag.IsSet(TABLE_USE_ITEM2))
	{
		DBO_EXPORT_TABLE(m_pUseItemTable2, serializer, pFileNameList->GetFileNameW(TABLE_USE_ITEM2), bNeedToEncrypt);
	}
	if (false != rTableFlag.IsSet(TABLE_SET_ITEM))
	{
		DBO_EXPORT_TABLE(m_pSetItemTable, serializer, pFileNameList->GetFileNameW(TABLE_SET_ITEM), bNeedToEncrypt);
	}
	if (false != rTableFlag.IsSet(TABLE_DRAGONBALL))
	{
		DBO_EXPORT_TABLE(m_pDragonBallTable, serializer, pFileNameList->GetFileNameW(TABLE_DRAGONBALL), bNeedToEncrypt);
	}
	if (false != rTableFlag.IsSet(TABLE_DRAGONBALL_REWARD))
	{
		DBO_EXPORT_TABLE(m_pDragonBallRewardTable, serializer, pFileNameList->GetFileNameW(TABLE_DRAGONBALL_REWARD), bNeedToEncrypt);
	}
	if (false != rTableFlag.IsSet(TABLE_EXCELLENT_DROP))
	{
		DBO_EXPORT_TABLE(m_pExcellentDropTable, serializer, pFileNameList->GetFileNameW(TABLE_EXCELLENT_DROP), bNeedToEncrypt);
	}
	//--------------------------------------------------------------------------------

	//--------------------------------------------------------------------------------
	// Misc
	//--------------------------------------------------------------------------------
	if (false != rTableFlag.IsSet(TABLE_ACTION))
	{
		DBO_EXPORT_TABLE(m_pActionTable, serializer, pFileNameList->GetFileNameW(TABLE_ACTION), bNeedToEncrypt);
	}
	if (false != rTableFlag.IsSet(TABLE_CHAT_COMMAND))
	{
		DBO_EXPORT_TABLE(m_pChatCommandTable, serializer, pFileNameList->GetFileNameW(TABLE_CHAT_COMMAND), bNeedToEncrypt);
	}
	if (false != rTableFlag.IsSet(TABLE_DIRECTION_LINK))
	{
		DBO_EXPORT_TABLE(m_pDirectionLinkTable, serializer, pFileNameList->GetFileNameW(TABLE_DIRECTION_LINK), bNeedToEncrypt);
	}
	if (false != rTableFlag.IsSet(TABLE_FORMULA))
	{
		DBO_EXPORT_TABLE(m_pFormulaTable, serializer, pFileNameList->GetFileNameW(TABLE_FORMULA), bNeedToEncrypt);
	}

	if (false != rTableFlag.IsSet(TABLE_ITEM_ENCHANT))
	{
		DBO_EXPORT_TABLE(m_pItemEnchantTable, serializer, pFileNameList->GetFileNameW(TABLE_ITEM_ENCHANT), bNeedToEncrypt);
	}
	//--------------------------------------------------------------------------------

	//--------------------------------------------------------------------------------
	// Party
	//--------------------------------------------------------------------------------
	if (false != rTableFlag.IsSet(TABLE_CHARM))
	{
		DBO_EXPORT_TABLE(m_pCharmTable, serializer, pFileNameList->GetFileNameW(TABLE_CHARM), bNeedToEncrypt);
	}
	//--------------------------------------------------------------------------------

	//--------------------------------------------------------------------------------
	// Quest
	//--------------------------------------------------------------------------------
	if (false != rTableFlag.IsSet(TABLE_QUEST_DROP))
	{
		DBO_EXPORT_TABLE(m_pQuestDropTable, serializer, pFileNameList->GetFileNameW(TABLE_QUEST_DROP), bNeedToEncrypt);
	}
	if (false != rTableFlag.IsSet(TABLE_QUEST_ITEM))
	{
		DBO_EXPORT_TABLE(m_pQuestItemTable, serializer, pFileNameList->GetFileNameW(TABLE_QUEST_ITEM), bNeedToEncrypt);
	}
	if (false != rTableFlag.IsSet(TABLE_QUEST_PROBABILITY))
	{
		DBO_EXPORT_TABLE(m_pQuestProbalityTable, serializer, pFileNameList->GetFileNameW(TABLE_QUEST_PROBABILITY), bNeedToEncrypt);
	}
	if (false != rTableFlag.IsSet(TABLE_QUEST_PROBABILITY2))
	{
		DBO_EXPORT_TABLE(m_pQuestProbalityTable2, serializer, pFileNameList->GetFileNameW(TABLE_QUEST_PROBABILITY2), bNeedToEncrypt);
	}
	if (false != rTableFlag.IsSet(TABLE_QUEST_TEXT_DATA))
	{
		DBO_EXPORT_TABLE(m_pQuestTextDataTable, serializer, pFileNameList->GetFileNameW(TABLE_QUEST_TEXT_DATA), bNeedToEncrypt);
	}
	if (false != rTableFlag.IsSet(TABLE_QUEST_REWARD))
	{
		DBO_EXPORT_TABLE(m_pQuestRewardTable, serializer, pFileNameList->GetFileNameW(TABLE_QUEST_REWARD), bNeedToEncrypt);
	}
	if (false != rTableFlag.IsSet(TABLE_QUEST_REWARD_SELECT))
	{
		DBO_EXPORT_TABLE(m_pQuestRewardSelectTable, serializer, pFileNameList->GetFileNameW(TABLE_QUEST_REWARD_SELECT), bNeedToEncrypt);
	}
	//--------------------------------------------------------------------------------

	//--------------------------------------------------------------------------------
	// Skill
	//--------------------------------------------------------------------------------
	if (false != rTableFlag.IsSet(TABLE_HTB_SET))
	{
		DBO_EXPORT_TABLE(m_pHTBSetTable, serializer, pFileNameList->GetFileNameW(TABLE_HTB_SET), bNeedToEncrypt);
	}
	if (false != rTableFlag.IsSet(TABLE_SKILL))
	{
		DBO_EXPORT_TABLE(m_pSkillTable, serializer, pFileNameList->GetFileNameW(TABLE_SKILL), bNeedToEncrypt);
	}
	if (false != rTableFlag.IsSet(TABLE_SYSTEM_EFFECT))
	{
		DBO_EXPORT_TABLE(m_pSystemEffectTable, serializer, pFileNameList->GetFileNameW(TABLE_SYSTEM_EFFECT), bNeedToEncrypt);
	}
	//--------------------------------------------------------------------------------

	//--------------------------------------------------------------------------------
	// Text
	//--------------------------------------------------------------------------------
	if (false != rTableFlag.IsSet(TABLE_TEXT_ALL))
	{
		DBO_EXPORT_TABLE(m_pTextAllTable, serializer, pFileNameList->GetFileNameW(TABLE_TEXT_ALL), bNeedToEncrypt);
	}
	if (false != rTableFlag.IsSet(TABLE_CHATTING_FILTER))
	{
		DBO_EXPORT_TABLE(m_pChattingFilterTable, serializer, pFileNameList->GetFileNameW(TABLE_CHATTING_FILTER), bNeedToEncrypt);
	}
	if (false != rTableFlag.IsSet(TABLE_TEXT_SERVER))
	{
		DBO_EXPORT_TABLE(m_pTextServerTable, serializer, pFileNameList->GetFileNameW(TABLE_TEXT_SERVER), bNeedToEncrypt);
	}
	//--------------------------------------------------------------------------------

	//--------------------------------------------------------------------------------
	// World
	//--------------------------------------------------------------------------------
	if (false != rTableFlag.IsSet(TABLE_WORLD))
	{
		DBO_EXPORT_TABLE(m_pWorldTable, serializer, pFileNameList->GetFileNameW(TABLE_WORLD), bNeedToEncrypt);
	}
	if (false != rTableFlag.IsSet(TABLE_WORLD_ZONE))
	{
		DBO_EXPORT_TABLE(m_pWorldZoneTable, serializer, pFileNameList->GetFileNameW(TABLE_WORLD_ZONE), bNeedToEncrypt);
	}
	if (false != rTableFlag.IsSet(TABLE_OBJECT))
	{
		for (Table::TABLEIT iter = m_pWorldTable->Begin(); m_pWorldTable->End() != iter; iter++)
		{
			sWORLD_TBLDAT* pWorldTableData = (sWORLD_TBLDAT*)(iter->second);

			DBO_EXPORT_REGISTERED_TABLE(ObjectTable, serializer, pWorldTableData->wszObjSpawn_Table_Name, bNeedToEncrypt, m_mapObjectTable, pWorldTableData->tblidx);
		}
	}
	if (false != rTableFlag.IsSet(TABLE_NPC_SPAWN))
	{
		for (Table::TABLEIT iter = m_pWorldTable->Begin(); m_pWorldTable->End() != iter; iter++)
		{
			sWORLD_TBLDAT* pWorldTableData = (sWORLD_TBLDAT*)(iter->second);

			DBO_EXPORT_REGISTERED_TABLE(SpawnTable, serializer, pWorldTableData->wszNpcSpawn_Table_Name, bNeedToEncrypt, m_mapNpcSpawnTable, pWorldTableData->tblidx);
		}
	}
	if (false != rTableFlag.IsSet(TABLE_MOB_SPAWN))
	{
		for (Table::TABLEIT iter = m_pWorldTable->Begin(); m_pWorldTable->End() != iter; iter++)
		{
			sWORLD_TBLDAT* pWorldTableData = (sWORLD_TBLDAT*)(iter->second);

			DBO_EXPORT_REGISTERED_TABLE(SpawnTable, serializer, pWorldTableData->wszMobSpawn_Table_Name, bNeedToEncrypt, m_mapMobSpawnTable, pWorldTableData->tblidx);
		}
	}
	if (false != rTableFlag.IsSet(TABLE_WORLD_MAP))
	{
		DBO_EXPORT_TABLE(m_pWorldMapTable, serializer, pFileNameList->GetFileNameW(TABLE_WORLD_MAP), bNeedToEncrypt);
	}
	if (false != rTableFlag.IsSet(TABLE_LAND_MARK))
	{
		DBO_EXPORT_TABLE(m_pLandMarkTable, serializer, pFileNameList->GetFileNameW(TABLE_LAND_MARK), bNeedToEncrypt);
	}
	//--------------------------------------------------------------------------------


	//--------------------------------------------------------------------------------
	// 
	//--------------------------------------------------------------------------------
	if (false != rTableFlag.IsSet(TABLE_TIMEQUEST))
	{
		DBO_EXPORT_TABLE(m_pTimeQuestTable, serializer, pFileNameList->GetFileNameW(TABLE_TIMEQUEST), bNeedToEncrypt);
	}

	if (false != rTableFlag.IsSet(TABLE_RANKBATTLE))
	{
		DBO_EXPORT_TABLE(m_pRankBattleTable, serializer, pFileNameList->GetFileNameW(TABLE_RANKBATTLE), bNeedToEncrypt);
	}

	if (false != rTableFlag.IsSet(TABLE_BUDOKAI))
	{
		DBO_EXPORT_TABLE(m_pBudokaiTable, serializer, pFileNameList->GetFileNameW(TABLE_BUDOKAI), bNeedToEncrypt);
	}


	//--------------------------------------------------------------------------------
	// GraphicData
	//--------------------------------------------------------------------------------
	// 그래픽 데이타는 TableContainer로 export하지 않습니다.
	// Graphic data is not supposed to be exported via TableContainer.
	// by YOSHIKI(2007-04-05)

	if (false != rTableFlag.IsSet(TABLE_PORTAL))
	{
		DBO_EXPORT_TABLE(m_pPortalTable, serializer, pFileNameList->GetFileNameW(TABLE_PORTAL), bNeedToEncrypt);
	}

	if (false != rTableFlag.IsSet(TABLE_SPEECH))
	{
		DBO_EXPORT_TABLE(m_pNpcSpeechTable, serializer, pFileNameList->GetFileNameW(TABLE_SPEECH), bNeedToEncrypt);
	}

	if (false != rTableFlag.IsSet(TABLE_WORLD_PLAY))
	{
		DBO_EXPORT_TABLE(m_pWorldPlayTable, serializer, pFileNameList->GetFileNameW(TABLE_WORLD_PLAY), bNeedToEncrypt);
	}

	if (false != rTableFlag.IsSet(TABLE_SCRIPT_LINK))
	{
		DBO_EXPORT_TABLE(m_pScriptLinkTable, serializer, pFileNameList->GetFileNameW(TABLE_SCRIPT_LINK), bNeedToEncrypt);
	}

	if (false != rTableFlag.IsSet(TABLE_DUNGEON))
	{
		DBO_EXPORT_TABLE(m_pDungeonTable, serializer, pFileNameList->GetFileNameW(TABLE_DUNGEON), bNeedToEncrypt);
	}

	if (false != rTableFlag.IsSet(TABLE_QUEST_NARRATION))
	{
		DBO_EXPORT_TABLE(m_pQuestNarrationTable, serializer, pFileNameList->GetFileNameW(TABLE_QUEST_NARRATION), bNeedToEncrypt);
	}

	if (false != rTableFlag.IsSet(TABLE_VEHICLE))
	{
		DBO_EXPORT_TABLE(m_pVehicleTable, serializer, pFileNameList->GetFileNameW(TABLE_VEHICLE), bNeedToEncrypt);
	}

	if (false != rTableFlag.IsSet(TABLE_ITEM_RECIPE))
	{
		DBO_EXPORT_TABLE(m_pItemRecipeTable, serializer, pFileNameList->GetFileNameW(TABLE_ITEM_RECIPE), bNeedToEncrypt);
	}

	if (false != rTableFlag.IsSet(TABLE_ITEM_RECIPE2))
	{
		DBO_EXPORT_TABLE(m_pItemRecipeTable2, serializer, pFileNameList->GetFileNameW(TABLE_ITEM_RECIPE2), bNeedToEncrypt);
	}

	if (false != rTableFlag.IsSet(TABLE_DYNAMIC_OBJECT))
	{
		DBO_EXPORT_TABLE(m_pDynamicObjectTable, serializer, pFileNameList->GetFileNameW(TABLE_DYNAMIC_OBJECT), bNeedToEncrypt);
	}

	if (false != rTableFlag.IsSet(TABLE_MOB_MOVE_PATTERN))
	{
		DBO_EXPORT_TABLE(m_pMobMovePatternTable, serializer, pFileNameList->GetFileNameW(TABLE_MOB_MOVE_PATTERN), bNeedToEncrypt);
	}

	if (false != rTableFlag.IsSet(TABLE_DOJO))
	{
		DBO_EXPORT_TABLE(m_pDojoTable, serializer, pFileNameList->GetFileNameW(TABLE_DOJO), bNeedToEncrypt);
	}

	if (false != rTableFlag.IsSet(TABLE_ITEM_UPGRADE))
	{
		DBO_EXPORT_TABLE(m_pItemUpgradeTable, serializer, pFileNameList->GetFileNameW(TABLE_ITEM_UPGRADE), bNeedToEncrypt);
	}

	if (false != rTableFlag.IsSet(TABLE_MIX_MACHINE))
	{
		DBO_EXPORT_TABLE(m_pItemMixMachineTable, serializer, pFileNameList->GetFileNameW(TABLE_MIX_MACHINE), bNeedToEncrypt);
	}

	if (false != rTableFlag.IsSet(TABLE_HLS_MERCHANT))
	{
		DBO_EXPORT_TABLE(m_pHLSMerchantTable, serializer, pFileNameList->GetFileNameW(TABLE_HLS_MERCHANT), bNeedToEncrypt);
	}

	if (false != rTableFlag.IsSet(TABLE_HLS_ITEM))
	{
		DBO_EXPORT_TABLE(m_pHLSItemTable, serializer, pFileNameList->GetFileNameW(TABLE_HLS_ITEM), bNeedToEncrypt);
	}

	if (false != rTableFlag.IsSet(TABLE_CHAR_TITLE))
	{
		DBO_EXPORT_TABLE(m_pCharTitleTable, serializer, pFileNameList->GetFileNameW(TABLE_CHAR_TITLE), bNeedToEncrypt);
	}

	if (false != rTableFlag.IsSet(TABLE_CASHITEM_TABLE))
	{
		DBO_EXPORT_TABLE(m_pCashItemTable, serializer, pFileNameList->GetFileNameW(TABLE_CASHITEM_TABLE), bNeedToEncrypt);
	}

	return true;
}

bool TableContainer::ReloadTable(Table* pTable, FileSerializer& serializer, char* pszFileNameWithoutExtension)
{
	if (NULL == pszFileNameWithoutExtension)
	{
		return false;
	}

	int iRequiredChars = ::MultiByteToWideChar(m_dwCodePage, 0, pszFileNameWithoutExtension, -1, NULL, 0);
	WCHAR* pwszUnicodeFileName = new WCHAR[iRequiredChars];
	if (NULL == pwszUnicodeFileName)
	{
		return false;
	}

	::MultiByteToWideChar(m_dwCodePage, 0, pszFileNameWithoutExtension, -1, pwszUnicodeFileName, iRequiredChars);

	bool bResult = ReloadTable(pTable, serializer, pwszUnicodeFileName);

	delete[] pwszUnicodeFileName;

	return bResult;
}

bool TableContainer::ReloadTable(Table* pTable, FileSerializer& serializer, WCHAR* pwszFileNameWithoutExtension)
{
	std::wstring wstrFullPath(m_wstrPath);

	wstrFullPath += L"\\";
	wstrFullPath += pwszFileNameWithoutExtension;

	switch (m_eLoadingMethod)
	{
	case LOADING_METHOD_XML:
	{
		wstrFullPath += L".xml";

		if (false == pTable->LoadFromXml((WCHAR*)wstrFullPath.c_str(), true))
		{
			return false;
		}
	}
	break;

	case LOADING_METHOD_BINARY:
	{
		wstrFullPath += L".rdf";

		serializer.LoadFile((WCHAR*)wstrFullPath.c_str(), false);

		if (false == pTable->LoadFromBinary(serializer, true))
		{
			return false;
		}
	}
	break;

	case LOADING_METHOD_SECURED_BINARY:
	{
		wstrFullPath += L".edf";

		serializer.LoadFile((WCHAR*)wstrFullPath.c_str(), true, L"KEY_FOR_GAME_DATA_TABLE");

		int nDataSize = 0;
		serializer >> nDataSize;

		FileSerializer dataSerializer;
		serializer.Out(dataSerializer, nDataSize);

		if (false == pTable->LoadFromBinary(dataSerializer, true))
		{
			return false;
		}
	}
	break;

	default:
	{
		return false;
	}
	break;
	}

	return true;
}

bool TableContainer::InitializeTable(Table* pTable, FileSerializer& serializer, char* pszFileNameWithoutExtension, ICallBack* pCall)
{
	if (NULL == pszFileNameWithoutExtension)
	{
		return false;
	}

	int iRequiredChars = ::MultiByteToWideChar(m_dwCodePage, 0, pszFileNameWithoutExtension, -1, NULL, 0);
	WCHAR* pwszUnicodeFileName = new WCHAR[iRequiredChars];
	if (NULL == pwszUnicodeFileName)
	{
		return false;
	}

	::MultiByteToWideChar(m_dwCodePage, 0, pszFileNameWithoutExtension, -1, pwszUnicodeFileName, iRequiredChars);

	bool bResult = InitializeTable(pTable, serializer, pwszUnicodeFileName, pCall);

	delete[] pwszUnicodeFileName;

	return bResult;
}

bool TableContainer::InitializeTable(Table* pTable, FileSerializer& serializer, WCHAR* pwszFileNameWithoutExtension, ICallBack* pCall)
{
	UNREFERENCED_PARAMETER(pCall);
	std::wstring wstrFullPath;

	wstrFullPath = m_wstrPath;
	wstrFullPath += L"\\";
	wstrFullPath += pwszFileNameWithoutExtension;


	switch (m_eLoadingMethod)
	{
	case LOADING_METHOD_XML:
	{
		wstrFullPath += L".xml";

		if (false == pTable->LoadFromXml((WCHAR*)wstrFullPath.c_str(), false))
		{
			return false;
		}
	}
	break;

	case LOADING_METHOD_BINARY:
	{
		wstrFullPath += L".rdf";

		serializer.LoadFile((WCHAR*)wstrFullPath.c_str());

		if (false == pTable->LoadFromBinary(serializer, false))
		{
			return false;
		}
	}
	break;

	case LOADING_METHOD_SECURED_BINARY:
	{
		wstrFullPath += L".edf";

		serializer.LoadFile((WCHAR*)wstrFullPath.c_str(), true, L"KEY_FOR_GAME_DATA_TABLE");

		int nDataSize = 0;
		serializer >> nDataSize;

		FileSerializer dataSerializer;
		serializer.Out(dataSerializer, nDataSize);

		if (false == pTable->LoadFromBinary(dataSerializer, false))
		{
			return false;
		}
	}
	break;

	default:
	{
		//- yoshiki : To log system!
		return false;
	}
	break;
	}

	return true;
}

bool TableContainer::InitializePackTable(Table* pTable, FileSerializer& serializer, char* pszFileNameWithoutExtension, ICallBack* pCall)
{
	if (NULL == pszFileNameWithoutExtension)
	{
		return false;
	}

	int iRequiredChars = ::MultiByteToWideChar(m_dwCodePage, 0, pszFileNameWithoutExtension, -1, NULL, 0);
	WCHAR* pwszUnicodeFileName = new WCHAR[iRequiredChars];
	if (NULL == pwszUnicodeFileName)
	{
		return false;
	}

	::MultiByteToWideChar(m_dwCodePage, 0, pszFileNameWithoutExtension, -1, pwszUnicodeFileName, iRequiredChars);

	bool bResult = InitializePackTable(pTable, serializer, pwszUnicodeFileName, pCall);

	delete[] pwszUnicodeFileName;

	return bResult;
}

bool TableContainer::InitializePackTable(Table* pTable, FileSerializer& serializer, WCHAR* pwszFileNameWithoutExtension, ICallBack* pCall)
{
	std::wstring wstrFullPath;

	wstrFullPath = m_wstrPath;
	wstrFullPath += L"\\";
	wstrFullPath += pwszFileNameWithoutExtension;

	char* pchFileName = WC2MB((WCHAR*)wstrFullPath.c_str());
	char* pszCryptPassword = NULL;

	std::string strFullFileName = pchFileName;

	switch (m_eLoadingMethod)
	{
	case LOADING_METHOD_XML:
	{
		strFullFileName += ".xml";

		if (false == pCall->Call(strFullFileName.c_str(), &serializer, pszCryptPassword))
		{
			return false;
		}

		CleanUpHeapString(pchFileName);

		if (false == pTable->LoadFromBinary(serializer, false))
		{
			return false;
		}
	}
	break;

	case LOADING_METHOD_BINARY:
	{
		strFullFileName += ".rdf";

		if (false == pCall->Call(strFullFileName.c_str(), &serializer, pszCryptPassword))
		{
			return false;
		}

		CleanUpHeapString(pchFileName);

		if (false == pTable->LoadFromBinary(serializer, false))
		{
			return false;
		}
	}
	break;

	case LOADING_METHOD_SECURED_BINARY:
	{
		strFullFileName += ".edf";
		pszCryptPassword = "KEY_FOR_GAME_DATA_TABLE";

		if (false == pCall->Call(strFullFileName.c_str(), &serializer, pszCryptPassword))
		{
			return false;
		}

		int nDataSize = 0;
		serializer >> nDataSize;

		FileSerializer dataSerializer;
		serializer.Out(dataSerializer, nDataSize);

		CleanUpHeapString(pchFileName);

		if (false == pTable->LoadFromBinary(dataSerializer, false))
		{
			return false;
		}
	}
	break;

	default:
	{
		return false;
	}
	break;
	}

	return true;
}

bool TableContainer::InitializeTable(TextAllTable* pTextAllTable, FileSerializer& serializer, char* pszFileNameWithoutExtension, ICallBack* pCall)
{
	if (NULL == pszFileNameWithoutExtension)
	{
		sLog.outError("NULL == pszFileNameWithoutExtension");
		return false;
	}

	int iRequiredChars = ::MultiByteToWideChar(m_dwCodePage, 0, pszFileNameWithoutExtension, -1, NULL, 0);
	WCHAR* pwszUnicodeFileName = new WCHAR[iRequiredChars];
	if (NULL == pwszUnicodeFileName)
	{
		sLog.outError("NULL == pwszUnicodeFileName");
		return false;
	}

	::MultiByteToWideChar(m_dwCodePage, 0, pszFileNameWithoutExtension, -1, pwszUnicodeFileName, iRequiredChars);

	bool bResult = InitializeTable(pTextAllTable, serializer, pwszUnicodeFileName, pCall);

	delete[] pwszUnicodeFileName;
	sLog.outError("bResult = %s", bResult ? "true":"false");
	return bResult;
}

bool TableContainer::InitializeTable(TextAllTable* pTextAllTable, FileSerializer& serializer, WCHAR* pwszFileNameWithoutExtension, ICallBack* pCall)
{
	UNREFERENCED_PARAMETER(pCall);
	std::wstring wstrFullPath;

	wstrFullPath = m_wstrPath;
	wstrFullPath += L"\\";
	wstrFullPath += pwszFileNameWithoutExtension;

	switch (m_eLoadingMethod)
	{
	case LOADING_METHOD_XML:
	{
		wstrFullPath += L".xml";

		if (false == pTextAllTable->LoadFromXml((WCHAR*)(wstrFullPath.c_str())))
		{
			return false;
		}
	}
	break;

	case LOADING_METHOD_BINARY:
	{
		wstrFullPath += L".rdf";

		serializer.LoadFile((WCHAR*)(wstrFullPath.c_str()), false);

		if (false == pTextAllTable->LoadFromBinary(serializer))
		{
			return false;
		}
	}
	break;

	case LOADING_METHOD_SECURED_BINARY:
	{
		wstrFullPath += L".edf";

		serializer.LoadFile((WCHAR*)(wstrFullPath.c_str()), true, L"KEY_FOR_GAME_DATA_TABLE");

		int nDataSize = 0;
		serializer >> nDataSize;

		FileSerializer dataSerializer;
		serializer.Out(dataSerializer, nDataSize);

		if (false == pTextAllTable->LoadFromBinary(dataSerializer))
		{
			return false;
		}
	}
	break;

	default:
	{
		//- yoshiki : To log system!
		return false;
	}
	break;
	}

	return true;
}

bool TableContainer::InitializePackTable(TextAllTable* pTextAllTable, FileSerializer& serializer, char* pszFileNameWithoutExtension, ICallBack* pCall)
{
	if (NULL == pszFileNameWithoutExtension)
	{
		return false;
	}

	int iRequiredChars = ::MultiByteToWideChar(m_dwCodePage, 0, pszFileNameWithoutExtension, -1, NULL, 0);
	WCHAR* pwszUnicodeFileName = new WCHAR[iRequiredChars];
	if (NULL == pwszUnicodeFileName)
	{
		return false;
	}

	::MultiByteToWideChar(m_dwCodePage, 0, pszFileNameWithoutExtension, -1, pwszUnicodeFileName, iRequiredChars);

	bool bResult = InitializePackTable(pTextAllTable, serializer, pwszUnicodeFileName, pCall);

	delete[] pwszUnicodeFileName;

	return bResult;
}

bool TableContainer::InitializePackTable(TextAllTable* pTextAllTable, FileSerializer& serializer, WCHAR* pwszFileNameWithoutExtension, ICallBack* pCall)
{
	std::wstring wstrFullPath;

	wstrFullPath = m_wstrPath;
	wstrFullPath += L"\\";
	wstrFullPath += pwszFileNameWithoutExtension;

	char* pchFileName = WC2MB((WCHAR*)wstrFullPath.c_str());
	char* pszCryptPassword = NULL;

	std::string strFullFileName = pchFileName;

	switch (m_eLoadingMethod)
	{
	case LOADING_METHOD_XML:
	{
		strFullFileName += ".xml";

		if (false == pCall->Call(strFullFileName.c_str(), &serializer, pszCryptPassword))
		{
			return false;
		}

		CleanUpHeapString(pchFileName);

		if (false == pTextAllTable->LoadFromBinary(serializer))
		{
			return false;
		}
	}
	break;

	case LOADING_METHOD_BINARY:
	{
		strFullFileName += ".rdf";

		if (false == pCall->Call(strFullFileName.c_str(), &serializer, pszCryptPassword))
		{
			return false;
		}

		CleanUpHeapString(pchFileName);

		if (false == pTextAllTable->LoadFromBinary(serializer))
		{
			return false;
		}
	}
	break;

	case LOADING_METHOD_SECURED_BINARY:
	{
		strFullFileName += ".edf";
		pszCryptPassword = "KEY_FOR_GAME_DATA_TABLE";

		if (false == pCall->Call(strFullFileName.c_str(), &serializer, pszCryptPassword))
		{
			return false;
		}

		int nDataSize = 0;
		serializer >> nDataSize;

		FileSerializer dataSerializer;
		serializer.Out(dataSerializer, nDataSize);

		CleanUpHeapString(pchFileName);

		if (false == pTextAllTable->LoadFromBinary(dataSerializer))
		{
			return false;
		}
	}
	break;

	default:
	{
		return false;
	}
	break;
	}

	return true;
}

SpawnTable* TableContainer::GetNpcSpawnTable(TBLIDX worldTblidx)
{
	SPAWNTABLEIT it = m_mapNpcSpawnTable.find(worldTblidx);
	if (it == m_mapNpcSpawnTable.end())
	{
		return NULL;
	}

	return it->second;
}

SpawnTable* TableContainer::GetMobSpawnTable(TBLIDX worldTblidx)
{
	SPAWNTABLEIT it = m_mapMobSpawnTable.find(worldTblidx);
	if (it == m_mapMobSpawnTable.end())
	{
		return NULL;
	}

	return it->second;
}

ObjectTable* TableContainer::GetObjectTable(TBLIDX worldTblidx)
{
	OBJTABLEIT it = m_mapObjectTable.find(worldTblidx);
	if (it == m_mapObjectTable.end())
	{
		return NULL;
	}

	return it->second;
}

TableContainer::OBJTABLEIT TableContainer::BeginObjectTable()
{
	return m_mapObjectTable.begin();
}

TableContainer::OBJTABLEIT TableContainer::EndObjectTable()
{
	return m_mapObjectTable.end();
}

TableContainer::SPAWNTABLEIT TableContainer::BeginNpcSpawnTable()
{
	return m_mapNpcSpawnTable.begin();
}

TableContainer::SPAWNTABLEIT TableContainer::EndNpcSpawnTable()
{
	return m_mapNpcSpawnTable.end();
}

TableContainer::SPAWNTABLEIT TableContainer::BeginMobSpawnTable()
{
	return m_mapMobSpawnTable.begin();
}

TableContainer::SPAWNTABLEIT TableContainer::EndMobSpawnTable()
{
	return m_mapMobSpawnTable.end();
}
