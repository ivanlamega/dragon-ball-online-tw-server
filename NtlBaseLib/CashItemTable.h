#pragma once

#include "Table.h"
#include "ItemTable.h"
#include "NtlItem.h"

// Hard Coding


#pragma pack(push, 4)
struct sCASHITEM_TBLDAT : public sITEM_TBLDAT
{
	sCASHITEM_TBLDAT()
	{
		bValidity_Able = true;
	};
	
};
#pragma pack(pop)

class CashItemTable : public Table
{
public:

	CashItemTable(void);
	virtual ~CashItemTable(void);

	bool Create(DWORD dwCodePage);
	void Destroy();

protected:
	void Init();

public:
	sTBLDAT *			FindData(TBLIDX tblidx);

protected:
	WCHAR** GetSheetListInWChar() { return &(CashItemTable::m_pwszSheetList[0]); }
	void* AllocNewTable(WCHAR* pwszSheetName, DWORD dwCodePage);
	bool DeallocNewTable(void* pvTable, WCHAR* pwszSheetName);
	bool AddTable(void * pvTable, bool bReload);
	bool SetTableData(void* pvTable, WCHAR* pwszSheetName, std::wstring* pstrDataName, BSTR bstrData);

public:
	virtual bool				LoadFromBinary(Serializer& serializer, bool bReload);
	virtual bool				SaveToBinary(Serializer& serializer);

private:
	static WCHAR* m_pwszSheetList[];
};