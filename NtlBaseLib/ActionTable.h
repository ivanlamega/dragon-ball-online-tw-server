#pragma once

#include "Table.h"

const DWORD		DBO_MAX_LENGTH_ACTION_ICON_NAME = 32;

#pragma pack(push, 4)
struct sACTION_TBLDAT : public sTBLDAT
{
	sACTION_TBLDAT()
	{
		bValidity_Able = true;
	};

public:
	bool			bValidity_Able;
	BYTE			byAction_Type;
	TBLIDX			Action_Name;
	char			szIcon_Name[DBO_MAX_LENGTH_ACTION_ICON_NAME + 1];
	TBLIDX			Note;
	TBLIDX			chat_Command_Index;
	BYTE			byETC_Action_Type;

protected:
	virtual int GetDataSize()
	{
		return sizeof(*this) - sizeof(void*);
	}
};
#pragma pack(pop)

enum eACTION_TYPE
{
	ACTION_TYPE_NORMAL_ACTION = 1,
	ACTION_TYPE_SOCIAL_ACTION,

	ACTION_TYPE_COUNT,

	ACTION_TYPE_UNKNOWN = 0xFF,

	ACTION_TYPE_FIRST = ACTION_TYPE_NORMAL_ACTION,
	ACTION_TYPE_LAST = ACTION_TYPE_SOCIAL_ACTION
};

enum eACTION_FUNC_TYPE
{
	ACTION_FUNC_TYPE_SCOUTER_USE = 0,
	ACTION_FUNC_TYPE_PC_SHOP_OPEN,
	ACTION_FUNC_TYPE_NORMAL_DICE_OPEN,
	ACTION_FUNC_TYPE_BASIC_ATTACK,
	ACTION_FUNC_TYPE_ASSIST,
	ACTION_FUNC_TYPE_GET_ITEM,
	ACTION_FUNC_TYPE_RELAX_ACTION,
};

enum eACTION_FUNC_TYPE_BIT_FLAG
{
	ACTION_FUNC_TYPE_BIT_FLAG_SCOUTER_USE = 0x01 << ACTION_FUNC_TYPE_SCOUTER_USE,
	ACTION_FUNC_TYPE_BIT_FLAG_PC_SHOP_OPEN = 0x01 << ACTION_FUNC_TYPE_PC_SHOP_OPEN,
	ACTION_FUNC_TYPE_BIT_FLAG_NORMAL_DICE_OPEN = 0x01 << ACTION_FUNC_TYPE_NORMAL_DICE_OPEN,
	ACTION_FUNC_TYPE_BIT_FLAG_BASIC_ATTACK = 0x01 << ACTION_FUNC_TYPE_BASIC_ATTACK,
	ACTION_FUNC_TYPE_BIT_FLAG_ASSIST = 0x01 << ACTION_FUNC_TYPE_ASSIST,
	ACTION_FUNC_TYPE_BIT_FLAG_GET_ITEM = 0x01 << ACTION_FUNC_TYPE_GET_ITEM,
	ACTION_FUNC_TYPE_BIT_FLAG_RELAX_ACTION = 0x01 << ACTION_FUNC_TYPE_RELAX_ACTION,
};

class ActionTable : public Table
{
public:
	ActionTable(void);
	virtual ~ActionTable(void);

	bool Create(DWORD dwCodePage);
	void Destroy();

	sTBLDAT* FindData(TBLIDX tblidx);

	virtual bool LoadFromBinary(Serializer& serializer, bool bReload);
	virtual bool SaveToBinary(Serializer& serializer);

protected:
	void Init();

	WCHAR** GetSheetListInWChar() { return &(ActionTable::m_pwszSheetList[0]); }
	void* AllocNewTable(WCHAR* pwszSheetName, DWORD dwCodePage);
	bool DeallocNewTable(void* pvTable, WCHAR* pwszSheetName);
	bool AddTable(void * pvTable, bool bReload);
	bool SetTableData(void* pvTable, WCHAR* pwszSheetName, std::wstring* pstrDataName, BSTR bstrData);

private:
	static WCHAR* m_pwszSheetList[];
};