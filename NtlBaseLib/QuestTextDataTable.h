#pragma once

#include <vector>
#include "Table.h"

#pragma pack(push, 4)
struct sQUEST_TEXT_DATA_TBLDAT : public sTBLDAT
{
public:
	std::wstring wstrText;

protected:
	virtual int GetDataSize()
	{
		return sizeof(*this) - sizeof(void*);
	}
};
#pragma pack(pop)

class QuestTextDataTable : public Table
{
public:
	QuestTextDataTable(void);
	virtual ~QuestTextDataTable(void);

	bool Create(DWORD dwCodePage);
	void Destroy();

	sTBLDAT* FindData(TBLIDX tblidx);
	void FindDataRange(TBLIDX tblBegin, TBLIDX tblEnd, std::vector<sQUEST_TEXT_DATA_TBLDAT*>& vecRangeList);

	virtual bool LoadFromBinary(Serializer& serializer, bool bReload);
	virtual bool SaveToBinary(Serializer& serializer);

protected:
	void Init();

	WCHAR** GetSheetListInWChar() { return &(QuestTextDataTable::m_pwszSheetList[0]); }
	void* AllocNewTable(WCHAR* pwszSheetName, DWORD dwCodePage);
	bool DeallocNewTable(void* pvTable, WCHAR* pwszSheetName);
	bool AddTable(void * pvTable, bool bReload);
	bool SetTableData(void* pvTable, WCHAR* pwszSheetName, std::wstring* pstrDataName, BSTR bstrData);

private:
	static WCHAR* m_pwszSheetList[];
};
