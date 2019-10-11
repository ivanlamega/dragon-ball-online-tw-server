#pragma once

#include "Table.h"
#include "NtlItem.h"

const DWORD		DBO_MAX_COUNT_RECIPE_CREATE_ITEM = 3;

#pragma pack(push, 4)

struct sRECIPE_CREATE_DATA
{
	TBLIDX	itemTblidx;			// 재료테이블 인덱스 INVALID_
	BYTE	itemRate;
	TBLIDX	itemTblidxGreate;
};

struct sRECIPE_MATERIAL_DATA
{
	TBLIDX	materialTblidx;			// 재료테이블 인덱스 INVALID_
	BYTE	byMaterialCount;
};

struct sITEM_RECIPE_TBLDAT : public sTBLDAT
{
	sITEM_RECIPE_TBLDAT()
	{
		bValidityAble = true;
	};
public:
	bool						bValidityAble;
	DWORD						dwName;
	BYTE						byRecipeType;
	BYTE						byNeedMixLevel;
	DWORD						dwNeedMixZenny;
	sRECIPE_CREATE_DATA 		asCreateItemTblidx[DBO_MAX_COUNT_RECIPE_CREATE_ITEM];
	TBLIDX						createJunkTblidx;
	sRECIPE_MATERIAL_DATA		asMaterial[DBO_MAX_COUNT_RECIPE_MATERIAL_ITEM];

public:
	virtual int GetDataSize()
	{
		return sizeof(*this) - sizeof(void*);
	}
};
#pragma pack(pop)

class ItemRecipeTable : public Table
{
public:
	ItemRecipeTable(void);
	virtual ~ItemRecipeTable(void);

	bool Create(DWORD dwCodePage);
	void Destroy();

	sTBLDAT* FindData(TBLIDX tblidx);

	virtual bool LoadFromBinary(Serializer& serializer, bool bReload);
	virtual bool SaveToBinary(Serializer& serializer);

protected:
	void Init();

	WCHAR** GetSheetListInWChar() { return &(ItemRecipeTable::m_pwszSheetList[0]); }
	void* AllocNewTable(WCHAR* pwszSheetName, DWORD dwCodePage);
	bool DeallocNewTable(void* pvTable, WCHAR* pwszSheetName);
	bool AddTable(void * pvTable, bool bReload);
	bool SetTableData(void* pvTable, WCHAR* pwszSheetName, std::wstring* pstrDataName, BSTR bstrData);

private:
	static WCHAR* m_pwszSheetList[];
};