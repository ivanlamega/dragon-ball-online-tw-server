#pragma once

#include "Table.h"
#include "NtlItem.h"
#include "NtlDragonBall.h"

#pragma pack(push, 4)
struct sDRAGONBALL_TBLDAT : public sTBLDAT
{
public:
	DWORD		dwAltarGroup;
	BYTE		byBallType;
	TBLIDX		aBallTblidx[ITEM_MAX_DRAGONBALL];
	TBLIDX		ballDropTblidx;
	TBLIDX		ballJunkTblidx;
	TBLIDX		startDialog;
	TBLIDX      endDialog;
	TBLIDX      hurryDialog;
	TBLIDX		timeoverDialog;
	TBLIDX		noRepeatDialog;
	TBLIDX		dragonNPCTblidx;
	TBLIDX		defaultSummonChat;
	TBLIDX      inventoryFullDialog;
	sVECTOR2	fDir;

protected:
	virtual int GetDataSize()
	{
		return sizeof(*this) - sizeof(void*);
	}
};
#pragma pack(pop)

class DragonBallTable : public Table
{
public:
	DragonBallTable(void);
	virtual ~DragonBallTable(void);

	bool Create(DWORD dwCodePage);
	void Destroy();

	sTBLDAT* FindData(TBLIDX tblidx);
	sTBLDAT* GetDBTbldatByGroup(DWORD dwGroupID);
	bool SetDBTbldatByGroup(DWORD dwGroupID, TBLIDX tblidx);
	sTBLDAT* GetDBTbldat(BYTE byType);
	bool SetDBTbldat(BYTE byType, sTBLDAT * pTbldat);
	bool GetType(UINT uiSerial, OUT BYTE& byType, OUT BYTE& byNumber);
	eDRAGON_BALL_TYPE GetDropItemType(UINT dropTblidx);

	virtual bool LoadFromBinary(Serializer& serializer, bool bReload);
	virtual bool SaveToBinary(Serializer& serializer);

protected:
	void Init();

	WCHAR** GetSheetListInWChar() { return &(DragonBallTable::m_pwszSheetList[0]); }
	void* AllocNewTable(WCHAR* pwszSheetName, DWORD dwCodePage);
	bool DeallocNewTable(void* pvTable, WCHAR* pwszSheetName);
	bool AddTable(void * pvTable, bool bReload);
	bool SetTableData(void* pvTable, WCHAR* pwszSheetName, std::wstring* pstrDataName, BSTR bstrData);

	sTBLDAT* m_aDBTbldat[SCHEDULE_EVENT_TYPE_COUNT];

private:
	typedef std::multimap<DWORD, TBLIDX> DRAGONBALLGROUP;
	typedef DRAGONBALLGROUP::iterator DRAGONBALLGROUP_IT;
	typedef DRAGONBALLGROUP::value_type DRAGONBALLGROUP_VAL;
	DRAGONBALLGROUP	m_dragonGroup;
	static WCHAR* m_pwszSheetList[];
};