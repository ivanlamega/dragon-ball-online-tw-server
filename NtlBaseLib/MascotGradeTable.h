#pragma once

#include "Table.h"
#pragma pack(push, 4)
struct sMASCOT_GRADE_TBLDAT : public sTBLDAT
{

public:
	//TBLIDX Tblidx;
	DWORD unknown1;
	WORD unknown2;
	WORD unknown3;
	WORD unknown4;
	//WORD padding; -uncomment if problems arise
public:

	virtual int GetDataSize()
	{
		return sizeof(*this) - sizeof(void*);
	}
};
#pragma pack(pop)

class MascotGradeTable : public Table
{
public:

	MascotGradeTable(void);
	virtual ~MascotGradeTable(void);

	bool Create(DWORD dwCodePage);
	void Destroy();

protected:
	void Init();

public:
	sTBLDAT *			FindData(TBLIDX tblidx);

protected:
	WCHAR** GetSheetListInWChar() { return &(MascotGradeTable::m_pwszSheetList[0]); }
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
