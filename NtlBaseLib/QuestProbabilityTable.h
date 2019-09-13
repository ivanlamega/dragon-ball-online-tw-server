#pragma once

#include "Table.h"

const int QUEST_PROBABILITY_MAX_NAME_LENGTH = 64;
const int QUEST_PROBABILITY_MAX_NOTE_LENGTH = 255;
const int QUEST_PROBABILITY_MAX_COUNT = 50;

enum eTEMP_REWARD_TYPE
{
	eTEMP_REWARD_TYPE_NORMAL_ITEM,
	eTEMP_REWARD_TYPE_QUEST_ITEM,
	eTEMP_REWARD_TYPE_EXP,
	eTEMP_REWARD_TYPE_SKILL,
	eTEMP_REWARD_TYPE_ZENY,
	eTEMP_REWARD_TYPE_CHANGE_CLASS,
	eTEMP_REWARD_TYPE_BUFF,
	eTEMP_REWARD_TYPE_PROBABILITY,

	INVALID_TEMP_REWARD_TYPE = 0xff,
};

#pragma pack(push, 4)
struct sQUEST_PROBABILITY_DATA
{
	BYTE byType; //REWARD_TYPE
	BYTE unknown[3];//FFFFFF
	DWORD tblidx;
	DWORD dwMinValue;
	DWORD dwMaxValue;
	float    fRate;
};
#pragma pack(pop)

#pragma pack(push, 4)
struct sQUEST_PROBABILITY_TBLDAT : public sTBLDAT
{
	
public:
	WCHAR wszName[QUEST_PROBABILITY_MAX_NAME_LENGTH + 1];
	WCHAR wszNote[QUEST_PROBABILITY_MAX_NOTE_LENGTH + 1];
	//BYTE padding[2];
	DWORD byProbabilityType;
	WORD unknown;
	BYTE unknown2;
	//BYTE padding;
	sQUEST_PROBABILITY_DATA    asProbabilityData[QUEST_PROBABILITY_MAX_COUNT];

protected:
	virtual int GetDataSize()
	{
		return sizeof(*this) - sizeof(void*);
	}
};
#pragma pack(pop)

class QuestProbabilityTable :
	public Table
{
public:
	QuestProbabilityTable(void);
	virtual ~QuestProbabilityTable(void);

	bool Create(DWORD dwCodePage);
	void Destroy();

	sTBLDAT* FindData(TBLIDX tblidx);

	virtual bool LoadFromBinary(Serializer& serializer, bool bReload);
	virtual bool SaveToBinary(Serializer& serializer);

protected:
	void Init();

	WCHAR** GetSheetListInWChar() { return &(QuestProbabilityTable::m_pwszSheetList[0]); }
	void* AllocNewTable(WCHAR* pwszSheetName, DWORD dwCodePage);
	bool DeallocNewTable(void* pvTable, WCHAR* pwszSheetName);
	bool AddTable(void * pvTable, bool bReload);
	bool SetTableData(void* pvTable, WCHAR* pwszSheetName, std::wstring* pstrDataName, BSTR bstrData);

private:
	static WCHAR* m_pwszSheetList[];
};
