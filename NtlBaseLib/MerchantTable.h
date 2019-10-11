#pragma once

#include "Table.h"
#include "NtlItem.h"

const DWORD		DBO_MAX_LENGTH_MERCHANT_NAME_TEXT = 16;

#pragma pack(push, 4)
struct sMERCHANT_TBLDAT : public sTBLDAT
{
public:
	WCHAR			wszNameText[DBO_MAX_LENGTH_MERCHANT_NAME_TEXT + 1]; //+1
	BYTE			bySell_Type;
	BYTE			DFAligment;
	TBLIDX			Tab_Name;
	DWORD			dwNeedMileage;

	TBLIDX			aitem_Tblidx[MAX_MERCHANT_COUNT];
	TBLIDX			aRequiredItemID[MAX_MERCHANT_COUNT];
	BYTE			byRequiredItemStack[MAX_MERCHANT_COUNT];
	DWORD			dwRequiredZenny[MAX_MERCHANT_COUNT];
public:
	virtual int GetDataSize()
	{
		return sizeof(*this) - sizeof(void*);
	}
};
#pragma pack(pop)

class MerchantTable : public Table
{
public:
	MerchantTable(void);
	virtual ~MerchantTable(void);

	bool Create(DWORD dwCodePage);
	void Destroy();

protected:
	void Init();

public:
	sTBLDAT* FindData(TBLIDX tblidx);
	static TBLIDX FindMerchantItem(sMERCHANT_TBLDAT* psTbldat, BYTE byIndex);

protected:
	WCHAR** GetSheetListInWChar() { return &(MerchantTable::m_pwszSheetList[0]); }
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