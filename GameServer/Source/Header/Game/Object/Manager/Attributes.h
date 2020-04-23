#ifndef __ATTRIBUTES_H
#define __ATTRIBUTES_H

#pragma once

#include <Packet\Game\PacketGU.h>
#include <TableAll.h>
#include <DboTSCoreDefine.h>

class Player;
class Object;

struct OutWorld
{
	sVECTOR3	position;
	sVECTOR3	rotation;
	TBLIDX		worldTblidx;
};

struct TeleportInfo
{
	sVECTOR3	position;
	sVECTOR3	rotation;
	BYTE		byTeleportType;
	bool		bIsToMoveAnotherServer;
	sWORLD_INFO worldInfo;
	OutWorld	outWorld;
};

struct ObjectDataQuest
{
	TBLIDX				objTblidx;
	NTL_TS_T_ID			specificQuestId;
	NTL_TS_T_ID			triggerObject;
	NTL_TS_T_ID			triggerId;
	int					evtId;
	std::vector<TBLIDX> mobsTblidx;
	std::vector<TBLIDX> NPCTblidx;
};
struct SubClassInfoQuest
{
	bool			inQuest;
	HOBJECT			npcHandle;
	TBLIDX			useItemTblidx;
	bool			majinKarmaObject;
	int				curQuestId;
	BYTE			objChoseIndex;
	ObjectDataQuest	objData[2];
};

struct TLQ1Info
{
	HOBJECT handleNpc;
};

struct TLQ2Info
{
	HOBJECT handleNpc;
};

struct TLQ3Info
{
	HOBJECT handleNpcMilk;
	HOBJECT handleNpc1;
	HOBJECT handleNpc2;
	HOBJECT handleNpc3;
	HOBJECT handleNpcGoku;
	int		maxKillMob;
	int		curKillMob;
};

struct GrowUpInfo
{
	bool			inQuest;
	TBLIDX			mobTblidx;
	int				countKill;
	int				maxKill;
};

struct QuestData
{
	int						QuestID;
	int						RewardID;
	bool					sPawnMobQuest;
	TBLIDX					npcClick;
	TBLIDX					lastNPCQuest;
	HOBJECT					mobHandle;
	NTL_TS_TC_ID			tcId;
	NTL_TS_TA_ID			taId;
	eSTOC_EVT_DATA_TYPE		evtDataType;
	/*int MobID;
	int count;
	int Maxcount;*/
	uSTOC_EVT_DATA			uEvtData;
	sQUEST_PROGRESS_INFO	progressInfo;
	GrowUpInfo				growUpInfo;
	SubClassInfoQuest		questSubCls;
	TLQ1Info				tlq1Info;
	TLQ2Info				tlq2Info;
	TLQ3Info				tlq3Info;
};

struct BuffTimeInfo
{
	HOBJECT			PlayerHandle;
	bool			BuffIsActive;
	DWORD			BuffTime;
	DWORD			BuffEndTime;
	TBLIDX			BuffID;
	BYTE			BuffSlot;
	bool			isAffectPlayer;
	DWORD			EffectType;
	float			EffectValue[2];
	bool			isMob;
	int				StunedType;
	BuffTypeSkill	buffInfo;
	sSKILL_TBLDAT* skillInfo;
};

class AttributesManager
{
public:
	AttributesManager();
	~AttributesManager();
	int Stats[200];
	int MinValue;
	int MaxValue;
	int countstats;
	//Quest
	int KillerCount;
	//bool sPawnMobQuest;
	//TBLIDX			lastNPCQuest;
	//QuestData		QuestDat[30];

	//TLQ 1
	//TLQ1Info tlq1Info;

	// GROW UP

	//GrowUpInfo growUpInfo;

	// SUB CLASS
	//SubClassInfoQuest questSubCls;

	// Teleport
	TeleportInfo teleportInfo;

