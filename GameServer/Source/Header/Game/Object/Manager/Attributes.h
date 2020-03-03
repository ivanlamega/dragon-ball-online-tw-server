#ifndef __ATTRIBUTES_H
#define __ATTRIBUTES_H

#pragma once

#include <Packet\Game\PacketGU.h>
#include <TableAll.h>
#include <DboTSCoreDefine.h>

class Player;

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
	struct BuffTimeInfo
	{
		HOBJECT		PlayerHandle;
		bool		BuffIsActive;
		DWORD		BuffTime;
		DWORD		BuffEndTime;
		TBLIDX		BuffID;
		BYTE		BuffSlot;		
		bool        isAffectPlayer;
		DWORD		EffectType;
		float		EffectValue[2];
		bool		isMob;
		int			StunedType;
	};
	
	//Control Stun Time Need change
	BuffTimeInfo sBuffTimeInfo[34];
	int StunedTypes[34];
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

	//RP Passive
	bool		IsPowerUp;
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