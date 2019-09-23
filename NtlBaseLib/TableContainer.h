#pragma once

#include "Table.h"
#include "NtlSharedType.h"
#include <map>
#include <Singleton.h>

class FileSerializer;
class CNtlBitFlagManager;
class TableFileNameList;

// Table Classes
//Character
class ExpTable;
class GuideHintTable;
class HelpTable;
class MerchantTable;
class MerchantTable2;
class MobTable;
class NewbieTable;
class NPCTable;
class PCTable;
class StatusTransformTable;
class GameManiaTimeTable;

// Item
class BasicDropTable;
class DragonBallRewardTable;
class DragonBallTable;
class ItemOptionTable;
class ItemTable;
class LegendaryDropTable;
class NormalDropTable;
class SuperiorDropTable;
class UseItemTable;
class UseItemTable2;
class SetItemTable;
class EachDropTable;
class TypeDropTable;
class ExcellentDropTable;
class TableMascot;

// Misc
class ActionTable;
class ChatCommandTable;
class DirectionLinkTable;
class FormulaTable;

// Party
class CharmTable;

// Quest
class QuestDropTable;
class QuestItemTable;
class QuestProbabilityTable;
class QuestProbabilityTable2;
class QuestTextDataTable;
class QuestRewardTable;

// Rule
class RankBattleTable;
class TimeQuestTable;
class BudokaiTable;
class DungeonTable;

// Skill
class HTBSetTable;
class SkillTable;
class SystemEffectTable;

// Text
class TextAllTable;
class ChattingFilterTable;
class TextServerTable;

// World
class SpawnTable;
class ObjectTable;
class LandMarkTable;
class WorldMapTable;
class WorldTable;
class WorldZoneTable;
class WorldPlayTable;

// World Data
class WorldPathTable;

// Portal Data
class PortalTable;

// Other Systems Table
class NpcSpeechTable;
class ScriptLinkTable;
class QuestNarrationTable;
class VehicleTable;
class ItemRecipeTable;
class DynamicObjectTable;
class MobMovePatternTable;
class DojoTable;
class ItemUpgradeTable;
class ItemMixMachineTable;
class HLSItemTable;
class HLSMerchantTable;
class CharTitleTable;
class CashItemTable;
class TableContainer
{
public:
	enum eTABLE
	{
		// Character
		TABLE_EXP = 0,
		TABLE_HELP,
		TABLE_MERCHANT,
		TABLE_MERCHANT2,
		TABLE_MOB,
		TABLE_NEWBIE,
		TABLE_NPC,
		TABLE_PC,
		TABLE_STATUS_TRANSFORM,
		TABLE_GAME_MANIA_TIME,
		TABLE_GUIDE_HINT,

		// Item
		TABLE_BASIC_DROP,
		TABLE_ITEM_OPTION,
		TABLE_ITEM,
		TABLE_LEGENDARY_DROP,
		TABLE_NORMAL_DROP,
		TABLE_SUPERIOR_DROP,
		TABLE_USE_ITEM,
		TABLE_USE_ITEM2,
		TABLE_SET_ITEM,
		TABLE_DRAGONBALL,
		TABLE_DRAGONBALL_REWARD,

		// Misc
		TABLE_MASCOT,
		TABLE_ACTION,
		TABLE_CHAT_COMMAND,
		TABLE_DIRECTION_LINK,
		TABLE_FORMULA,

		// Party
		TABLE_CHARM,

		// Quest
		TABLE_QUEST_DROP,
		TABLE_QUEST_ITEM,
		TABLE_QUEST_PROBABILITY,
		TABLE_QUEST_PROBABILITY2,
		TABLE_QUEST_TEXT_DATA,
		TABLE_QUEST_REWARD,

		// Rule
		TABLE_RANKBATTLE,
		TABLE_TIMEQUEST,
		TABLE_BUDOKAI,

