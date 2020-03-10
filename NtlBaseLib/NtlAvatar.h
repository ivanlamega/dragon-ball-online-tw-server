#pragma once

enum eATTRIBUTE_TO_UPDATE
{
	ATTRIBUTE_TO_UPDATE_STR_BASE,
	ATTRIBUTE_TO_UPDATE_STR_LAST,
	ATTRIBUTE_TO_UPDATE_CON_BASE,
	ATTRIBUTE_TO_UPDATE_CON_LAST,
	ATTRIBUTE_TO_UPDATE_FOC_BASE,
	ATTRIBUTE_TO_UPDATE_FOC_LAST,
	ATTRIBUTE_TO_UPDATE_DEX_BASE,
	ATTRIBUTE_TO_UPDATE_DEX_LAST,
	ATTRIBUTE_TO_UPDATE_SOL_BASE,
	ATTRIBUTE_TO_UPDATE_SOL_LAST,
	ATTRIBUTE_TO_UPDATE_ENG_BASE,
	ATTRIBUTE_TO_UPDATE_ENG_LAST,

	ATTRIBUTE_TO_UPDATE_MAX_LP_BASE,
	ATTRIBUTE_TO_UPDATE_MAX_LP_LAST,
	ATTRIBUTE_TO_UPDATE_MAX_EP_BASE,
	ATTRIBUTE_TO_UPDATE_MAX_EP_LAST,
	ATTRIBUTE_TO_UPDATE_MAX_AP_BASE,
	ATTRIBUTE_TO_UPDATE_MAX_AP_LAST,
	ATTRIBUTE_TO_UPDATE_MAX_RP_BASE,
	ATTRIBUTE_TO_UPDATE_MAX_RP_LAST,

	ATTRIBUTE_TO_UPDATE_LP_REGENERATION_BASE,
	ATTRIBUTE_TO_UPDATE_LP_REGENERATION_LAST,
	ATTRIBUTE_TO_UPDATE_LP_SITDOWN_REGENERATION_BASE,
	ATTRIBUTE_TO_UPDATE_LP_SITDOWN_REGENERATION_LAST,
	ATTRIBUTE_TO_UPDATE_LP_BATTLE_REGENERATION_BASE,
	ATTRIBUTE_TO_UPDATE_LP_BATTLE_REGENERATION_LAST,

	ATTRIBUTE_TO_UPDATE_EP_REGENERATION_BASE,
	ATTRIBUTE_TO_UPDATE_EP_REGENERATION_LAST,
	ATTRIBUTE_TO_UPDATE_EP_SITDOWN_REGENERATION_BASE,
	ATTRIBUTE_TO_UPDATE_EP_SITDOWN_REGENERATION_LAST,
	ATTRIBUTE_TO_UPDATE_EP_BATTLE_REGENERATION_BASE,
	ATTRIBUTE_TO_UPDATE_EP_BATTLE_REGENERATION_LAST,

	ATTRIBUTE_TO_UPDATE_AP_REGENERATION_BASE,
	ATTRIBUTE_TO_UPDATE_AP_REGENERATION_LAST,
	ATTRIBUTE_TO_UPDATE_AP_SITDOWN_REGENERATION_BASE,
	ATTRIBUTE_TO_UPDATE_AP_SITDOWN_REGENERATION_LAST,
	ATTRIBUTE_TO_UPDATE_AP_BATTLE_REGENERATION_BASE,
	ATTRIBUTE_TO_UPDATE_AP_BATTLE_REGENERATION_LAST,

	ATTRIBUTE_TO_UPDATE_UNKNOWN_INT16_0,
	ATTRIBUTE_TO_UPDATE_UNKNOWN_INT16_1,
	ATTRIBUTE_TO_UPDATE_UNKNOWN_INT16_2,
	ATTRIBUTE_TO_UPDATE_UNKNOWN_INT16_3,

	ATTRIBUTE_TO_UPDATE_RP_CHARGE_SPEED_BASE,
	ATTRIBUTE_TO_UPDATE_RP_CHARGE_SPEED_LAST,
	ATTRIBUTE_TO_UPDATE_RP_DIMIMUTION,

