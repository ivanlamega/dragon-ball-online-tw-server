#pragma once

#include "Table.h"


#pragma pack(push, 4)
struct sITEM_UPGRADE_TBLDAT : public sTBLDAT
{
	sITEM_UPGRADE_TBLDAT()
	{
	};

public:
	WORD			PysicalValue[15 + 1];
	WORD			EnergyValue[15 + 1];

public:
	virtual int GetDataSize()
	{
		return sizeof(*this) - sizeof(void*);
	}
};
#pragma pack(pop)

class ItemUpgradeTable : public Table
{
public:
	ItemUpgradeTable(void);
	virtual	~ItemUpgradeTable(void);

	bool			Create(DWORD dwCodePage);
	void			Destroy();

	sTBLDAT* FindData(TBLIDX tblidx);

	virtual bool LoadFromBinary(Serializer& serializer, bool bReload);
	virtual bool SaveToBinary(Serializer& serializer);

protected:
	void Init();

	WCHAR** GetSheetListInWChar() { return &(ItemUpgradeTable::m_pwszSheetList[0]); }
	void* AllocNewTable(WCHAR* pwszSheetName, DWORD dwCodePage);
	bool DeallocNewTable(void* pvTable, WCHAR* pwszSheetName);
	bool AddTable(void * pvTable, bool bReload);
	bool SetTableData(void* pvTable, WCHAR* pwszSheetName, std::wstring* pstrDataName, BSTR bstrData);

private:
	static WCHAR* m_pwszSheetList[];
};