	//CashShop Info
	DWORD		cashpoit;
	DWORD		WagguCoin;
	DWORD		EventCoin;
	//Player Help get Class/Race
	int			PlayerClassID;
	int			PlayerRaceID;
	int			PlayerGanderID;
	//Free PVP
	DWORD		ReviveDelay;
	bool		ActiveDelay;
	bool        IsinPVP;
	//Control Food Time/Buff Need change	
	struct FoodInfo
	{
		bool		GetFood = false;
		bool		IsRemovedBuff = true;
		TBLIDX		FoodItemID;
		DWORD		TypeEffect;
		float		FoodHealAumont[2];
		DWORD		BuffTime;
		DWORD		BuffKeepTime;
	};
	bool LpFoodIsActive = false;
	bool EpFoodIsActive = false;
	FoodInfo sFoodInfo[16];

	struct SpinningInfo
	{
		DWORD		spinTime;
		DWORD		spinMilisecond;
		DWORD		spinEndTime;
		TBLIDX		skillId;
		bool		forceEndSpin;
		float		damage;
		float		distance;
		BYTE		bySkill_Effect_Type[2];
		double		SkillValue[2];
		std::vector<Object*> enemyList;
	};

	// Control of spin
	SpinningInfo spinInfo;
	
	//Control Stun Time Need change
	BuffTimeInfo sBuffTimeInfo[34];
	int StunedTypes[34];
	// list of effects applied in player
	typedef std::unordered_map<DWORD, std::vector<float>> ATTR_EFFECTS;
	typedef ATTR_EFFECTS::iterator ATTR_EFFECTSIT;

	ATTR_EFFECTS			effectsApplied;

	//std::vector<float> effectsApplied[MAX_SYSTEM_EFFECT_CODE];
	std::vector<BuffTimeInfo> vBuffTimeInfo;
	//////////
	//Caontrol FreeBatle Need change
	int			atackerType;
	int			Type;
	HOBJECT		FreeBatleChellenger;
	bool		PlayerInFreeBatle;
	bool		OutBatle;
	bool		showMensageOut;
	bool		LoseBatle ;
	DWORD		OutBatleTime;
	DWORD		OutBatleFinalTime;
	sVECTOR3	vRefreeLoc;
	//////
	// Control Player Trade Need change
	bool		PlayerTradeOK;
	sITEM_DATA	Tradeinvent[13];
	BYTE		tradecount = 0;
	//Get pet in use
	BYTE		PetInUse;
	//Get Party Info Need change
	HOBJECT		PartyLeader;
	//Transformations

	// Update attr
	void			SetIsUpdated(bool isUpdated) { AttrIsUpdated = isUpdated; };
	bool			GetIsUpdated() { return AttrIsUpdated; };

	// Buffs
	void			AddBuff(BuffTimeInfo buff);
	void			DeleteBuff(TBLIDX buffIdx);
	BuffTimeInfo*	GetBuff(TBLIDX buffIdx);
	// Attributes effect list
	float			AddAttrEffect(WORD effectType, float value);
	float			DeleteAttrEffect(WORD effectType, float value);
	float			GetAttrEffectByType(WORD effectType, float value, bool addRemove);
	std::vector<float> GetAttrEffects(WORD effectType);
	float			SetAllEffects(WORD actEffectUp, WORD actEffectDown, WORD pasEffectType, float originalValue);

	//RP Passive
	bool			IsPowerUp;
	DWORD			RPTimer;
	bool			LoadAttributes(CHARACTERID _id, Player* _plr);
	bool			SaveAvatarAttribute(void* pvBuffer, DWORD* pwdDataSize);
	void			UpdateLevelUpAtributes();
	void			LoadAttributesFromItems(sITEM_BRIEF *brief);
	void			FillAttributesLink();
	void			SendRpBallInformation();
	void			CreatePlayerBaseAttributesBitFlag();
	void			UpdateAttributes();
	void			UpdateAttributesFromItem(sITEM_TBLDAT& item, BYTE Grade, bool remove = false);
	void			UpdateExtraAttributesFromItem(sITEM_EFFECT aitemEffect[6], bool isRemove = false);