	ATTRIBUTE_TO_UPDATE_PHYSICAL_OFFENCE_BASE,
	ATTRIBUTE_TO_UPDATE_PHYSICAL_OFFENCE_LAST,
	ATTRIBUTE_TO_UPDATE_PHYSICAL_DEFENCE_BASE,
	ATTRIBUTE_TO_UPDATE_PHYSICAL_DEFENCE_LAST,

	ATTRIBUTE_TO_UPDATE_ENERGY_OFFENCE_BASE,
	ATTRIBUTE_TO_UPDATE_ENERGY_OFFENCE_LAST,
	ATTRIBUTE_TO_UPDATE_ENERGY_DEFENCE_BASE,
	ATTRIBUTE_TO_UPDATE_ENERGY_DEFENCE_LAST,

	ATTRIBUTE_TO_UPDATE_ATTACK_RATE_BASE,
	ATTRIBUTE_TO_UPDATE_ATTACK_RATE_LAST,
	ATTRIBUTE_TO_UPDATE_DODGE_RATE_BASE,
	ATTRIBUTE_TO_UPDATE_DODGE_RATE_LAST,
	ATTRIBUTE_TO_UPDATE_BLOCK_RATE_BASE,
	ATTRIBUTE_TO_UPDATE_BLOCK_RATE_LAST,

	ATTRIBUTE_TO_UPDATE_CURSE_SUCCESS_BASE,
	ATTRIBUTE_TO_UPDATE_CURSE_SUCCESS_LAST,
	ATTRIBUTE_TO_UPDATE_CURSE_TOLERANCE_BASE,
	ATTRIBUTE_TO_UPDATE_CURSE_TOLERANCE_LAST,

	ATTRIBUTE_TO_UPDATE_UNKNOW_RATE1,
	ATTRIBUTE_TO_UPDATE_UNKNOW_RATE2,

	ATTRIBUTE_TO_UPDATE_PHYSICAL_CRITICAL_BASE,
	ATTRIBUTE_TO_UPDATE_PHYSICAL_CRITICAL_LAST,
	ATTRIBUTE_TO_UPDATE_ENERGY_CRITICAL_BASE,
	ATTRIBUTE_TO_UPDATE_ENERGY_CRITICAL_LAST,

	ATTRIBUTE_TO_UPDATE_UNKNOW_FLOAT1_0,
	ATTRIBUTE_TO_UPDATE_UNKNOW_FLOAT1_1,

	ATTRIBUTE_TO_UPDATE_UNKNOW_FLOAT2_0,
	ATTRIBUTE_TO_UPDATE_UNKNOW_FLOAT2_1,


	ATTRIBUTE_TO_UPDATE_RUN_SPEED_BASE,
	ATTRIBUTE_TO_UPDATE_RUN_SPEED_LAST,

	ATTRIBUTE_TO_UPDATE_AIR_SPEED_BASE,
	ATTRIBUTE_TO_UPDATE_AIR_SPEED_LAST,
	ATTRIBUTE_TO_UPDATE_AIR_DASH_SPEED_BASE,
	ATTRIBUTE_TO_UPDATE_AIR_DASH_SPEED_LAST,
	ATTRIBUTE_TO_UPDATE_AIR_DASH2_SPEED_BASE,
	ATTRIBUTE_TO_UPDATE_AIR_DASH2_SPEED_LAST,

	ATTRIBUTE_TO_UPDATE_ATTACK_SPEED_RATE_BASE,
	ATTRIBUTE_TO_UPDATE_ATTACK_SPEED_RATE_LAST,
	ATTRIBUTE_TO_UPDATE_ATTACK_RANGE_BASE,
	ATTRIBUTE_TO_UPDATE_ATTACK_RANGE_LAST,

