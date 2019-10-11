#pragma once

#include "Table.h"

#pragma pack(push, 4)
struct sEXP_TBLDAT : public sTBLDAT
{
public:
	DWORD		dwExp;		// Required exp to become the level from level 1.
	DWORD		dwNeed_Exp;		// Required exp to become the level from the previous level.
	WORD		wUnknown[20];		//No Clue?

public:

	virtual int GetDataSize()
	{
		return sizeof(*this) - sizeof(void*);
	}
};
#pragma pack(pop)

class ExpTable : public Table
{
public:
	ExpTable(void);
	virtual ~ExpTable(void);

	bool Create(DWORD dwCodePage);
	void Destroy();

protected:
	void Init();

public:
	sTBLDAT* FindData(TBLIDX tblidx);

protected:
	WCHAR** GetSheetListInWChar() { return &(ExpTable::m_pwszSheetList[0]); }
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