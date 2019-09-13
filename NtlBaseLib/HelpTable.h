#pragma once

#include "Table.h"

const DWORD		DBO_MAX_LENGTH_HELP_TITLE_TEXT = 32;
const DWORD		DBO_MAX_LENGTH_HELP_HINT_TEXT = 255;
const DWORD		DBO_MAX_LENGTH_HELP_HTML_NAME = 32;

#pragma pack(push, 4)
struct sHELP_TBLDAT : public sTBLDAT
{
public:
	BYTE		byCategory;
	DWORD		dwHelpTitle;
	DWORD		dwPopoHint;
	WCHAR		wszHelpHTMLName[DBO_MAX_LENGTH_HELP_HTML_NAME + 1];
	BYTE		byConditionCheck;

protected:

	virtual int GetDataSize()
	{
		return sizeof(*this) - sizeof(void*);
	}
};
#pragma pack(pop)

class HelpTable : public Table
{
public:
	HelpTable(void);
	virtual ~HelpTable(void);

	bool Create(DWORD dwCodePage);
	void Destroy();

	sTBLDAT* FindData(TBLIDX tblidx);

	virtual bool LoadFromBinary(Serializer& serializer, bool bReload);
	virtual bool SaveToBinary(Serializer& serializer);

protected:
	void Init();

	WCHAR** GetSheetListInWChar() { return &(HelpTable::m_pwszSheetList[0]); }
	void* AllocNewTable(WCHAR* pwszSheetName, DWORD dwCodePage);
	bool DeallocNewTable(void* pvTable, WCHAR* pwszSheetName);
	bool AddTable(void * pvTable, bool bReload);
	bool SetTableData(void* pvTable, WCHAR* pwszSheetName, std::wstring* pstrDataName, BSTR bstrData);

private:
	static WCHAR* m_pwszSheetList[];
};