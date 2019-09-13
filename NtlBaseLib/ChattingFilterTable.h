#pragma once

#include "Table.h"

const DWORD		DBO_MAX_LENGTH_SLANG = 32;

#pragma pack(push, 4)
struct sCHAT_FILTER_TBLDAT : public sTBLDAT
{
public:
	WCHAR			wszSlangText[DBO_MAX_LENGTH_SLANG + 1];
	TBLIDX			filteringTextIndex;

protected:

	virtual int GetDataSize()
	{
		return sizeof(*this) - sizeof(void*);
	}
};
#pragma pack(pop)

class ChattingFilterTable : public Table
{
public:
	ChattingFilterTable(void);
	virtual ~ChattingFilterTable(void);

	bool Create(DWORD dwCodePage);
	void Destroy();

	sTBLDAT* FindData(TBLIDX tblidx);

	virtual bool LoadFromBinary(Serializer& serializer, bool bReload);
	virtual bool SaveToBinary(Serializer& serializer);

protected:
	void Init();

	WCHAR** GetSheetListInWChar() { return &(ChattingFilterTable::m_pwszSheetList[0]); }
	void* AllocNewTable(WCHAR* pwszSheetName, DWORD dwCodePage);
	bool DeallocNewTable(void* pvTable, WCHAR* pwszSheetName);
	bool AddTable(void * pvTable, bool bReload);
	bool SetTableData(void* pvTable, WCHAR* pwszSheetName, std::wstring* pstrDataName, BSTR bstrData);

private:
	static WCHAR* m_pwszSheetList[];
};