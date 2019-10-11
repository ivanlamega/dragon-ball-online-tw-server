#pragma once

#include "Table.h"
#include "NtlVector.h"

const DWORD		DBO_MAX_LENGTH_WORLD_NAME = 32;
const DWORD		DBO_MAX_LENGTH_WORLD_NAME_IN_UNICODE = 32;
const DWORD		DBO_MAX_LENGTH_WORLD_MOB_SPAWN_TABLE_NAME = 64;
const DWORD		DBO_MAX_LENGTH_WORLD_NPC_SPAWN_TABLE_NAME = 64;
const DWORD		DBO_MAX_LENGTH_WORLD_OBJ_SPAWN_TABLE_NAME = 64;
const DWORD		DBO_MAX_LENGTH_WORLD_RESOURCE_FOLDER_NAME = 64;
const DWORD		DBO_MAX_LENGTH_WORLD_RESOURCE_FLASH_NAME = 32;

#pragma pack(push, 4)
struct sWORLD_TBLDAT : public sTBLDAT
{
public:

	char			szName[DBO_MAX_LENGTH_WORLD_NAME + 1];
	WCHAR			wszName[DBO_MAX_LENGTH_WORLD_NAME_IN_UNICODE + 1];
	bool			bDynamic;
	DWORD			nCreateCount;
	BYTE			byDoorType;
	WORD			wUnknown1;
	BYTE			byUnknown1;
	DWORD			dwDestroyTimeInMilliSec;

	//	std::wstring	wstrMobSpawn_Table_Name;
	WCHAR			wszMobSpawn_Table_Name[DBO_MAX_LENGTH_WORLD_MOB_SPAWN_TABLE_NAME + 1];
	//	std::wstring	wstrNpcSpawn_Table_Name;
	WCHAR			wszNpcSpawn_Table_Name[DBO_MAX_LENGTH_WORLD_NPC_SPAWN_TABLE_NAME + 1];
	//	std::wstring	wstrObjSpawn_Table_Name;
	WCHAR			wszObjSpawn_Table_Name[DBO_MAX_LENGTH_WORLD_OBJ_SPAWN_TABLE_NAME + 1];

	CNtlVector		vStart;
	CNtlVector		vEnd;

	CNtlVector		vStandardLoc;

	CNtlVector		vBattleStartLoc;
	CNtlVector		vBattleEndLoc;

	CNtlVector		vOutSideBattleStartLoc;
	CNtlVector		vOutSideBattleEndLoc;

	CNtlVector		vSpectatorStartLoc;
	CNtlVector		vSpectatorEndLoc;

	CNtlVector		UnknownLoc;
	CNtlVector		UnknownDir;

	CNtlVector		vDefaultLoc;
	CNtlVector		vDefaultDir;

	CNtlVector		vStart1Loc;
	CNtlVector		vStart1Dir;

	CNtlVector		vStart2Loc;
	CNtlVector		vStart2Dir;

	CNtlVector		UnknownVec[4];


	float			fSplitSize;
	bool			bNight_Able;
	BYTE			byStatic_Time;


	WORD			wFuncFlag;

	BYTE			byWorldRuleType;	// eGAMERULE_TYPE
	TBLIDX			worldRuleTbldx;		// 해당하는 룰 테이블 인덱스 ( 룰마다 테이블 틀림 : 랭크배틀/타임퀘스트/ 등등... )

	TBLIDX			outWorldTblidx;
	CNtlVector		outWorldLoc;
	CNtlVector		outWorldDir;
	WCHAR			wszResourceFolder[DBO_MAX_LENGTH_WORLD_RESOURCE_FOLDER_NAME + 1];
	float			fBGMRestTime;
	uint32_t		dwWorldResourceID;
	float			fFreeCamera_Height;

	WCHAR			wszEnterResourceFlash[DBO_MAX_LENGTH_WORLD_RESOURCE_FLASH_NAME + 1];
	WCHAR			wszLeaveResourceFlash[DBO_MAX_LENGTH_WORLD_RESOURCE_FLASH_NAME + 1];

	TBLIDX			wpsLinkIndex;

	uint8_t unknown3[11];
	uint32_t unknown4;
protected:

	virtual int GetDataSize()
	{
		return sizeof(*this) - sizeof(void*);
	}
};
#pragma pack(pop)

class WorldTable : public Table
{
public:

	WorldTable(void);
	virtual ~WorldTable(void);

	/*
	public:

	BOOL				Check() { return TRUE; }*/

	bool Create(DWORD dwCodePage);
	void Destroy();

protected:
	void Init();

public:
	sTBLDAT *			FindData(TBLIDX tblidx);

protected:
	WCHAR** GetSheetListInWChar() { return &(WorldTable::m_pwszSheetList[0]); }
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
