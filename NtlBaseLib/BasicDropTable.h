#pragma once

#include "Table.h"
#include "NtlVector.h"
#include "NtlItem.h"

#pragma pack(push, 4)
struct sBASIC_DROP_TBLDAT : public sTBLDAT
{
public:

	BYTE		byMax;
	float		afNoramalTblidxRate[MAX_DROP_TABLE_SELECT];
	TBLIDX		aNoramalDropTblidx[MAX_DROP_TABLE_SELECT];
	float		afSuperiorTblidxRate[MAX_DROP_TABLE_SELECT];
	TBLIDX		aSuperiorDropTblidx[MAX_DROP_TABLE_SELECT];
	float		afExcellentTblidxRate[MAX_DROP_TABLE_SELECT];
	TBLIDX		aExcellentDropTblidx[MAX_DROP_TABLE_SELECT];
	float		afLegendaryTblidxRate[MAX_DROP_TABLE_SELECT];
	TBLIDX		aLegendaryDropTblidx[MAX_DROP_TABLE_SELECT];

	float		fSuperior_Drop_Rate_Control;
	float		fSuperior_Option_Rate_Control;
	float		fExcellent_Drop_Rate_Control;
	float		fLegendary_Drop_Rate_Control;

public:

	virtual int GetDataSize()
	{
		return sizeof(*this) - sizeof(void*);
	}
};
#pragma pack(pop)

class BasicDropTable : public Table
{
public:
	BasicDropTable(void);
	virtual ~BasicDropTable(void);

	bool Create(DWORD dwCodePage);
	void Destroy();

	sTBLDAT* FindData(TBLIDX tblidx);
	static TBLIDX FindNormalDropIndex(sBASIC_DROP_TBLDAT* psTblData, BYTE byIndex);
	static float FindNormalDropRate(sBASIC_DROP_TBLDAT* psTblData, BYTE byIndex);
	static TBLIDX FindSuperiorDropIndex(sBASIC_DROP_TBLDAT* psTblData, BYTE byIndex);
	static float FindSuperiorDropRate(sBASIC_DROP_TBLDAT* psTblData, BYTE byIndex);
	static TBLIDX FindLegendaryDropIndex(sBASIC_DROP_TBLDAT* psTblData, BYTE byIndex);
	static float FindLegendaryDropRate(sBASIC_DROP_TBLDAT* psTblData, BYTE byIndex);
	static TBLIDX FindExcellentDropIndex(sBASIC_DROP_TBLDAT* psTblData, BYTE byIndex);
	static float FindExcellentDropRate(sBASIC_DROP_TBLDAT* psTblData, BYTE byIndex);

	virtual bool LoadFromBinary(Serializer& serializer, bool bReload);
	virtual bool SaveToBinary(Serializer& serializer);

protected:
	void Init();

	WCHAR** GetSheetListInWChar() { return &(BasicDropTable::m_pwszSheetList[0]); }
	void* AllocNewTable(WCHAR* pwszSheetName, DWORD dwCodePage);
	bool DeallocNewTable(void* pvTable, WCHAR* pwszSheetName);
	bool AddTable(void * pvTable, bool bReload);
	bool SetTableData(void* pvTable, WCHAR* pwszSheetName, std::wstring* pstrDataName, BSTR bstrData);

private:
	static WCHAR* m_pwszSheetList[];
};