	ATTRIBUTE_TO_UPDATE_CASTING_TIME_CHANGE_PERCENT,
	ATTRIBUTE_TO_UPDATE_COOL_TIME_CHANGE_PERCENT,
	ATTRIBUTE_TO_UPDATE_KEEP_TIME_CHANGE_PERCENT,
	ATTRIBUTE_TO_UPDATE_DOT_VALUE_CHANGE_PERCENT,
	ATTRIBUTE_TO_UPDATE_DOT_TIME_CHANGE_ABSOLUTE,
	ATTRIBUTE_TO_UPDATE_REQUIRED_EP_CHANGE_PERCENT,

	ATTRIBUTE_TO_UPDATE_HONEST_OFFENCE,
	ATTRIBUTE_TO_UPDATE_HONEST_DEFENCE,
	ATTRIBUTE_TO_UPDATE_STRANGE_OFFENCE,
	ATTRIBUTE_TO_UPDATE_STRANGE_DEFENCE,
	ATTRIBUTE_TO_UPDATE_WILD_OFFENCE,
	ATTRIBUTE_TO_UPDATE_WILD_DEFENCE,
	ATTRIBUTE_TO_UPDATE_ELEGANCE_OFFENCE,
	ATTRIBUTE_TO_UPDATE_ELEGANCE_DEFENCE,
	ATTRIBUTE_TO_UPDATE_FUNNY_OFFENCE,
	ATTRIBUTE_TO_UPDATE_FUNNY_DEFENCE,

	ATTRIBUTE_TO_UPDATE_UNKNOW2,

	ATTRIBUTE_TO_UPDATE_PARALYZE_TOLERANCE_RATE,
	ATTRIBUTE_TO_UPDATE_TERROR_TOLERANCE_RATE,
	ATTRIBUTE_TO_UPDATE_CONFUSE_TOLERANCE_RATE,
	ATTRIBUTE_TO_UPDATE_STONE_TOLERANCE_RATE,
	ATTRIBUTE_TO_UPDATE_CANDY_TOLERANCE_RATE,

	ATTRIBUTE_TO_UPDATE_PARALYZE_KEEP_TIME_DOWN,
	ATTRIBUTE_TO_UPDATE_TERROR_KEEP_TIME_DOWN,
	ATTRIBUTE_TO_UPDATE_CONFUSE_KEEP_TIME_DOWN,
	ATTRIBUTE_TO_UPDATE_STONE_KEEP_TIME_DOWN,
	ATTRIBUTE_TO_UPDATE_CANDY_KEEP_TIME_DOWN,
	ATTRIBUTE_TO_UPDATE_BLEEDING_KEEP_TIME_DOWN,
	ATTRIBUTE_TO_UPDATE_POISON_KEEP_TIME_DOWN,
	ATTRIBUTE_TO_UPDATE_STOMACHACHE_KEEP_TIME_DOWN,

	ATTRIBUTE_TO_UPDATE_CRITICAL_BLOCK_SUCCESS_RATE,

	ATTRIBUTE_TO_UPDATE_GUARD_RATE_BASE,

	ATTRIBUTE_TO_UPDATE_UNKNOW6,

	ATTRIBUTE_TO_UPDATE_SKILL_DAMAGE_BLOCK_MODE_SUCCESS_RATE_LAST,
	ATTRIBUTE_TO_UPDATE_CURSE_BLOCK_MODE_SUCCESS_RATE_LAST,
	ATTRIBUTE_TO_UPDATE_KNOCKDOWN_BLOCK_MODE_SUCCESS_RATE_LAST,
	ATTRIBUTE_TO_UPDATE_HTB_BLOCK_MODE_SUCCESS_RATE_LAST,

	ATTRIBUTE_TO_UPDATE_SIT_DOWN_LP_REGENERATION_UP,
	ATTRIBUTE_TO_UPDATE_SIT_DOWN_EP_REGENERATION_UP,
	ATTRIBUTE_TO_UPDATE_PHYSICAL_CRITICAL_DAMAGE_UP,
	ATTRIBUTE_TO_UPDATE_ENERGY_CRITICAL_DAMAGE_UP,

	ATTRIBUTE_TO_UPDATE_ITEM_UPGRADE_RATE_UP,
	ATTRIBUTE_TO_UPDATE_ITEM_BREAK_RATE_DOWN,

