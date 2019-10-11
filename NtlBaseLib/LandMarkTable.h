#pragma once

#include "Table.h"
#include "NtlVector.h"

const DWORD		DBO_MAX_LENGTH_LAND_MARK_NAME = 40;
const DWORD		DBO_MAX_LENGTH_LAND_MARK_ICON_NAME = 32;

#pragma pack(push, 4)
struct sLAND_MARK_TBLDAT : public sTBLDAT
{
public:

	DWORD           RewardItemID[3];//Item craft Reward after disamble
	BYTE            number;//can reward x craft item 
	BYTE            number2;//can reward x craft item 

protected:

	virtual int GetDataSize()
	{
		return sizeof(*this) - sizeof(void*);
	}
};
#pragma pack(pop)

class LandMarkTable : public Table
{
public:
	LandMarkTable(void);
	virtual ~LandMarkTable(void);

	bool Create(DWORD dwCodePage);
	void Destroy();

	sTBLDAT* FindData(TBLIDX tblidx);

	virtual bool LoadFromBinary(Serializer& serializer, bool bReload);
	virtual bool SaveToBinary(Serializer& serializer);

protected:
	void Init();

	WCHAR** GetSheetListInWChar() { return &(LandMarkTable::m_pwszSheetList[0]); }
	void* AllocNewTable(WCHAR* pwszSheetName, DWORD dwCodePage);
	bool DeallocNewTable(void* pvTable, WCHAR* pwszSheetName);
	bool AddTable(void * pvTable, bool bReload);
	bool SetTableData(void* pvTable, WCHAR* pwszSheetName, std::wstring* pstrDataName, BSTR bstrData);

private:
	static WCHAR* m_pwszSheetList[];
};