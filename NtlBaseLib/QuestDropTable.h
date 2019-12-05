#pragma once

#include "Table.h"

const int QUEST_ITEM_DROP_MAX_COUNT = 5;

#pragma pack(push, 4)
struct sQUEST_DROP_TBLDAT : public sTBLDAT
{
	sQUEST_DROP_TBLDAT()
	{
		memset(aQuestItemTblidx, 0xFF, sizeof(TBLIDX) * QUEST_ITEM_DROP_MAX_COUNT);
		memset(aDropRate, 0xFF, sizeof(float) * QUEST_ITEM_DROP_MAX_COUNT);
	}

public:
	TBLIDX		aQuestItemTblidx[QUEST_ITEM_DROP_MAX_COUNT];
	float		aDropRate[QUEST_ITEM_DROP_MAX_COUNT];

protected:
	virtual int GetDataSize()
	{
		return sizeof(*this) - sizeof(void*);
	}
};
#pragma pack(pop)

class QuestDropTable : public Table
{
public:

	typedef std::unordered_map<TBLIDX, std::vector<TBLIDX>> QUESTDROP;
	typedef QUESTDROP::iterator QUESTDROPIT;
	typedef QUESTDROP::value_type QUESTDROPVAL;

	QUESTDROP					m_mapQuestDropList;

	QuestDropTable(void);
	virtual ~QuestDropTable(void);

	bool Create(DWORD dwCodePage);
	void Destroy();

	sTBLDAT* FindData(TBLIDX tblidx);
	std::vector<TBLIDX>	FindByItemTblidx(TBLIDX itemTblidx);

	QUESTDROPIT QuestDropBegin() { return m_mapQuestDropList.begin(); };
	QUESTDROPIT QuestDropEnd() { return m_mapQuestDropList.end(); };

	virtual bool LoadFromBinary(Serializer& serializer, bool bReload);
	virtual bool SaveToBinary(Serializer& serializer);

protected:
	void Init();

	WCHAR** GetSheetListInWChar() { return &(QuestDropTable::m_pwszSheetList[0]); }
	void* AllocNewTable(WCHAR* pwszSheetName, DWORD dwCodePage);
	bool DeallocNewTable(void* pvTable, WCHAR* pwszSheetName);
	bool AddTable(void * pvTable, bool bReload);
	bool SetTableData(void* pvTable, WCHAR* pwszSheetName, std::wstring* pstrDataName, BSTR bstrData);

private:
	static WCHAR* m_pwszSheetList[];
};