	ATTRIBUTE_TO_UPDATE_UNKNOW3_0,
	ATTRIBUTE_TO_UPDATE_UNKNOW3_1,
	ATTRIBUTE_TO_UPDATE_UNKNOW3_2,
	ATTRIBUTE_TO_UPDATE_SKILL_SPEED,
	ATTRIBUTE_TO_UPDATE_UNKNOW3_4,
	ATTRIBUTE_TO_UPDATE_UNKNOW3_5,
	ATTRIBUTE_TO_UPDATE_MAX_WEIGHT,
	ATTRIBUTE_TO_UPDATE_UNKNOW3_w6,
	ATTRIBUTE_TO_UPDATE_UNKNOW3_7,
	ATTRIBUTE_TO_UPDATE_UNKNOW3_8,
	ATTRIBUTE_TO_UPDATE_UNKNOW3_9,
	ATTRIBUTE_TO_UPDATE_UNKNOW3_10,
	ATTRIBUTE_TO_UPDATE_UNKNOW3_11,
	ATTRIBUTE_TO_UPDATE_UNKNOW3_12,
	ATTRIBUTE_TO_UPDATE_UNKNOW3_13,

	ATTRIBUTE_TO_UPDATE_UNKNOW4_0,
	ATTRIBUTE_TO_UPDATE_UNKNOW4_1,
	ATTRIBUTE_TO_UPDATE_UNKNOW4_2,
	ATTRIBUTE_TO_UPDATE_UNKNOW4_3,
	ATTRIBUTE_TO_UPDATE_UNKNOW4_4,
	ATTRIBUTE_TO_UPDATE_UNKNOW4_5,
	ATTRIBUTE_TO_UPDATE_UNKNOW4_6,

	ATTRIBUTE_TO_UPDATE_UNKNOW5_0,
	ATTRIBUTE_TO_UPDATE_UNKNOW5_1,
	ATTRIBUTE_TO_UPDATE_UNKNOW5_2,
	ATTRIBUTE_TO_UPDATE_UNKNOW5_3,
	ATTRIBUTE_TO_UPDATE_UNKNOW5_4,
	ATTRIBUTE_TO_UPDATE_UNKNOW5_5,

	ATTRIBUTE_TO_UPDATE_COUNT,
	ATTRIBUTE_TO_UPDATE_UNKNOWN = 0xFF,

	ATTRIBUTE_TO_UPDATE_FIRST = ATTRIBUTE_TO_UPDATE_STR_BASE,
	ATTRIBUTE_TO_UPDATE_LAST = ATTRIBUTE_TO_UPDATE_COUNT - 1,
};

#pragma pack(push, 1)

