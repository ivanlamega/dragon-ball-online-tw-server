#include "StdAfx.h"
#include "NtlBitFlag.h"
#include "NtlAvatar.h"

#include "NtlBitFlagManager.h"

CNtlAvatar::CNtlAvatar(void)
{
	Init();
}

CNtlAvatar::~CNtlAvatar(void)
{
}

void CNtlAvatar::Init()
{
	InitializeAttributeLink();
}

void CNtlAvatar::InitializeAttributeLink()
{
}

CNtlAvatar* CNtlAvatar::GetInstance()
{
	static CNtlAvatar avatar;
	return &avatar;
}

bool CNtlAvatar::UpdateAvatarAttribute(BYTE byAttributeTotalCount, void* pvRawData, sAVATAR_ATTRIBUTE* pAttributeData)
{
	BYTE* pbyCurrentPosition = (BYTE*)pvRawData;
	BYTE* pbyAttributeData = (BYTE*)pAttributeData;

	CNtlBitFlagManager changedFlag;
	if (false == changedFlag.Create(pvRawData, byAttributeTotalCount))
	{
		return false;
	}

	pbyCurrentPosition += changedFlag.GetBytesUsed();

	for (BYTE byIndex = ATTRIBUTE_TO_UPDATE_FIRST ; byIndex <= ATTRIBUTE_TO_UPDATE_LAST ; byIndex++)
	{
		if (false != changedFlag.IsSet(byIndex))
		{
			DWORD dwDataSize = m_attributeLogic[byIndex].pCopyAttributeFunction(pbyCurrentPosition, pbyAttributeData + m_attributeLogic[byIndex].dwFieldOffset);
			if (0 == dwDataSize)
			{
				return false;
			}
			else
			{
				pbyCurrentPosition += dwDataSize;
			}
		}
	}

	return true;
}
//Convert Attributes to Attribute Link - Luiz45
sAVATAR_ATTRIBUTE_LINK CNtlAvatar::ConvertAttributeToAttributeLink(sAVATAR_ATTRIBUTE* pAttributes)
{
	sAVATAR_ATTRIBUTE_LINK newAttribs;
	//Bases
	void* byBaseCon = &pAttributes->byBaseCon;
	void* byBaseStr = &pAttributes->byBaseStr;
	void* byBaseSol = &pAttributes->byBaseSol;
	void* byBaseFoc = &pAttributes->byBaseFoc;
	void* byBaseEng = &pAttributes->byBaseEng;
	void* byBaseDex = &pAttributes->byBaseDex;

	void* wBaseAttackRate = &pAttributes->wBaseAttackRate;
	void* wBaseAttackSpeedRate = &pAttributes->wBaseAttackSpeedRate;
	void* wBaseBlockRate = &pAttributes->wBaseBlockRate;
	void* wBaseCurseSuccessRate = &pAttributes->wBaseCurseSuccessRate;
	void* wBaseCurseToleranceRate = &pAttributes->wBaseCurseToleranceRate;
	void* wBaseDodgeRate = &pAttributes->wBaseDodgeRate;
	void* wBaseEnergyCriticalRate = &pAttributes->wBaseEnergyCriticalRate;
	void* wBaseEnergyDefence = &pAttributes->wBaseEnergyDefence;
	void* wBaseEnergyOffence = &pAttributes->wBaseEnergyOffence;
	void* wBasePhysicalCriticalRate = &pAttributes->wBasePhysicalCriticalRate;
	void* wBasePhysicalOffence = &pAttributes->wBasePhysicalOffence;
	void* wBasePhysicalDefence = &pAttributes->wBasePhysicalDefence;
	void* wBaseEpBattleRegen = &pAttributes->wBaseEpBattleRegen;
	void* wBaseEpRegen = &pAttributes->wBaseEpRegen;
	void* wBaseEpSitdownRegen = &pAttributes->wBaseEpSitdownRegen;
	void* wBaseLpBattleRegen = &pAttributes->wBaseLpBattleRegen;
	void* wBaseLpRegen = &pAttributes->wBaseLpRegen;
	void* wBaseLpSitdownRegen = &pAttributes->wBaseLpSitdownRegen;
	void* wBaseRpRegen = &pAttributes->wBaseRpRegen;
	void* wBaseMaxEP = &pAttributes->wBaseMaxEP;
	void* wBaseMaxLP = &pAttributes->wBaseMaxLP;
	void* wBaseMaxRP = &pAttributes->wBaseMaxRP;
	//Lasts
	void* byLastCon = &pAttributes->byLastCon;
	void* byLastStr = &pAttributes->byLastStr;
	void* byLastSol = &pAttributes->byLastSol;
	void* byLastFoc = &pAttributes->byLastFoc;
	void* byLastEng = &pAttributes->byLastEng;
	void* byLastDex = &pAttributes->byLastDex;
	
	void* wLastAttackRate = &pAttributes->wLastAttackRate;
	void* wLastAttackSpeedRate = &pAttributes->wLastAttackSpeedRate;
	void* wLastBlockRate = &pAttributes->wLastBlockRate;
	void* wLastCurseSuccessRate = &pAttributes->wLastCurseSuccessRate;
	void* wLastCurseToleranceRate = &pAttributes->wLastCurseToleranceRate;
	void* wLastDodgeRate = &pAttributes->wLastDodgeRate;
	void* wLastEnergyCriticalRate = &pAttributes->wLastEnergyCriticalRate;
	void* wLastEnergyOffence = &pAttributes->wLastEnergyOffence;
	void* wLastEnergyDefence = &pAttributes->wLastEnergyDefence;
	void* wLastPhysicalCriticalRate = &pAttributes->wLastPhysicalCriticalRate;
	void* wLastPhysicalOffence = &pAttributes->wLastPhysicalOffence;
	void* wLastPhysicalDefence = &pAttributes->wLastPhysicalDefence;
	void* wLastEpBattleRegen = &pAttributes->wLastEpBattleRegen;
	void* wLastEpRegen = &pAttributes->wLastEpRegen;
	void* wLastEpSitdownRegen = &pAttributes->wLastEpSitdownRegen;
	void* wLastLpBattleRegen = &pAttributes->wLastLpBattleRegen;
	void* wLastLpRegen = &pAttributes->wLastLpRegen;
	void* wLastLpSitdownRegen = &pAttributes->wLastLpSitdownRegen;
	void* wLastRpRegen = &pAttributes->wLastRpRegen;
	void* wLastRpDimimutionRate = &pAttributes->wLastRpDimimutionRate;
	void* wLastMaxEP = &pAttributes->wLastMaxEP;
	void* wLastMaxLP = &pAttributes->wLastMaxLP;
	void* wLastMaxRP = &pAttributes->wLastMaxRP;
	void* wGuardRate = &pAttributes->wGuardRate;
	void* wParalyzeToleranceRate = &pAttributes->wParalyzeToleranceRate;
	void* wTerrorToleranceRate = &pAttributes->wTerrorToleranceRate;
	void* wConfuseToleranceRate = &pAttributes->wConfuseToleranceRate;
	void* wStoneToleranceRate = &pAttributes->wStoneToleranceRate;
	void* wCandyToleranceRate = &pAttributes->wCandyToleranceRate;
	//Others
	void* fBaseAttackRange = &pAttributes->fBaseAttackRange;
	void* fBleedingKeepTimeDown = &pAttributes->fBleedingKeepTimeDown;
	void* fCandyKeepTimeDown = &pAttributes->fCandyKeepTimeDown;
	void* fCastingTimeChangePercent = &pAttributes->fCastingTimeChangePercent;
	void* fConfuseKeepTimeDown = &pAttributes->fConfuseKeepTimeDown;
	void* fCoolTimeChangePercent = &pAttributes->fCoolTimeChangePercent;
	void* fCriticalBlockSuccessRate = &pAttributes->fCriticalBlockSuccessRate;
	void* fCurseBlockModeSuccessRate = &pAttributes->fCurseBlockModeSuccessRate;
	void* fDotTimeChangeAbsolute = &pAttributes->fDotTimeChangeAbsolute;
	void* fDotValueChangePercent = &pAttributes->fDotValueChangePercent;
	void* fEleganceDefence = &pAttributes->fEleganceDefence;
	void* fEleganceOffence = &pAttributes->fEleganceOffence;
	void* fEnergyCriticalDamageBonusRate = &pAttributes->fEnergyCriticalDamageBonusRate;
	void* fFunnyDefence = &pAttributes->fFunnyDefence;
	void* fFunnyOffence = &pAttributes->fFunnyOffence;
	void* fHonestDefence = &pAttributes->fHonestDefence;
	void* fHonestOffence = &pAttributes->fHonestOffence;
	void* fHtbBlockModeSuccessRate = &pAttributes->fHtbBlockModeSuccessRate;
	void* fItemUpgradeBonusRate = &pAttributes->fItemUpgradeBonusRate;
	void* fItemUpgradeBreakBonusRate = &pAttributes->fItemUpgradeBreakBonusRate;
	void* fKeepTimeChangePercent = &pAttributes->fKeepTimeChangePercent;
	void* fKnockdownBlockModeSuccessRate = &pAttributes->fKnockdownBlockModeSuccessRate;
	void* fLastAttackRange = &pAttributes->fLastAttackRange;
	void* fLastRunSpeed = &pAttributes->fLastRunSpeed;
	void* fParalyzeKeepTimeDown = &pAttributes->fParalyzeKeepTimeDown;
	void* fPhysicalCriticalDamageBonusRate = &pAttributes->fPhysicalCriticalDamageBonusRate;
	void* fPoisonKeepTimeDown = &pAttributes->fPoisonKeepTimeDown;
	void* fRequiredEpChangePercent = &pAttributes->fRequiredEpChangePercent;
	void* fSitDownEpRegenBonusRate = &pAttributes->fSitDownEpRegenBonusRate;
	void* fSitDownLpRegenBonusRate = &pAttributes->fSitDownLpRegenBonusRate;
	void* fSkillDamageBlockModeSuccessRate = &pAttributes->fSkillDamageBlockModeSuccessRate;
	void* fStomachacheKeepTimeDown = &pAttributes->fStomachacheKeepTimeDown;
	void* fStoneKeepTimeDown = &pAttributes->fStoneKeepTimeDown;
	void* fStrangeDefence = &pAttributes->fStrangeDefence;
	void* fStrangeOffence = &pAttributes->fStrangeOffence;
	void* fTerrorKeepTimeDown = &pAttributes->fTerrorKeepTimeDown;
	void* fWildDefence = &pAttributes->fWildDefence;
	void* fWildOffence = &pAttributes->fWildOffence;
	
	//New Attribs
	newAttribs.pbyBaseCon = (BYTE*)byBaseCon;
	newAttribs.pbyBaseStr = (BYTE*)byBaseStr;
	newAttribs.pbyBaseSol = (BYTE*)byBaseSol;
	newAttribs.pbyBaseFoc = (BYTE*)byBaseFoc;
	newAttribs.pbyBaseEng = (BYTE*)byBaseEng;
	newAttribs.pbyBaseDex = (BYTE*)byBaseDex;

	newAttribs.pbyLastCon = (BYTE*)byLastCon;
	newAttribs.pbyLastStr = (BYTE*)byLastStr;
	newAttribs.pbyLastSol = (BYTE*)byLastSol;
	newAttribs.pbyLastFoc = (BYTE*)byLastFoc;
	newAttribs.pbyLastEng = (BYTE*)byLastEng;
	newAttribs.pbyLastDex = (BYTE*)byLastDex;

	newAttribs.pwBaseAttackRate = (WORD*)wBaseAttackRate;
	newAttribs.pwBaseAttackSpeedRate = (WORD*)wBaseAttackSpeedRate;
	newAttribs.pwBaseBlockRate = (WORD*)wBaseBlockRate;
	newAttribs.pwBaseCurseSuccessRate = (WORD*)wBaseCurseSuccessRate;
	newAttribs.pwBaseCurseToleranceRate = (WORD*)wBaseCurseToleranceRate;
	newAttribs.pwBaseDodgeRate = (WORD*)wBaseDodgeRate;
	newAttribs.pwBaseEnergyCriticalRate = (WORD*)wBaseEnergyCriticalRate;
	newAttribs.pwBaseEnergyOffence = (WORD*)wBaseEnergyOffence;
	newAttribs.pwBaseEnergyDefence = (WORD*)wBaseEnergyDefence;
	newAttribs.pwBasePhysicalCriticalRate = (WORD*)wBasePhysicalCriticalRate;
	newAttribs.pwBasePhysicalOffence = (WORD*)wBasePhysicalOffence;
	newAttribs.pwBasePhysicalDefence = (WORD*)wBasePhysicalDefence;
	newAttribs.pwBaseEpBattleRegen = (WORD*)wBaseEpBattleRegen;
	newAttribs.pwBaseEpRegen = (WORD*)wBaseEpRegen;
	newAttribs.pwBaseEpSitdownRegen = (WORD*)wBaseEpSitdownRegen;	
	newAttribs.pwBaseLpBattleRegen = (WORD*)wBaseLpBattleRegen;
	newAttribs.pwBaseLpRegen = (WORD*)wBaseLpRegen;
	newAttribs.pwBaseLpSitdownRegen = (WORD*)wBaseLpSitdownRegen;
	newAttribs.pwBaseRpRegen = (WORD*)wBaseRpRegen;
	newAttribs.pwBaseMaxEP = (WORD*)wBaseMaxEP;
	newAttribs.pwBaseMaxLP = (WORD*)wBaseMaxLP;
	newAttribs.pwBaseMaxRP = (WORD*)wBaseMaxRP;	
	newAttribs.pwBaseEpSitdownRegen = (WORD*)wBaseEpSitdownRegen;

	newAttribs.pwLastAttackRate = (WORD*)wLastAttackRate;
	newAttribs.pwLastAttackSpeedRate = (WORD*)wLastAttackSpeedRate;
	newAttribs.pwLastBlockRate = (WORD*)wLastBlockRate;
	newAttribs.pwLastCurseSuccessRate = (WORD*)wLastCurseSuccessRate;
	newAttribs.pwLastCurseToleranceRate = (WORD*)wLastCurseToleranceRate;
	newAttribs.pwLastDodgeRate = (WORD*)wLastDodgeRate;
	newAttribs.pwLastEnergyCriticalRate = (WORD*)wLastEnergyCriticalRate;
	newAttribs.pwLastEnergyOffence = (WORD*)wLastEnergyOffence;
	newAttribs.pwLastEnergyDefence = (WORD*)wLastEnergyDefence;
	newAttribs.pwLastPhysicalCriticalRate = (WORD*)wLastPhysicalCriticalRate;
	newAttribs.pwLastPhysicalOffence = (WORD*)wLastPhysicalOffence;
	newAttribs.pwLastPhysicalDefence = (WORD*)wLastPhysicalDefence;
	newAttribs.pwLastEpBattleRegen = (WORD*)wLastEpBattleRegen;
	newAttribs.pwLastEpRegen = (WORD*)wLastEpRegen;
	newAttribs.pwLastEpSitdownRegen = (WORD*)wLastEpSitdownRegen;	
	newAttribs.pwLastLpBattleRegen = (WORD*)wLastLpBattleRegen;
	newAttribs.pwLastLpRegen = (WORD*)wLastLpRegen;
	newAttribs.pwLastLpSitdownRegen = (WORD*)wLastLpSitdownRegen;
	newAttribs.pwLastRpRegen = (WORD*)wLastRpRegen;
	newAttribs.pwLastRpDimimutionRate = (WORD*)wLastRpDimimutionRate;
	newAttribs.pwLastMaxEP = (WORD*)wLastMaxEP;
	newAttribs.pwLastMaxLP = (WORD*)wLastMaxLP;
	newAttribs.pwLastMaxRP = (WORD*)wLastMaxRP;
	
	newAttribs.pwGuardRate = (WORD*)wGuardRate;
	newAttribs.pwParalyzeToleranceRate = (WORD*)wParalyzeToleranceRate;
	newAttribs.pwTerrorToleranceRate = (WORD*)wTerrorToleranceRate;
	newAttribs.pwConfuseToleranceRate = (WORD*)wConfuseToleranceRate;
	newAttribs.pwCandyToleranceRate = (WORD*)wCandyToleranceRate;
	newAttribs.pwStoneToleranceRate = (WORD*)wStoneToleranceRate;

	newAttribs.pfBaseAttackRange = (float*)fBaseAttackRange;
	newAttribs.pfBleedingKeepTimeDown = (float*)fBleedingKeepTimeDown;
	newAttribs.pfCandyKeepTimeDown = (float*)fCandyKeepTimeDown;
	newAttribs.pfCastingTimeChangePercent = (float*)fCastingTimeChangePercent;
	newAttribs.pfConfuseKeepTimeDown = (float*)fConfuseKeepTimeDown;
	newAttribs.pfCoolTimeChangePercent = (float*)fCoolTimeChangePercent;
	newAttribs.pfCriticalBlockSuccessRate = (float*)fCriticalBlockSuccessRate;
	newAttribs.pfCurseBlockModeSuccessRate = (float*)fCurseBlockModeSuccessRate;
	newAttribs.pfDotTimeChangeAbsolute = (float*)fDotTimeChangeAbsolute;
	newAttribs.pfDotValueChangePercent = (float*)fDotValueChangePercent;
	newAttribs.pfEleganceOffence = (float*)fEleganceOffence;
	newAttribs.pfEleganceDefence = (float*)fEleganceDefence;
	newAttribs.pfEnergyCriticalDamageBonusRate = (float*)fEnergyCriticalDamageBonusRate;
	newAttribs.pfFunnyOffence = (float*)fFunnyOffence;
	newAttribs.pfFunnyDefence = (float*)fFunnyDefence;
	newAttribs.pfHonestOffence = (float*)fHonestOffence;
	newAttribs.pfHonestDefence = (float*)fHonestDefence;
	newAttribs.pfHtbBlockModeSuccessRate = (float*)fHtbBlockModeSuccessRate;
	newAttribs.pfItemUpgradeBonusRate = (float*)fItemUpgradeBonusRate;
	newAttribs.pfItemUpgradeBreakBonusRate = (float*)fItemUpgradeBreakBonusRate;
	newAttribs.pfKeepTimeChangePercent = (float*)fKeepTimeChangePercent;
	newAttribs.pfKnockdownBlockModeSuccessRate = (float*)fKnockdownBlockModeSuccessRate;
	newAttribs.pfLastAttackRange = (float*)fLastAttackRange;
	newAttribs.pfLastRunSpeed = (float*)fLastRunSpeed;
	newAttribs.pfParalyzeKeepTimeDown = (float*)fParalyzeKeepTimeDown;
	newAttribs.pfPhysicalCriticalDamageBonusRate = (float*)fPhysicalCriticalDamageBonusRate;
	newAttribs.pfPoisonKeepTimeDown = (float*)fPoisonKeepTimeDown;
	newAttribs.pfRequiredEpChangePercent = (float*)fRequiredEpChangePercent;
	newAttribs.pfSitDownEpRegenBonusRate = (float*)fSitDownEpRegenBonusRate;
	newAttribs.pfSitDownLpRegenBonusRate = (float*)fSitDownLpRegenBonusRate;
	newAttribs.pfSkillDamageBlockModeSuccessRate = (float*)fSkillDamageBlockModeSuccessRate;
	newAttribs.pfStomachacheKeepTimeDown = (float*)fStomachacheKeepTimeDown;
	newAttribs.pfStoneKeepTimeDown = (float*)fStoneKeepTimeDown;
	newAttribs.pfStrangeDefence = (float*)fStrangeDefence;
	newAttribs.pfStrangeOffence = (float*)fStrangeOffence;
	newAttribs.pfTerrorKeepTimeDown = (float*)fTerrorKeepTimeDown;
	newAttribs.pfWildDefence = (float*)fWildDefence;
	newAttribs.pfWildOffence = (float*)fWildOffence;

	return newAttribs;
}
bool CNtlAvatar::SaveAvatarAttribute(CNtlBitFlagManager* pChangedFlag, sAVATAR_ATTRIBUTE_LINK* pAttributeDataLink, void* pvBuffer, DWORD* pwdDataSize)
{
	BYTE* pbyBuffer = (BYTE*)pvBuffer;
	BYTE* pbyAttributeDataLink = (BYTE*)pAttributeDataLink;

	*pwdDataSize = 0;
	
	::CopyMemory(pbyBuffer, pChangedFlag->GetRawData(), pChangedFlag->GetBytesUsed());

	pbyBuffer += pChangedFlag->GetBytesUsed();
	*pwdDataSize += pChangedFlag->GetBytesUsed();

	for (BYTE byIndex = ATTRIBUTE_TO_UPDATE_FIRST ; byIndex <= ATTRIBUTE_TO_UPDATE_LAST ; byIndex++)
	{
		if (false != pChangedFlag->IsSet(byIndex))
		{
			void* pvAttributeFieldLink = *((void**)(pbyAttributeDataLink + byIndex * sizeof(void*)));
			if (NULL == pvAttributeFieldLink)
			{
				continue;
			}

			DWORD dwDataSize = m_attributeLogic[byIndex].pCopyAttributeFunction(pvAttributeFieldLink, pbyBuffer);
			if (0 == dwDataSize)
			{
				return false;
			}
			else
			{
				pbyBuffer += dwDataSize;
				*pwdDataSize += dwDataSize;
			}
		}
	}

	return true;
}

