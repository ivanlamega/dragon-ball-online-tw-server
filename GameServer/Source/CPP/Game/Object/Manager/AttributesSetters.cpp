#include <Game\Object\Manager\Attributes.h>
#include <Game\Object\Player.h>
#include <WorldSession.h>
#include <mysqlconn_wrapper.h>
#include <Logger.h>
#include <Packet\Game\PacketGU.h>

void AttributesManager::SetLastStr(WORD val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_STR_LAST);
	PlayerProfile.avatarAttribute.byLastStr = val;
	AttrIsUpdated = true;
}
void AttributesManager::SetLastCon(WORD val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_CON_LAST);
	PlayerProfile.avatarAttribute.byLastCon = val;
	AttrIsUpdated = true;
}
void AttributesManager::SetLastFoc(WORD val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_FOC_LAST);
	PlayerProfile.avatarAttribute.byLastFoc = val;
	AttrIsUpdated = true;
}
void AttributesManager::SetLastDex(WORD val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_DEX_LAST);
	PlayerProfile.avatarAttribute.byLastDex = val;
	AttrIsUpdated = true;
}
void AttributesManager::SetLastEng(WORD val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_ENG_LAST);
	PlayerProfile.avatarAttribute.byLastEng = val;
	AttrIsUpdated = true;
}
void AttributesManager::SetLastSol(WORD val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_SOL_LAST);
	PlayerProfile.avatarAttribute.byLastSol = val;
	AttrIsUpdated = true;
}
void AttributesManager::SetLastMaxLP(DWORD val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_MAX_LP_LAST);
	PlayerProfile.avatarAttribute.wLastMaxLP = val;
	AttrIsUpdated = true;
}
void AttributesManager::SetLastMaxEP(WORD val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_MAX_EP_LAST);
	PlayerProfile.avatarAttribute.wLastMaxEP = val;
	AttrIsUpdated = true;
}
void AttributesManager::SetLastMaxAP(DWORD val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_MAX_AP_LAST);
	PlayerProfile.avatarAttribute.wLastMaxAp = val;
	AttrIsUpdated = true;
}
void AttributesManager::SetLastMaxRP(WORD val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_MAX_RP_LAST);
	PlayerProfile.avatarAttribute.wLastMaxRP = val;
	AttrIsUpdated = true;
}
void AttributesManager::SetLastLPRegen(WORD val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_LP_REGENERATION_LAST);
	PlayerProfile.avatarAttribute.wLastLpRegen = val;
	AttrIsUpdated = true;
}
void AttributesManager::SetLastEPRegen(WORD val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_EP_REGENERATION_LAST);
	PlayerProfile.avatarAttribute.wLastEpRegen = val;
	AttrIsUpdated = true;
}
void AttributesManager::SetLastAPRegen(WORD val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_AP_REGENERATION_LAST);
	PlayerProfile.avatarAttribute.wLastApRegen = val;
	AttrIsUpdated = true;
}
void AttributesManager::SetLastPhysicalOffence(WORD val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_PHYSICAL_OFFENCE_LAST);
	PlayerProfile.avatarAttribute.wLastPhysicalOffence = val;
	AttrIsUpdated = true;
}
void AttributesManager::SetLastPhysicalDefence(WORD val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_PHYSICAL_DEFENCE_LAST);
	PlayerProfile.avatarAttribute.wLastPhysicalDefence = val;
	AttrIsUpdated = true;
}
void AttributesManager::SetLastEnergyOffence(WORD val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_ENERGY_OFFENCE_LAST);
	PlayerProfile.avatarAttribute.wLastEnergyOffence = val;
	AttrIsUpdated = true;
}
void AttributesManager::SetLastEnergyDefence(WORD val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_ENERGY_DEFENCE_LAST);
	PlayerProfile.avatarAttribute.wLastEnergyDefence = val;
	AttrIsUpdated = true;
}
void AttributesManager::SetLastAttackRate(WORD val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_ATTACK_RATE_LAST);
	PlayerProfile.avatarAttribute.wLastAttackRate = val;
	AttrIsUpdated = true;
}
void AttributesManager::SetLastDodgeRate(WORD val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_DODGE_RATE_LAST);
	PlayerProfile.avatarAttribute.wLastDodgeRate = val;
	AttrIsUpdated = true;
}
void AttributesManager::SetLastBlockRate(WORD val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_BLOCK_RATE_LAST);
	PlayerProfile.avatarAttribute.wLastBlockRate = val;
	AttrIsUpdated = true;
}
void AttributesManager::SetLastCurseSuccessRate(WORD val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_CURSE_SUCCESS_LAST);
	PlayerProfile.avatarAttribute.wLastCurseSuccessRate = val;
	AttrIsUpdated = true;
}
void AttributesManager::SetLastCurseToleranceRate(WORD val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_CURSE_TOLERANCE_LAST);
	PlayerProfile.avatarAttribute.wLastCurseToleranceRate = val;
	AttrIsUpdated = true;
}
void AttributesManager::SetLastPhysicalCriticalRate(WORD val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_PHYSICAL_CRITICAL_LAST);
	PlayerProfile.avatarAttribute.wLastPhysicalCriticalRate = val;
	AttrIsUpdated = true;
}
void AttributesManager::SetLastEnergyCriticalRate(WORD val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_ENERGY_CRITICAL_LAST);
	PlayerProfile.avatarAttribute.wLastEnergyCriticalRate = val;
	AttrIsUpdated = true;
}
void AttributesManager::SetLastRunSpeed(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_RUN_SPEED_LAST);
	PlayerProfile.avatarAttribute.fLastRunSpeed = val;
	AttrIsUpdated = true;
}
void AttributesManager::SetLastAirSpeed(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_AIR_SPEED_LAST);
	PlayerProfile.avatarAttribute.fLastAirSpeed = val;
	AttrIsUpdated = true;
}
void AttributesManager::SetLastAirDashSpeed(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_AIR_DASH_SPEED_LAST);
	PlayerProfile.avatarAttribute.fLastAirDashSpeed = val;
	AttrIsUpdated = true;
}
void AttributesManager::SetLastAirDash2Speed(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_AIR_DASH2_SPEED_LAST);
	PlayerProfile.avatarAttribute.fLastAirDash2Speed = val;
	AttrIsUpdated = true;
}
void AttributesManager::SetLastAttackSpeedRate(WORD val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_ATTACK_SPEED_RATE_LAST);
	PlayerProfile.avatarAttribute.wLastAttackSpeedRate = val;
	AttrIsUpdated = true;
}
void AttributesManager::SetLastAttackRange(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_ATTACK_RANGE_LAST);
	PlayerProfile.avatarAttribute.fLastAttackRange = val;
	AttrIsUpdated = true;
}
void AttributesManager::SetCastingTimeChangePercent(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_CASTING_TIME_CHANGE_PERCENT);
	PlayerProfile.avatarAttribute.fCastingTimeChangePercent = val;
	AttrIsUpdated = true;
}
void AttributesManager::SetCoolTimeChangePercent(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_COOL_TIME_CHANGE_PERCENT);
	PlayerProfile.avatarAttribute.fCoolTimeChangePercent = val;
	AttrIsUpdated = true;
}
void AttributesManager::SetKeepTimeChangePercent(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_KEEP_TIME_CHANGE_PERCENT);
	PlayerProfile.avatarAttribute.fKeepTimeChangePercent = val;
	AttrIsUpdated = true;
}
void AttributesManager::SetDotValueChangePercent(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_DOT_VALUE_CHANGE_PERCENT);
	PlayerProfile.avatarAttribute.fDotValueChangePercent = val;
	AttrIsUpdated = true;
}
void AttributesManager::SetDotTimeChangeAbsolute(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_DOT_TIME_CHANGE_ABSOLUTE);
	PlayerProfile.avatarAttribute.fDotTimeChangeAbsolute = val;
	AttrIsUpdated = true;
}
void AttributesManager::SetRequiredEpChangePercent(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_REQUIRED_EP_CHANGE_PERCENT);
	PlayerProfile.avatarAttribute.fRequiredEpChangePercent = val;
	AttrIsUpdated = true;
}
void AttributesManager::SetHonestOffence(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_HONEST_OFFENCE);
	PlayerProfile.avatarAttribute.fHonestOffence = val;
	AttrIsUpdated = true;
}
void AttributesManager::SetHonestDefence(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_HONEST_DEFENCE);
	PlayerProfile.avatarAttribute.fHonestDefence = val;
	AttrIsUpdated = true;
}
void AttributesManager::SetStrangeOffence(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_STRANGE_OFFENCE);
	PlayerProfile.avatarAttribute.fStrangeOffence = val;
	AttrIsUpdated = true;
}
void AttributesManager::SetStrangeDefence(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_STRANGE_DEFENCE);
	PlayerProfile.avatarAttribute.fStrangeDefence = val;
	AttrIsUpdated = true;
}
void AttributesManager::SetWildOffence(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_WILD_OFFENCE);
	PlayerProfile.avatarAttribute.fWildOffence = val;
	AttrIsUpdated = true;
}
void AttributesManager::SetWildDefence(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_WILD_DEFENCE);
	PlayerProfile.avatarAttribute.fWildDefence = val;
	AttrIsUpdated = true;
}
void AttributesManager::SetEleganceOffence(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_ELEGANCE_OFFENCE);
	PlayerProfile.avatarAttribute.fEleganceOffence = val;
	AttrIsUpdated = true;
}
void AttributesManager::SetEleganceDefence(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_ELEGANCE_DEFENCE);
	PlayerProfile.avatarAttribute.fEleganceDefence = val;
	AttrIsUpdated = true;
}
void AttributesManager::SetFunnyOffence(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_FUNNY_OFFENCE);
	PlayerProfile.avatarAttribute.fFunnyOffence = val;
	AttrIsUpdated = true;
}
void AttributesManager::SetFunnyDefence(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_FUNNY_DEFENCE);
	PlayerProfile.avatarAttribute.fFunnyDefence = val;
	AttrIsUpdated = true;
}
void AttributesManager::SetParalyzeToleranceRate(WORD val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_PARALYZE_TOLERANCE_RATE);
	PlayerProfile.avatarAttribute.wParalyzeToleranceRate = val;
	AttrIsUpdated = true;
}
void AttributesManager::SetTerrorToleranceRate(WORD val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_TERROR_TOLERANCE_RATE);
	PlayerProfile.avatarAttribute.wTerrorToleranceRate = val;
	AttrIsUpdated = true;
}
void AttributesManager::SetConfuseToleranceRate(WORD val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_CONFUSE_TOLERANCE_RATE);
	PlayerProfile.avatarAttribute.wConfuseToleranceRate = val;
	AttrIsUpdated = true;
}
void AttributesManager::SetStoneToleranceRate(WORD val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_STONE_TOLERANCE_RATE);
	PlayerProfile.avatarAttribute.wStoneToleranceRate = val;
	AttrIsUpdated = true;
}
void AttributesManager::SetCandyToleranceRate(WORD val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_CANDY_TOLERANCE_RATE);
	PlayerProfile.avatarAttribute.wCandyToleranceRate = val;
	AttrIsUpdated = true;
}
void AttributesManager::SetParalyzeKeepTimeDown(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_PARALYZE_TOLERANCE_RATE);
	PlayerProfile.avatarAttribute.fParalyzeKeepTimeDown = val;
	AttrIsUpdated = true;
}
void AttributesManager::SetTerrorKeepTimeDown(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_TERROR_KEEP_TIME_DOWN);
	PlayerProfile.avatarAttribute.fTerrorKeepTimeDown = val;
	AttrIsUpdated = true;
}
void AttributesManager::SetConfuseKeepTimeDown(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_CONFUSE_KEEP_TIME_DOWN);
	PlayerProfile.avatarAttribute.fConfuseKeepTimeDown = val;
	AttrIsUpdated = true;
}
void AttributesManager::SetStoneKeepTimeDown(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_STONE_KEEP_TIME_DOWN);
	PlayerProfile.avatarAttribute.fStoneKeepTimeDown = val;
	AttrIsUpdated = true;
}
void AttributesManager::SetCandyKeepTimeDown(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_CANDY_KEEP_TIME_DOWN);
	PlayerProfile.avatarAttribute.fCandyKeepTimeDown = val;
	AttrIsUpdated = true;
}
void AttributesManager::SetBleedingKeepTimeDown(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_BLEEDING_KEEP_TIME_DOWN);
	PlayerProfile.avatarAttribute.fBleedingKeepTimeDown = val;
	AttrIsUpdated = true;
}
void AttributesManager::SetPoisonKeepTimeDown(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_POISON_KEEP_TIME_DOWN);
	PlayerProfile.avatarAttribute.fPoisonKeepTimeDown = val;
	AttrIsUpdated = true;
}
void AttributesManager::SetStomachacheKeepTimeDown(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_STOMACHACHE_KEEP_TIME_DOWN);
	PlayerProfile.avatarAttribute.fStoneKeepTimeDown = val;
	AttrIsUpdated = true;
}
void AttributesManager::SetCriticalBlockSuccessRate(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_CRITICAL_BLOCK_SUCCESS_RATE);
	PlayerProfile.avatarAttribute.fCriticalBlockSuccessRate = val;
	AttrIsUpdated = true;
}
void AttributesManager::SetGuardRate(WORD val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_GUARD_RATE_BASE);
	PlayerProfile.avatarAttribute.wGuardRate = val;
	AttrIsUpdated = true;
}
void AttributesManager::SetSkillDamageBlockModeSuccessRate(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_SKILL_DAMAGE_BLOCK_MODE_SUCCESS_RATE_LAST);
	PlayerProfile.avatarAttribute.fSkillDamageBlockModeSuccessRate = val;
	AttrIsUpdated = true;
}
void AttributesManager::SetCurseBlockModeSuccessRate(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_CURSE_BLOCK_MODE_SUCCESS_RATE_LAST);
	PlayerProfile.avatarAttribute.fCurseBlockModeSuccessRate = val;
	AttrIsUpdated = true;
}
void AttributesManager::SetKnockdownBlockModeSuccessRate(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_KNOCKDOWN_BLOCK_MODE_SUCCESS_RATE_LAST);
	PlayerProfile.avatarAttribute.fKnockdownBlockModeSuccessRate = val;
	AttrIsUpdated = true;
}
void AttributesManager::SetHtbBlockModeSuccessRate(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_HTB_BLOCK_MODE_SUCCESS_RATE_LAST);
	PlayerProfile.avatarAttribute.fHtbBlockModeSuccessRate = val;
	AttrIsUpdated = true;
}
void AttributesManager::SetSitDownLpRegenBonusRate(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_SIT_DOWN_LP_REGENERATION_UP);
	PlayerProfile.avatarAttribute.fSitDownLpRegenBonusRate = val;
	AttrIsUpdated = true;
}
void AttributesManager::SetSitDownEpRegenBonusRate(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_SIT_DOWN_EP_REGENERATION_UP);
	PlayerProfile.avatarAttribute.fSitDownEpRegenBonusRate = val;
	AttrIsUpdated = true;
}
void AttributesManager::SetPhysicalCriticalDamageBonusRate(float val)
{
	PlayerProfile.avatarAttribute.fPhysicalCriticalDamageBonusRate = val;
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_PHYSICAL_CRITICAL_DAMAGE_UP);
	AttrIsUpdated = true;
}
void AttributesManager::SetEnergyCriticalDamageBonusRate(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_ENERGY_CRITICAL_DAMAGE_UP);
	PlayerProfile.avatarAttribute.fEnergyCriticalDamageBonusRate = val;
	AttrIsUpdated = true;
}
void AttributesManager::SetItemUpgradeBonusRate(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_ITEM_UPGRADE_RATE_UP);
	PlayerProfile.avatarAttribute.fItemUpgradeBonusRate = val;
	AttrIsUpdated = true;
}
void AttributesManager::SetItemUpgradeBreakBonusRate(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_ITEM_BREAK_RATE_DOWN);
	PlayerProfile.avatarAttribute.fItemUpgradeBreakBonusRate = val;
	AttrIsUpdated = true;
}
void AttributesManager::SetSkillSpeed(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_SKILL_SPEED);
	PlayerProfile.avatarAttribute.SkillSpeed = val;
	AttrIsUpdated = true;
}

