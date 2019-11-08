#pragma once

#include "Table.h"

const int QUEST_REWARD_SELECT_DEF_MAX_CNT = 4;			/* DboTSCoreDefine.h => MAX_DEFAULT_REWARD */
const int QUEST_REWARD_SELECT_SEL_MAX_CNT = 4;			/* DboTSCoreDefine.h => MAX_SELECTION_REWARD */

#pragma pack(push, 4)
struct sQUEST_REWARD_SELECT_DATASET
{
	BYTE			unknown;
	TBLIDX			itemTblidx;
	unsigned int	amount;

};

struct sQUEST_REWARD_SELECT_TBLDAT : public sTBLDAT
{
public:
	BYTE					unknown;
	sQUEST_REWARD_SELECT_DATASET	rewardData[20];
protected:

	virtual int GetDataSize()
	{
		return sizeof(*this) - sizeof(void*);
	}
};
#pragma pack(pop)



class QuestRewardSelectTable : public Table
{
public:
	QuestRewardSelectTable(void);
	virtual ~QuestRewardSelectTable(void);

	bool Create(DWORD dwCodePage);
	void Destroy();

	sTBLDAT* FindData(TBLIDX tblidx);

	virtual bool LoadFromBinary(Serializer& serializer, bool bReload);
	virtual bool SaveToBinary(Serializer& serializer);

protected:
	void Init();

	WCHAR** GetSheetListInWChar() { return &(QuestRewardSelectTable::m_pwszSheetList[0]); }
	void* AllocNewTable(WCHAR* pwszSheetName, DWORD dwCodePage);
	bool DeallocNewTable(void* pvTable, WCHAR* pwszSheetName);
	bool AddTable(void* pvTable, bool bReload);
	bool SetTableData(void* pvTable, WCHAR* pwszSheetName, std::wstring* pstrDataName, BSTR bstrData);

private:
	static WCHAR* m_pwszSheetList[];
};