bool CNtlAvatar::FillAvatarAttribute(sAVATAR_ATTRIBUTE_LINK* pAttributeDataLink, sAVATAR_ATTRIBUTE* pAttributeData)
{
	BYTE* pbyAttributeDataLink = (BYTE*)pAttributeDataLink;
	BYTE* pbyAttributeData = (BYTE*)pAttributeData;

	for (BYTE byIndex = ATTRIBUTE_TO_UPDATE_FIRST ; byIndex <= ATTRIBUTE_TO_UPDATE_LAST ; byIndex++)
	{
		void* pvAttributeFieldLink = *((void**)(pbyAttributeDataLink + byIndex * sizeof(void*)));
		if (NULL == pvAttributeFieldLink)
		{
			continue;
		}

		DWORD dwDataSize = m_attributeLogic[byIndex].pCopyAttributeFunction(
																			pvAttributeFieldLink,
																			pbyAttributeData + m_attributeLogic[byIndex].dwFieldOffset);
		if (0 == dwDataSize)
		{
			return false;
		}
	}

	return true;
}

#ifndef ATTRIBUTE_LOGIC_DEFINE
#define ATTRIBUTE_LOGIC_DEFINE(field_name, type)					\
	{																\
		PtrToUlong(&(((sAVATAR_ATTRIBUTE*)NULL)->field_name)),		\
		CopyValueByType_##type										\
	}