void AttributesManager::SetLastPhysicalCriticalDefenceRate(WORD val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_PHYSICAL_CRITICAL_DEFENCE_RATE_LAST);
	PlayerProfile.avatarAttribute.lastPhysicalCriticalDefenceRate = val;
	AttrIsUpdated = true;
}

void AttributesManager::SetLastEnergyCriticalDefenceRate(WORD val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_ENERGY_CRITICAL_DEFENCE_RATE_LAST);
	PlayerProfile.avatarAttribute.lastEnergyCriticalDefenceRate = val;
	AttrIsUpdated = true;
}

void AttributesManager::SetLastPhysicalCriticalRange(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_PHYSICAL_CRITICAL_RANGE_LAST);
	PlayerProfile.avatarAttribute.fLastPhysicalCriticalRange = val;
	AttrIsUpdated = true;
}

void AttributesManager::SetLastEnergyCriticalRange(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_ENERGY_CRITICAL_RANGE_LAST);
	PlayerProfile.avatarAttribute.fLastEnergyCriticalRange = val;
	AttrIsUpdated = true;
}

void AttributesManager::SetLastApDegeneration(WORD val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_AP_DEGENERATION_LAST);
	PlayerProfile.avatarAttribute.wLastApDegen = val;
	AttrIsUpdated = true;
}

