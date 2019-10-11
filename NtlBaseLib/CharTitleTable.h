#pragma once
#include "Table.h"

const DWORD		AKCORE_MAX_TITLE_TEXT = 512;

/*
//3132 Bytes total structure
struct sCHAR_TITLE_DATA
{

};*/
#pragma pack(push, 4)
struct sCHAR_TITLE_TBLDAT : public sTBLDAT
{
public:
	TBLIDX     tTitleTblidx;
	WORD       classBitFlags;
	WCHAR      wszIconName[512 + 1];
	WCHAR      wszRewardCond[512 + 1];
	WCHAR      wszUnk3[512 + 1];
	DWORD      dwUnk1;
	DWORD      dwUnk2;
	DWORD      dwUnk3;
	BYTE       byUnk1;
	WORD       wUnk1;
	DWORD      dwUnk4;
	WORD       wUnk2;
	BYTE       byUnk2;
	BYTE       byUnk3;
	DWORD      dwUnkA[4];

public:

	virtual int GetDataSize()
	{
		return sizeof(*this) - sizeof(void*);
	}
};
#pragma pack(pop)

class CharTitleTable : public Table
{
public:

	CharTitleTable(void);
	virtual ~CharTitleTable(void);

	bool Create(DWORD dwCodePage);
	void Destroy();

protected:
	void Init();

public:
	sTBLDAT *			FindData(TBLIDX tblidx);

protected:
	WCHAR** GetSheetListInWChar() { return &(CharTitleTable::m_pwszSheetList[0]); }
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