	// Spinning attack
	bool			IsInListSpin(HOBJECT hTarget);
	void			AddEnemyToSpinList(Object* enemy);
	void			DeleteEnemy(HOBJECT hTarget);

	// Calcule stats
	int				CalculeBasicStats(WORD basicStat, float basicStatLvUp, BYTE playerLevel);
	DWORD			CalculeLP(BYTE pcClass, int lastCon);
	WORD			CalculeEP(BYTE pcClass, int lastEng);
	int				CalculeRP(BYTE playerLevel);
	WORD			CalculePhysicalOffence(BYTE pcClass, BYTE playerLevel, int lastStr, int lastDex);
	WORD			CalculeEnergyOffence(BYTE pcClass, BYTE playerLevel, int lastSol, int lastFoc);
	WORD			CalculePhysicalCriticalRate(BYTE pcClass, int lastDex);
	WORD			CalculeEnergyCriticalRate(BYTE pcClass, int lastFoc);
	WORD			CalculeHitRate(int lastFoc);
	WORD			CalculeDodgeRate(int lastDex);
	WORD			CalculeBlockRate(int lastDex, int lastCon);
	WORD			CalculePhysicalCriticalDefenceRate(int lastCon);
	WORD			CalculeEnergyCriticalDefenceRate(int lastEng);
	float			CalculePhysicalCriticalRange(BYTE pcClass, int lastDex);
	float			CalculeEnergyCriticalRange(BYTE pcClass, int lastFoc);
	WORD			CalculeLPRegeneration(int lastCon);
	WORD			CalculeLPSitDownRegeneration(WORD lastLpRegeneration);
	WORD			CalculeEPRegeneration(int lastEng);
	WORD			CalculeEPSitDownRegeneration(WORD lastEpRegeneration);
	WORD			CalculeEPBattleRegeneration(WORD lastEpRegeneration);
	WORD			CalculeRPRegeneration(WORD maxRP);
	WORD			CalculeRPDiminution(WORD maxRP);
	WORD			CalculeRPHitCharge(BYTE deffLevel, BYTE attLevel);
	WORD			CalculeRPHitChargeRate(BYTE deffLevel, BYTE attLevel);
	WORD			CalculeCurseSuccessRate(int lastFoc);
	WORD			CalculeCurseToleranceRate(int lastDex);
	WORD			CalculeBlockDamageRate(int lastDex, int lastCon);
	WORD			CalculeGuardRate(int lastDex);

	float			GetPercent(float percent, float value);