struct sAVATAR_ATTRIBUTE
{
	WORD byBaseStr;
	WORD byLastStr;
	WORD byBaseCon;
	WORD byLastCon;
	WORD byBaseFoc;
	WORD byLastFoc;
	WORD byBaseDex;
	WORD byLastDex;
	WORD byBaseSol;
	WORD byLastSol;
	WORD byBaseEng;
	WORD byLastEng;
	//
	DWORD wBaseMaxLP;
	DWORD wLastMaxLP;
	WORD wBaseMaxEP;
	WORD wLastMaxEP;
	DWORD wBaseMaxAp;
	DWORD wLastMaxAp;
	WORD wBaseMaxRP;
	WORD wLastMaxRP;
	//
	WORD wBaseLpRegen;
	WORD wLastLpRegen;
	WORD wBaseLpSitdownRegen;
	WORD wLastLpSitdownRegen;
	WORD wBaseLpBattleRegen;
	WORD wLastLpBattleRegen;
	//
	WORD wBaseEpRegen;
	WORD wLastEpRegen;
	WORD wBaseEpSitdownRegen;
	WORD wLastEpSitdownRegen;
	WORD wBaseEpBattleRegen;
	WORD wLastEpBattleRegen;
	//
	WORD wBaseApRegen;
	WORD wLastApRegen;
	WORD wBaseApSitdownRegen;
	WORD wLastApSitdownRegen;
	WORD wBaseApBattleRegen;
	WORD wLastApBattleRegen;
	//
	WORD unknown_int16_0;//wBaseApDegen
	WORD unknown_int16_1;//wLastApDegen
	WORD unknown_int16_2;//wBaseApBattleDegen
	WORD unknown_int16_3;//wLastApBattleDegen
	//
	WORD wBaseRpRegen;
	WORD wLastRpRegen;
	WORD wLastRpDimimutionRate;
	//
	WORD wBasePhysicalOffence;
	WORD wLastPhysicalOffence;
	WORD wBasePhysicalDefence;
	WORD wLastPhysicalDefence;
	//
	//unsigned __int16 wBasePhysicalPiercingOffence;
	//unsigned __int16 wLastPhysicalPiercingOffence;
	//
	WORD wBaseEnergyOffence;
	WORD wLastEnergyOffence;
	WORD wBaseEnergyDefence;
	WORD wLastEnergyDefence;
	//
	//unsigned __int16 wBaseEnergyPiercingOffence;
	//unsigned __int16 wLastEnergyPiercingOffence;
	//
	WORD wBaseAttackRate;
	WORD wLastAttackRate;
	WORD wBaseDodgeRate;
	WORD wLastDodgeRate;
	WORD wBaseBlockRate;
	WORD wLastBlockRate;
	//
	//unsigned __int16 wBaseBlockDamageRate;
	//unsigned __int16 wLastBlockDamageRate;
	//
	WORD wBaseCurseSuccessRate;
	WORD wLastCurseSuccessRate;
	WORD wBaseCurseToleranceRate;
	WORD wLastCurseToleranceRate;

	WORD unknown_rate1;// wBaseBlockDamageRate
	WORD unknown_rate2;// wLastBlockDamageRate

	WORD wBasePhysicalCriticalRate;
	WORD wLastPhysicalCriticalRate;
	WORD wBaseEnergyCriticalRate;
	WORD wLastEnergyCriticalRate;

	float unknown_float1_0;//??
	float unknown_float1_1;//??
	float unknown_float2_0;//??
	float unknown_float2_1;//??

	float fBaseRunSpeed;
	float fLastRunSpeed;

	float fBaseAirSpeed;
	float fLastAirSpeed;
	float fBaseAirDashSpeed;
	float fLastAirDashSpeed;
	float fBaseAirDash2Speed;
	float fLastAirDash2Speed;


	WORD wBaseAttackSpeedRate;
	WORD wLastAttackSpeedRate;
	float fBaseAttackRange;
	float fLastAttackRange;

	float fCastingTimeChangePercent;
	float fCoolTimeChangePercent;
	float fKeepTimeChangePercent;
	float fDotValueChangePercent;
	float fDotTimeChangeAbsolute;
	float fRequiredEpChangePercent;
	
	float fHonestOffence;
	float fHonestDefence;
	float fStrangeOffence;
	float fStrangeDefence;
	float fWildOffence;
	float fWildDefence;
	float fEleganceOffence;
	float fEleganceDefence;
	float fFunnyOffence;
	float fFunnyDefence;

	float unknown2;// mob speed maybe

	WORD wParalyzeToleranceRate;
	WORD wTerrorToleranceRate;
	WORD wConfuseToleranceRate;
	WORD wStoneToleranceRate;
	WORD wCandyToleranceRate;

	float fParalyzeKeepTimeDown;
	float fTerrorKeepTimeDown;
	float fConfuseKeepTimeDown;
	float fStoneKeepTimeDown;
	float fCandyKeepTimeDown;
	float fBleedingKeepTimeDown;
	float fPoisonKeepTimeDown;
	float fStomachacheKeepTimeDown;

	float fCriticalBlockSuccessRate;

	WORD wGuardRate;
	DWORD unknown6;

	DWORD fSkillDamageBlockModeSuccessRate;
	DWORD fCurseBlockModeSuccessRate;
	DWORD fKnockdownBlockModeSuccessRate;