#endif

CNtlAvatar::sATTRIBUTE_LOGIC CNtlAvatar::m_attributeLogic[ATTRIBUTE_TO_UPDATE_COUNT] =
{
	ATTRIBUTE_LOGIC_DEFINE(byBaseStr, BYTE),
	ATTRIBUTE_LOGIC_DEFINE(byLastStr, BYTE),
	ATTRIBUTE_LOGIC_DEFINE(byBaseCon, BYTE),
	ATTRIBUTE_LOGIC_DEFINE(byLastCon, BYTE),
	ATTRIBUTE_LOGIC_DEFINE(byBaseFoc, BYTE),
	ATTRIBUTE_LOGIC_DEFINE(byLastFoc, BYTE),
	ATTRIBUTE_LOGIC_DEFINE(byBaseDex, BYTE),
	ATTRIBUTE_LOGIC_DEFINE(byLastDex, BYTE),
	ATTRIBUTE_LOGIC_DEFINE(byBaseSol, BYTE),
	ATTRIBUTE_LOGIC_DEFINE(byLastSol, BYTE),
	ATTRIBUTE_LOGIC_DEFINE(byBaseEng, BYTE),
	ATTRIBUTE_LOGIC_DEFINE(byLastEng, BYTE),

	ATTRIBUTE_LOGIC_DEFINE(wBaseMaxLP, WORD),
	ATTRIBUTE_LOGIC_DEFINE(wLastMaxLP, WORD),
	ATTRIBUTE_LOGIC_DEFINE(wBaseMaxEP, WORD),
	ATTRIBUTE_LOGIC_DEFINE(wLastMaxEP, WORD),
	ATTRIBUTE_LOGIC_DEFINE(wBaseMaxRP, WORD),
	ATTRIBUTE_LOGIC_DEFINE(wLastMaxRP, WORD),

	ATTRIBUTE_LOGIC_DEFINE(wBaseLpRegen, WORD),
	ATTRIBUTE_LOGIC_DEFINE(wLastLpRegen, WORD),
	ATTRIBUTE_LOGIC_DEFINE(wBaseLpSitdownRegen, WORD),
	ATTRIBUTE_LOGIC_DEFINE(wLastLpSitdownRegen, WORD),
	ATTRIBUTE_LOGIC_DEFINE(wBaseLpBattleRegen, WORD),
	ATTRIBUTE_LOGIC_DEFINE(wLastLpBattleRegen, WORD),

	ATTRIBUTE_LOGIC_DEFINE(wBaseEpRegen, WORD),
	ATTRIBUTE_LOGIC_DEFINE(wLastEpRegen, WORD),
	ATTRIBUTE_LOGIC_DEFINE(wBaseEpSitdownRegen, WORD),
	ATTRIBUTE_LOGIC_DEFINE(wLastEpSitdownRegen, WORD),
	ATTRIBUTE_LOGIC_DEFINE(wBaseEpBattleRegen, WORD),
	ATTRIBUTE_LOGIC_DEFINE(wLastEpBattleRegen, WORD),

	ATTRIBUTE_LOGIC_DEFINE(wBaseRpRegen, WORD),
	ATTRIBUTE_LOGIC_DEFINE(wLastRpRegen, WORD),
	ATTRIBUTE_LOGIC_DEFINE(wLastRpDimimutionRate, WORD),

	ATTRIBUTE_LOGIC_DEFINE(wBasePhysicalOffence, WORD),
	ATTRIBUTE_LOGIC_DEFINE(wLastPhysicalOffence, WORD),
	ATTRIBUTE_LOGIC_DEFINE(wBasePhysicalDefence, WORD),
	ATTRIBUTE_LOGIC_DEFINE(wLastPhysicalDefence, WORD),

	ATTRIBUTE_LOGIC_DEFINE(wBaseEnergyOffence, WORD),
	ATTRIBUTE_LOGIC_DEFINE(wLastEnergyOffence, WORD),
	ATTRIBUTE_LOGIC_DEFINE(wBaseEnergyDefence, WORD),
	ATTRIBUTE_LOGIC_DEFINE(wLastEnergyDefence, WORD),

	ATTRIBUTE_LOGIC_DEFINE(wBaseAttackRate, WORD),
	ATTRIBUTE_LOGIC_DEFINE(wLastAttackRate, WORD),
	ATTRIBUTE_LOGIC_DEFINE(wBaseDodgeRate, WORD),
	ATTRIBUTE_LOGIC_DEFINE(wLastDodgeRate, WORD),
	ATTRIBUTE_LOGIC_DEFINE(wBaseBlockRate, WORD),
	ATTRIBUTE_LOGIC_DEFINE(wLastBlockRate, WORD),

	ATTRIBUTE_LOGIC_DEFINE(wBaseCurseSuccessRate, WORD),
	ATTRIBUTE_LOGIC_DEFINE(wLastCurseSuccessRate, WORD),
	ATTRIBUTE_LOGIC_DEFINE(wBaseCurseToleranceRate, WORD),
	ATTRIBUTE_LOGIC_DEFINE(wLastCurseToleranceRate, WORD),

	ATTRIBUTE_LOGIC_DEFINE(wBasePhysicalCriticalRate, WORD),
	ATTRIBUTE_LOGIC_DEFINE(wLastPhysicalCriticalRate, WORD),
	ATTRIBUTE_LOGIC_DEFINE(wBaseEnergyCriticalRate, WORD),
	ATTRIBUTE_LOGIC_DEFINE(wLastEnergyCriticalRate, WORD),

	ATTRIBUTE_LOGIC_DEFINE(fLastRunSpeed, float),

	ATTRIBUTE_LOGIC_DEFINE(wBaseAttackSpeedRate, WORD),
	ATTRIBUTE_LOGIC_DEFINE(wLastAttackSpeedRate, WORD),
	ATTRIBUTE_LOGIC_DEFINE(fBaseAttackRange, float),
	ATTRIBUTE_LOGIC_DEFINE(fLastAttackRange, float),

	ATTRIBUTE_LOGIC_DEFINE(fCastingTimeChangePercent, float),
	ATTRIBUTE_LOGIC_DEFINE(fCoolTimeChangePercent, float),
	ATTRIBUTE_LOGIC_DEFINE(fKeepTimeChangePercent, float),
	ATTRIBUTE_LOGIC_DEFINE(fDotValueChangePercent, float),
	ATTRIBUTE_LOGIC_DEFINE(fDotTimeChangeAbsolute, float),
	ATTRIBUTE_LOGIC_DEFINE(fRequiredEpChangePercent, float),

	ATTRIBUTE_LOGIC_DEFINE(fHonestOffence, float),
	ATTRIBUTE_LOGIC_DEFINE(fHonestDefence, float),
	ATTRIBUTE_LOGIC_DEFINE(fStrangeOffence, float),
	ATTRIBUTE_LOGIC_DEFINE(fStrangeDefence, float),
	ATTRIBUTE_LOGIC_DEFINE(fWildOffence, float),
	ATTRIBUTE_LOGIC_DEFINE(fWildDefence, float),
	ATTRIBUTE_LOGIC_DEFINE(fEleganceOffence, float),
	ATTRIBUTE_LOGIC_DEFINE(fEleganceDefence, float),
	ATTRIBUTE_LOGIC_DEFINE(fFunnyOffence, float),
	ATTRIBUTE_LOGIC_DEFINE(fFunnyDefence, float),

	ATTRIBUTE_LOGIC_DEFINE(wParalyzeToleranceRate, WORD),
	ATTRIBUTE_LOGIC_DEFINE(wTerrorToleranceRate, WORD),
	ATTRIBUTE_LOGIC_DEFINE(wConfuseToleranceRate, WORD),
	ATTRIBUTE_LOGIC_DEFINE(wStoneToleranceRate, WORD),
	ATTRIBUTE_LOGIC_DEFINE(wCandyToleranceRate, WORD),

	ATTRIBUTE_LOGIC_DEFINE(fParalyzeKeepTimeDown, float),
	ATTRIBUTE_LOGIC_DEFINE(fTerrorKeepTimeDown, float),
	ATTRIBUTE_LOGIC_DEFINE(fConfuseKeepTimeDown, float),
	ATTRIBUTE_LOGIC_DEFINE(fStoneKeepTimeDown, float),
	ATTRIBUTE_LOGIC_DEFINE(fCandyKeepTimeDown, float),
	ATTRIBUTE_LOGIC_DEFINE(fBleedingKeepTimeDown, float),
	ATTRIBUTE_LOGIC_DEFINE(fPoisonKeepTimeDown, float),
	ATTRIBUTE_LOGIC_DEFINE(fStomachacheKeepTimeDown, float),

	ATTRIBUTE_LOGIC_DEFINE(fCriticalBlockSuccessRate, float),

	ATTRIBUTE_LOGIC_DEFINE(wGuardRate, WORD),

	ATTRIBUTE_LOGIC_DEFINE(fSkillDamageBlockModeSuccessRate, float),
	ATTRIBUTE_LOGIC_DEFINE(fCurseBlockModeSuccessRate, float),
	ATTRIBUTE_LOGIC_DEFINE(fKnockdownBlockModeSuccessRate, float),
	ATTRIBUTE_LOGIC_DEFINE(fHtbBlockModeSuccessRate, float),

	ATTRIBUTE_LOGIC_DEFINE(fSitDownLpRegenBonusRate, float),
	ATTRIBUTE_LOGIC_DEFINE(fSitDownEpRegenBonusRate, float),
	ATTRIBUTE_LOGIC_DEFINE(fPhysicalCriticalDamageBonusRate, float),
	ATTRIBUTE_LOGIC_DEFINE(fEnergyCriticalDamageBonusRate, float),

	ATTRIBUTE_LOGIC_DEFINE(fItemUpgradeBonusRate, float),
	ATTRIBUTE_LOGIC_DEFINE(fItemUpgradeBreakBonusRate, float),
};

#undef ATTRIBUTE_LOGIC_DEFINE

DWORD CNtlAvatar::CopyValueByType_BYTE(void* pvValue, void* pvBuffer)
{
	BYTE* pbyBuffer = (BYTE*)pvBuffer;

	*pbyBuffer = *((BYTE*)pvValue);

	return sizeof(BYTE);
}

DWORD CNtlAvatar::CopyValueByType_WORD(void* pvValue, void* pvBuffer)
{
	WORD* pbyBuffer = (WORD*)pvBuffer;

	*pbyBuffer = *((WORD*)pvValue);

	return sizeof(WORD);
}

DWORD CNtlAvatar::CopyValueByType_float(void* pvValue, void* pvBuffer)
{
	float* pbyBuffer = (float*)pvBuffer;

	*pbyBuffer = *((float*)pvValue);

	return sizeof(float);
}