void AttributesManager::SetLastApBattleDegeneration(WORD val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_AP_BATTLE_DEGENERATION_LAST);
	PlayerProfile.avatarAttribute.wLastApBattleDegen = val;
	AttrIsUpdated = true;
}

void AttributesManager::SetLastBlockDamageRate(WORD val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_BLOCK_DAMAGE_RATE_LAST);
	PlayerProfile.avatarAttribute.wLastBlockDamageRate = val;
	AttrIsUpdated = true;
}

void AttributesManager::SetLastLPSitDownRegeneration(WORD val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_LP_SITDOWN_REGENERATION_LAST);
	PlayerProfile.avatarAttribute.wLastLpSitdownRegen = val;
	AttrIsUpdated = true;
}

void AttributesManager::SetLastEPSitDownRegeneration(WORD val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_EP_SITDOWN_REGENERATION_LAST);
	PlayerProfile.avatarAttribute.wLastEpSitdownRegen = val;
	AttrIsUpdated = true;
}

void AttributesManager::SetLastEPBattleRegeneration(WORD val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_EP_BATTLE_REGENERATION_LAST);
	PlayerProfile.avatarAttribute.wLastEpBattleRegen = val;
	AttrIsUpdated = true;
}

void AttributesManager::SetLastRpRegen(WORD val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_RP_CHARGE_SPEED_LAST);
	PlayerProfile.avatarAttribute.wLastRpRegen = val;
	AttrIsUpdated = true;
}

