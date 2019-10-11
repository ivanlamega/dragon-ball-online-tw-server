#pragma once

#include "Table.h"
#include "NtlItem.h"

// Hard Coding
#define	HOIPOISTONE_ITEM_INDEX	19954

const DWORD		DBO_MAX_LENGTH_ITEM_NAME_TEXT = 32;//Old 32
const DWORD		DBO_MAX_LENGTH_ITEM_ICON_NAME = 32;
const DWORD		DBO_MAX_LENGTH_ITEM_MODEL_NAME = 32;
const DWORD		DBO_MAX_LENGTH_ITEM_SUBWEAPON_ACT_MODEL_NAME = 32;

#pragma pack(push, 4)
struct sITEM_TBLDAT : public sTBLDAT
{
	sITEM_TBLDAT()
	{
		bValidity_Able = true;
	};
	
public:
	bool			bValidity_Able;

	TBLIDX          tbxName;
	WCHAR           awcNameText[DBO_MAX_LENGTH_ITEM_NAME_TEXT + 1];
	CHAR            acIconName[DBO_MAX_LENGTH_ITEM_ICON_NAME + 1];

	BYTE            byModelType;

	CHAR            acModel[DBO_MAX_LENGTH_ITEM_MODEL_NAME + 1];
	CHAR            acSubWeaponActModel[DBO_MAX_LENGTH_ITEM_SUBWEAPON_ACT_MODEL_NAME + 1];

	BYTE	        eItemType; // BYTE
	BYTE			eEquipType; // BYTE

	DWORD           dwEquipSlotTypeBitFlag;
	WORD            wFunctionBitFlag;

	BYTE            byMaxStack;
	BYTE		    eRank; // BYTE

	DWORD           dwWeight;

	DWORD           dwCost;
	TBLIDX          tbxSellPrice;

	BYTE            byDurability;
	BYTE            byDurabilityCount;
	BYTE			eBattleAttribute; // BYTE

	WORD            wPhysicalOffence;
	WORD            wEnergyOffence;
	WORD            wPhysicalDefence;
	WORD            wEnergyDefence;

	FLOAT           fAttackRangeBonus;
	WORD            wAttackSpeedRate;

	BYTE            byNeedLevel;
	BYTE            byNeedMaxLevel;
	DWORD           dwNeedClassBitFlag;
	DWORD           dwNeedGenderBitFlag;

	BYTE            byClassSpecial;
	BYTE            byRaceSpecial;

	WORD            wNeedStr;
	WORD            wNeedCon;
	WORD            wNeedFoc;
	WORD            wNeedDex;
	WORD            wNeedSol;
	WORD            wNeedEng;

	TBLIDX          tbxSetItem;

	TBLIDX          tbxNote;

	BYTE            byBagSize;

	WORD            wScouterWatt;
	DWORD           dwScouterMaxPower;
	WORD            wScouterPartsType;
	WORD            wScouterPartsValue;
	TBLIDX          tbxUseItem;
	bool	        bCanHaveOption;

	TBLIDX          tbxItemOption;
	BYTE            byItemGroup;//ticket upgrade here^^

	TBLIDX          tbxCharm;
	WORD            wCostumeHideBitFlag;

	TBLIDX          tbxNeedItem;
	DWORD           dwCommonPoint;
	BYTE            byCommonPointType;

	BYTE            byNeedFunction;

	DWORD           dwUseDurationMax;
	BYTE		    eDurationType; // BYTE

	TBLIDX          tbxContents;
	DWORD           dwDurationGroup;
	BYTE            byDropLevel;

	DWORD           dwCreateEnchentRateID;
	DWORD           dwExcellentID;
	DWORD           dwRareID;
	DWORD           dwLegendaryID;
	bool			bCreateSuperiorAble;
	bool			bCreateExcelentAble;
	bool			bCreateRareAble;
	bool			bCreateLegendaryAble;

	BYTE			eRestrictType; // BYTE

	FLOAT           fAttackPhysical;
	FLOAT           fAttackEnergy;
	FLOAT           fDefencePhysical;
	FLOAT           fDefenceEnergy;

	BYTE            byTmpCategoryType;
	bool	        bCanRenewal;
	WORD            wDisassembleBitFlag;

	BYTE            byNormalMin;
	BYTE            byNormalMax;
	BYTE            byRankUpMin;
	BYTE            byRankUpMax;

	bool           bUseDisassemble;
	bool           bDropVisual;
public:

	virtual int GetDataSize()
	{
		return sizeof(*this) - sizeof(void*);
	}
};
#pragma pack(pop)

class ItemTable : public Table
{
public:

	ItemTable(void);
	virtual ~ItemTable(void);

	bool Create(DWORD dwCodePage);
	void Destroy();

protected:
	void Init();

public:
	sTBLDAT *			FindData(TBLIDX tblidx);

protected:
	WCHAR** GetSheetListInWChar() { return &(ItemTable::m_pwszSheetList[0]); }
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