	DWORD fHtbBlockModeSuccessRate;//bleeding defese
	DWORD fSitDownLpRegenBonusRate;// posion defese
	DWORD fSitDownEpRegenBonusRate;// defesa sangramento
	DWORD fPhysicalCriticalDamageBonusRate; //burn defese

	DWORD fEnergyCriticalDamageBonusRate;
	DWORD fItemUpgradeBonusRate;
	DWORD fItemUpgradeBreakBonusRate;

	float unknown3_0;//??
	float unknown3_1;//??
	float unknown3_2;//??
	float unknown3_3;//??
	float SkillSpeed;//??
	float unknown3_5;//??
	WORD MaxWeight;
	WORD unknown3_w6;
	//float unknown3_6;//??
	float unknown3_7;//??
	float unknown3_8;//??
	float unknown3_9;//??
	float unknown3_10;//??
	float unknown3_11;//??
	float unknown3_12;//??
	float unknown3_13;//??
	WORD unknown4_0;//??
	WORD unknown4_1;//??
	WORD unknown4_2;//??
	WORD unknown4_3;//??
	WORD unknown4_4;//??
	WORD unknown4_5;//??
	WORD unknown4_6;//??
	float unknown5_0;//??
	float unknown5_1;//??
	float unknown5_2;//??
	float unknown5_3;//??
	float unknown5_4;//??
	WORD unknown5_5;//??
};

struct sAVATAR_ATTRIBUTE_LINK
{
	WORD* pbyBaseStr;
	WORD* pbyLastStr;
	WORD* pbyBaseCon;
	WORD* pbyLastCon;
	WORD* pbyBaseFoc;
	WORD* pbyLastFoc;
	WORD* pbyBaseDex;
	WORD* pbyLastDex;
	WORD* pbyBaseSol;
	WORD* pbyLastSol;
	WORD* pbyBaseEng;
	WORD* pbyLastEng;

	DWORD* pwBaseMaxLP;
	DWORD* pwLastMaxLP;
	WORD* pwBaseMaxEP;
	WORD* pwLastMaxEP;
	DWORD* pwBaseMaxAp;
	DWORD* pwLastMaxAp;
	WORD* pwBaseMaxRP;
	WORD* pwLastMaxRP;

	WORD* pwBaseLpRegen;
	WORD* pwLastLpRegen;
	WORD* pwBaseLpSitdownRegen;
	WORD* pwLastLpSitdownRegen;
	WORD* pwBaseLpBattleRegen;
	WORD* pwLastLpBattleRegen;

	WORD* pwBaseEpRegen;
	WORD* pwLastEpRegen;
	WORD* pwBaseEpSitdownRegen;
	WORD* pwLastEpSitdownRegen;
	WORD* pwBaseEpBattleRegen;
	WORD* pwLastEpBattleRegen;

	WORD* pwBaseApRegen;
	WORD* pwLastApRegen;
	WORD* pwBaseApSitdownRegen;
	WORD* pwLastApSitdownRegen;
	WORD* pwBaseApBattleRegen;
	WORD* pwLastApBattleRegen;

	WORD *unknown_int16_0;
	WORD *unknown_int16_1;
	WORD *unknown_int16_2;
	WORD *unknown_int16_3;

	WORD* pwBaseRpRegen;
	WORD* pwLastRpRegen;
	WORD* pwLastRpDimimutionRate;

	WORD* pwBasePhysicalOffence;
	WORD* pwLastPhysicalOffence;
	WORD* pwBasePhysicalDefence;
	WORD* pwLastPhysicalDefence;

	WORD* pwBaseEnergyOffence;
	WORD* pwLastEnergyOffence;
	WORD* pwBaseEnergyDefence;
	WORD* pwLastEnergyDefence;

	WORD* pwBaseAttackRate;
	WORD* pwLastAttackRate;
	WORD* pwBaseDodgeRate;
	WORD* pwLastDodgeRate;
	WORD* pwBaseBlockRate;
	WORD* pwLastBlockRate;

