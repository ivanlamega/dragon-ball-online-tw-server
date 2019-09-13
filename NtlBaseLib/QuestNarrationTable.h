#pragma once
#include "table.h"

const DWORD		DBO_MAX_COUNT_OF_NARRATION = 10;

#pragma pack(push, 4)

struct sQUEST_NARRATION_DATASET
{
	BYTE			byUIShowHideDirection;
	BYTE			byOwnerType;
	DWORD			dwOwner;
	BYTE			byCondition;
	BYTE			byDirection;
	DWORD			dwDialog;
	BYTE			byUiType;
	BYTE			byUIDirection;
};

struct sQUEST_NARRATION_TBLDAT : public sTBLDAT
{
public:
	bool			bType;		// false : Narration, true : Mini narration
	BYTE			byNumber;
	BYTE			byTime;
	sQUEST_NARRATION_DATASET asData[DBO_MAX_COUNT_OF_NARRATION];

protected:
	virtual int GetDataSize()
	{
		return sizeof(*this) - sizeof(void*);
	}
};
#pragma pack(pop)

class QuestNarrationTable : public Table
{
public:
	QuestNarrationTable(void);
	virtual ~QuestNarrationTable(void);

	bool Create(DWORD dwCodePage);
	void Destroy(void);

	sTBLDAT* FindData(TBLIDX tblidx);

	virtual bool LoadFromBinary(Serializer& serializer, bool bReload);
	virtual bool SaveToBinary(Serializer& serializer);

protected:
	void Init(void);

	WCHAR** GetSheetListInWChar(void) { return &m_pwszSheetList[0]; }
	void* AllocNewTable(WCHAR* pwszSheetName, DWORD dwCodePage);
	bool DeallocNewTable(void* pvTable, WCHAR* pwszSheetName);
	bool AddTable(void* pvTable, bool bReload);
	bool SetTableData(void* pvTable, WCHAR* pwszSheetName, std::wstring* pstrDataName, BSTR bstrData);

	static WCHAR* m_pwszSheetList[];
};