	// Update cascading stats bool add = 0 add, 1 set
	// Update cascading stats bool addRemove = true add, false remove
	// Update phyicalOffence
	void			UpdateStr(WORD effectType, int lastStr, bool add, bool addRemove);
	// Update LP, blockRate, physicalCriticalDefenceRate, blockDamageRate
	void			UpdateCon(WORD effectType, int lastCon, bool add, bool addRemove);
	// Update energyOffence, energyCriticalRate, hitRate(attackRate), energyCriticalRange, curseSuccessRate
	void			UpdateFoc(WORD effectType, int lastFoc, bool add, bool addRemove);
	// Update physicalOffence, physicalCriticalRate, dodgeRate, blockRate, physicalCriticalRange, curseToleranceRate, blockDamageRate, guardRate
	void			UpdateDex(WORD effectType, int lastDex, bool add, bool addRemove);
	// Update energyOffence
	void			UpdateSol(WORD effectType, int lastSol, bool add, bool addRemove);
	// Update EP and EnergyCriticalDefenceRate
	void			UpdateEng(WORD effectType, int lastEng, bool add, bool addRemove);
	void			UpdateLP(WORD effectType, DWORD lp, bool add, bool addRemove);
	void			UpdateEP(WORD effectType, WORD ep, bool add, bool addRemove);
	// Update RpRegeneration and RPDiminution
	void			UpdateRP(WORD effectType, int rp, bool add, bool addRemove);
	void			UpdatePhysicalOffence(WORD effectType, WORD physicalOffence, bool add, bool addRemove);
	void			UpdatePhysicalDefence(WORD effectType, WORD physicalDefence, bool add, bool addRemove);
	void			UpdateEnergyOffence(WORD effectType, WORD energyOffence, bool add, bool addRemove);
	void			UpdateEnergyDefence(WORD effectType, WORD energyDefence, bool add, bool addRemove);
	void			UpdatePhysicalCriticalRate(WORD effectType, WORD physicalCriticalRate, bool add, bool addRemove);
	void			UpdateEnergyCriticalRate(WORD effectType, WORD energyCriticalRate, bool add, bool addRemove);
	void			UpdateHitRate(WORD effectType, WORD hitRate, bool add, bool addRemove);
	void			UpdateDodgeRate(WORD effectType, WORD dodgeRate, bool add, bool addRemove);
	void			UpdateBlockRate(WORD effectType, WORD blockRate, bool add, bool addRemove);
	void			UpdatePhysicalCriticalDefenceRate(WORD physicalCriticalDefenceRate, bool add);
	void			UpdateEnergyCriticalDefenceRate(WORD energyCriticalDefenceRate, bool add);
	void			UpdatePhysicalCriticalRange(WORD effectType, float physicalCriticalRange, bool add, bool addRemove);
	void			UpdateEnergyCriticalRange(WORD effectType, float energyCriticalRange, bool add, bool addRemove);
	// Update LPSitDownRegeneration
	void			UpdateLPRegeneration(WORD effectType, WORD LpRegen, bool add, bool addRemove);
	void			UpdateLPSitDownRegeneration(WORD effectType, WORD lpSitDownRegen, bool add, bool addRemove);
	// Update EPSitDownRegeneration, EPBattleRegeneration
	void			UpdateEPRegeneration(WORD effectType, WORD EpRegen, bool add, bool addRemove);
	void			UpdateEPSitDownRegeneration(WORD effectType, WORD epSitDownRegen, bool add, bool addRemove);
	void			UpdateEPBattleRegeneration(WORD epBattleRegen, bool add);
	void			UpdateRPRegeneration(WORD effectType, WORD RPRegen, bool add, bool addRemove);
	void			UpdateRPDiminution(WORD RPDimin, bool add);
	void			UpdateCurseSuccessRate(WORD effectType, WORD curseSuccessRate, bool add, bool addRemove);
	void			UpdateCurseToleranceRate(WORD effectType, WORD curseToleranceRate, bool add, bool addRemove);
	void			UpdateRunSpeed(WORD effectType, float runSpeed, bool add, bool addRemove);
	void			UpdateCoolTimeChangePercent(WORD effectType, float coolTimeChange, bool add, bool addRemove);
	void			UpdateAttackspeedRate(WORD effectType, WORD attackSpeed, bool add, bool addRemove);
	void			UpdateBlockDamageRate(WORD effectType, WORD blockDamageRate, bool add, bool addRemove);
	void			UpdateGuardRate(WORD effectType, WORD guardRate, bool add, bool addRemove);
	void			UpdateGuardNormalSuccess(WORD effectType, float guardNormalSuccess, bool add, bool addRemove);
	void			UpdateGuardHTBSuccess(WORD effecType, float guardHTBSuccess, bool add, bool addRemove);
	void			UpdateGuardKnockdownSuccess(WORD effectType, float guardKnockdownSuccess, bool add, bool addRemove);
	void			UpdateGuardCurseSuccess(WORD effectType, float guardCurseSuccess, bool add, bool addRemove);
	void			UpdateGuardCriticalSuccess(WORD effectType, float guardCriticalSuccess, bool add, bool addRemove);
	void			UpdateAgroPointsPercent(WORD effectType, float agroPoints, bool add, bool addRemove);
	void			UpdateAgroPointsAbsolute(WORD effectType, float agroPoints, bool add, bool addRemove);
	void			UpdateDirectHealPerecent(WORD effectType, float directHeal, bool add, bool addRemove);
	void			UpdateDirectHealAbsolute(WORD effectType, float directHeal, bool add, bool addRemove);
	void			UpdateHealOverTimePercent(WORD effectType, float healOverTime, bool add, bool addRemove);
	void			UpdateHealOverTimeAbsolute(WORD effectType, float healOverTime, bool add, bool addRemove);
	void			UpdateBleedingDefence(WORD effectType, WORD bleedingDefence, bool add, bool addRemove);
	void			UpdateBurnDefence(WORD effectType, WORD burnDefence, bool add, bool addRemove);

