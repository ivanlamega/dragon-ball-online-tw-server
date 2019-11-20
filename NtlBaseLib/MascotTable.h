#pragma once

#include "Table.h"

#pragma pack(push, 4)
struct sMASCOT_TBLDAT : public sTBLDAT
{

public:
	//TBLIDX Tblidx;
	TBLIDX UnknownID;
	DWORD unknownDW;
	BYTE unknownABY[64];
	//BYTE unkBY;
	//BYTE unkBY2;
	BYTE EggModel[33];
	BYTE unknownBY;
	BYTE unknownBY2;
	WORD unknownW;
	WORD unknownW2;
public:

	virtual int GetDataSize()
	{
		return sizeof(*this) - sizeof(void*);
	}
};
#pragma pack(pop)

class MascotTable : public Table
{
public:

	MascotTable(void);
	virtual ~MascotTable(void);

	bool Create(DWORD dwCodePage);
	void Destroy();

protected:
	void Init();

public:
	sTBLDAT *			FindData(TBLIDX tblidx);

protected:
	WCHAR** GetSheetListInWChar() { return &(MascotTable::m_pwszSheetList[0]); }
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