#pragma once

#include "Table.h"
#include "NtlItem.h"

#pragma pack(push, 4)
struct sDRAGONBALL_REWARD_TBLDAT : public sTBLDAT
{
public:
	BYTE		byBallType;
	BYTE		byRewardCategoryDepth;
	TBLIDX		rewardCategoryName;
	TBLIDX		rewardCategoryDialog;
	BYTE		byRewardType;
	TBLIDX		rewardName;
	TBLIDX		rewardLinkTblidx;
	DWORD		dwRewardZenny;
	TBLIDX		rewardDialog1;
	TBLIDX		rewardDialog2;
	TBLIDX		rewardDialog3;

protected:
	virtual int GetDataSize()
	{
		return sizeof(*this) - sizeof(void*);
	}
};
#pragma pack(pop)

class DragonBallRewardTable : public Table
{
public:
	DragonBallRewardTable(void);
	virtual ~DragonBallRewardTable(void);

	bool Create(DWORD dwCodePage);
	void Destroy();

	sTBLDAT* FindData(TBLIDX tblidx);

	virtual bool LoadFromBinary(Serializer& serializer, bool bReload);
	virtual bool SaveToBinary(Serializer& serializer);

protected:
	void Init();

	WCHAR** GetSheetListInWChar() { return &(DragonBallRewardTable::m_pwszSheetList[0]); }
	void* AllocNewTable(WCHAR* pwszSheetName, DWORD dwCodePage);
	bool DeallocNewTable(void* pvTable, WCHAR* pwszSheetName);
	bool AddTable(void * pvTable, bool bReload);
	bool SetTableData(void* pvTable, WCHAR* pwszSheetName, std::wstring* pstrDataName, BSTR bstrData);

private:
	static WCHAR* m_pwszSheetList[];
};