void AttributesManager::SetLastRpDimimution(WORD val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_RP_DIMIMUTION);
	PlayerProfile.avatarAttribute.wLastRpDimimutionRate = val;
	AttrIsUpdated = true;
}

//Add


void AttributesManager::AddLastStr(WORD val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_STR_LAST);
	PlayerProfile.avatarAttribute.byLastStr += val;
	AttrIsUpdated = true;
}
void AttributesManager::AddLastCon(WORD val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_CON_LAST);
	PlayerProfile.avatarAttribute.byLastCon += val;
	AttrIsUpdated = true;
}
void AttributesManager::AddLastFoc(WORD val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_FOC_LAST);
	PlayerProfile.avatarAttribute.byLastFoc += val;
	AttrIsUpdated = true;
}
void AttributesManager::AddLastDex(WORD val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_DEX_LAST);
	PlayerProfile.avatarAttribute.byLastDex += val;
	AttrIsUpdated = true;
}
void AttributesManager::AddLastEng(WORD val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_ENG_LAST);
	PlayerProfile.avatarAttribute.byLastEng += val;
	AttrIsUpdated = true;
}
void AttributesManager::AddLastSol(WORD val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_SOL_LAST);
	PlayerProfile.avatarAttribute.byLastSol += val;
	AttrIsUpdated = true;
}
void AttributesManager::AddLastMaxLP(DWORD val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_MAX_LP_LAST);
	PlayerProfile.avatarAttribute.wLastMaxLP += val;
	AttrIsUpdated = true;
}
void AttributesManager::AddLastMaxEP(WORD val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_MAX_EP_LAST);
	PlayerProfile.avatarAttribute.wLastMaxEP += val;
	AttrIsUpdated = true;
}
void AttributesManager::AddLastMaxAP(DWORD val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_MAX_AP_LAST);
	PlayerProfile.avatarAttribute.wLastMaxAp += val;
	AttrIsUpdated = true;
}
void AttributesManager::AddLastMaxRP(WORD val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_MAX_RP_LAST);
	PlayerProfile.avatarAttribute.wLastMaxRP += val;
	AttrIsUpdated = true;
}
void AttributesManager::AddLastLPRegen(WORD val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_LP_REGENERATION_LAST);
	PlayerProfile.avatarAttribute.wLastLpRegen += val;
	AttrIsUpdated = true;
}
void AttributesManager::AddLastEPRegen(WORD val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_EP_REGENERATION_LAST);
	PlayerProfile.avatarAttribute.wLastEpRegen += val;
	AttrIsUpdated = true;
}
void AttributesManager::AddLastAPRegen(WORD val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_AP_REGENERATION_LAST);
	PlayerProfile.avatarAttribute.wLastApRegen += val;
	AttrIsUpdated = true;
}
void AttributesManager::AddLastPhysicalOffence(WORD val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_PHYSICAL_OFFENCE_LAST);
	PlayerProfile.avatarAttribute.wLastPhysicalOffence += val;
	AttrIsUpdated = true;
}
void AttributesManager::AddLastPhysicalDefence(WORD val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_PHYSICAL_DEFENCE_LAST);
	PlayerProfile.avatarAttribute.wLastPhysicalDefence += val;
	AttrIsUpdated = true;
}
void AttributesManager::AddLastEnergyOffence(WORD val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_ENERGY_OFFENCE_LAST);
	PlayerProfile.avatarAttribute.wLastEnergyOffence += val;
	AttrIsUpdated = true;
}
void AttributesManager::AddLastEnergyDefence(WORD val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_ENERGY_DEFENCE_LAST);
	PlayerProfile.avatarAttribute.wLastEnergyDefence += val;
	AttrIsUpdated = true;
}
void AttributesManager::AddLastAttackRate(WORD val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_ATTACK_RATE_LAST);
	PlayerProfile.avatarAttribute.wLastAttackRate += val;
	AttrIsUpdated = true;
}
void AttributesManager::AddLastDodgeRate(WORD val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_DODGE_RATE_LAST);
	PlayerProfile.avatarAttribute.wLastDodgeRate += val;
	AttrIsUpdated = true;
}
void AttributesManager::AddLastBlockRate(WORD val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_BLOCK_RATE_LAST);
	PlayerProfile.avatarAttribute.wLastBlockRate += val;
	AttrIsUpdated = true;
}
void AttributesManager::AddLastCurseSuccessRate(WORD val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_CURSE_SUCCESS_LAST);
	PlayerProfile.avatarAttribute.wLastCurseSuccessRate += val;
	AttrIsUpdated = true;
}
void AttributesManager::AddLastCurseToleranceRate(WORD val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_CURSE_TOLERANCE_LAST);
	PlayerProfile.avatarAttribute.wLastCurseToleranceRate += val;
	AttrIsUpdated = true;
}
void AttributesManager::AddLastPhysicalCriticalRate(WORD val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_PHYSICAL_CRITICAL_LAST);
	PlayerProfile.avatarAttribute.wLastPhysicalCriticalRate += val;
	AttrIsUpdated = true;
}
void AttributesManager::AddLastEnergyCriticalRate(WORD val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_ENERGY_CRITICAL_LAST);
	PlayerProfile.avatarAttribute.wLastEnergyCriticalRate += val;
	AttrIsUpdated = true;
}
void AttributesManager::AddLastRunSpeed(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_RUN_SPEED_LAST);
	PlayerProfile.avatarAttribute.fLastRunSpeed += val;
	AttrIsUpdated = true;
}
void AttributesManager::AddLastAirSpeed(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_AIR_SPEED_LAST);
	PlayerProfile.avatarAttribute.fLastAirSpeed += val;
	AttrIsUpdated = true;
}
void AttributesManager::AddLastAirDashSpeed(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_AIR_DASH_SPEED_LAST);
	PlayerProfile.avatarAttribute.fLastAirDashSpeed += val;
	AttrIsUpdated = true;
}
void AttributesManager::AddLastAirDash2Speed(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_AIR_DASH2_SPEED_LAST);
	PlayerProfile.avatarAttribute.fLastAirDash2Speed += val;
	AttrIsUpdated = true;
}
void AttributesManager::AddLastAttackSpeedRate(WORD val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_ATTACK_SPEED_RATE_LAST);
	PlayerProfile.avatarAttribute.wLastAttackSpeedRate += val;
	AttrIsUpdated = true;
}
void AttributesManager::AddLastAttackRange(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_ATTACK_RANGE_LAST);
	PlayerProfile.avatarAttribute.fLastAttackRange += val;
	AttrIsUpdated = true;
}
void AttributesManager::AddCastingTimeChangePercent(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_CASTING_TIME_CHANGE_PERCENT);
	PlayerProfile.avatarAttribute.fCastingTimeChangePercent += val;
	AttrIsUpdated = true;
}
void AttributesManager::AddCoolTimeChangePercent(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_COOL_TIME_CHANGE_PERCENT);
	PlayerProfile.avatarAttribute.fCoolTimeChangePercent += val;
	AttrIsUpdated = true;
}
void AttributesManager::AddKeepTimeChangePercent(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_KEEP_TIME_CHANGE_PERCENT);
	PlayerProfile.avatarAttribute.fKeepTimeChangePercent += val;
	AttrIsUpdated = true;
}
void AttributesManager::AddDotValueChangePercent(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_DOT_VALUE_CHANGE_PERCENT);
	PlayerProfile.avatarAttribute.fDotValueChangePercent += val;
	AttrIsUpdated = true;
}
void AttributesManager::AddDotTimeChangeAbsolute(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_DOT_TIME_CHANGE_ABSOLUTE);
	PlayerProfile.avatarAttribute.fDotTimeChangeAbsolute += val;
	AttrIsUpdated = true;
}
void AttributesManager::AddRequiredEpChangePercent(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_REQUIRED_EP_CHANGE_PERCENT);
	PlayerProfile.avatarAttribute.fRequiredEpChangePercent += val;
	AttrIsUpdated = true;
}
void AttributesManager::AddHonestOffence(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_HONEST_OFFENCE);
	PlayerProfile.avatarAttribute.fHonestOffence += val;
	AttrIsUpdated = true;
}
void AttributesManager::AddHonestDefence(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_HONEST_DEFENCE);
	PlayerProfile.avatarAttribute.fHonestDefence += val;
	AttrIsUpdated = true;
}
void AttributesManager::AddStrangeOffence(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_STRANGE_OFFENCE);
	PlayerProfile.avatarAttribute.fStrangeOffence += val;
	AttrIsUpdated = true;
}
void AttributesManager::AddStrangeDefence(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_STRANGE_DEFENCE);
	PlayerProfile.avatarAttribute.fStrangeDefence += val;
	AttrIsUpdated = true;
}
void AttributesManager::AddWildOffence(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_WILD_OFFENCE);
	PlayerProfile.avatarAttribute.fWildOffence += val;
	AttrIsUpdated = true;
}
void AttributesManager::AddWildDefence(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_WILD_DEFENCE);
	PlayerProfile.avatarAttribute.fWildDefence += val;
	AttrIsUpdated = true;
}
void AttributesManager::AddEleganceOffence(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_ELEGANCE_OFFENCE);
	PlayerProfile.avatarAttribute.fEleganceOffence += val;
	AttrIsUpdated = true;
}
void AttributesManager::AddEleganceDefence(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_ELEGANCE_DEFENCE);
	PlayerProfile.avatarAttribute.fEleganceDefence += val;
	AttrIsUpdated = true;
}
void AttributesManager::AddFunnyOffence(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_FUNNY_OFFENCE);
	PlayerProfile.avatarAttribute.fFunnyOffence += val;
	AttrIsUpdated = true;
}
void AttributesManager::AddFunnyDefence(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_FUNNY_DEFENCE);
	PlayerProfile.avatarAttribute.fFunnyDefence += val;
	AttrIsUpdated = true;
}
void AttributesManager::AddParalyzeToleranceRate(WORD val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_PARALYZE_TOLERANCE_RATE);
	PlayerProfile.avatarAttribute.wParalyzeToleranceRate += val;
	AttrIsUpdated = true;
}
void AttributesManager::AddTerrorToleranceRate(WORD val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_TERROR_TOLERANCE_RATE);
	PlayerProfile.avatarAttribute.wTerrorToleranceRate += val;
	AttrIsUpdated = true;
}
void AttributesManager::AddConfuseToleranceRate(WORD val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_CONFUSE_TOLERANCE_RATE);
	PlayerProfile.avatarAttribute.wConfuseToleranceRate += val;
	AttrIsUpdated = true;
}
void AttributesManager::AddStoneToleranceRate(WORD val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_STONE_TOLERANCE_RATE);
	PlayerProfile.avatarAttribute.wStoneToleranceRate += val;
	AttrIsUpdated = true;
}
void AttributesManager::AddCandyToleranceRate(WORD val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_CANDY_TOLERANCE_RATE);
	PlayerProfile.avatarAttribute.wCandyToleranceRate += val;
	AttrIsUpdated = true;
}
void AttributesManager::AddParalyzeKeepTimeDown(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_PARALYZE_TOLERANCE_RATE);
	PlayerProfile.avatarAttribute.fParalyzeKeepTimeDown += val;
	AttrIsUpdated = true;
}
void AttributesManager::AddTerrorKeepTimeDown(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_TERROR_KEEP_TIME_DOWN);
	PlayerProfile.avatarAttribute.fTerrorKeepTimeDown += val;
	AttrIsUpdated = true;
}
void AttributesManager::AddConfuseKeepTimeDown(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_CONFUSE_KEEP_TIME_DOWN);
	PlayerProfile.avatarAttribute.fConfuseKeepTimeDown += val;
	AttrIsUpdated = true;
}
void AttributesManager::AddStoneKeepTimeDown(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_STONE_KEEP_TIME_DOWN);
	PlayerProfile.avatarAttribute.fStoneKeepTimeDown += val;
	AttrIsUpdated = true;
}
void AttributesManager::AddCandyKeepTimeDown(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_CANDY_KEEP_TIME_DOWN);
	PlayerProfile.avatarAttribute.fCandyKeepTimeDown += val;
	AttrIsUpdated = true;
}
void AttributesManager::AddBleedingKeepTimeDown(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_BLEEDING_KEEP_TIME_DOWN);
	PlayerProfile.avatarAttribute.fBleedingKeepTimeDown += val;
	AttrIsUpdated = true;
}
void AttributesManager::AddPoisonKeepTimeDown(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_POISON_KEEP_TIME_DOWN);
	PlayerProfile.avatarAttribute.fPoisonKeepTimeDown += val;
	AttrIsUpdated = true;
}
void AttributesManager::AddStomachacheKeepTimeDown(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_STOMACHACHE_KEEP_TIME_DOWN);
	PlayerProfile.avatarAttribute.fStoneKeepTimeDown += val;
	AttrIsUpdated = true;
}
void AttributesManager::AddCriticalBlockSuccessRate(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_CRITICAL_BLOCK_SUCCESS_RATE);
	PlayerProfile.avatarAttribute.fCriticalBlockSuccessRate += val;
	AttrIsUpdated = true;
}
void AttributesManager::AddGuardRate(WORD val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_GUARD_RATE_BASE);
	PlayerProfile.avatarAttribute.wGuardRate += val;
	AttrIsUpdated = true;
}
void AttributesManager::AddSkillDamageBlockModeSuccessRate(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_SKILL_DAMAGE_BLOCK_MODE_SUCCESS_RATE_LAST);
	PlayerProfile.avatarAttribute.fSkillDamageBlockModeSuccessRate += val;
	AttrIsUpdated = true;
}
void AttributesManager::AddCurseBlockModeSuccessRate(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_CURSE_BLOCK_MODE_SUCCESS_RATE_LAST);
	PlayerProfile.avatarAttribute.fCurseBlockModeSuccessRate += val;
	AttrIsUpdated = true;
}
void AttributesManager::AddKnockdownBlockModeSuccessRate(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_KNOCKDOWN_BLOCK_MODE_SUCCESS_RATE_LAST);
	PlayerProfile.avatarAttribute.fKnockdownBlockModeSuccessRate += val;
	AttrIsUpdated = true;
}
void AttributesManager::AddHtbBlockModeSuccessRate(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_HTB_BLOCK_MODE_SUCCESS_RATE_LAST);
	PlayerProfile.avatarAttribute.fHtbBlockModeSuccessRate += val;
	AttrIsUpdated = true;
}
void AttributesManager::AddSitDownLpRegenBonusRate(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_SIT_DOWN_LP_REGENERATION_UP);
	PlayerProfile.avatarAttribute.fSitDownLpRegenBonusRate += val;
	AttrIsUpdated = true;
}
void AttributesManager::AddSitDownEpRegenBonusRate(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_SIT_DOWN_EP_REGENERATION_UP);
	PlayerProfile.avatarAttribute.fSitDownEpRegenBonusRate += val;
	AttrIsUpdated = true;
}
void AttributesManager::AddPhysicalCriticalDamageBonusRate(float val)
{
	PlayerProfile.avatarAttribute.fPhysicalCriticalDamageBonusRate += val;
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_PHYSICAL_CRITICAL_DAMAGE_UP);
	AttrIsUpdated = true;
}
void AttributesManager::AddEnergyCriticalDamageBonusRate(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_ENERGY_CRITICAL_DAMAGE_UP);
	PlayerProfile.avatarAttribute.fEnergyCriticalDamageBonusRate += val;
	AttrIsUpdated = true;
}
void AttributesManager::AddItemUpgradeBonusRate(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_ITEM_UPGRADE_RATE_UP);
	PlayerProfile.avatarAttribute.fItemUpgradeBonusRate += val;
	AttrIsUpdated = true;
}
void AttributesManager::AddItemUpgradeBreakBonusRate(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_ITEM_BREAK_RATE_DOWN);
	PlayerProfile.avatarAttribute.fItemUpgradeBreakBonusRate += val;
	AttrIsUpdated = true;
}
void AttributesManager::AddSkillSpeed(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_SKILL_SPEED);
	PlayerProfile.avatarAttribute.SkillSpeed += val;
	AttrIsUpdated = true;
}

