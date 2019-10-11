#pragma once

#include "Table.h"

const DWORD		DBO_MAX_LENGTH_VEHICLE_MODEL_NAME = 32;

#pragma pack(push, 4)
struct sVEHICLE_TBLDAT : public sTBLDAT
{
	sVEHICLE_TBLDAT()
	{
	};

public:
	char			szModelName[DBO_MAX_LENGTH_VEHICLE_MODEL_NAME + 1];
	BYTE			bySRPType;
	BYTE			bySpeed;
	BYTE			byVehicleType;
	WORD			wRunHeight;
	BYTE			byPersonnel;

public:
	virtual int GetDataSize()
	{
		return sizeof(*this) - sizeof(void*);
	}
};
#pragma pack(pop)

class VehicleTable : public Table
{
public:
	VehicleTable(void);
	virtual	~VehicleTable(void);

	bool Create(DWORD dwCodePage);
	void Destroy();
	sTBLDAT* FindData(TBLIDX tblidx);

	virtual bool LoadFromBinary(Serializer& serializer, bool bReload);
	virtual bool SaveToBinary(Serializer& serializer);

protected:
	void Init();

	WCHAR** GetSheetListInWChar() { return &(VehicleTable::m_pwszSheetList[0]); }
	void* AllocNewTable(WCHAR* pwszSheetName, DWORD dwCodePage);
	bool DeallocNewTable(void* pvTable, WCHAR* pwszSheetName);
	bool AddTable(void * pvTable, bool bReload);
	bool SetTableData(void* pvTable, WCHAR* pwszSheetName, std::wstring* pstrDataName, BSTR bstrData);

private:
	static WCHAR*	m_pwszSheetList[];
};