		// Skill
		TABLE_HTB_SET,
		TABLE_SKILL,
		TABLE_SYSTEM_EFFECT,

		// Text
		TABLE_TEXT_ALL,
		TABLE_CHATTING_FILTER,
		TABLE_TEXT_SERVER,

		// World
		TABLE_LAND_MARK,
		TABLE_OBJECT,
		TABLE_NPC_SPAWN,
		TABLE_MOB_SPAWN,
		TABLE_WORLD_MAP,
		TABLE_WORLD,
		TABLE_WORLD_ZONE,
		TABLE_WORLD_PLAY,

		// GraphicData
		TABLE_MODEL_TOOL_CHAR,
		TABLE_MODEL_TOOL_OBJ,

		// World Data
		TABLE_PASS_POINT,

		// Portal Data
		TABLE_PORTAL,

		TABLE_SPEECH,

		TABLE_EACH_DROP,
		TABLE_TYPE_DROP,

		TABLE_SCRIPT_LINK,
		TABLE_EXCELLENT_DROP,
		TABLE_DUNGEON,

		TABLE_QUEST_NARRATION,

		TABLE_VEHICLE,
		TABLE_ITEM_RECIPE,
		TABLE_DYNAMIC_OBJECT,
		TABLE_MOB_MOVE_PATTERN,
		TABLE_DOJO,
		TABLE_ITEM_UPGRADE,
		TABLE_MIX_MACHINE,

		TABLE_HLS_MERCHANT,
		TABLE_HLS_ITEM,

		//Server Data
		TABLE_NPC_SERVER,
		TABLE_MOB_SERVER,

		TABLE_CHAR_TITLE,
		TABLE_CASHITEM_TABLE,

		TABLE_COUNT
	};
	virtual ~TableContainer();
	TableContainer();
	class ICallBack
	{
	public:
		virtual bool Call(const char* pfilename, FileSerializer* pSeralize, const char* pszCryptPassword) = 0;
	};

	typedef std::map<TBLIDX, SpawnTable*> SPAWNTABLEMAP;
	typedef SPAWNTABLEMAP::iterator SPAWNTABLEIT;
	typedef SPAWNTABLEMAP::value_type SPAWNTABLEVAL;

	typedef std::map<TBLIDX, ObjectTable*> OBJTABLEMAP;
	typedef OBJTABLEMAP::iterator OBJTABLEIT;
	typedef OBJTABLEMAP::value_type OBJTABLEVAL;

	bool Create(CNtlBitFlagManager& rTableFlag, char* pszPath, TableFileNameList* pFileNameList, eLOADING_METHOD eLoadingMethod, DWORD dwCodePage, ICallBack* pCall);
	bool Create(CNtlBitFlagManager& rTableFlag, WCHAR* pwszPath, TableFileNameList* pFileNameList, eLOADING_METHOD eLoadingMethod, DWORD dwCodePage, ICallBack* pCall);
	void Destroy();
	bool Reload(CNtlBitFlagManager& rTableFlag, TableFileNameList* pFileNameList);
	bool SaveToFile(CNtlBitFlagManager& rTableFlag, TableFileNameList* pFileNameList, bool bNeedToEncrypt);
	void SetPath(char* pszPath);
	void SetPath(WCHAR* pwszPath) { m_wstrPath = pwszPath; }


	// Character
	ExpTable* GetExpTable() { return m_pExpTable; }
	GuideHintTable* GetGuideHintTable() { return m_pGuideHintTable; }
	HelpTable* GetHelpTable() { return m_pHelpTable; }
	MerchantTable* GetMerchantTable() { return m_pMerchantTable; }
	MerchantTable2* GetMerchantTable2() { return m_pMerchantTable2; }
	MobTable* GetMobTable() { return m_pMobTable; }
	NewbieTable* GetNewbieTable() { return m_pNewbieTable; }
	NPCTable* GetNpcTable() { return m_pNpcTable; }
	PCTable* GetPcTable() { return m_pPcTable; }
	StatusTransformTable* GetStatusTransformTable() { return m_pStatusTransformTable; }
	GameManiaTimeTable* GetGameManiaTimeTable() { return m_pGameManiaTimeTable; }

