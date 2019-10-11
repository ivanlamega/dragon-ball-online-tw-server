#pragma once


#include "table.h"

#pragma pack(push, 4)
struct sDUNGEON_TBLDAT : public sTBLDAT
{
public:
	sDUNGEON_TBLDAT(void) { }

	BYTE			byDungeonType;			// 1:normal 2:hard
	BYTE			byMaxMember;
	TBLIDX			linkWorld;
	BYTE			byMinLevel;
	BYTE			byMaxLevel;
	TBLIDX			needItemTblidx;
	DWORD			dwHonorPoint;
	TBLIDX			wpsTblidx;
	TBLIDX			openCine;

protected:
	virtual int GetDataSize()
	{
		return sizeof(*this) - sizeof(void*);
	}
};
#pragma pack(pop)

class DungeonTable : public Table
{
public:
	DungeonTable(void);
	virtual ~DungeonTable(void);

	virtual bool LoadFromBinary(Serializer& serializer, bool bReload);
	virtual bool SaveToBinary(Serializer& serializer);

	bool Create(DWORD dwCodePage);
	void Destroy(void);

	sTBLDAT* FindData(TBLIDX tblidx);

protected:
	void Init(void);

	WCHAR** GetSheetListInWChar(void) { return &m_pwszSheetList[0]; }
	void* AllocNewTable(WCHAR* pwszSheetName, DWORD dwCodePage);
	bool DeallocNewTable(void* pvTable, WCHAR* pwszSheetName);
	bool AddTable(void* pvTable, bool bReload);
	bool SetTableData(void* pvTable, WCHAR* pwszSheetName, std::wstring* pstrDataName, BSTR bstrData);

protected:
	static WCHAR* m_pwszSheetList[];
};