	void			UpdateHonestOffence(WORD effectType, float honestOffence, bool add, bool addRemove);
	void			UpdateHonestDefence(WORD effectType, float honestDefence, bool add, bool addRemove);
	void			UpdateStrangeOffence(WORD effectType, float strangeOffence, bool add, bool addRemove);
	void			UpdateStrandeDefence(WORD effectType, float strangeDefenece, bool add, bool addRemove);
	void			UpdateWildOffence(WORD effectType, float wildOffence, bool add, bool addRemove);
	void			UpdateWildDefence(WORD effectType, float wildDefence, bool add, bool addRemove);
	void			UpdateEleganceOffence(WORD effectType, float eleganceOffence, bool add, bool addRemove);
	void			UpdateEleganceDefence(WORD effectType, float eleganceDefence, bool add, bool addRemove);
	void			UpdateFunnyOffence(WORD effectType, float funnyOffence, bool add, bool addRemove);
	void			UpdateFunnyDefence(WORD effectType, float funnyDefence, bool add, bool addRemove);
	void			UpdateBleedingKeepTime(WORD effectType, float bleedingKeepTime, bool add, bool addRemove);
	//	------------------------------------------------------------------------
	// GETTER
	//	------------------------------------------------------------------------
	sPC_PROFILE*	GetPlayerProfile() { return &PlayerProfile; }
	int				GetNumRpBall();
	int				GetNumFilledRpBall();
	//	------------------------------------------------------------------------
	// SETTERS
	//	------------------------------------------------------------------------
	void			SetNumFilledRpBall(int newBall);
	
	
private:
	bool			LoadCharacterAttrFromDB(sPC_TBLDAT* pTblData);
	bool			LoadAttributeFromDB();
	void			SetRPBall();

	bool			AttrIsUpdated;

	// CHARACTER
	sPC_PROFILE		PlayerProfile;
	sAVATAR_ATTRIBUTE_LINK	attrLink;
	// RP BALL
	int				RPCounter;
	int				RPFilledCounter;
	// UPDATE ATTRIBUTES
	CNtlBitFlagManager	changedFlag;

