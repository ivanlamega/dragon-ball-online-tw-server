#pragma once

#include "Table.h"

#pragma pack(push, 4)
struct sCHARM_TBLDAT : public sTBLDAT
{
public:
	WORD				wDrop_Rate;
	WORD				wEXP;
	WORD				wRP_Sharing;
	WORD				wCool_Time;
	WORD				wKeep_Time;
	DWORD				dwKeep_Time_In_Millisecs;
	DWORD				dwNeed_Zenny;
	BYTE				byDice_Min;
	BYTE				byDice_Max;
	BYTE				byCharm_Type_Bit_Flag;

protected:
	virtual int GetDataSize()
	{
		return sizeof(*this) - sizeof(void*);
	}
};
#pragma pack(pop)

class CharmTable : public Table
{
public:
	CharmTable(void);
	virtual ~CharmTable(void);

	bool Create(DWORD dwCodePage);
	void Destroy();

	sTBLDAT* FindData(TBLIDX tblidx);

	virtual bool LoadFromBinary(Serializer& serializer, bool bReload);
	virtual bool SaveToBinary(Serializer& serializer);

protected:
	void Init();

	WCHAR** GetSheetListInWChar() { return &(CharmTable::m_pwszSheetList[0]); }
	void* AllocNewTable(WCHAR* pwszSheetName, DWORD dwCodePage);
	bool DeallocNewTable(void* pvTable, WCHAR* pwszSheetName);
	bool AddTable(void * pvTable, bool bReload);
	bool SetTableData(void* pvTable, WCHAR* pwszSheetName, std::wstring* pstrDataName, BSTR bstrData);

private:
	static WCHAR* m_pwszSheetList[];
};