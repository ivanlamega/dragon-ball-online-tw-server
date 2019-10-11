#pragma once

#include "Table.h"

#pragma pack(push, 4)
struct sTEXT_TBLDAT : public sTBLDAT
{
	sTEXT_TBLDAT()
	{
		wstrText = L"";
	}

	std::wstring wstrText;

};
#pragma pack(pop)

class TextTable : public Table
{
public:
	enum TYPE { INDEX, TEXT };

	TextTable(VOID);
	virtual ~TextTable(VOID);

	BOOL	Create(DWORD dwCodePage, INT nField, INT nType);
	VOID	Destroy(VOID);

protected:
	VOID	Init(VOID);

public:
	sTBLDAT*		FindData(TBLIDX tblidx);
	std::wstring&	GetText(TBLIDX tblidx);
	BOOL			GetText(TBLIDX tblidx, std::wstring* pwstr);

protected:
	WCHAR**	GetSheetListInWChar(VOID) { return &(TextTable::m_pwszSheetList[0]); }
	VOID*	AllocNewTable(WCHAR* pwszSheetName, DWORD dwCodePage);
	bool	DeallocNewTable(VOID* pvTable, WCHAR* pwszSheetName);
	bool	AddTable(VOID* pvTable, bool bReload);
	bool	SetTableData(VOID* pvTable, WCHAR* pwszSheetName, TYPE eType, BSTR bstrData);
	bool	SetTableData(void* pvTable, WCHAR* pwszSheetName, std::wstring* pstrDataName, BSTR bstrData);


public:


	virtual bool				LoadFromBinary(Serializer& serializer, bool bReload);

	virtual bool				SaveToBinary(Serializer& serializer);


protected:

	virtual bool				InitializeFromXmlDoc(XMLDoc* pXmlDoc, WCHAR* pwszFileName, bool bReload);


private:
	static	WCHAR* m_pwszSheetList[];

	INT		m_nField;
	INT		m_nType;
};

class CMapNameTextTable : public TextTable
{
public:
	BOOL	GetZoneName(TBLIDX tblidx, std::wstring* pwstr);
	BOOL	GetSectorName(TBLIDX tblidx, std::wstring* pwstr);
	BOOL	GetAreaName(TBLIDX tblidx, std::wstring* pwstr);
	std::wstring GetZoneName(TBLIDX tblidx);
	std::wstring GetSectorName(TBLIDX tblidx);
	std::wstring GetAreaName(TBLIDX tblidx);

	VOID GetErrorText(TBLIDX tblidx, std::wstring* pwString);
};

class TextAllTable
{
public:
	enum TABLETYPE
	{
		ACTION_DATA,
		CHAT_COMMMAND_DATA,
		HTB_SET_DATA,
		ITEM_DATA,
		MERCHANT_DATA,
		MOB_DATA,
		NPC_DATA,
		SKILL_DATA,
		SYSTEM_EFFECT,
		USE_ITEM_DATA,
		MAP_NAME,
		OBJECT_DATA,
		QUEST_ITEM_DATA,
		ETC_TEXT,
		HELP_DATA,
		HELP_POPOHINT_DATA,
		DRAGON_BALL,
		DB_REWARD,
		TMQ_DATA,
		CS_TEXT,
		MILEPOST,
		FILTERING,
		NPC_DIALOG,
		GM_TOOL,
		DBO_TIP,
		DBO_UNKNOWN,
		DBO_UNKNOWN2,
		DBO_UNKNOWN3,

		TABLE_COUNT
	};

	TextAllTable(VOID);
	~TextAllTable(VOID);

	BOOL	Create(DWORD dwCodePage);
	VOID	Destroy(VOID);

	TextTable*	GetTextTbl(TABLETYPE eType) { return m_pTextTable[eType]; }
	TextTable* GetActionTbl(VOID) { return m_pTextTable[ACTION_DATA]; }
	TextTable* GetChatCommandTbl(VOID) { return m_pTextTable[CHAT_COMMMAND_DATA]; }
	TextTable* GetHTBSetTbl(VOID) { return m_pTextTable[HTB_SET_DATA]; }
	TextTable* GetItemTbl(VOID) { return m_pTextTable[ITEM_DATA]; }
	TextTable* GetMerchantTbl(VOID) { return m_pTextTable[MERCHANT_DATA]; }
	TextTable* GetMobTbl(VOID) { return m_pTextTable[MOB_DATA]; }
	TextTable* GetNPCTbl(VOID) { return m_pTextTable[NPC_DATA]; }
	TextTable* GetSkillTbl(VOID) { return m_pTextTable[SKILL_DATA]; }
	TextTable* GetSystemEffectTbl(VOID) { return m_pTextTable[SYSTEM_EFFECT]; }
	TextTable* GetUseItemTbl(VOID) { return m_pTextTable[USE_ITEM_DATA]; }
	CMapNameTextTable* GetMapNameTbl(VOID) { return reinterpret_cast<CMapNameTextTable*>(m_pTextTable[MAP_NAME]); }
	TextTable* GetObjectTbl(VOID) { return m_pTextTable[OBJECT_DATA]; }
	TextTable* GetQuestItemTbl(VOID) { return m_pTextTable[QUEST_ITEM_DATA]; }
	TextTable* GetETCTbl(VOID) { return m_pTextTable[ETC_TEXT]; }
	TextTable* GetHelpTbl(VOID) { return m_pTextTable[HELP_DATA]; }
	TextTable* GetHelpPopoTbl(VOID) { return m_pTextTable[HELP_POPOHINT_DATA]; }
	TextTable* GetDragonTbl(VOID) { return m_pTextTable[DRAGON_BALL]; }
	TextTable* GetDBRewardTbl(VOID) { return m_pTextTable[DB_REWARD]; }
	TextTable* GetTMQTbl(VOID) { return m_pTextTable[TMQ_DATA]; }
	TextTable* GetCSTextTble(VOID) { return m_pTextTable[CS_TEXT]; }
	TextTable* GetMilePostTable(VOID) { return m_pTextTable[MILEPOST]; }
	TextTable* GetFilteringTable(VOID) { return m_pTextTable[FILTERING]; }
	TextTable* GetNpcDialogTbl(VOID) { return m_pTextTable[NPC_DIALOG]; }
	TextTable* GetGMToolTbl(VOID) { return m_pTextTable[GM_TOOL]; }
	TextTable* GetDBOTipTbl(VOID) { return m_pTextTable[DBO_TIP]; }
public:

	void						Reset();

	bool						LoadFromXml(char* pszFileName);

	bool						LoadFromXml(WCHAR* pwszFileName);

	virtual bool				LoadFromBinary(Serializer& serializer);

	virtual bool				SaveToBinary(Serializer& serializer);


private:
	INT		TypeToField(INT eType);

	TextTable* m_pTextTable[TABLE_COUNT];

	DWORD						m_dwCodePage;
};