#pragma once

#include "Table.h"

#pragma pack(push, 4)
struct sSTATUS_TRANSFORM_TBLDAT : public sTBLDAT
{
public:
	float			fLP_Transform;
	float			fEP_Transform;
	float			fPhysical_Offence_Transform;
	float			fEnergy_Offence_Transform;
	float			fPhysical_Defence_Transform;
	float			fEnergy_Defence_Transform;
	float			fRun_Speed_Transform;
	float			fAttack_Speed_Transform;
	float			fAttack_Rate_Transform;
	float			fDodge_Rate_Transform;
	float			fBlock_Rate_Transform;
	float			fCurse_Success_Transform;
	float			fCurse_Tolerance_Transform;
	float			fAttack_Range_Change;

protected:

	virtual int GetDataSize()
	{
		return sizeof(*this) - sizeof(void*);
	}
};
#pragma pack(pop)

class StatusTransformTable : public Table
{
public:
	StatusTransformTable();
	virtual ~StatusTransformTable();

	bool Create(DWORD dwCodePage);
	void Destroy();

	sTBLDAT* FindData(TBLIDX tblidx);

	virtual bool LoadFromBinary(Serializer& serializer, bool bReload);
	virtual bool SaveToBinary(Serializer& serializer);

protected:
	void Init();

	WCHAR** GetSheetListInWChar() { return &(StatusTransformTable::m_pwszSheetList[0]); }
	void* AllocNewTable(WCHAR* pwszSheetName, DWORD dwCodePage);
	bool DeallocNewTable(void* pvTable, WCHAR* pwszSheetName);
	bool AddTable(void * pvTable, bool bReload);
	bool SetTableData(void* pvTable, WCHAR* pwszSheetName, std::wstring* pstrDataName, BSTR bstrData);

private:
	static WCHAR* m_pwszSheetList[];
};