	// Item
	BasicDropTable* GetBasicDropTable() { return m_pBasicDropTable; }
	DragonBallRewardTable* GetDragonBallRewardTable() { return m_pDragonBallRewardTable; }
	DragonBallTable* GetDragonBallTable() { return m_pDragonBallTable; }
	ItemOptionTable* GetItemOptionTable() { return m_pItemOptionTable; }
	ItemTable* GetItemTable() { return m_pItemTable; }
	LegendaryDropTable* GetLegendaryDropTable() { return m_pLegendaryDropTable; }
	NormalDropTable* GetNormalDropTable() { return m_pNormalDropTable; }
	SuperiorDropTable* GetSuperiorDropTable() { return m_pSuperiorDropTable; }
	UseItemTable* GetUseItemTable() { return m_pUseItemTable; }
	UseItemTable2* GetUseItemTable2() { return m_pUseItemTable2; }
	SetItemTable* GetSetItemTable() { return m_pSetItemTable; }
	EachDropTable* GetEachDropTable() { return m_pEachDropTable; }
	TypeDropTable* GetTypeDropTable() { return m_pTypeDropTable; }
	ExcellentDropTable* GetExcellentDropTable() { return m_pExcellentDropTable; }

	// Misc
	TableMascot* GetTableMascot() { return m_pTableMascot; }
	ActionTable* GetActionTable() { return m_pActionTable; }
	ChatCommandTable* GetChatCommandTable() { return m_pChatCommandTable; }
	DirectionLinkTable* GetDirectionLinkTable() { return m_pDirectionLinkTable; }
	FormulaTable* GetFormulaTable() { return m_pFormulaTable; }

	// Party
	CharmTable* GetCharmTable() { return m_pCharmTable; }

	// Quest
	QuestDropTable* GetQuestDropTable() { return m_pQuestDropTable; }
	QuestItemTable* GetQuestItemTable() { return m_pQuestItemTable; }
	QuestProbabilityTable* GetQuestProbabilityTable() { return m_pQuestProbalityTable; }
	QuestProbabilityTable2* GetQuestProbabilityTable2() { return m_pQuestProbalityTable2; }
	QuestTextDataTable* GetQuestTextDataTable() { return m_pQuestTextDataTable; }
	QuestRewardTable* GetQuestRewardTable() { return m_pQuestRewardTable; }

	// Rule
	RankBattleTable* GetRankBattleTable() { return m_pRankBattleTable; }
	TimeQuestTable* GetTimeQuestTable() { return m_pTimeQuestTable; }
	BudokaiTable* GetBudokaiTable() { return m_pBudokaiTable; }
	DungeonTable* GetDungeonTable() { return m_pDungeonTable; }

	// Skill
	HTBSetTable* GetHTBSetTable() { return m_pHTBSetTable; }
	SkillTable* GetSkillTable() { return m_pSkillTable; }
	SystemEffectTable* GetSystemEffectTable() { return m_pSystemEffectTable; }

	// Text
	TextAllTable* GetTextAllTable() { return m_pTextAllTable; }
	ChattingFilterTable* GetChattingFilterTable() { return m_pChattingFilterTable; }
	TextServerTable* GetTextServerTable() { return m_pTextServerTable; }

	// World
	LandMarkTable* GetLandMarkTable() { return m_pLandMarkTable; }
	ObjectTable* GetObjectTable(TBLIDX worldTblidx);
	SpawnTable* GetNpcSpawnTable(TBLIDX worldTblidx);
	SpawnTable* GetMobSpawnTable(TBLIDX worldTblidx);
	WorldMapTable* GetWorldMapTable() { return m_pWorldMapTable; }
	WorldTable* GetWorldTable() { return m_pWorldTable; }
	WorldZoneTable* GetWorldZoneTable() { return m_pWorldZoneTable; }

