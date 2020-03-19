#pragma once

#include "Table.h"

const DWORD		DBO_MAX_FORMULA_RATE_COUNT = 4;
const DWORD		DBO_MAX_FORMULA_IDX = 1000;

#pragma pack(push, 4)
struct sFORMULA_TBLDAT : public sTBLDAT
{
public:
	bool			bValidity_Able;
	float			afRate[4];

protected:

	virtual int GetDataSize()
	{
		return sizeof(*this) - sizeof(void*);
	}
};
#pragma pack(pop)

struct CLASS_INFO
{
	BYTE	byClass;
	TBLIDX	Physical_Offence;
	TBLIDX	LP;
	TBLIDX	Energy_Offence;
	TBLIDX	EP;
	TBLIDX	Physical_Critical_Rate;
	TBLIDX	Physical_Critical_Range;
	TBLIDX	Energy_Critical_Rate;
	TBLIDX	Energy_Critical_Range;
	TBLIDX	Max_AP;
};

class FormulaTable : public Table
{
public:
	FormulaTable(void);
	virtual ~FormulaTable(void);

	bool Create(DWORD dwCodePage);
	void Destroy();

	sTBLDAT* FindData(TBLIDX tblidx);
	CLASS_INFO* FindClassInfoByClass(BYTE byClass);

	virtual bool LoadFromBinary(Serializer& serializer, bool bReload);
	virtual bool SaveToBinary(Serializer& serializer);

protected:
	void Init();

	WCHAR** GetSheetListInWChar() { return &(FormulaTable::m_pwszSheetList[0]); }
	void* AllocNewTable(WCHAR* pwszSheetName, DWORD dwCodePage);
	bool DeallocNewTable(void* pvTable, WCHAR* pwszSheetName);
	bool AddTable(void * pvTable, bool bReload);
	bool SetTableData(void* pvTable, WCHAR* pwszSheetName, std::wstring* pstrDataName, BSTR bstrData);

	void AddClassInfo(BYTE byClass);
	void LoadClassInfo();

	// WARNING :
	// The value of 'm' in the variable 'afRate[m][n]' means tblidx.
	// For example, if you want to get data whose tblidx is 6, you must use 'm_afRate[6]' instead of 'm_afRate[5]'.
	// The value of 'n' in the variable 'afRate[m][n]' means an index.
	// For example, if you want to get value of 'fRate2', you must use 'm_afRate[m][2]' instead of 'm_afRate[m][1]'.
	// m_afRate[m][n]에서의 m은 tblidx를 뜻합니다.
	// 예를 들어, tblidx가 6인 공식 데이타를 얻을 때에는 m_afRate[5]가 아닌 m_afRate[6]을 사용해야 합니다.
	// m_afRate[m][n]에서의 n은 인덱스를 뜻합니다.
	// 예를 들어, fRate2의 값을 얻을 때에는 m_afRate[m][1]이 아닌 m_afRate[m][2]를 사용해야 합니다.
	// by YOSHIKI(2009-07-13)
	static float m_afRate[DBO_MAX_FORMULA_IDX + 1][DBO_MAX_FORMULA_RATE_COUNT + 1];

private:
	typedef std::unordered_map<BYTE, CLASS_INFO> CLASS_INFODATA;
	typedef CLASS_INFODATA::iterator CLASS_INFODATAIT;
	typedef CLASS_INFODATA::value_type CLASS_INFODATAVAL;

	static WCHAR* m_pwszSheetList[];

	CLASS_INFODATA m_mapClassInfoList;

	CLASS_INFODATAIT ClassInfoBegin() { return m_mapClassInfoList.begin(); };
	CLASS_INFODATAIT ClassInfoEnd() { return m_mapClassInfoList.end(); }
};