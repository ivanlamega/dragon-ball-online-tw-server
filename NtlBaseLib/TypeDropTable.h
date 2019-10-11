#pragma once

#include "Table.h"
#include "NtlVector.h"
#include "NtlItem.h"

#pragma pack(push, 4)
struct sTYPE_DROP_TBLDAT : public sTBLDAT
{
public:

	TBLIDX		aItem_Tblidx[MAX_TYPE_DROP];
	float		afDrop_Rate[MAX_TYPE_DROP];

protected:

	virtual int GetDataSize()
	{
		return sizeof(*this) - sizeof(void*);
	}
};
#pragma pack(pop)

class TypeDropTable : public Table
{
public:
	TypeDropTable(void);
	virtual ~TypeDropTable(void);

	bool Create(DWORD dwCodePage);
	void Destroy();

	sTBLDAT* FindData(TBLIDX tblidx);
	static TBLIDX FindDropIndex(sTYPE_DROP_TBLDAT* psTblData, BYTE byIndex);
	static float FindDropRate(sTYPE_DROP_TBLDAT* psTblData, BYTE byIndex);

	virtual bool LoadFromBinary(Serializer& serializer, bool bReload);
	virtual bool SaveToBinary(Serializer& serializer);

protected:
	void Init();

	WCHAR** GetSheetListInWChar() { return &(TypeDropTable::m_pwszSheetList[0]); }
	void* AllocNewTable(WCHAR* pwszSheetName, DWORD dwCodePage);
	bool DeallocNewTable(void* pvTable, WCHAR* pwszSheetName);
	bool AddTable(void * pvTable, bool bReload);
	bool SetTableData(void* pvTable, WCHAR* pwszSheetName, std::wstring* pstrDataName, BSTR bstrData);

private:
	static WCHAR* m_pwszSheetList[];
};