	// World Data
	WorldPathTable* GetWorldPathTable() { return m_pWorldPathTable; }
	WorldPlayTable* GetWorldPlayTable() { return m_pWorldPlayTable; }

	// Portal Data
	PortalTable* GetPortalTable() { return m_pPortalTable; }

	// Other Systems
	NpcSpeechTable* GetNpcSpeechTable() { return m_pNpcSpeechTable; }
	ScriptLinkTable* GetScriptLinkTable() { return m_pScriptLinkTable; }
	QuestNarrationTable* GetQuestNarrationTable() { return m_pQuestNarrationTable; }
	VehicleTable* GetVehicleTable() { return m_pVehicleTable; }
	ItemRecipeTable* GetItemRecipeTable() { return m_pItemRecipeTable; }
	DynamicObjectTable* GetDynamicObjectTable() { return m_pDynamicObjectTable; }
	MobMovePatternTable* GetMobMovePatternTable() { return m_pMobMovePatternTable; }
	DojoTable* GetDojoTable() { return m_pDojoTable; }
	ItemUpgradeTable* GetItemUpgradeTable() { return m_pItemUpgradeTable; }
	ItemMixMachineTable* GetItemMixMachineTable() { return m_pItemMixMachineTable; }
	HLSItemTable* GetHLSItemTable() { return m_pHLSItemTable; }
	HLSMerchantTable* GetHLSMerchantTable() { return m_pHLSMerchantTable; }
	CharTitleTable* GetCharTitleTable() { return m_pCharTitleTable; }
	CashItemTable* GetCashItemTable() { return m_pCashItemTable; }

	OBJTABLEIT BeginObjectTable();
	OBJTABLEIT EndObjectTable();
	SPAWNTABLEIT BeginNpcSpawnTable();
	SPAWNTABLEIT EndNpcSpawnTable();
	SPAWNTABLEIT BeginMobSpawnTable();
	SPAWNTABLEIT EndMobSpawnTable();

protected:
	void Init();

	bool InitializeTable(Table* pTable, FileSerializer& serializer, char* pszFileNameWithoutExtension, ICallBack* pCall);
	bool InitializeTable(Table* pTable, FileSerializer& serializer, WCHAR* pwszFileNameWithoutExtension, ICallBack* pCall);
	bool InitializeTable(TextAllTable* pTextAllTable, FileSerializer& serializer, char* pszFileNameWithoutExtension, ICallBack* pCall);
	bool InitializeTable(TextAllTable* pTextAllTable, FileSerializer& serializer, WCHAR* pwszFileNameWithoutExtension, ICallBack* pCall);
	bool InitializePackTable(Table* pTable, FileSerializer& serializer, WCHAR* pszFileNameWithoutExtension, ICallBack* pCall);
	bool InitializePackTable(Table* pTable, FileSerializer& serializer, char* pszFileNameWithoutExtension, ICallBack* pCall);
	bool InitializePackTable(TextAllTable* pTextAllTable, FileSerializer& serializer, WCHAR* pszFileNameWithoutExtension, ICallBack* pCall);
	bool InitializePackTable(TextAllTable* pTextAllTable, FileSerializer& serializer, char* pszFileNameWithoutExtension, ICallBack* pCall);
	bool ReloadTable(Table* pTable, FileSerializer& serializer, char* pwszFileNameWithoutExtension);
	bool ReloadTable(Table* pTable, FileSerializer& serializer, WCHAR* pwszFileNameWithoutExtension);

	std::wstring m_wstrPath;
	eLOADING_METHOD m_eLoadingMethod;
	DWORD m_dwCodePage;