void AttributesManager::AddLastPhysicalCriticalDefenceRate(WORD val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_PHYSICAL_CRITICAL_DEFENCE_RATE_LAST);
	PlayerProfile.avatarAttribute.lastPhysicalCriticalDefenceRate += val;
	AttrIsUpdated = true;
}

void AttributesManager::AddLastEnergyCriticalDefenceRate(WORD val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_ENERGY_CRITICAL_DEFENCE_RATE_LAST);
	PlayerProfile.avatarAttribute.lastEnergyCriticalDefenceRate += val;
	AttrIsUpdated = true;
}

void AttributesManager::AddLastPhysicalCriticalRange(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_PHYSICAL_CRITICAL_RANGE_LAST);
	PlayerProfile.avatarAttribute.fLastPhysicalCriticalRange += val;
	AttrIsUpdated = true;
}

void AttributesManager::AddLastEnergyCriticalRange(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_ENERGY_CRITICAL_RANGE_LAST);
	PlayerProfile.avatarAttribute.fLastEnergyCriticalRange += val;
	AttrIsUpdated = true;
}

void AttributesManager::AddLastApDegeneration(WORD val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_AP_DEGENERATION_LAST);
	PlayerProfile.avatarAttribute.wLastApDegen += val;
	AttrIsUpdated = true;
}

