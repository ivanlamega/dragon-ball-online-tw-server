#pragma once

#include "Table.h"
#include "QuestProbabilityTable.h"
#pragma pack(push, 4)
struct sQUEST_PROBABILITY_TBLDAT2 : public sQUEST_PROBABILITY_TBLDAT
{


};
#pragma pack(pop)

class QuestProbabilityTable2 :
	public Table
{
public:
	QuestProbabilityTable2(void);
	virtual ~QuestProbabilityTable2(void);

	bool Create(DWORD dwCodePage);
	void Destroy();

	sTBLDAT* FindData(TBLIDX tblidx);

	virtual bool LoadFromBinary(Serializer& serializer, bool bReload);
	virtual bool SaveToBinary(Serializer& serializer);

protected:
	void Init();

	WCHAR** GetSheetListInWChar() { return &(QuestProbabilityTable2::m_pwszSheetList[0]); }
	void* AllocNewTable(WCHAR* pwszSheetName, DWORD dwCodePage);
	bool DeallocNewTable(void* pvTable, WCHAR* pwszSheetName);
	bool AddTable(void * pvTable, bool bReload);
	bool SetTableData(void* pvTable, WCHAR* pwszSheetName, std::wstring* pstrDataName, BSTR bstrData);

private:
	static WCHAR* m_pwszSheetList[];
};