#include <Game\Object\Manager\Attributes.h>
#include <Game\Object\Player.h>
#include <WorldSession.h>
#include <mysqlconn_wrapper.h>
#include <Logger.h>
#include <Packet\Game\PacketGU.h>

void AttributesManager::SetLastStr(WORD val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_STR_LAST);
	PlayerProfile.avatarAttribute.byLastStr += val;
}
void AttributesManager::SetLastCon(WORD val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_CON_LAST);
	PlayerProfile.avatarAttribute.byLastCon += val;
}
void AttributesManager::SetLastFoc(WORD val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_FOC_LAST);
	PlayerProfile.avatarAttribute.byLastFoc += val;
}
void AttributesManager::SetLastDex(WORD val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_DEX_LAST);
	PlayerProfile.avatarAttribute.byLastDex += val;
}
void AttributesManager::SetLastEng(WORD val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_ENG_LAST);
	PlayerProfile.avatarAttribute.byLastEng += val;
}
void AttributesManager::SetLastSol(WORD val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_SOL_LAST);
	PlayerProfile.avatarAttribute.byLastSol += val;
}
void AttributesManager::SetLastMaxLP(DWORD val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_MAX_LP_LAST);
	PlayerProfile.avatarAttribute.wLastMaxLP += val;
}
void AttributesManager::SetLastMaxEP(WORD val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_MAX_EP_LAST);
	PlayerProfile.avatarAttribute.wLastMaxEP += val;
}
void AttributesManager::SetLastMaxAP(DWORD val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_MAX_AP_LAST);
	PlayerProfile.avatarAttribute.wLastMaxAp = val;
}
void AttributesManager::SetLastMaxRP(WORD val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_MAX_RP_LAST);
	PlayerProfile.avatarAttribute.wLastMaxRP = val;
}
void AttributesManager::SetLastLPRegen(WORD val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_LP_REGENERATION_LAST);
	PlayerProfile.avatarAttribute.wLastLpRegen = val;
}
void AttributesManager::SetLastEPRegen(WORD val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_EP_REGENERATION_LAST);
	PlayerProfile.avatarAttribute.wLastEpRegen = val;
}
void AttributesManager::SetLastAPRegen(WORD val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_AP_REGENERATION_LAST);
	PlayerProfile.avatarAttribute.wLastApRegen = val;
}
void AttributesManager::SetLastPhysicalOffence(WORD val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_PHYSICAL_OFFENCE_LAST);
	PlayerProfile.avatarAttribute.wLastPhysicalOffence += val;
}
void AttributesManager::SetLastPhysicalDefence(WORD val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_PHYSICAL_DEFENCE_LAST);
	PlayerProfile.avatarAttribute.wLastPhysicalDefence += val;
}
void AttributesManager::SetLastEnergyOffence(WORD val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_ENERGY_OFFENCE_LAST);
	PlayerProfile.avatarAttribute.wLastEnergyOffence += val;
}
void AttributesManager::SetLastEnergyDefence(WORD val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_ENERGY_DEFENCE_LAST);
	PlayerProfile.avatarAttribute.wLastEnergyDefence += val;
}
void AttributesManager::SetLastAttackRate(WORD val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_ATTACK_RATE_LAST);
	PlayerProfile.avatarAttribute.wLastAttackRate += val;
}
void AttributesManager::SetLastDodgeRate(WORD val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_DODGE_RATE_LAST);
	PlayerProfile.avatarAttribute.wLastDodgeRate += val;
}
void AttributesManager::SetLastBlockRate(WORD val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_BLOCK_RATE_LAST);
	PlayerProfile.avatarAttribute.wLastBlockRate += val;
}
void AttributesManager::SetLastCurseSuccessRate(WORD val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_CURSE_SUCCESS_LAST);
	PlayerProfile.avatarAttribute.wLastCurseSuccessRate += val;
}
void AttributesManager::SetLastCurseToleranceRate(WORD val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_CURSE_TOLERANCE_LAST);
	PlayerProfile.avatarAttribute.wBaseCurseToleranceRate += val;
}
void AttributesManager::SetLastPhysicalCriticalRate(WORD val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_PHYSICAL_CRITICAL_LAST);
	PlayerProfile.avatarAttribute.wLastPhysicalCriticalRate += val;
}
void AttributesManager::SetLastEnergyCriticalRate(WORD val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_ENERGY_CRITICAL_LAST);
	PlayerProfile.avatarAttribute.wLastEnergyCriticalRate += val;
}
void AttributesManager::SetLastRunSpeed(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_RUN_SPEED_LAST);
	PlayerProfile.avatarAttribute.fLastRunSpeed = val;
}
void AttributesManager::SetLastAirSpeed(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_AIR_SPEED_LAST);
	PlayerProfile.avatarAttribute.fLastAirSpeed += val;
}
void AttributesManager::SetLastAirDashSpeed(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_AIR_DASH_SPEED_LAST);
	PlayerProfile.avatarAttribute.fLastAirDashSpeed += val;
}
void AttributesManager::SetLastAirDash2Speed(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_AIR_DASH2_SPEED_LAST);
	PlayerProfile.avatarAttribute.fLastAirDash2Speed += val;
}
void AttributesManager::SetLastAttackSpeedRate(WORD val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_ATTACK_SPEED_RATE_LAST);
	PlayerProfile.avatarAttribute.wLastAttackSpeedRate += val;
}
void AttributesManager::SetLastAttackRange(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_ATTACK_RANGE_LAST);
	PlayerProfile.avatarAttribute.fLastAttackRange = val;
}
void AttributesManager::SetCastingTimeChangePercent(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_CASTING_TIME_CHANGE_PERCENT);
	PlayerProfile.avatarAttribute.fCastingTimeChangePercent = val;
}
void AttributesManager::SetCoolTimeChangePercent(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_COOL_TIME_CHANGE_PERCENT);
	PlayerProfile.avatarAttribute.fCoolTimeChangePercent += val;
}
void AttributesManager::SetKeepTimeChangePercent(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_KEEP_TIME_CHANGE_PERCENT);
	PlayerProfile.avatarAttribute.fKeepTimeChangePercent = val;
}
void AttributesManager::SetDotValueChangePercent(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_DOT_VALUE_CHANGE_PERCENT);
	PlayerProfile.avatarAttribute.fDotValueChangePercent = val;
}
void AttributesManager::SetDotTimeChangeAbsolute(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_DOT_TIME_CHANGE_ABSOLUTE);
	PlayerProfile.avatarAttribute.fDotTimeChangeAbsolute = val;
}
void AttributesManager::SetRequiredEpChangePercent(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_REQUIRED_EP_CHANGE_PERCENT);
	PlayerProfile.avatarAttribute.fRequiredEpChangePercent = val;
}
void AttributesManager::SetHonestOffence(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_HONEST_OFFENCE);
	PlayerProfile.avatarAttribute.fHonestOffence += val;
}
void AttributesManager::SetHonestDefence(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_HONEST_DEFENCE);
	PlayerProfile.avatarAttribute.fHonestDefence += val;
}
void AttributesManager::SetStrangeOffence(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_STRANGE_OFFENCE);
	PlayerProfile.avatarAttribute.fStrangeOffence += val;
}
void AttributesManager::SetStrangeDefence(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_STRANGE_DEFENCE);
	PlayerProfile.avatarAttribute.fStrangeDefence += val;
}
void AttributesManager::SetWildOffence(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_WILD_OFFENCE);
	PlayerProfile.avatarAttribute.fWildOffence += val;
}
void AttributesManager::SetWildDefence(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_WILD_DEFENCE);
	PlayerProfile.avatarAttribute.fWildDefence += val;
}
void AttributesManager::SetEleganceOffence(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_ELEGANCE_OFFENCE);
	PlayerProfile.avatarAttribute.fEleganceOffence += val;
}
void AttributesManager::SetEleganceDefence(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_ELEGANCE_DEFENCE);
	PlayerProfile.avatarAttribute.fEleganceDefence += val;
}
void AttributesManager::SetFunnyOffence(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_FUNNY_OFFENCE);
	PlayerProfile.avatarAttribute.fFunnyOffence += val;
}
void AttributesManager::SetFunnyDefence(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_FUNNY_DEFENCE);
	PlayerProfile.avatarAttribute.fFunnyDefence += val;
}
void AttributesManager::SetParalyzeToleranceRate(WORD val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_PARALYZE_TOLERANCE_RATE);
	PlayerProfile.avatarAttribute.wParalyzeToleranceRate = val;
}
void AttributesManager::SetTerrorToleranceRate(WORD val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_TERROR_TOLERANCE_RATE);
	PlayerProfile.avatarAttribute.wTerrorToleranceRate = val;
}
void AttributesManager::SetConfuseToleranceRate(WORD val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_CONFUSE_TOLERANCE_RATE);
	PlayerProfile.avatarAttribute.wConfuseToleranceRate = val;
}
void AttributesManager::SetStoneToleranceRate(WORD val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_STONE_TOLERANCE_RATE);
	PlayerProfile.avatarAttribute.wStoneToleranceRate = val;
}
void AttributesManager::SetCandyToleranceRate(WORD val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_CANDY_TOLERANCE_RATE);
	PlayerProfile.avatarAttribute.wCandyToleranceRate = val;
}
void AttributesManager::SetParalyzeKeepTimeDown(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_PARALYZE_TOLERANCE_RATE);
	PlayerProfile.avatarAttribute.fParalyzeKeepTimeDown = val;
}
void AttributesManager::SetTerrorKeepTimeDown(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_TERROR_KEEP_TIME_DOWN);
	PlayerProfile.avatarAttribute.fTerrorKeepTimeDown = val;
}
void AttributesManager::SetConfuseKeepTimeDown(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_CONFUSE_KEEP_TIME_DOWN);
	PlayerProfile.avatarAttribute.fConfuseKeepTimeDown = val;
}
void AttributesManager::SetStoneKeepTimeDown(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_STONE_KEEP_TIME_DOWN);
	PlayerProfile.avatarAttribute.fStoneKeepTimeDown = val;
}
void AttributesManager::SetCandyKeepTimeDown(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_CANDY_KEEP_TIME_DOWN);
	PlayerProfile.avatarAttribute.fCandyKeepTimeDown = val;
}
void AttributesManager::SetBleedingKeepTimeDown(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_BLEEDING_KEEP_TIME_DOWN);
	PlayerProfile.avatarAttribute.fBleedingKeepTimeDown = val;
}
void AttributesManager::SetPoisonKeepTimeDown(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_POISON_KEEP_TIME_DOWN);
	PlayerProfile.avatarAttribute.fPoisonKeepTimeDown = val;
}
void AttributesManager::SetStomachacheKeepTimeDown(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_STOMACHACHE_KEEP_TIME_DOWN);
	PlayerProfile.avatarAttribute.fStoneKeepTimeDown = val;
}
void AttributesManager::SetCriticalBlockSuccessRate(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_CRITICAL_BLOCK_SUCCESS_RATE);
	PlayerProfile.avatarAttribute.fCriticalBlockSuccessRate = val;
}
void AttributesManager::SetGuardRate(WORD val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_GUARD_RATE_BASE);
	PlayerProfile.avatarAttribute.wGuardRate = val;
}
void AttributesManager::SetSkillDamageBlockModeSuccessRate(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_SKILL_DAMAGE_BLOCK_MODE_SUCCESS_RATE_LAST);
	PlayerProfile.avatarAttribute.fSkillDamageBlockModeSuccessRate = val;
}
void AttributesManager::SetCurseBlockModeSuccessRate(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_CURSE_BLOCK_MODE_SUCCESS_RATE_LAST);
	PlayerProfile.avatarAttribute.fCurseBlockModeSuccessRate = val;
}
void AttributesManager::SetKnockdownBlockModeSuccessRate(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_KNOCKDOWN_BLOCK_MODE_SUCCESS_RATE_LAST);
	PlayerProfile.avatarAttribute.fKnockdownBlockModeSuccessRate = val;
}
void AttributesManager::SetHtbBlockModeSuccessRate(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_HTB_BLOCK_MODE_SUCCESS_RATE_LAST);
	PlayerProfile.avatarAttribute.fHtbBlockModeSuccessRate = val;
}
void AttributesManager::SetSitDownLpRegenBonusRate(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_SIT_DOWN_LP_REGENERATION_UP);
	PlayerProfile.avatarAttribute.fSitDownLpRegenBonusRate = val;
}
void AttributesManager::SetSitDownEpRegenBonusRate(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_SIT_DOWN_EP_REGENERATION_UP);
	PlayerProfile.avatarAttribute.fSitDownEpRegenBonusRate = val;
}
void AttributesManager::SetPhysicalCriticalDamageBonusRate(float val)
{
	PlayerProfile.avatarAttribute.fPhysicalCriticalDamageBonusRate = val;
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_PHYSICAL_CRITICAL_DAMAGE_UP);
}
void AttributesManager::SetEnergyCriticalDamageBonusRate(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_ENERGY_CRITICAL_DAMAGE_UP);
	PlayerProfile.avatarAttribute.fEnergyCriticalDamageBonusRate = val;
}
void AttributesManager::SetItemUpgradeBonusRate(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_ITEM_UPGRADE_RATE_UP);
	PlayerProfile.avatarAttribute.fItemUpgradeBonusRate = val;
}
void AttributesManager::SetItemUpgradeBreakBonusRate(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_ITEM_BREAK_RATE_DOWN);
	PlayerProfile.avatarAttribute.fItemUpgradeBreakBonusRate = val;
}
void AttributesManager::SetSkillSpeed(float val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_SKILL_SPEED);
	PlayerProfile.avatarAttribute.SkillSpeed = val;
}

void AttributesManager::SetPhysicalCriticalDefenceRate(WORD val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_PHYSICAL_CRITICAL_DEFENCE_RATE);
	PlayerProfile.avatarAttribute.physicalCriticalDefenceRate = val;
}

void AttributesManager::SetEnergyCriticalDefenceRate(WORD val)
{
	changedFlag.Set(eATTRIBUTE_TO_UPDATE::ATTRIBUTE_TO_UPDATE_ENERGY_CRITICAL_DEFENCE_RATE);
	PlayerProfile.avatarAttribute.energyCriticalDefenceRate = val;
}