	CHARACTERID		charid;
	Player			*plr;

public:
	void SetLastStr(WORD val);
	void SetLastCon(WORD val);
	void SetLastFoc(WORD val);
	void SetLastDex(WORD val);
	void SetLastEng(WORD val);
	void SetLastSol(WORD val);
	void SetLastMaxLP(DWORD val);
	void SetLastMaxEP(WORD val);
	void SetLastMaxAP(DWORD val);
	void SetLastMaxRP(WORD val);
	void SetLastLPRegen(WORD val);
	void SetLastEPRegen(WORD val);
	void SetLastAPRegen(WORD val);
	void SetLastPhysicalOffence(WORD val);
	void SetLastPhysicalDefence(WORD val);
	void SetLastEnergyOffence(WORD val);
	void SetLastEnergyDefence(WORD val);
	void SetLastAttackRate(WORD val);
	void SetLastDodgeRate(WORD val);
	void SetLastBlockRate(WORD val);
	void SetLastCurseSuccessRate(WORD val);
	void SetLastCurseToleranceRate(WORD val);
	void SetLastPhysicalCriticalRate(WORD val);
	void SetLastEnergyCriticalRate(WORD val);
	void SetLastRunSpeed(float val);
	void SetLastAirSpeed(float val);
	void SetLastAirDashSpeed(float val);
	void SetLastAirDash2Speed(float val);
	void SetLastAttackSpeedRate(WORD val);
	void SetLastAttackRange(float val);
	void SetCastingTimeChangePercent(float val);
	void SetCoolTimeChangePercent(float val);
	void SetKeepTimeChangePercent(float val);
	void SetKeepTimeChangeSeconds(float val);
	void SetDotValueChangePercent(float val);
	void SetDotTimeChangeAbsolute(float val);
	void SetRequiredEpChangePercent(float val);
	void SetHonestOffence(float val);
	void SetHonestDefence(float val);
	void SetStrangeOffence(float val);
	void SetStrangeDefence(float val);
	void SetWildOffence(float val);
	void SetWildDefence(float val);
	void SetEleganceOffence(float val);
	void SetEleganceDefence(float val);
	void SetFunnyOffence(float val);
	void SetFunnyDefence(float val);
	void SetParalyzeToleranceRate(WORD val);
	void SetTerrorToleranceRate(WORD val);
	void SetConfuseToleranceRate(WORD val);
	void SetStoneToleranceRate(WORD val);
	void SetCandyToleranceRate(WORD val);
	void SetParalyzeKeepTimeDown(float val);
	void SetTerrorKeepTimeDown(float val);
	void SetConfuseKeepTimeDown(float val);
	void SetStoneKeepTimeDown(float val);
	void SetCandyKeepTimeDown(float val);
	void SetBleedingKeepTimeDown(float val);
	void SetPoisonKeepTimeDown(float val);
	void SetStomachacheKeepTimeDown(float val);
	void SetCriticalBlockSuccessRate(float val);
	void SetGuardRate(WORD val);
	void SetSkillDamageBlockModeSuccessRate(float val);
	void SetCurseBlockModeSuccessRate(float val);
	void SetKnockdownBlockModeSuccessRate(float val);
	void SetHtbBlockModeSuccessRate(float val);
	void SetSitDownLpRegenBonusRate(float val);
	void SetSitDownEpRegenBonusRate(float val);
	void SetPhysicalCriticalDamageBonusRate(float val);
	void SetEnergyCriticalDamageBonusRate(float val);
	void SetItemUpgradeBonusRate(float val);
	void SetItemUpgradeBreakBonusRate(float val);
	void SetSkillSpeed(float val);
	void SetLastPhysicalCriticalDefenceRate(WORD val);
	void SetLastEnergyCriticalDefenceRate(WORD val);
	void SetLastPhysicalCriticalRange(float val);
	void SetLastEnergyCriticalRange(float val);
	void SetLastApDegeneration(WORD val);
	void SetLastApBattleDegeneration(WORD val);
	void SetLastBlockDamageRate(WORD val);
	void SetLastLPSitDownRegeneration(WORD val);
	void SetLastEPSitDownRegeneration(WORD val);
	void SetLastEPBattleRegeneration(WORD val);
	void SetLastRpRegen(WORD val);
	void SetLastRpDimimution(WORD val);
	void SetValueDirectHealChangePercent(float val);
	void SetValueDirectHealChangeAbsolute(float val);
	void SetValueHealOverTimeChangePercent(float val);
	void SetValueHealOverTimeChangeAbsolute(float val);
	void SetAgroPointsPercent(float val);
	void SetAgroPointsAbsolute(float val);
	void SetLastBleedingDefence(WORD val);
	void SetLastBurnDefence(WORD val);