void AttributesManager::AddLastApBattleDegeneration(WORD val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_AP_BATTLE_DEGENERATION_LAST);
	PlayerProfile.avatarAttribute.wLastApBattleDegen += val;
	AttrIsUpdated = true;
}

void AttributesManager::AddLastBlockDamageRate(WORD val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_BLOCK_DAMAGE_RATE_LAST);
	PlayerProfile.avatarAttribute.wLastBlockDamageRate += val;
	AttrIsUpdated = true;
}

void AttributesManager::AddLastLPSitDownRegeneration(WORD val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_LP_SITDOWN_REGENERATION_LAST);
	PlayerProfile.avatarAttribute.wLastLpSitdownRegen += val;
	AttrIsUpdated = true;
}

void AttributesManager::AddLastEPSitDownRegeneration(WORD val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_EP_SITDOWN_REGENERATION_LAST);
	PlayerProfile.avatarAttribute.wLastEpSitdownRegen += val;
	AttrIsUpdated = true;
}

void AttributesManager::AddLastEPBattleRegeneration(WORD val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_EP_BATTLE_REGENERATION_LAST);
	PlayerProfile.avatarAttribute.wLastEpBattleRegen += val;
	AttrIsUpdated = true;
}

void AttributesManager::AddLastRpRegen(WORD val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_RP_CHARGE_SPEED_LAST);
	PlayerProfile.avatarAttribute.wLastRpRegen += val;
	AttrIsUpdated = true;
}

void AttributesManager::AddLastRpDimimution(WORD val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_RP_DIMIMUTION);
	PlayerProfile.avatarAttribute.wLastRpDimimutionRate += val;
	AttrIsUpdated = true;
}