	WORD* pwBaseCurseSuccessRate;
	WORD* pwLastCurseSuccessRate;
	WORD* pwBaseCurseToleranceRate;
	WORD* pwLastCurseToleranceRate;

	WORD* pwunknown_rate1;// ??
	WORD* pwunknown_rate2;// ??

	WORD* pwBasePhysicalCriticalRate;
	WORD* pwLastPhysicalCriticalRate;
	WORD* pwBaseEnergyCriticalRate;
	WORD* pwLastEnergyCriticalRate;

	float *unknown_float1_0;//??
	float *unknown_float1_1;//??
	float *unknown_float2_0;//??
	float *unknown_float2_1;//??

	float* pfBaseRunSpeed;
	float* pfLastRunSpeed;

	float* pfBaseAirSpeed;
	float* pfLastAirSpeed;
	float* pfBaseAirDashSpeed;
	float* pfLastAirDashSpeed;
	float* pfBaseAirDash2Speed;
	float* pfLastAirDash2Speed;

	WORD* pwBaseAttackSpeedRate;
	WORD* pwLastAttackSpeedRate;
	float* pfBaseAttackRange;
	float* pfLastAttackRange;

	float* pfCastingTimeChangePercent;
	float* pfCoolTimeChangePercent;
	float* pfKeepTimeChangePercent;
	float* pfDotValueChangePercent;
	float* pfDotTimeChangeAbsolute;
	float* pfRequiredEpChangePercent;

	float* pfHonestOffence;
	float* pfHonestDefence;
	float* pfStrangeOffence;
	float* pfStrangeDefence;
	float* pfWildOffence;
	float* pfWildDefence;
	float* pfEleganceOffence;
	float* pfEleganceDefence;
	float* pfFunnyOffence;
	float* pfFunnyDefence;

	float* pfunknown2;//??

	WORD* pwParalyzeToleranceRate;
	WORD* pwTerrorToleranceRate;
	WORD* pwConfuseToleranceRate;
	WORD* pwStoneToleranceRate;
	WORD* pwCandyToleranceRate;

	float* pfParalyzeKeepTimeDown;
	float* pfTerrorKeepTimeDown;
	float* pfConfuseKeepTimeDown;
	float* pfStoneKeepTimeDown;
	float* pfCandyKeepTimeDown;
	float* pfBleedingKeepTimeDown;
	float* pfPoisonKeepTimeDown;
	float* pfStomachacheKeepTimeDown;

	float* pfCriticalBlockSuccessRate;

	WORD*  pwGuardRate;
	DWORD*  pwunknown6;

	DWORD* pfSkillDamageBlockModeSuccessRate;
	DWORD* pfCurseBlockModeSuccessRate;
	DWORD* pfKnockdownBlockModeSuccessRate;
	DWORD* pfHtbBlockModeSuccessRate;

	DWORD* pfSitDownLpRegenBonusRate;
	DWORD* pfSitDownEpRegenBonusRate;

	DWORD* pfPhysicalCriticalDamageBonusRate;
	DWORD* pfEnergyCriticalDamageBonusRate;

	DWORD* pfItemUpgradeBonusRate;
	DWORD* pfItemUpgradeBreakBonusRate;

	float *unknown3_0;//??
	float *unknown3_1;//??
	float *unknown3_2;//??
	float *unknown3_3;//??
	float *SkillSpeed;//??
	float *unknown3_5;//??
	WORD *MaxWeight;
	WORD *unknown3_w6;//??
	float *unknown3_7;//??
	float *unknown3_8;//??
	float *unknown3_9;//??
	float *unknown3_10;//??
	float *unknown3_11;//??
	float *unknown3_12;//??
	float *unknown3_13;//??
	WORD *unknown4_0;//??
	WORD *unknown4_1;//??
	WORD *unknown4_2;//??
	WORD *unknown4_3;//??
	WORD *unknown4_4;//??
	WORD *unknown4_5;//??
	WORD *unknown4_6;//??
	float *unknown5_0;//??
	float *unknown5_1;//??
	float *unknown5_2;//??
	float *unknown5_3;//??
	float *unknown5_4;//??
	WORD *unknown5_5;//??
};
#pragma pack(pop)

