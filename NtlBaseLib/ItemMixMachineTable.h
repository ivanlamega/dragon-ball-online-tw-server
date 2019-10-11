#pragma once

#include "Table.h"
#include "NtlItem.h"

const DWORD		DBO_MAX_COUNT_BUILT_IN_RECIPE = 3;

#pragma pack(push, 4)
struct sITEM_MIX_MACHINE_TBLDAT : public sTBLDAT
{
	sITEM_MIX_MACHINE_TBLDAT()
	{
		bValidityAble = true;
	};
public:
	bool						bValidityAble;
	TBLIDX						name;
	BYTE						byMachineType;
	WORD						wFunctionBitFlag;
	BYTE						byMixZennyDiscountRate;
	TBLIDX						dynamicObjectTblidx;
	TBLIDX						aBuiltInRecipeTblidx[DBO_MAX_COUNT_BUILT_IN_RECIPE];

public:
	virtual int GetDataSize()
	{
		return sizeof(*this) - sizeof(void*);
	}
};
#pragma pack(pop)

class ItemMixMachineTable : public Table
{
public:

	ItemMixMachineTable(void);
	virtual ~ItemMixMachineTable(void);

	bool Create(DWORD dwCodePage);
	void Destroy();

	sTBLDAT* FindData(TBLIDX tblidx);

	virtual bool LoadFromBinary(Serializer& serializer, bool bReload);
	virtual bool SaveToBinary(Serializer& serializer);

protected:
	void Init();

	WCHAR** GetSheetListInWChar() { return &(ItemMixMachineTable::m_pwszSheetList[0]); }
	void* AllocNewTable(WCHAR* pwszSheetName, DWORD dwCodePage);
	bool DeallocNewTable(void* pvTable, WCHAR* pwszSheetName);
	bool AddTable(void * pvTable, bool bReload);
	bool SetTableData(void* pvTable, WCHAR* pwszSheetName, std::wstring* pstrDataName, BSTR bstrData);

private:
	static WCHAR* m_pwszSheetList[];
};