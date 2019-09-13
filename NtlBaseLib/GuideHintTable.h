#pragma once

#include "Table.h"

const DWORD		DBO_MAX_LENGTH_RESOURCE = 32;
const DWORD		DBO_MAX_LENGTH_NOTE = 32;

#pragma pack(push, 4)
struct sGUIDE_HINT_TBLDAT : public sTBLDAT
{
public:
	BYTE			byType;
	BYTE			byWidthPosition;
	BYTE			byHeightPosition;
	WORD			wWidthSize;
	WORD			wHeightSize;
	char			szResource[DBO_MAX_LENGTH_RESOURCE + 1];
	char			szNote[DBO_MAX_LENGTH_NOTE + 1];
	bool			bAutoShow;

protected:

	virtual int GetDataSize()
	{
		return sizeof(*this) - sizeof(void*);
	}
};
#pragma pack(pop)

class GuideHintTable : public Table
{
public:
	GuideHintTable(void);
	virtual ~GuideHintTable(void);

	bool Create(DWORD dwCodePage);
	void Destroy();

	sTBLDAT* FindData(TBLIDX tblidx);

	virtual bool LoadFromBinary(Serializer& serializer, bool bReload);
	virtual bool SaveToBinary(Serializer& serializer);

protected:
	void Init();

	WCHAR** GetSheetListInWChar() { return &(GuideHintTable::m_pwszSheetList[0]); }
	void* AllocNewTable(WCHAR* pwszSheetName, DWORD dwCodePage);
	bool DeallocNewTable(void* pvTable, WCHAR* pwszSheetName);
	bool AddTable(void * pvTable, bool bReload);
	bool SetTableData(void* pvTable, WCHAR* pwszSheetName, std::wstring* pstrDataName, BSTR bstrData);

private:
	static WCHAR* m_pwszSheetList[];
};