#pragma once

#include "Table.h"
#include "NtlVector.h"

const DWORD		DBO_MAX_LENGTH_WORLD_MAP_NAME = 32;
const DWORD		DBO_WORLD_MAP_TABLE_COUNT_WORLD_WARFOG = 8;
#pragma pack(push, 4)
struct sWORLD_MAP_TBLDAT : public sTBLDAT
{
public:
	DWORD           World_Tblidx;
	DWORD           Zone_Tblidx;
	TBLIDX			Worldmap_Name;
	WCHAR           wszName[32 + 1];
	bool			bValidityAble;
	BYTE			byMapType;
	float           vStandardLoc[3];
	float           Worldmap_Scale;
	BYTE            unk[3];
	DWORD           MapID;
	WORD			wWarfog[8];
	WORD            unk2;
	WORD            unk3;
	DWORD           unk4;
	WORD            unk5[3];
public:

	virtual int GetDataSize()
	{
		return sizeof(*this) - sizeof(void*);
	}
};
#pragma pack(pop)

class WorldMapTable : public Table
{
public:
	WorldMapTable(void);
	virtual ~WorldMapTable(void);

	bool Create(DWORD dwCodePage);
	void Destroy();

protected:
	void Init();

public:
	sTBLDAT* FindData(TBLIDX tblidx);

protected:
	WCHAR** GetSheetListInWChar() { return &(WorldMapTable::m_pwszSheetList[0]); }
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