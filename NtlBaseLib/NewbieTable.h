#pragma once

#include "Table.h"
#include "NtlVector.h"
#include "NtlCharacter.h"

#pragma pack(push, 4)
struct sNEWBIE_TBLDAT : public sTBLDAT
{
public:

	BYTE			byRace;
	BYTE			byClass;
	WORLDID			world_Id;
	TBLIDX			tutorialWorld;
	CNtlVector      vSpawn_Loc;
	CNtlVector      vSpawn_Dir;
	CNtlVector      vBind_Loc;
	CNtlVector      vBind_Dir;
	TBLIDX			aitem_Tblidx[MAX_NEWBIE_ITEM];
	BYTE			abyPos[MAX_NEWBIE_ITEM];
	BYTE			abyStack_Quantity[MAX_NEWBIE_ITEM];
	TBLIDX			mapNameTblidx;
	TBLIDX			aSkillTblidx[MAX_NEWBIE_SKILL];
	sNEWBIE_QUICKSLOT_DATA	asQuickData[MAX_NEWBIE_QUICKSLOT_COUNT];
	PORTALID		defaultPortalTblidx;
	PORTALID		defaultPortalTblidx1;
	PORTALID		defaultPortalTblidx2;

	TBLIDX			qItemTblidx1;
	BYTE			byQPosition1;
	BYTE			byQStackQuantity1;

	uint8_t unknown3;	/* 0x01 ? */
	uint8_t unknown4;	/* 0x00 ? */
protected:

	virtual int GetDataSize()
	{
		return sizeof(*this) - sizeof(void*);
	}
};
#pragma pack(pop)

class NewbieTable :
	public Table
{
public:
	NewbieTable(void);
public:
	virtual ~NewbieTable(void);

	bool Create(DWORD dwCodePage);
	void Destroy();

protected:
	void Init();

public:
	sTBLDAT *					FindData(TBLIDX tblidx);

	sTBLDAT *					GetNewbieTbldat(BYTE byRace, BYTE byClass);

	bool						SetNewbieTbldat(BYTE byRace, BYTE byClass, sTBLDAT * pTbldat);

protected:
	WCHAR** GetSheetListInWChar() { return &(NewbieTable::m_pwszSheetList[0]); }
	void* AllocNewTable(WCHAR* pwszSheetName, DWORD dwCodePage);
	bool DeallocNewTable(void* pvTable, WCHAR* pwszSheetName);
	bool AddTable(void * pvTable, bool bReload);
	bool SetTableData(void* pvTable, WCHAR* pwszSheetName, std::wstring* pstrDataName, BSTR bstrData);

public:

	virtual bool				LoadFromBinary(Serializer& serializer, bool bReload);

	virtual bool				SaveToBinary(Serializer& serializer);


protected:

	sTBLDAT *					m_aNewbieTbldat[RACE_COUNT][PC_CLASS_COUNT];

private:
	static WCHAR* m_pwszSheetList[];
};
