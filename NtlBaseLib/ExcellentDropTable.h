#pragma once

#include "Table.h"
#include "NtlVector.h"
#include "NtlItem.h"

#pragma pack(push, 4)
struct sEXCELLENT_DROP_TBLDAT : public sTBLDAT
{
public:

	TBLIDX		aItem_Tblidx[MAX_EXCELLENT_DROP];
	float		afDrop_Rate[MAX_EXCELLENT_DROP];

public:

	virtual int GetDataSize()
	{
		return sizeof(*this) - sizeof(void*);
	}
};
#pragma pack(pop)

class ExcellentDropTable : public Table
{
public:
	ExcellentDropTable(void);
	virtual ~ExcellentDropTable(void);

	bool Create(DWORD dwCodePage);
	void Destroy();

	sTBLDAT* FindData(TBLIDX tblidx);
	static TBLIDX FindDropIndex(sEXCELLENT_DROP_TBLDAT* psTblData, BYTE byIndex);
	static float FindDropRate(sEXCELLENT_DROP_TBLDAT* psTblData, BYTE byIndex);

	virtual bool LoadFromBinary(Serializer& serializer, bool bReload);
	virtual bool SaveToBinary(Serializer& serializer);

protected:
	void Init();

	WCHAR** GetSheetListInWChar() { return &(ExcellentDropTable::m_pwszSheetList[0]); }
	void* AllocNewTable(WCHAR* pwszSheetName, DWORD dwCodePage);
	bool DeallocNewTable(void* pvTable, WCHAR* pwszSheetName);
	bool AddTable(void * pvTable, bool bReload);
	bool SetTableData(void* pvTable, WCHAR* pwszSheetName, std::wstring* pstrDataName, BSTR bstrData);

private:
	static WCHAR* m_pwszSheetList[];
};