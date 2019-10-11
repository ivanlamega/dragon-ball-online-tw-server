#pragma once

#include "Table.h"
#include "NtlSkill.h"

const DWORD		DBO_MAX_LENGTH_HTB_SET_NAME_TEXT = 40;
const DWORD		DBO_MAX_LENGTH_HTB_SET_ICON_NAME = 32;

#pragma pack(push, 4)
struct sHTB_ACTION
{
	BYTE				bySkillType;
	TBLIDX				skillTblidx;
};
#pragma pack(pop)

#pragma pack(push, 4)
struct sHTB_SET_TBLDAT : public sTBLDAT
{
	sHTB_SET_TBLDAT()
	{
		bValidity_Able = true;
	};

public:
	WCHAR				wszNameText[DBO_MAX_LENGTH_HTB_SET_NAME_TEXT + 1];
	TBLIDX				HTB_Skill_Name;
	bool				bValidity_Able;
	DWORD				dwPC_Class_Bit_Flag;// // enum ePC_CLASS_FLAG
	BYTE				bySlot_Index;
	BYTE				bySkill_Grade;
	char				szIcon_Name[DBO_MAX_LENGTH_HTB_SET_ICON_NAME + 1];
	WORD				wNeed_EP;
	BYTE				byRequire_Train_Level;
	DWORD				dwRequire_Zenny;
	WORD				wNext_Skill_Train_Exp;
	WORD				wCool_Time;
	DWORD				dwCoolTimeInMilliSecs;
	TBLIDX				Note;
	BYTE				bySetCount;
	BYTE				byStop_Point;

	sHTB_ACTION			aHTBAction[HTB_MAX_SKILL_COUNT_IN_SET];
	WORD				wRequireSP;

protected:
	virtual int GetDataSize()
	{
		return sizeof(*this) - sizeof(void*);
	}
};
#pragma pack(pop)

class HTBSetTable : public Table
{
public:

	HTBSetTable(void);
	virtual ~HTBSetTable(void);

	bool Create(DWORD dwCodePage);
	void Destroy();

	sTBLDAT* FindData(TBLIDX tblidx);

	virtual bool LoadFromBinary(Serializer& serializer, bool bReload);
	virtual bool SaveToBinary(Serializer& serializer);

protected:
	void Init();

	WCHAR** GetSheetListInWChar() { return &(HTBSetTable::m_pwszSheetList[0]); }
	void* AllocNewTable(WCHAR* pwszSheetName, DWORD dwCodePage);
	bool DeallocNewTable(void* pvTable, WCHAR* pwszSheetName);
	bool AddTable(void * pvTable, bool bReload);
	bool SetTableData(void* pvTable, WCHAR* pwszSheetName, std::wstring* pstrDataName, BSTR bstrData);

private:
	static WCHAR* m_pwszSheetList[];
};