	// Character
	ExpTable* m_pExpTable;
	GuideHintTable* m_pGuideHintTable;
	HelpTable* m_pHelpTable;
	MerchantTable* m_pMerchantTable;
	MerchantTable2* m_pMerchantTable2;
	MobTable* m_pMobTable;
	NewbieTable* m_pNewbieTable;
	NPCTable* m_pNpcTable;
	PCTable* m_pPcTable;
	StatusTransformTable* m_pStatusTransformTable;
	GameManiaTimeTable* m_pGameManiaTimeTable;

	// Item
	BasicDropTable* m_pBasicDropTable;
	DragonBallRewardTable* m_pDragonBallRewardTable;
	DragonBallTable* m_pDragonBallTable;
	ItemOptionTable* m_pItemOptionTable;
	ItemTable* m_pItemTable;
	LegendaryDropTable* m_pLegendaryDropTable;
	NormalDropTable* m_pNormalDropTable;
	SuperiorDropTable* m_pSuperiorDropTable;
	UseItemTable* m_pUseItemTable;
	UseItemTable2* m_pUseItemTable2;
	SetItemTable* m_pSetItemTable;
	EachDropTable* m_pEachDropTable;
	TypeDropTable* m_pTypeDropTable;
	ExcellentDropTable* m_pExcellentDropTable;

	// Misc
	TableMascot* m_pTableMascot;
	ActionTable* m_pActionTable;
	ChatCommandTable* m_pChatCommandTable;
	DirectionLinkTable* m_pDirectionLinkTable;
	FormulaTable* m_pFormulaTable;

	// Party
	CharmTable* m_pCharmTable;

	// Quest
	QuestDropTable* m_pQuestDropTable;
	QuestItemTable* m_pQuestItemTable;
	QuestProbabilityTable* m_pQuestProbalityTable;
	QuestProbabilityTable2* m_pQuestProbalityTable2;
	QuestTextDataTable* m_pQuestTextDataTable;
	QuestRewardTable* m_pQuestRewardTable;

	// Rule
	RankBattleTable* m_pRankBattleTable;
	TimeQuestTable* m_pTimeQuestTable;
	BudokaiTable* m_pBudokaiTable;
	DungeonTable* m_pDungeonTable;

	// Skill
	HTBSetTable* m_pHTBSetTable;
	SkillTable* m_pSkillTable;
	SystemEffectTable* m_pSystemEffectTable;

	// Text
	TextAllTable* m_pTextAllTable;
	ChattingFilterTable* m_pChattingFilterTable;
	TextServerTable* m_pTextServerTable;

	// World
	LandMarkTable* m_pLandMarkTable;
	WorldMapTable* m_pWorldMapTable;
	WorldTable*	m_pWorldTable;
	WorldZoneTable*	m_pWorldZoneTable;
	WorldPlayTable*	m_pWorldPlayTable;

	// World Maps
	OBJTABLEMAP	m_mapObjectTable;
	SPAWNTABLEMAP m_mapNpcSpawnTable;
	SPAWNTABLEMAP m_mapMobSpawnTable;

	// World Data
	WorldPathTable* m_pWorldPathTable;

	// Portal Data
	PortalTable* m_pPortalTable;

	// Other Systems Table
	NpcSpeechTable* m_pNpcSpeechTable;
	ScriptLinkTable* m_pScriptLinkTable;
	QuestNarrationTable* m_pQuestNarrationTable;
	VehicleTable* m_pVehicleTable;
	ItemRecipeTable* m_pItemRecipeTable;
	DynamicObjectTable* m_pDynamicObjectTable;
	MobMovePatternTable* m_pMobMovePatternTable;
	DojoTable* m_pDojoTable;
	ItemUpgradeTable* m_pItemUpgradeTable;
	ItemMixMachineTable* m_pItemMixMachineTable;
	HLSItemTable* m_pHLSItemTable;
	HLSMerchantTable* m_pHLSMerchantTable;
	CharTitleTable* m_pCharTitleTable;
	CashItemTable* m_pCashItemTable;
};

// Table container singleton
#define sTBM AKCore::Singleton<TableContainer>::Instance()