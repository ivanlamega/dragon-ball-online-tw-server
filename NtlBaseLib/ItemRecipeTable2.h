#pragma once

#include "Table.h"
#include "NtlItem.h"
#include "ItemRecipeTable.h"

#pragma pack(push, 4)

struct sITEM_RECIPE_TBLDAT2 : public sITEM_RECIPE_TBLDAT
{


};
#pragma pack(pop)

class ItemRecipeTable2 : public Table
{
public:
	ItemRecipeTable2(void);
	virtual ~ItemRecipeTable2(void);

	bool Create(DWORD dwCodePage);
	void Destroy();

	sTBLDAT* FindData(TBLIDX tblidx);

	virtual bool LoadFromBinary(Serializer& serializer, bool bReload);
	virtual bool SaveToBinary(Serializer& serializer);

protected:
	void Init();

	WCHAR** GetSheetListInWChar() { return &(ItemRecipeTable2::m_pwszSheetList[0]); }
	void* AllocNewTable(WCHAR* pwszSheetName, DWORD dwCodePage);
	bool DeallocNewTable(void* pvTable, WCHAR* pwszSheetName);
	bool AddTable(void * pvTable, bool bReload);
	bool SetTableData(void* pvTable, WCHAR* pwszSheetName, std::wstring* pstrDataName, BSTR bstrData);

private:
	static WCHAR* m_pwszSheetList[];
};