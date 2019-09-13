#pragma once

#include "Table.h"
#include "NtlCharacter.h"

#pragma pack(push, 4)
struct sGMT_TBLDAT : public sTBLDAT
{
public:
	BYTE			byEffectTerm;			// GMT 유지 시간의 주기
	BYTE			byEffectType;
	BYTE			byEffectValue;
	BYTE			byMaxTimeNumber;
	BYTE			abyTimeSet[GMT_MAX_TIME_SLOT_SIZE];

protected:

	virtual int GetDataSize()
	{
		return sizeof(*this) - sizeof(void*);
	}
};
#pragma pack(pop)

class GameManiaTimeTable : public Table
{
public:
	GameManiaTimeTable(void);
	virtual ~GameManiaTimeTable(void);

	bool Create(DWORD dwCodePage);
	void Destroy();

	sTBLDAT* FindData(TBLIDX tblidx);

	virtual bool LoadFromBinary(Serializer& serializer, bool bReload);
	virtual bool SaveToBinary(Serializer& serializer);

protected:
	void Init();

	WCHAR** GetSheetListInWChar() { return &(GameManiaTimeTable::m_pwszSheetList[0]); }
	void* AllocNewTable(WCHAR* pwszSheetName, DWORD dwCodePage);
	bool DeallocNewTable(void* pvTable, WCHAR* pwszSheetName);
	bool AddTable(void * pvTable, bool bReload);
	bool SetTableData(void* pvTable, WCHAR* pwszSheetName, std::wstring* pstrDataName, BSTR bstrData);

private:
	static WCHAR* m_pwszSheetList[];
};
