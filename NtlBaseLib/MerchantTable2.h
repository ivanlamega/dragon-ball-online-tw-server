#pragma once

#include "Table.h"
#include "NtlItem.h"
#include "MerchantTable.h"


#pragma pack(push, 4)
struct sMERCHANT_TBLDAT2 : public sMERCHANT_TBLDAT
{

};
#pragma pack(pop)

class MerchantTable2 : public Table
{
public:
	MerchantTable2(void);
	virtual ~MerchantTable2(void);

	bool Create(DWORD dwCodePage);
	void Destroy();

protected:
	void Init();

public:
	sTBLDAT* FindData(TBLIDX tblidx);
	static TBLIDX FindMerchantItem(sMERCHANT_TBLDAT2* psTbldat, BYTE byIndex);

protected:
	WCHAR** GetSheetListInWChar() { return &(MerchantTable2::m_pwszSheetList[0]); }
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