class CNtlBitFlagManager;

class CNtlAvatar
{
public:
	struct sATTRIBUTE_LOGIC
	{
		DWORD dwFieldOffset;
		DWORD(*pCopyAttributeFunction)(void* pvBuffer, void* pvValue);
	};

protected:
	CNtlAvatar(void);
public:
	virtual ~CNtlAvatar(void);

protected:
	void Init();

	virtual void InitializeAttributeLink();

public:
	static CNtlAvatar* GetInstance();

public:
	// ÆÐÅ¶ÀÇ raw µ¥ÀÌÅ¸·ÎºÎÅÍ sAVATAR_ATTRIBUTE ±¸Á¶Ã¼¸¦ ¾÷µ¥ÀÌÆ®ÇÑ´Ù.(ÁÖ·Î Å¬¶óÀÌ¾ðÆ®¿¡¼­ »ç¿ëÇÏ°Ô µÈ´Ù.)
	// Updates sAVATAR_ATTRIBUTE structure with using raw data in a packet.(This function will be used mainly on client-side.)
	//
	// (ÆÐÅ¶ -> ¸ÞÅ¸ µ¥ÀÌÅ¸ + sAVATAR_ATTRIBUTE)
	// (Packet -> Meta data + sAVATAR_ATTRIBUTE)
	//
	static bool UpdateAvatarAttribute(BYTE byAttributeTotalCount, void* pvRawData, sAVATAR_ATTRIBUTE* pAttributeData);

	// ¼Ó¼º µ¥ÀÌÅ¸¸¦ ÆÐÅ¶ÀÇ raw µ¥ÀÌÅ¸·Î ÀúÀåÇÑ´Ù.(ÁÖ·Î ¼­¹ö¿¡¼­ »ç¿ëÇÏ°Ô µÈ´Ù.)
	// Generates raw data in a packet with using attribute data.(This function will be used mainly on server-side.)
	//
	// (¸ÞÅ¸ µ¥ÀÌÅ¸ + ¼Ó¼º µ¥ÀÌÅ¸ -> ÆÐÅ¶)
	// (Meta data + Attribute data -> Packet)
	//
	static bool SaveAvatarAttribute(CNtlBitFlagManager* pChangedFlag, sAVATAR_ATTRIBUTE_LINK* pAttributeDataLink, void* pvBuffer, DWORD* pwdDataSize);

	// ¼Ó¼º µ¥ÀÌÅ¸¸¦ sAVATAR_ATTRIBUTE ±¸Á¶Ã¼·Î º¹»çÇÑ´Ù.(ÁÖ·Î ¼­¹ö¿¡¼­ »ç¿ëÇÏ°Ô µÈ´Ù.)
	// Copies attribute data into sAVATAR_ATTRIBUTE structure.(This function will be used mainly on server-side.)
	//
	// (¼Ó¼º µ¥ÀÌÅ¸ -> sAVATAR_ATTRIBUTE)
	// (Attribute data -> sAVATAR_ATTRIBUTE)
	//
	static bool FillAvatarAttribute(sAVATAR_ATTRIBUTE_LINK* pAttributeDataLink, sAVATAR_ATTRIBUTE* pAttributeData);
	//Convert Attributes - Luiz45
	static sAVATAR_ATTRIBUTE_LINK ConvertAttributeToAttributeLink(sAVATAR_ATTRIBUTE* pAttribute);

	static sATTRIBUTE_LOGIC m_attributeLogic[ATTRIBUTE_TO_UPDATE_COUNT];
protected:
	

	static DWORD CopyValueByType_BYTE(void* pvValue, void* pvBuffer);
	static DWORD CopyValueByType_WORD(void* pvValue, void* pvBuffer);
	static DWORD CopyValueByType_float(void* pvValue, void* pvBuffer);
	static DWORD CopyValueByType_DWORD(void* pvValue, void* pvBuffer);
};