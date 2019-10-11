#pragma once

#include "Table.h"
#include "NtlItem.h"
#include "NtlHlsItem.h"

const DWORD		DBO_MAX_LENGTH_HLSITEM_ID_TEXT = 128;
const DWORD		DBO_MAX_LENGTH_HLSITEM_NAME_TEXT = 20;

struct sSUB_ITEM
{
	TBLIDX	itemTblidx;
	BYTE	byStackCount;
};

#pragma pack(push, 4)
struct sHLS_ITEM_TBLDAT : public sTBLDAT
{
public:

	WCHAR            wszName[32 + 1];
	WCHAR            wszCJIProductID[128 + 1];
	WCHAR            wszIcon[32 + 1];
	WORD            wHLSItemType;
	bool            bOnSale;
	BYTE            bySellType;
	BYTE            byDiscount;
	BYTE            byStackCount;//it is Worong correct value are at  >> ItemAmount <<
	bool            bCjVip;
	DWORD           itemTblidx;//HLS item TBLIDX"
	DWORD           itemTblidx2;//HLS Item Name TBLIDX"
	DWORD           itemTblidx3;// Item TBLIDX what we use to get Item on bag
	WORD            wUnknown1;
	DWORD           dwCost;  //This is 100% correct.
	BYTE            wUnk2;
	BYTE            ItemAmount; //This is 100% correct. 
	WORD            wUnk4;
	
	sSUB_ITEM       asSubItem[5]; //These are correct Maybe
	BYTE            bUnk1;
	BYTE            dwUnk1;
	DWORD           bUnk2;
	BYTE            bUnk3;

public:

	virtual int GetDataSize()
	{
		return sizeof(*this) - sizeof(void*);
	}
};
#pragma pack(pop)

class HLSItemTable : public Table
{
public:

	HLSItemTable(void);
	virtual ~HLSItemTable(void);

	bool Create(DWORD dwCodePage);
	void Destroy();

protected:
	void Init();

public:
	sTBLDAT *			FindData(TBLIDX tblidx);

protected:
	WCHAR** GetSheetListInWChar() { return &(HLSItemTable::m_pwszSheetList[0]); }
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