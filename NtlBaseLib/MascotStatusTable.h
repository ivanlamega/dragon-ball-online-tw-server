#pragma once

#include "Table.h"

#pragma pack(push, 4)
struct sMASCOT_STATUS_TBLDAT : public sTBLDAT
{

public:
	//TBLIDX Tblidx;
	TBLIDX Unknown_ID;
	DWORD unknownDW;
	BYTE UnknownABY[62];
	BYTE unknownby1;
	BYTE EggModel[33];
	BYTE unknownby2;
	BYTE unknownby3;
	WORD unknownW1;
	WORD unknownW2;
	//WORD padding;
	WORD unknownW3;
	WORD unknownW4;
	WORD unknownW5;
	//WORD padding2;
	WORD unknownW6;
	//WORD padding3;
	DWORD unknownDW2;
	DWORD unknownDW3;
public:

	virtual int GetDataSize()
	{
		return sizeof(*this) - sizeof(void*);
	}
};
#pragma pack(pop)

class MascotStatusTable : public Table
{
public:

	MascotStatusTable(void);
	virtual ~MascotStatusTable(void);

	bool Create(DWORD dwCodePage);
	void Destroy();

protected:
	void Init();

public:
	sTBLDAT *			FindData(TBLIDX tblidx);

protected:
	WCHAR** GetSheetListInWChar() { return &(MascotStatusTable::m_pwszSheetList[0]); }
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