#pragma once
#include "Table.h"

const DWORD		DBO_MAX_LENGTH_QUEST_ITEM_ICON_NAME = 32;

enum eQUEST_ITEM_FUNC_TYPE
{
	QUEST_ITEM_FUNC_TYPE_DEL_FORBIDDEN,
};

enum eQUEST_ITEM_FUNC_BIT_FLAG
{
	QUEST_ITEM_FUNC_BIT_FLAG_DEL_FORBIDDEN = 0x01 << QUEST_ITEM_FUNC_TYPE_DEL_FORBIDDEN,
};

// Object
#pragma pack(push, 4)
struct sQUESTITEM_TBLDAT : public sTBLDAT
{
public:
	TBLIDX			ItemName;
	char			szIconName[DBO_MAX_LENGTH_QUEST_ITEM_ICON_NAME + 1];
	TBLIDX			Note;
	BYTE			byFunctionBitFlag;

protected:
	virtual int GetDataSize()
	{
		return sizeof(*this) - sizeof(void*);
	}
};
#pragma pack(pop)

class QuestItemTable : public Table
{
public:
	QuestItemTable(void);
	virtual ~QuestItemTable(void);

	bool Create(DWORD dwCodePage);
	void Destroy(void);

	sTBLDAT* FindData(TBLIDX tblidx);
	
	virtual bool LoadFromBinary(Serializer& serializer, bool bReload);
	virtual bool SaveToBinary(Serializer& serializer);

protected:
	void Init(void);

	WCHAR** GetSheetListInWChar(void) { return &m_pwszSheetList[0]; }
	void* AllocNewTable(WCHAR* pwszSheetName, DWORD dwCodePage);
	bool DeallocNewTable(void* pvTable, WCHAR* pwszSheetName);
	bool AddTable(void* pvTable, bool bReload);
	bool SetTableData(void* pvTable, WCHAR* pwszSheetName, std::wstring* pstrDataName, BSTR bstrData);

	static WCHAR* m_pwszSheetList[];
};