	// Add
	void AddLastStr(WORD val);
	void AddLastCon(WORD val);
	void AddLastFoc(WORD val);
	void AddLastDex(WORD val);
	void AddLastEng(WORD val);
	void AddLastSol(WORD val);
	void AddLastMaxLP(DWORD val);
	void AddLastMaxEP(WORD val);
	void AddLastMaxAP(DWORD val);
	void AddLastMaxRP(WORD val);
	void AddLastLPRegen(WORD val);
	void AddLastEPRegen(WORD val);
	void AddLastAPRegen(WORD val);
	void AddLastPhysicalOffence(WORD val);
	void AddLastPhysicalDefence(WORD val);
	void AddLastEnergyOffence(WORD val);
	void AddLastEnergyDefence(WORD val);
	void AddLastAttackRate(WORD val);
	void AddLastDodgeRate(WORD val);
	void AddLastBlockRate(WORD val);
	void AddLastCurseSuccessRate(WORD val);
	void AddLastCurseToleranceRate(WORD val);
	void AddLastPhysicalCriticalRate(WORD val);
	void AddLastEnergyCriticalRate(WORD val);
	void AddLastRunSpeed(float val);
	void AddLastAirSpeed(float val);
	void AddLastAirDashSpeed(float val);
	void AddLastAirDash2Speed(float val);
	void AddLastAttackSpeedRate(WORD val);
	void AddLastAttackRange(float val);
	void AddCastingTimeChangePercent(float val);
	void AddCoolTimeChangePercent(float val);
	void AddKeepTimeChangePercent(float val);
	void AddKeepTimeChangeSeconds(float val);
	void AddDotValueChangePercent(float val);
	void AddDotTimeChangeAbsolute(float val);
	void AddRequiredEpChangePercent(float val);
	void AddHonestOffence(float val);
	void AddHonestDefence(float val);
	void AddStrangeOffence(float val);
	void AddStrangeDefence(float val);
	void AddWildOffence(float val);
	void AddWildDefence(float val);
	void AddEleganceOffence(float val);
	void AddEleganceDefence(float val);
	void AddFunnyOffence(float val);
	void AddFunnyDefence(float val);
	void AddParalyzeToleranceRate(WORD val);
	void AddTerrorToleranceRate(WORD val);
	void AddConfuseToleranceRate(WORD val);
	void AddStoneToleranceRate(WORD val);
	void AddCandyToleranceRate(WORD val);
	void AddParalyzeKeepTimeDown(float val);
	void AddTerrorKeepTimeDown(float val);
	void AddConfuseKeepTimeDown(float val);
	void AddStoneKeepTimeDown(float val);
	void AddCandyKeepTimeDown(float val);
	void AddBleedingKeepTimeDown(float val);
	void AddPoisonKeepTimeDown(float val);
	void AddStomachacheKeepTimeDown(float val);
	void AddCriticalBlockSuccessRate(float val);
	void AddGuardRate(WORD val);
	void AddSkillDamageBlockModeSuccessRate(float val);
	void AddCurseBlockModeSuccessRate(float val);
	void AddKnockdownBlockModeSuccessRate(float val);
	void AddHtbBlockModeSuccessRate(float val);
	void AddSitDownLpRegenBonusRate(float val);
	void AddSitDownEpRegenBonusRate(float val);
	void AddPhysicalCriticalDamageBonusRate(float val);
	void AddEnergyCriticalDamageBonusRate(float val);
	void AddItemUpgradeBonusRate(float val);
	void AddItemUpgradeBreakBonusRate(float val);
	void AddSkillSpeed(float val);
	void AddLastPhysicalCriticalDefenceRate(WORD val);
	void AddLastEnergyCriticalDefenceRate(WORD val);
	void AddLastPhysicalCriticalRange(float val);
	void AddLastEnergyCriticalRange(float val);
	void AddLastApDegeneration(WORD val);
	void AddLastApBattleDegeneration(WORD val);
	void AddLastBlockDamageRate(WORD val);
	void AddLastLPSitDownRegeneration(WORD val);
	void AddLastEPSitDownRegeneration(WORD val);
	void AddLastEPBattleRegeneration(WORD val);
	void AddLastRpRegen(WORD val);
	void AddLastRpDimimution(WORD val);
	void AddValueDirectHealChangePercent(float val);
	void AddValueDirectHealChangeAbsolute(float val);
	void AddValueHealOverTimeChangePercent(float val);
	void AddValueHealOverTimeChangeAbsolute(float val);
	void AddAgroPointsPercent(float val);
	void AddAgroPointsAbsolute(float val);
	void AddLastBleedingDefence(WORD val);
	void AddLastBurnDefence(WORD val);
};

#endif