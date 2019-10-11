#pragma once

#include "Table.h"
#include "NtlItem.h"

const DWORD		DBO_MAX_LENGTH_USE_ITEM_CASTING_EFFECT_NAME = 32;
const DWORD		DBO_MAX_LENGTH_USE_ITEM_ACTION_EFFECT_NAME = 32;

enum eUSE_ITEM_NEED_STATE
{
	USE_ITEM_NEED_STATE_NORMAL_IDLE = 0,
	USE_ITEM_NEED_STATE_SIT_DOWN,
	USE_ITEM_NEED_STATE_MOVING,
	USE_ITEM_NEED_STATE_NORMAL_BATTLE
};

#pragma pack(push, 4)
struct sUSE_ITEM_TBLDAT : public sTBLDAT
{
public:

	BYTE    byUseItemActiveType;
	BYTE    byBuffGroup;
	BYTE    byBuffKeepType;

	DWORD   dwCoolDownBitFlag;
	WORD    wFunctionBitFlag;

	DWORD   dwUseRestrictionRuleBitFlag;
	DWORD   dwUseAllowRuleBitFlag;

	BYTE    byAppointTarget;
	BYTE    byApplyTarget;

	DWORD   dwApplyTargetIndex;

	BYTE    byApplyTargetMax;
	BYTE    byAapplyRange;
	BYTE    byApplyAreaSize1;
	BYTE    byApplyAreaSize2;

	WORD    wNeedStateBitFlag;

	DWORD   adwSystemEffect[MAX_EFFECT_IN_ITEM];
	BYTE    abySystemEffectType[MAX_EFFECT_IN_ITEM];
	DOUBLE  adSystemEffectValue[MAX_EFFECT_IN_ITEM];

	DWORD   dwRequireLp;
	WORD    wRequireEp;
	BYTE    byRequireRpBall;

	DWORD   dwCastingTime;
	DWORD   dwCastingTimeMs;

	DWORD   dwCooldown;
	DWORD   dwCooldownMs;

	DWORD   dwKeepTime;
	DWORD   dwKeepTimeMs;

	BOOLEAN     bKeepEffect;
	BYTE        byUseRangeMin;
	FLOAT       fUseRangeMin;
	BYTE        byUseRangeMax;
	FLOAT       fUseRangeMax;
	TBLIDX      tbxUseInfoText;

	CHAR    acCastingEffect[DBO_MAX_LENGTH_USE_ITEM_CASTING_EFFECT_NAME + 1];
	CHAR    acActionEffect[DBO_MAX_LENGTH_USE_ITEM_CASTING_EFFECT_NAME + 1];

	WORD    wCastingAnimationStart;
	WORD    wCastingAnimationLoop;

	WORD    wActionAnimationIndex;
	WORD    wActionAnimationLoopIndex;
	WORD    wActionEndAnimationIndex;

	BYTE    byCastinfEffectPos;
	BYTE    byActionEffectPos;

	TBLIDX  tbxUseWorldIndex;

	FLOAT   fUseLocX;
	FLOAT   fUseLocZ;
	FLOAT   fUseLocRadius;

	WORD    wRequiredQuestID;

public:

	virtual int GetDataSize()
	{
		return sizeof(*this) - sizeof(void*);
	}
};
#pragma pack(pop)

enum eUSE_ITEM_FUNCTION
{
	USE_ITEM_FUNCTION_NON_CONSUMABLE = 0,

	USE_ITEM_FUNCTION_COUNT,

	USE_ITEM_FUNCTION_FIRST = USE_ITEM_FUNCTION_NON_CONSUMABLE,
	USE_ITEM_FUNCTION_LAST = USE_ITEM_FUNCTION_NON_CONSUMABLE
};

class UseItemTable : public Table
{
public:

	UseItemTable(void);
	virtual ~UseItemTable(void);

	bool Create(DWORD dwCodePage);
	void Destroy();

	sTBLDAT* FindData(TBLIDX tblidx);

	virtual bool LoadFromBinary(Serializer& serializer, bool bReload);
	virtual bool SaveToBinary(Serializer& serializer);

protected:
	void Init();

	WCHAR** GetSheetListInWChar() { return &(UseItemTable::m_pwszSheetList[0]); }
	void* AllocNewTable(WCHAR* pwszSheetName, DWORD dwCodePage);
	bool DeallocNewTable(void* pvTable, WCHAR* pwszSheetName);
	bool AddTable(void * pvTable, bool bReload);
	bool SetTableData(void* pvTable, WCHAR* pwszSheetName, std::wstring* pstrDataName, BSTR bstrData);

private:
	static WCHAR* m_pwszSheetList[];
};