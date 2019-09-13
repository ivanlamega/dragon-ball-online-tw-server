#ifndef __ATTRIBUTES_H
#define __ATTRIBUTES_H

#pragma once

#include <Packet\Game\PacketGU.h>
#include <TableAll.h>

class Player;
class AttributesManager
{
public:
	AttributesManager();
	~AttributesManager();
	//CashShop Info
	DWORD		cashpoit;
	DWORD		WagguCoin;
	DWORD		EventCoin;
	//Player Help get Class/Race
	int			PlayerClassID;
	int			PlayerRaceID;

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
	struct BuffTimeInfo
	{
		HOBJECT		PlayerHandle;
		bool		BuffIsActive = false;
		DWORD		BuffTime;
		DWORD		BuffEndTime;
		TBLIDX		BuffID;
		BYTE		BuffSlot;				
	};
	//Control Stun Time Need change
	BuffTimeInfo sBuffTimeInfo[16];
	//////////
	//Caontrol FreeBatle Need change
	int			atackerType;
	int			Type;
	HOBJECT		FreeBatleChellenger;
	bool		PlayerInFreeBatle = false;
	bool		OutBatle = false;
	bool		showMensageOut = false;
	bool		LoseBatle = false;
	DWORD		OutBatleTime;
	DWORD		OutBatleFinalTime;
	sVECTOR3	vRefreeLoc;
	//////
	// Control Player Trade Need change
	bool		PlayerTradeOK = false;
	sITEM_DATA	Tradeinvent[13];
	BYTE		tradecount = 0;
	//Get pet in use
	BYTE		PetInUse;
	//Get Party Info Need change
	HOBJECT		PartyLeader;

	bool			LoadAttributes(CHARACTERID _id, Player* _plr);
	bool			SaveAvatarAttribute(void* pvBuffer, DWORD* pwdDataSize);
	void			LoadAttributesFromItems(sITEM_BRIEF *brief);
	void			FillAttributesLink();
	void			SendRpBallInformation();
	void			CreatePlayerBaseAttributesBitFlag();
	void			UpdateAttributes();
	void			UpdateAttributesFromItem(sITEM_TBLDAT& item, BYTE Grade, bool remove = false);

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
};

#endif