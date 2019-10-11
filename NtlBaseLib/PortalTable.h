#pragma once

#include "Table.h"
#include "NtlVector.h"
const DWORD		DBO_MAX_LENGTH_POINT_NAME = 40;
const DWORD		DBO_MAX_POINT_PORTAL = 50;
#pragma pack(push, 4)
struct sPORTAL_TBLDAT : public sTBLDAT
{
public:
	DWORD			dwPointName;
	char			szPointNameText[DBO_MAX_LENGTH_POINT_NAME + 1];
	DWORD			dwUnknown;
	WORLDID			worldId;
	BYTE			byUnknown1;
	CNtlVector		vLoc;
	CNtlVector		vDir;
	CNtlVector		vMap;
	PORTALID		aPoint[DBO_MAX_POINT_PORTAL];
	DWORD			adwPointZenny[DBO_MAX_POINT_PORTAL];
	BYTE			byUnknown[98];

protected:

	virtual int GetDataSize()
	{
		return sizeof(*this) - sizeof(void*);
	}
};
#pragma pack(pop)

class PortalTable : public Table
{
public:
	PortalTable(void);
	virtual ~PortalTable(void);

	bool Create(DWORD dwCodePage);
	void Destroy();

protected:
	void Init();

public:
	sTBLDAT* FindData(TBLIDX tblidx);

protected:
	WCHAR** GetSheetListInWChar() { return &(PortalTable::m_pwszSheetList[0]); }
	void* AllocNewTable(WCHAR* pwszSheetName, DWORD dwCodePage);
	bool DeallocNewTable(void* pvTable, WCHAR* pwszSheetName);
	bool AddTable(void * pvTable, bool bReload);
	bool SetTableData(void* pvTable, WCHAR* pwszSheetName, std::wstring* pstrDataName, BSTR bstrData);

public:

	virtual bool				LoadFromBinary(Serializer& serializer, bool bReload);

	virtual bool				SaveToBinary(Serializer& serializer);


private:
	static WCHAR* m_pwszSheetList[];
};