#pragma once

#include "Table.h"

const DWORD MAX_CHAT_COMMAND = 8;

#pragma pack(push, 4)
struct sCHAT_COMMAND_TBLDAT : public sTBLDAT
{
	sCHAT_COMMAND_TBLDAT()
	{
		bValidity_Able = true;
	};

public:
	bool			bValidity_Able;
	WORD			wAction_Animation_Index;
	TBLIDX			aChat_Command[MAX_CHAT_COMMAND];

protected:
	virtual int GetDataSize()
	{
		return sizeof(*this) - sizeof(void*);
	}
};
#pragma pack(pop)

class ChatCommandTable : public Table
{
public:

	ChatCommandTable(void);
	virtual ~ChatCommandTable(void);

	bool Create(DWORD dwCodePage);
	void Destroy();

	sTBLDAT* FindData(TBLIDX tblidx);

	virtual bool LoadFromBinary(Serializer& serializer, bool bReload);
	virtual bool SaveToBinary(Serializer& serializer);

protected:
	void Init();

	WCHAR** GetSheetListInWChar() { return &(ChatCommandTable::m_pwszSheetList[0]); }
	void* AllocNewTable(WCHAR* pwszSheetName, DWORD dwCodePage);
	bool DeallocNewTable(void* pvTable, WCHAR* pwszSheetName);
	bool AddTable(void * pvTable, bool bReload);
	bool SetTableData(void* pvTable, WCHAR* pwszSheetName, std::wstring* pstrDataName, BSTR bstrData);

private:
	static WCHAR* m_pwszSheetList[];
};