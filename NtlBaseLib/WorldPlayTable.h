#pragma once
#include "Table.h"
#include "NtlWorld.h"

#pragma pack(push, 4)
struct sWORLDPLAY_TBLDAT : public sTBLDAT
{
public:
	DWORD					dwGroup;
	BYTE					byExecuterType;		// eWORLDPLAY_EXECUTER_TYPE
	BYTE					byShareType;		// eWORLDPLAY_SHARE_TYPE
	DWORD					dwShareLimitTime;	// Share Limit Time

protected:

	virtual int GetDataSize()
	{
		return sizeof(*this) - sizeof(void*);
	}
};
#pragma pack(pop)

class WorldPlayTable : public Table
{
public:
	WorldPlayTable(void);
	virtual ~WorldPlayTable(void);

	bool Create(DWORD dwCodePage);
	void Destroy();

	sTBLDAT* FindData(TBLIDX tblidx);

	virtual bool LoadFromBinary(Serializer& serializer, bool bReload);
	virtual bool SaveToBinary(Serializer& serializer);

protected:
	void Init();

	WCHAR** GetSheetListInWChar() { return &(WorldPlayTable::m_pwszSheetList[0]); }
	void* AllocNewTable(WCHAR* pwszSheetName, DWORD dwCodePage);
	bool DeallocNewTable(void* pvTable, WCHAR* pwszSheetName);
	bool AddTable(void * pvTable, bool bReload);
	bool SetTableData(void* pvTable, WCHAR* pwszSheetName, std::wstring* pstrDataName, BSTR bstrData);

private:
	static WCHAR* m_pwszSheetList[];
};
