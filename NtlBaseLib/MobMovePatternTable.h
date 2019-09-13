#pragma once

#include "Table.h"

const DWORD		DBO_MAX_COUNT_MOVE_PATTERN = 64;

#pragma pack(push, 4)
struct sMOVE_PATTERN_TBLDAT : public sTBLDAT
{
public:
	BYTE		abyPattern[DBO_MAX_COUNT_MOVE_PATTERN];

public:

	virtual int GetDataSize()
	{
		return sizeof(*this) - sizeof(void*);
	}
};
#pragma pack(pop)

class MobMovePatternTable : public Table
{
public:
	MobMovePatternTable(void);
	virtual ~MobMovePatternTable(void);

	bool Create(DWORD dwCodePage);
	void Destroy();

	sTBLDAT* FindData(TBLIDX tblidx);

	virtual bool LoadFromBinary(Serializer& serializer, bool bReload);
	virtual bool SaveToBinary(Serializer& serializer);

protected:
	void Init();

	WCHAR** GetSheetListInWChar() { return &(MobMovePatternTable::m_pwszSheetList[0]); }
	void* AllocNewTable(WCHAR* pwszSheetName, DWORD dwCodePage);
	bool DeallocNewTable(void* pvTable, WCHAR* pwszSheetName);
	bool AddTable(void * pvTable, bool bReload);
	bool SetTableData(void* pvTable, WCHAR* pwszSheetName, std::wstring* pstrDataName, BSTR bstrData);

private:
	static WCHAR* m_pwszSheetList[];
};