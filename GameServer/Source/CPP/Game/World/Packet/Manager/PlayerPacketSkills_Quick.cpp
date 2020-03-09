#include <Game\World\WorldSession.h>
#include <Packet\Game\PacketGU.h>
#include <Packet\Game\PacketUG.h>
#include <Game\Object\Player.h>
#include <Game\Maps\MapManager.h>
#include <mysqlconn_wrapper.h>
#include <Logger.h>
#include <World.h>

//----------------------------------------
//	Send buff info from database
//----------------------------------------
void WorldSession::SendAvatarBuffInfo()
{
	sGU_AVATAR_BUFF_INFO res;
	memset(&res, 0, sizeof(sGU_AVATAR_BUFF_INFO));

	res.byBuffCount = _player->skillManager.getBuffCount();
	for (int i = 0; i <= res.byBuffCount; i++)
	{
		res.aBuffInfo[i].SourceTblidx = _player->skillManager.getBuffInfos()[i].SourceTblidx;
		res.aBuffInfo[i].bySourceType = _player->skillManager.getBuffInfos()[i].bySourceType;
		res.aBuffInfo[i].dwInitialDuration = _player->skillManager.getBuffInfos()[i].dwInitialDuration;
		res.aBuffInfo[i].dwTimeRemaining = _player->skillManager.getBuffInfos()[i].dwTimeRemaining;
		res.aBuffInfo[i].IsActive = 1;//Active?
		res.aBuffInfo[i].EffectType = 0;//Need discover where get the value
		res.aBuffInfo[i].InitialDuration = _player->skillManager.getBuffInfos()[i].InitialDuration;
		res.aBuffInfo[i].afEffectValue[0] = _player->skillManager.getBuffInfos()[i].afEffectValue[0];
		res.aBuffInfo[i].afEffectValue[1] = _player->skillManager.getBuffInfos()[i].afEffectValue[1];

		res.aBuffInfo[i].EffectType2 = 0;//Need discover where get the value
		res.aBuffInfo[i].InitialDuration2 = _player->skillManager.getBuffInfos()[i].InitialDuration2;
		res.aBuffInfo[i].afEffectValue2[0] = _player->skillManager.getBuffInfos()[i].afEffectValue2[0];
		res.aBuffInfo[i].afEffectValue2[1] = _player->skillManager.getBuffInfos()[i].afEffectValue2[1];
		res.aBuffInfo[i].unk6 = 1;
		
	}
	res.wOpCode = GU_AVATAR_BUFF_INFO;
	res.wPacketSize = sizeof(sGU_AVATAR_BUFF_INFO) - 2;
	SendPacket((char*)&res, sizeof(sGU_AVATAR_BUFF_INFO));
}
//----------------------------------------
//	Send HTB info
//----------------------------------------
void WorldSession::SendAvatarHTBInfo()
{
	sGU_AVATAR_HTB_INFO res;
	memset(&res, 0, sizeof(sGU_AVATAR_HTB_INFO));

	res.byHTBSkillCount = _player->skillManager.getHTBCounter();
	for (int i = 0; i < res.byHTBSkillCount; i++)
	{
		res.aHTBSkillnfo[i].bySlotId = _player->skillManager.getHTBSkillInfos()[i].bySlotId;
		res.aHTBSkillnfo[i].dwTimeRemaining = _player->skillManager.getHTBSkillInfos()[i].dwTimeRemaining;
		res.aHTBSkillnfo[i].skillId = _player->skillManager.getHTBSkillInfos()[i].skillId;
	}
	memset(&res, 0, sizeof(sGU_AVATAR_HTB_INFO));

	res.wOpCode = GU_AVATAR_HTB_INFO;
	res.wPacketSize = sizeof(sGU_AVATAR_HTB_INFO) - 2;

	SendPacket((char*)&res, sizeof(sGU_AVATAR_HTB_INFO));
}
//----------------------------------------
//	Send the quick slot info
//----------------------------------------
void WorldSession::SendSlotInfo()
{
	sGU_QUICK_SLOT_INFO res;
	memset(&res, 0, sizeof(sGU_QUICK_SLOT_INFO));

	res.wOpCode = GU_QUICK_SLOT_INFO;
	/*res.byQuickSlotCount = _player->skillManager.getQuickSlotsCounter();
	for (int i = 0; i < res.byQuickSlotCount; i++)
	{
		res.asQuickSlotData[i].bySlot = _player->skillManager.getQuickSlots()[i].bySlot;
		res.asQuickSlotData[i].byType = _player->skillManager.getQuickSlots()[i].byType;
		res.asQuickSlotData[i].hItem = _player->skillManager.getQuickSlots()[i].hItem;
		res.asQuickSlotData[i].tblidx = _player->skillManager.getQuickSlots()[i].tblidx;
	}*/
	res.wPacketSize = sizeof(sGU_QUICK_SLOT_INFO) - 2;//((2 * sizeof(BYTE)) + (res.byQuickSlotCount * sizeof(sQUICK_SLOT_DATA)));
	_player->GetQuickSlotInfo(res);
	SendPacket((char*)&res, sizeof(sGU_QUICK_SLOT_INFO));
}
//----------------------------------------
//	Send skill info get from database
//----------------------------------------
void	WorldSession::SendAvatarSkillInfo()
{
	sGU_AVATAR_SKILL_INFO res;
	memset(&res, 0, sizeof(sGU_AVATAR_SKILL_INFO));

	res.wOpCode = GU_AVATAR_SKILL_INFO;
	res.bySkillCount = _player->skillManager.getSkillsCount();
	for (int i = 0; i < res.bySkillCount; i++)
	{
		res.aSkillInfo[i].bIsRpBonusAuto = _player->skillManager.getSkillsInfos()[i].bIsRpBonusAuto;
		res.aSkillInfo[i].byRpBonusType = _player->skillManager.getSkillsInfos()[i].byRpBonusType;
		res.aSkillInfo[i].bySlotId = _player->skillManager.getSkillsInfos()[i].bySlotId;
		res.aSkillInfo[i].dwTimeRemaining = _player->skillManager.getSkillsInfos()[i].dwTimeRemaining;
		res.aSkillInfo[i].nExp = _player->skillManager.getSkillsInfos()[i].nExp;
		res.aSkillInfo[i].tblidx = _player->skillManager.getSkillsInfos()[i].tblidx;
	}
	res.wPacketSize = sizeof(sGU_AVATAR_SKILL_INFO) - 2;
	SendPacket((char*)&res, sizeof(sGU_AVATAR_SKILL_INFO));
}
void	WorldSession::SendUpdateSkillPassiveAtribute()
{
	int bySkillCount = _player->skillManager.getSkillsCount();
	for (int i = 0; i < bySkillCount; i++)
	{
		int skillID = _player->skillManager.getSkillsInfos()[i].tblidx;
		SkillTable * skillTable = sTBM.GetSkillTable();
		sSKILL_TBLDAT * skillDataOriginal = reinterpret_cast<sSKILL_TBLDAT*>(skillTable->FindData(skillID));
		if (skillDataOriginal != NULL)
		{
			for (int Effect = 0; Effect <= 2; Effect++)
			{
				int count = 0;
				sSYSTEM_EFFECT_TBLDAT * SystemEffectData = NULL;
				SystemEffectData = (sSYSTEM_EFFECT_TBLDAT*)sTBM.GetSystemEffectTable()->FindData(skillDataOriginal->skill_Effect[Effect]);
				if (SystemEffectData != NULL)
				{
				//	printf("skill_Effect %d \n", skillDataOriginal->skill_Effect[Effect]);
				//	printf("effectCode %d \n", SystemEffectData->effectCode);
				//	printf("Effect %d \n", Effect);
					switch (SystemEffectData->effectCode)
					{
					case PASSIVE_MAX_LP_UP:
					{						
						_player->GetAttributesManager()->SetLastMaxLP(skillDataOriginal->SkillValue[Effect]);
						break;
					}
					case PASSIVE_MAX_EP_UP:
					{						
						_player->GetAttributesManager()->SetLastMaxEP(skillDataOriginal->SkillValue[Effect]);
						break;
					}
					case PASSIVE_MAX_RP_DOWN:
					{						
						_player->GetAttributesManager()->SetLastMaxRP(skillDataOriginal->SkillValue[Effect]);						
						break;
					}
					case PASSIVE_PHYSICAL_OFFENCE_UP:
					{						
						_player->GetAttributesManager()->SetLastPhysicalOffence(skillDataOriginal->SkillValue[Effect]);						
						break;
					}
					case PASSIVE_ENERGY_OFFENCE_UP:
					{					
						_player->GetAttributesManager()->SetLastEnergyOffence(skillDataOriginal->SkillValue[Effect]);					
						break;
					}
					case PASSIVE_PHYSICAL_DEFENCE_UP:
					{						
						_player->GetAttributesManager()->SetLastPhysicalDefence(skillDataOriginal->SkillValue[Effect]);						
						break;
					}
					case PASSIVE_ENERGY_DEFENCE_UP:
					{						
						_player->GetAttributesManager()->SetLastEnergyDefence(skillDataOriginal->SkillValue[Effect]);						
						break;
					}
					case PASSIVE_STR_UP:
					{						
						_player->GetAttributesManager()->SetLastStr(skillDataOriginal->SkillValue[Effect]);
						WORD LevelStr = skillDataOriginal->SkillValue[Effect];
						float StrByPoint = 1.66; // 1Str = 1.66 Physical old tw
						WORD PhysicalOffence = static_cast<WORD>(LevelStr * StrByPoint);
						_player->GetAttributesManager()->SetLastPhysicalOffence(PhysicalOffence);						
						break;
					}
					case PASSIVE_CON_UP:
					{						
						_player->GetAttributesManager()->SetLastCon(skillDataOriginal->SkillValue[Effect]);
						float LevelCon = skillDataOriginal->SkillValue[Effect];
						float ConByPoint = 85; // 1con = 85 old tw
						float LP = static_cast<float>(LevelCon * ConByPoint);
						_player->GetAttributesManager()->SetLastMaxLP(LP);						
						break;
					}
					case PASSIVE_FOC_UP:
					{					
						_player->GetAttributesManager()->SetLastFoc(skillDataOriginal->SkillValue[Effect]);
						WORD LevelFoc = skillDataOriginal->SkillValue[Effect];
						float EnergyCriticalByPoint = 0.2; // 1Focus = 1 pont critical 
						float EnergyAttackByPoint = 2; // 1Focus = 1 pont critical 
						float HitRateByPoint = 10; // 1 point = 10 hit rate old tw
						WORD EnergyCriticalRate = static_cast<WORD>(LevelFoc * EnergyCriticalByPoint);
						WORD EnergyAttack = static_cast<WORD>(LevelFoc * EnergyAttackByPoint);
						WORD HitRate = static_cast<WORD>(LevelFoc * HitRateByPoint);
						_player->GetAttributesManager()->SetLastEnergyCriticalRate(EnergyCriticalRate);
						_player->GetAttributesManager()->SetLastEnergyOffence(EnergyAttack);	
						_player->GetAttributesManager()->SetLastAttackRate(HitRate);
						break;
					}
					case PASSIVE_DEX_UP:
					{
						
						_player->GetAttributesManager()->SetLastDex(skillDataOriginal->SkillValue[Effect]);
						WORD LevelDex = skillDataOriginal->SkillValue[Effect];
						float CriticalAttackByPoint = 0.2; // 1Dex = 1 critical old tw
						float PhyAttackByPoint = 2; // 1Dex = 1 phyattack old tw
						float DoggeByPoint = 5;
						WORD PhysicalCriticalRate = static_cast<WORD>(LevelDex * CriticalAttackByPoint);
						WORD PhysicalAttack = static_cast<WORD>(LevelDex * PhyAttackByPoint);
						WORD DodgeRate = static_cast<WORD>(LevelDex * DoggeByPoint);
						_player->GetAttributesManager()->SetLastPhysicalCriticalRate(PhysicalCriticalRate);
						_player->GetAttributesManager()->SetLastPhysicalOffence(PhysicalAttack);
						_player->GetAttributesManager()->SetLastDodgeRate(DodgeRate);
						break;
					}
					case PASSIVE_SOL_UP:
					{					
						_player->GetAttributesManager()->SetLastSol(skillDataOriginal->SkillValue[Effect]);
						WORD LevelSol = skillDataOriginal->SkillValue[Effect];
						float SolByPoint = 1.66; // 1Soul = 1.66 Physical old tw
						WORD EnergyOffence = static_cast<WORD>(LevelSol * SolByPoint);
						_player->GetAttributesManager()->SetLastEnergyOffence(EnergyOffence);						
						break;
					}
					case PASSIVE_ENG_UP:
					{						
						_player->GetAttributesManager()->SetLastEng(skillDataOriginal->SkillValue[Effect]);
						WORD LevelEng = skillDataOriginal->SkillValue[Effect];
						float EngByPoint = 45; // 1Eng = 45 ep old tw
						WORD EP = static_cast<WORD>(LevelEng * EngByPoint);
						_player->GetAttributesManager()->SetLastMaxEP(EP);						
						break;
					}
					case PASSIVE_DASH:
					{
						break;
					}
					case PASSIVE_HOVERING:
					{
						break;
					}
					case PASSIVE_LP_REGENERATION:
					{
						_player->GetAttributesManager()->SetLastLPRegen(skillDataOriginal->SkillValue[Effect]);
						break;
					}
					case PASSIVE_EP_REGENERATION:
					{
						_player->GetAttributesManager()->SetLastEPRegen(skillDataOriginal->SkillValue[Effect]);
						break;
					}
					case PASSIVE_ATTACK_RATE_UP:
					{
						_player->GetAttributesManager()->SetLastAttackRate(skillDataOriginal->SkillValue[Effect]);
						break;
					}
					case PASSIVE_DODGE_RATE_UP:
					{
						_player->GetAttributesManager()->SetLastDodgeRate(skillDataOriginal->SkillValue[Effect]);
						break;
					}
					case PASSIVE_BLOCK_RATE_UP:
					{
						_player->GetAttributesManager()->SetLastBlockRate(skillDataOriginal->SkillValue[Effect]);
						break;
					}
					case PASSIVE_CURSE_SUCCESS_UP:
					{
						_player->GetAttributesManager()->SetLastCurseSuccessRate(skillDataOriginal->SkillValue[Effect]);
						break;
					}
					case PASSIVE_CURSE_TOLERANCE_UP:
					{
						break;
					}
					case PASSIVE_PHYSICAL_CRITICAL_UP:
					{
						_player->GetAttributesManager()->SetLastPhysicalCriticalRate(skillDataOriginal->SkillValue[Effect]);
						break;
					}
					case PASSIVE_ENERGY_CRITICAL_UP:
					{
						_player->GetAttributesManager()->SetLastEnergyCriticalRate(skillDataOriginal->SkillValue[Effect]);
						break;
					}
					case PASSIVE_RP_CHARGE_SPEED:
					{
						break;
					}
					case PASSIVE_MOVE_SPEED:
					{
						break;
					}
					case PASSIVE_ATTACK_SPEED_UP:
					{
						break;
					}
					case PASSIVE_SKILL_CASTING_TIME_DOWN:
					{
						break;
					}
					case PASSIVE_SKILL_COOL_TIME_DOWN:
					{						
						_player->GetAttributesManager()->SetCoolTimeChangePercent(skillDataOriginal->SkillValue[Effect] * -1);
						break;
					}
					case PASSIVE_CHARGE:
					{
						break;
					}
					case PASSIVE_BLOCK_MODE:
					{
						break;
					}
					case PASSIVE_GUARD_COUNTERATTACK:
					{
						break;
					}
					case PASSIVE_DOT_VALUE_UP_ALL:
					{
						break;
					}
					case PASSIVE_DOT_TIME_UP_ALL:
					{
						break;
					}
					case PASSIVE_SKILL_EFFECT_VALUE_UP:
					{
						break;
					}
					case PASSIVE_SKILL_KEEP_TIME_UP:
					{
						break;
					}
					case PASSIVE_REQUIRE_EP_DOWN:
					{
						break;
					}
					case PASSIVE_CHANGE_APPLY_RANGE:
					{
						break;
					}
					case PASSIVE_APPLY_AREA_SIZE_UP:
					{
						break;
					}
					case PASSIVE_USE_RANGE_UP:
					{
						break;
					}
					case PASSIVE_MASTERY:
					{
						break;
					}
					case PASSIVE_AIR_MASTERY:
					{
						break;
					}
					//Next Case
					}
				}
			}
		}
	}	
}
void	WorldSession::SendUpdateSkillPassiveAtributeByID(TBLIDX SkillID, bool isRemove)
{

	SkillTable * skillTable = sTBM.GetSkillTable();
	sSKILL_TBLDAT * skillDataOriginal = NULL;
	skillDataOriginal = reinterpret_cast<sSKILL_TBLDAT*>(skillTable->FindData(SkillID));
	if (skillDataOriginal != NULL)
	{
		for (int Effect = 0; Effect <= 2; Effect++)
		{
			int count = 0;
			sSYSTEM_EFFECT_TBLDAT * SystemEffectData = NULL;
			SystemEffectData = (sSYSTEM_EFFECT_TBLDAT*)sTBM.GetSystemEffectTable()->FindData(skillDataOriginal->skill_Effect[Effect]);
			if (SystemEffectData != NULL)
			{
				printf("skill_Effect %d \n", skillDataOriginal->skill_Effect[Effect]);
				printf("effectCode %d \n", SystemEffectData->effectCode);
				printf("Effect %d \n", Effect);
				switch (SystemEffectData->effectCode)
				{
				case PASSIVE_MAX_LP_UP:
				{
					if (isRemove == true)
						_player->GetAttributesManager()->SetLastMaxLP(skillDataOriginal->SkillValue[Effect] * -1);
					else
						_player->GetAttributesManager()->SetLastMaxLP(skillDataOriginal->SkillValue[Effect]);
					break;
				}
				case PASSIVE_MAX_EP_UP:
				{
					if (isRemove == true)
						_player->GetAttributesManager()->SetLastMaxEP(skillDataOriginal->SkillValue[Effect] * -1);
					else
						_player->GetAttributesManager()->SetLastMaxEP(skillDataOriginal->SkillValue[Effect]);
					break;
				}
				case PASSIVE_MAX_RP_DOWN:
				{

					if (isRemove == true)
						_player->GetAttributesManager()->SetLastMaxRP(skillDataOriginal->SkillValue[Effect] * -1);
					else
						_player->GetAttributesManager()->SetLastMaxRP(skillDataOriginal->SkillValue[Effect]);
					if (_player->GetPcProfile()->avatarAttribute.wLastMaxRP <= 0 || _player->GetPcProfile()->avatarAttribute.wLastMaxRP >= 60000)
						_player->GetAttributesManager()->SetLastMaxRP(0);
					break;
				}
				case PASSIVE_PHYSICAL_OFFENCE_UP:
				{

					if (isRemove == true)
						_player->GetAttributesManager()->SetLastPhysicalOffence(skillDataOriginal->SkillValue[Effect] * -1);
					else
						_player->GetAttributesManager()->SetLastPhysicalOffence(skillDataOriginal->SkillValue[Effect]);
					if (_player->GetPcProfile()->avatarAttribute.wBasePhysicalOffence <= 0 || _player->GetPcProfile()->avatarAttribute.wBasePhysicalOffence >= 60000)
						_player->GetAttributesManager()->SetLastPhysicalOffence(0);
					break;
				}
				case PASSIVE_ENERGY_OFFENCE_UP:
				{

					if (isRemove == true)
						_player->GetAttributesManager()->SetLastEnergyOffence(skillDataOriginal->SkillValue[Effect] * -1);
					else
						_player->GetAttributesManager()->SetLastEnergyOffence(skillDataOriginal->SkillValue[Effect]);
					if (_player->GetPcProfile()->avatarAttribute.wBaseEnergyOffence <= 0 || _player->GetPcProfile()->avatarAttribute.wBaseEnergyOffence >= 60000)
						_player->GetAttributesManager()->SetLastEnergyOffence(0);
					break;
				}
				case PASSIVE_PHYSICAL_DEFENCE_UP:
				{

					if (isRemove == true)
						_player->GetAttributesManager()->SetLastPhysicalDefence(skillDataOriginal->SkillValue[Effect] * -1);
					else
						_player->GetAttributesManager()->SetLastPhysicalDefence(skillDataOriginal->SkillValue[Effect]);
					if (_player->GetPcProfile()->avatarAttribute.wLastPhysicalDefence <= 0 || _player->GetPcProfile()->avatarAttribute.wLastPhysicalDefence >= 60000)
						_player->GetAttributesManager()->SetLastPhysicalDefence(0);
					break;
				}
				case PASSIVE_ENERGY_DEFENCE_UP:
				{

					if (isRemove == true)
						_player->GetAttributesManager()->SetLastEnergyDefence(skillDataOriginal->SkillValue[Effect] * -1);
					else
						_player->GetAttributesManager()->SetLastEnergyDefence(skillDataOriginal->SkillValue[Effect]);
					if (_player->GetPcProfile()->avatarAttribute.wLastEnergyDefence <= 0 || _player->GetPcProfile()->avatarAttribute.wLastEnergyDefence >= 60000)
						_player->GetAttributesManager()->SetLastEnergyDefence(0);
					break;
				}
				case PASSIVE_STR_UP:
				{
					if (isRemove == true)
					{
						_player->GetAttributesManager()->SetLastStr(skillDataOriginal->SkillValue[Effect] * -1);

						WORD LevelStr = skillDataOriginal->SkillValue[Effect];
						float StrByPoint = 1.66; // 1Str = 1.66 Physical old tw
						WORD PhysicalOffence = static_cast<WORD>(LevelStr * StrByPoint);

						_player->GetAttributesManager()->SetLastPhysicalOffence(PhysicalOffence * -1);
					}
					else
					{
						_player->GetAttributesManager()->SetLastStr(skillDataOriginal->SkillValue[Effect]);

						WORD LevelStr = skillDataOriginal->SkillValue[Effect];
						float StrByPoint = 1.66; // 1Str = 1.66 Physical old tw
						WORD PhysicalOffence = static_cast<WORD>(LevelStr * StrByPoint);

						_player->GetAttributesManager()->SetLastPhysicalOffence(PhysicalOffence);
					}
					break;
				}
				case PASSIVE_CON_UP:
				{
					if (isRemove == true)
					{
						_player->GetAttributesManager()->SetLastCon(skillDataOriginal->SkillValue[Effect] * -1);

						float LevelCon = skillDataOriginal->SkillValue[Effect];
						float ConByPoint = 85; // 1con = 85 old tw
						float LP = static_cast<float>(LevelCon * ConByPoint);

						_player->GetAttributesManager()->SetLastMaxLP(LP * -1);
					}
					else
					{
						_player->GetAttributesManager()->SetLastCon(skillDataOriginal->SkillValue[Effect]);

						float LevelCon = skillDataOriginal->SkillValue[Effect];
						float ConByPoint = 85; // 1con = 85 old tw
						float LP = static_cast<float>(LevelCon * ConByPoint);

						_player->GetAttributesManager()->SetLastMaxLP(LP);
					}
					break;
				}
				case PASSIVE_FOC_UP:
				{
					if (isRemove == true)
					{
						_player->GetAttributesManager()->SetLastFoc(skillDataOriginal->SkillValue[Effect] * -1);
						WORD LevelFoc = skillDataOriginal->SkillValue[Effect];
						float EnergyCriticalByPoint = 0.2; // 1Focus = 1 pont critical 
						float EnergyAttackByPoint = 2; // 1Focus = 1 pont critical 
						float HitRateByPoint = 10; // 1 point = 10 hit rate old tw
						WORD EnergyCriticalRate = static_cast<WORD>(LevelFoc * EnergyCriticalByPoint);
						WORD EnergyAttack = static_cast<WORD>(LevelFoc * EnergyAttackByPoint);
						WORD HitRate = static_cast<WORD>(LevelFoc * HitRateByPoint);
						_player->GetAttributesManager()->SetLastEnergyCriticalRate(EnergyCriticalRate * -1);
						_player->GetAttributesManager()->SetLastEnergyOffence(EnergyAttack * -1);
						_player->GetAttributesManager()->SetLastAttackRate(HitRate * -1);
					}
					else
					{
						_player->GetAttributesManager()->SetLastFoc(skillDataOriginal->SkillValue[Effect]);
						WORD LevelFoc = skillDataOriginal->SkillValue[Effect];
						float EnergyCriticalByPoint = 0.2; // 1Focus = 1 pont critical 
						float EnergyAttackByPoint = 2; // 1Focus = 1 pont critical 
						float HitRateByPoint = 10; // 1 point = 10 hit rate old tw
						WORD EnergyCriticalRate = static_cast<WORD>(LevelFoc * EnergyCriticalByPoint);
						WORD EnergyAttack = static_cast<WORD>(LevelFoc * EnergyAttackByPoint);
						WORD HitRate = static_cast<WORD>(LevelFoc * HitRateByPoint);
						_player->GetAttributesManager()->SetLastEnergyCriticalRate(EnergyCriticalRate);
						_player->GetAttributesManager()->SetLastEnergyOffence(EnergyAttack);
						_player->GetAttributesManager()->SetLastAttackRate(HitRate);
					}
					break;
				}
				case PASSIVE_DEX_UP:
				{
					if (isRemove == true)
					{
						_player->GetAttributesManager()->SetLastDex(skillDataOriginal->SkillValue[Effect] * -1);
						WORD LevelDex = skillDataOriginal->SkillValue[Effect];
						float CriticalAttackByPoint = 0.2; // 1Dex = 1 critical old tw
						float PhyAttackByPoint = 2; // 1Dex = 1 phyattack old tw
						float DoggeByPoint = 5;
						WORD PhysicalCriticalRate = static_cast<WORD>(LevelDex * CriticalAttackByPoint);
						WORD PhysicalAttack = static_cast<WORD>(LevelDex * PhyAttackByPoint);
						WORD DodgeRate = static_cast<WORD>(LevelDex * DoggeByPoint);
						_player->GetAttributesManager()->SetLastPhysicalCriticalRate(PhysicalCriticalRate * -1);
						_player->GetAttributesManager()->SetLastPhysicalOffence(PhysicalAttack * -1);
						_player->GetAttributesManager()->SetLastDodgeRate(DodgeRate * -1);
					}
					else
					{
						_player->GetAttributesManager()->SetLastDex(skillDataOriginal->SkillValue[Effect]);
						WORD LevelDex = skillDataOriginal->SkillValue[Effect];
						float CriticalAttackByPoint = 0.2; // 1Dex = 1 critical old tw
						float PhyAttackByPoint = 2; // 1Dex = 1 phyattack old tw
						float DoggeByPoint = 5;
						WORD PhysicalCriticalRate = static_cast<WORD>(LevelDex * CriticalAttackByPoint);
						WORD PhysicalAttack = static_cast<WORD>(LevelDex * PhyAttackByPoint);
						WORD DodgeRate = static_cast<WORD>(LevelDex * DoggeByPoint);
						_player->GetAttributesManager()->SetLastPhysicalCriticalRate(PhysicalCriticalRate);
						_player->GetAttributesManager()->SetLastPhysicalOffence(PhysicalAttack);
						_player->GetAttributesManager()->SetLastDodgeRate(DodgeRate);
					}
					break;
				}
				case PASSIVE_SOL_UP:
				{
					if (isRemove == true)
					{
						_player->GetAttributesManager()->SetLastSol(skillDataOriginal->SkillValue[Effect] * -1);

						WORD LevelSol = skillDataOriginal->SkillValue[Effect];
						float SolByPoint = 1.66; // 1Soul = 1.66 Physical old tw
						WORD EnergyOffence = static_cast<WORD>(LevelSol * SolByPoint);

						_player->GetAttributesManager()->SetLastEnergyOffence(EnergyOffence * -1);
					}
					else
					{
						_player->GetAttributesManager()->SetLastSol(skillDataOriginal->SkillValue[Effect]);

						WORD LevelSol = skillDataOriginal->SkillValue[Effect];
						float SolByPoint = 1.66; // 1Soul = 1.66 Physical old tw
						WORD EnergyOffence = static_cast<WORD>(LevelSol * SolByPoint);

						_player->GetAttributesManager()->SetLastEnergyOffence(EnergyOffence);
					}
					break;
				}
				case PASSIVE_ENG_UP:
				{
					if (isRemove == true)
					{
						_player->GetAttributesManager()->SetLastEng(skillDataOriginal->SkillValue[Effect] * -1);

						WORD LevelEng = skillDataOriginal->SkillValue[Effect];
						float EngByPoint = 45; // 1Eng = 45 ep old tw
						WORD EP = static_cast<WORD>(LevelEng * EngByPoint);

						_player->GetAttributesManager()->SetLastMaxEP(EP * -1);
					}
					else
					{
						_player->GetAttributesManager()->SetLastEng(skillDataOriginal->SkillValue[Effect]);

						WORD LevelEng = skillDataOriginal->SkillValue[Effect];
						float EngByPoint = 45; // 1Eng = 45 ep old tw
						WORD EP = static_cast<WORD>(LevelEng * EngByPoint);

						_player->GetAttributesManager()->SetLastMaxEP(EP);
					}
					break;
				}
				case PASSIVE_DASH:
				{
					break;
				}
				case PASSIVE_HOVERING:
				{
					break;
				}
				case PASSIVE_LP_REGENERATION:
				{
					if (isRemove == true)
					{
						_player->GetAttributesManager()->SetLastLPRegen(skillDataOriginal->SkillValue[Effect] * -1);						
					}
					else
					{
						_player->GetAttributesManager()->SetLastLPRegen(skillDataOriginal->SkillValue[Effect]);
					}
					break;
				}
				case PASSIVE_EP_REGENERATION:
				{
					if (isRemove == true)
					{
						_player->GetAttributesManager()->SetLastEPRegen(skillDataOriginal->SkillValue[Effect] * -1);
					}
					else
					{
						_player->GetAttributesManager()->SetLastEPRegen(skillDataOriginal->SkillValue[Effect]);
					}
					break;
				}
				case PASSIVE_ATTACK_RATE_UP:
				{
					if (isRemove == true)
					{
						_player->GetAttributesManager()->SetLastAttackRate(skillDataOriginal->SkillValue[Effect] * -1);
					}
					else
					{
						_player->GetAttributesManager()->SetLastAttackRate(skillDataOriginal->SkillValue[Effect]);
					}
					break;
				}
				case PASSIVE_DODGE_RATE_UP:
				{
					if (isRemove == true)
					{
						_player->GetAttributesManager()->SetLastDodgeRate(skillDataOriginal->SkillValue[Effect] * -1);
					}
					else
					{
						_player->GetAttributesManager()->SetLastDodgeRate(skillDataOriginal->SkillValue[Effect]);
					}
					break;
				}
				case PASSIVE_BLOCK_RATE_UP:
				{
					if (isRemove == true)
					{
						_player->GetAttributesManager()->SetLastBlockRate(skillDataOriginal->SkillValue[Effect] * -1);
					}
					else
					{
						_player->GetAttributesManager()->SetLastBlockRate(skillDataOriginal->SkillValue[Effect]);
					}
					break;
				}
				case PASSIVE_CURSE_SUCCESS_UP:
				{
					if (isRemove == true)
					{
						_player->GetAttributesManager()->SetLastCurseSuccessRate(skillDataOriginal->SkillValue[Effect] * -1);
					}
					else
					{
						_player->GetAttributesManager()->SetLastCurseSuccessRate(skillDataOriginal->SkillValue[Effect]);
					}
					break;
				}
				case PASSIVE_CURSE_TOLERANCE_UP:
				{
					break;
				}
				case PASSIVE_PHYSICAL_CRITICAL_UP:
				{
					if (isRemove == true)
					{
						_player->GetAttributesManager()->SetLastPhysicalCriticalRate(skillDataOriginal->SkillValue[Effect] * -1);
					}
					else
					{
						_player->GetAttributesManager()->SetLastPhysicalCriticalRate(skillDataOriginal->SkillValue[Effect]);
					}
					break;
				}
				case PASSIVE_ENERGY_CRITICAL_UP:
				{
					if (isRemove == true)
					{
						_player->GetAttributesManager()->SetCoolTimeChangePercent(skillDataOriginal->SkillValue[Effect]);
					}
					else
					{
						_player->GetAttributesManager()->SetCoolTimeChangePercent(skillDataOriginal->SkillValue[Effect] * -1);
					}
					break;
				}
				case PASSIVE_RP_CHARGE_SPEED:
				{
					break;
				}
				case PASSIVE_MOVE_SPEED:
				{
					break;
				}
				case PASSIVE_ATTACK_SPEED_UP:
				{
					break;
				}
				case PASSIVE_SKILL_CASTING_TIME_DOWN:
				{
					break;
				}
				case PASSIVE_SKILL_COOL_TIME_DOWN:
				{

					break;
				}
				case PASSIVE_CHARGE:
				{
					break;
				}
				case PASSIVE_BLOCK_MODE:
				{
					break;
				}
				case PASSIVE_GUARD_COUNTERATTACK:
				{
					break;
				}
				case PASSIVE_DOT_VALUE_UP_ALL:
				{
					break;
				}
				case PASSIVE_DOT_TIME_UP_ALL:
				{
					break;
				}
				case PASSIVE_SKILL_EFFECT_VALUE_UP:
				{
					break;
				}
				case PASSIVE_SKILL_KEEP_TIME_UP:
				{
					break;
				}
				case PASSIVE_REQUIRE_EP_DOWN:
				{
					break;
				}
				case PASSIVE_CHANGE_APPLY_RANGE:
				{
					break;
				}
				case PASSIVE_APPLY_AREA_SIZE_UP:
				{
					break;
				}
				case PASSIVE_USE_RANGE_UP:
				{
					break;
				}
				case PASSIVE_MASTERY:
				{
					break;
				}
				case PASSIVE_AIR_MASTERY:
				{
					break;
				}
				//Next Case
				}
			}
		}
	}
}
//----------------------------------------
//	Update the hot bar
//----------------------------------------
void WorldSession::SendUpdateQuickSlots(Packet& packet)
{
	sUG_QUICK_SLOT_UPDATE_REQ *req = (sUG_QUICK_SLOT_UPDATE_REQ*)packet.GetPacketBuffer();
	sGU_QUICK_SLOT_UPDATE_RES res;

	sLog.outDebug("Request interact with slot: slotid: %u, pos: %u, type: %u, place: %u, id: %d", req->bySlotID, req->byPos, req->byType, req->byPlace, req->tblidx);
	res.wPacketSize = sizeof(sGU_QUICK_SLOT_UPDATE_RES) - 2;
	res.wOpCode = GU_QUICK_SLOT_UPDATE_RES;
	res.wResultCode = GAME_SUCCESS;

	//_player->skillManager.UpdateSlot(req->bySlotID, req->tblidx, req->byType);
	_player->AddQuickSlot(req->tblidx, req->bySlotID, req->byType);

	res.byPlace = req->byPlace;
	res.byPos = req->byPos;
	res.bySlotID = req->bySlotID;
	res.byType = req->byType;
	res.tblidx = req->tblidx;
	SendPacket((char*)&res, sizeof(sGU_QUICK_SLOT_UPDATE_RES));
	//sDB.UpdateQuickSlots(res.tblidx, res.bySlotID, _player->charid);
}
//----------------------------------------
//	update our hot bar again
//----------------------------------------
void WorldSession::SendRemoveQuickSlots(Packet& packet)
{
	sUG_QUICK_SLOT_DEL_REQ * req = (sUG_QUICK_SLOT_DEL_REQ*)packet.GetPacketBuffer();
	//sGU_QUICK_SLOT_DEL_NFY res;
	//res.wPacketSize = sizeof(sGU_QUICK_SLOT_DEL_NFY) - 2;
	//res.bySlotID = req->bySlotID;
	//res.wOpCode = GU_QUICK_SLOT_DEL_NFY;
	//SendPacket((char*)&res, sizeof(sGU_QUICK_SLOT_DEL_NFY));

	//update data base
	//_player->skillManager.UpdateSlot(req->bySlotID, INVALID_TBLIDX, INVALID_BYTE);
	_player->DeleteQuickSlot(req->bySlotID);
	//sDB.UpdateQuickSlots(0, req->bySlotID, _player->charid);
}
//----------------------------------------
//	Send the social action to near player
//----------------------------------------
void WorldSession::SendSocialSkill(Packet& packet)
{
	sUG_SOCIAL_ACTION * req = (sUG_SOCIAL_ACTION*)packet.GetPacketBuffer();
	sGU_SOCIAL_ACTION res;

	res.hSubject = _player->GetHandle();
	res.socialActionId = req->socialActionId;
	res.wOpCode = GU_SOCIAL_ACTION;
	res.wPacketSize = sizeof(sGU_SOCIAL_ACTION) - 2;

	SendPacket((char*)&res, sizeof(sGU_SOCIAL_ACTION));
	_player->SendToPlayerList((char*)&res, sizeof(sGU_SOCIAL_ACTION));
}
//----------------------------------------
//	Learn a new skill
//----------------------------------------
void WorldSession::LearnMestrySkill(TBLIDX skillID)
{
	int bySkillCount = _player->skillManager.getSkillsCount();
	for (int i = 0; i < bySkillCount; i++)
	{
		int skillID = _player->skillManager.getSkillsInfos()[i].tblidx;
		SendUpdateSkillPassiveAtributeByID(skillID, true);
	}
	/*sql::ResultSet* result = sDB.executes("DELETE FROM `skills` WHERE `owner_id` = '%d';", _player->charid);
	if (result != NULL)
		delete result;

	//Delet All Skills
	sGU_SKILL_INIT_RES SkillReset;
	SkillReset.wOpCode = GU_SKILL_INIT_RES;
	SkillReset.wPacketSize = sizeof(sGU_SKILL_INIT_RES) - 2;
	SkillReset.wResultCode = GAME_SUCCESS;
	SendPacket((char*)&SkillReset, sizeof(sGU_SKILL_INIT_RES));

	sGU_SKILL_INIT_NFY skill;
	skill.wOpCode = GU_SKILL_INIT_NFY;
	skill.wPacketSize = sizeof(sGU_SKILL_INIT_NFY) - 2;
	skill.wResultCode = GAME_SUCCESS;
	SendPacket((char*)&skill, sizeof(sGU_SKILL_INIT_NFY));

	//Update Char SP
	sGU_UPDATE_CHAR_SP sp;
	sp.wOpCode = GU_UPDATE_CHAR_SP;
	sp.wPacketSize = sizeof(sGU_UPDATE_CHAR_SP) - 2;
	sp.dwSpPoint = _player->GetPcProfile()->byLevel;
	_player->GetPcProfile()->dwSpPoint = sp.dwSpPoint;
	SendPacket((char*)&sp, sizeof(sGU_UPDATE_CHAR_SP));

	sDB.UpdateSPPoint(_player->GetPcProfile()->dwSpPoint, _player->charid);*/
	// Learn BASE SKILL
	NewbieTable* pNewBieTable = sTBM.GetNewbieTable();
	sNEWBIE_TBLDAT* pNewbieTbldat = reinterpret_cast<sNEWBIE_TBLDAT*>(pNewBieTable->GetNewbieTbldat(_player->GetAttributesManager()->PlayerRaceID, _player->GetAttributesManager()->PlayerClassID));
	for (int i = 0; i < 7; i++)
	{
		if (pNewbieTbldat->aSkillTblidx[i] != -1)
		{
			//LearnSkill(pNewbieTbldat->aSkillTblidx[i]);
			sGU_SKILL_LEARN_RES res;
			res.wOpCode = GU_SKILL_LEARN_RES;
			res.wPacketSize = sizeof(sGU_SKILL_LEARN_RES) - 2;
			res.wResultCode = GAME_SUCCESS;

			sGU_SKILL_LEARNED_NFY nfy;
			nfy.bySlot = i + 1;//Need set frist skill to 0 when Reset skills;
			nfy.skillId = pNewbieTbldat->aSkillTblidx[i];
			nfy.wOpCode = GU_SKILL_LEARNED_NFY;
			nfy.wPacketSize = sizeof(sGU_SKILL_LEARNED_NFY) - 2;
			nfy.wResultCode = GAME_SUCCESS;

			SendPacket((char*)&res, sizeof(sGU_SKILL_LEARN_RES));
			SendPacket((char*)&nfy, sizeof(sGU_SKILL_LEARNED_NFY));
			sDB.LearnSkill(pNewbieTbldat->aSkillTblidx[i], _player->GetCharacterID(), nfy.bySlot);
			//Load skill for can use after that
			_player->skillManager.LoadSkill(_player->charid);
			SendAvatarSkillInfo();
			SendUpdateSkillPassiveAtributeByID(pNewbieTbldat->aSkillTblidx[i], false);
		}
	}

	//load skill for get correct rowcount 
	_player->skillManager.LoadSkill(_player->charid);
	int Slotid = NULL;
	if (_player->GetPcProfile()->dwSpPoint >= 1 || _player->GetPcProfile()->bIsGameMaster == true)
	{
		sGU_SKILL_LEARN_RES res;
		res.wOpCode = GU_SKILL_LEARN_RES;
		res.wPacketSize = sizeof(sGU_SKILL_LEARN_RES) - 2;
		res.wResultCode = GAME_SUCCESS;

		sGU_SKILL_LEARNED_NFY nfy;
		nfy.bySlot = _player->skillManager.getSkillsCount() + 1;//Need set frist skill to 0 when Reset skills;
		nfy.skillId = skillID;
		nfy.wOpCode = GU_SKILL_LEARNED_NFY;
		nfy.wPacketSize = sizeof(sGU_SKILL_LEARNED_NFY) - 2;
		nfy.wResultCode = GAME_SUCCESS;

		if (_player->GetPcProfile()->dwSpPoint >= 1)
		{
			sGU_UPDATE_CHAR_SP spPoint;

			spPoint.wOpCode = GU_UPDATE_CHAR_SP;
			spPoint.wPacketSize = sizeof(sGU_UPDATE_CHAR_SP) - 2;
			spPoint.dwSpPoint = _player->GetPcProfile()->dwSpPoint - 1;
			_player->GetPcProfile()->dwSpPoint = spPoint.dwSpPoint;
			sDB.UpdateSPPoint(_player->GetPcProfile()->dwSpPoint, _player->charid);
			SendPacket((char*)&spPoint, sizeof(sGU_UPDATE_CHAR_SP));
		}

		SendPacket((char*)&res, sizeof(sGU_SKILL_LEARN_RES));
		SendPacket((char*)&nfy, sizeof(sGU_SKILL_LEARNED_NFY));
		sDB.LearnSkill(skillID, _player->GetCharacterID(), nfy.bySlot);
		//Load skill for can use after that
		_player->skillManager.LoadSkill(_player->charid);
		SendAvatarSkillInfo();

		SendUpdateSkillPassiveAtributeByID(skillID, false);
	}
	else
	{
		sGU_SKILL_LEARN_RES res;
		res.wOpCode = GU_SKILL_LEARN_RES;
		res.wPacketSize = sizeof(sGU_SKILL_LEARN_RES) - 2;
		res.wResultCode = GAME_SKILL_NOT_ENOUGH_SP_POINT;
		SendPacket((char*)&res, sizeof(sGU_SKILL_LEARN_RES));
	}
}
void WorldSession::RewardSkill(TBLIDX skillID)
{
	//load skill for get correct rowcount 
	_player->skillManager.LoadSkill(_player->charid);
	int Slotid = NULL;
	
		SendUpdateSkillPassiveAtributeByID(skillID, true);
		sGU_SKILL_LEARN_RES res;
		res.wOpCode = GU_SKILL_LEARN_RES;
		res.wPacketSize = sizeof(sGU_SKILL_LEARN_RES) - 2;
		res.wResultCode = GAME_SUCCESS;

		sGU_SKILL_LEARNED_NFY nfy;
		nfy.bySlot = _player->skillManager.getSkillsCount() + 1;//Need set frist skill to 0 when Reset skills;
		nfy.skillId = skillID;
		nfy.wOpCode = GU_SKILL_LEARNED_NFY;
		nfy.wPacketSize = sizeof(sGU_SKILL_LEARNED_NFY) - 2;
		nfy.wResultCode = GAME_SUCCESS;		

		SendPacket((char*)&res, sizeof(sGU_SKILL_LEARN_RES));
		SendPacket((char*)&nfy, sizeof(sGU_SKILL_LEARNED_NFY));
		sDB.LearnSkill(skillID, _player->GetCharacterID(), nfy.bySlot);
		//Load skill for can use after that
		_player->skillManager.LoadSkill(_player->charid);
		SendAvatarSkillInfo();

		SendUpdateSkillPassiveAtributeByID(skillID, false);	
}
void WorldSession::LearnSkill(TBLIDX skillID)
{
	//load skill for get correct rowcount 
	_player->skillManager.LoadSkill(_player->charid);	
	int Slotid = NULL;	
	if (_player->GetPcProfile()->dwSpPoint >= 1 || _player->GetPcProfile()->bIsGameMaster == true)
	{
		SendUpdateSkillPassiveAtributeByID(skillID, true);
		sGU_SKILL_LEARN_RES res;
		res.wOpCode = GU_SKILL_LEARN_RES;
		res.wPacketSize = sizeof(sGU_SKILL_LEARN_RES) - 2;
		res.wResultCode = GAME_SUCCESS;		

		sGU_SKILL_LEARNED_NFY nfy;
		nfy.bySlot = _player->skillManager.getSkillsCount() + 1;//Need set frist skill to 0 when Reset skills;
		nfy.skillId = skillID;
		nfy.wOpCode = GU_SKILL_LEARNED_NFY;
		nfy.wPacketSize = sizeof(sGU_SKILL_LEARNED_NFY) - 2;
		nfy.wResultCode = GAME_SUCCESS;			

		if (_player->GetPcProfile()->dwSpPoint >= 1)
		{
			sGU_UPDATE_CHAR_SP spPoint;

			spPoint.wOpCode = GU_UPDATE_CHAR_SP;
			spPoint.wPacketSize = sizeof(sGU_UPDATE_CHAR_SP) - 2;
			spPoint.dwSpPoint = _player->GetPcProfile()->dwSpPoint - 1;
			_player->GetPcProfile()->dwSpPoint = spPoint.dwSpPoint;
			sDB.UpdateSPPoint(_player->GetPcProfile()->dwSpPoint, _player->charid);
			SendPacket((char*)&spPoint, sizeof(sGU_UPDATE_CHAR_SP));
		}
		
		SendPacket((char*)&res, sizeof(sGU_SKILL_LEARN_RES));
		SendPacket((char*)&nfy, sizeof(sGU_SKILL_LEARNED_NFY));		
		sDB.LearnSkill(skillID, _player->GetCharacterID(), nfy.bySlot);
		//Load skill for can use after that
		_player->skillManager.LoadSkill(_player->charid);
		SendAvatarSkillInfo();
	
		SendUpdateSkillPassiveAtributeByID(skillID, false);
	}
	else
	{
		sGU_SKILL_LEARN_RES res;
		res.wOpCode = GU_SKILL_LEARN_RES;
		res.wPacketSize = sizeof(sGU_SKILL_LEARN_RES) - 2;
		res.wResultCode = GAME_SKILL_NOT_ENOUGH_SP_POINT;
		SendPacket((char*)&res, sizeof(sGU_SKILL_LEARN_RES));
	}
}
void WorldSession::UpgradeSkill(Packet & packet)
{
	sUG_SKILL_UPGRADE_REQ *req = (sUG_SKILL_UPGRADE_REQ*)packet.GetPacketBuffer();

	int skillID = _player->skillManager.getIdAtPos(req->bySlotIndex);
	//sLog.outError("UG_SKILL_UPGRADE_REQ %d ", skillID);
	sSKILL_TBLDAT * skillDataOriginal = reinterpret_cast<sSKILL_TBLDAT*>(sTBM.GetSkillTable()->FindData(skillID));
	//sLog.outError("UG_SKILL_UPGRADE_REQ Slot: %d Skill: %d SkillNext: %d ", req->bySlotIndex, skillID, skillDataOriginal->dwNextSkillTblidx);
	if (_player->GetPcProfile()->dwSpPoint <= 0)
	{
		sGU_SKILL_LEARN_RES res;
		res.wOpCode = GU_SKILL_LEARN_RES;
		res.wPacketSize = sizeof(sGU_SKILL_LEARN_RES) - 2;
		res.wResultCode = GAME_SKILL_NOT_ENOUGH_SP_POINT;
		SendPacket((char*)&res, sizeof(sGU_SKILL_LEARN_RES));
	}
	else
	{
		SendUpdateSkillPassiveAtributeByID(skillID, true);
		sGU_SKILL_UPGRADE_RES SkillUpgrade;

		SkillUpgrade.wOpCode = GU_SKILL_UPGRADE_RES;
		SkillUpgrade.wPacketSize = sizeof(sGU_SKILL_UPGRADE_RES) - 2;

		SkillUpgrade.skillId = skillDataOriginal->dwNextSkillTblidx;
		SkillUpgrade.bySlot = req->bySlotIndex;
		SkillUpgrade.wResultCode = GAME_SUCCESS;
		sDB.UpdateSkill(SkillUpgrade.skillId, _player->charid, skillID);
		//Load skill for can use after that
		_player->skillManager.LoadSkill(_player->charid);		
		SendUpdateSkillPassiveAtributeByID(SkillUpgrade.skillId, false);
		SendPacket((char*)&SkillUpgrade, sizeof(sGU_SKILL_UPGRADE_RES));

		sGU_UPDATE_CHAR_SP spPoint;

		spPoint.dwSpPoint = _player->GetPcProfile()->dwSpPoint - 1;
		_player->GetPcProfile()->dwSpPoint = spPoint.dwSpPoint;
		spPoint.wOpCode = GU_UPDATE_CHAR_SP;
		spPoint.wPacketSize = sizeof(sGU_UPDATE_CHAR_SP) - 2;
		SendPacket((char*)&spPoint, sizeof(sGU_UPDATE_CHAR_SP));
		sDB.UpdateSPPoint(_player->GetPcProfile()->dwSpPoint, _player->charid);
	}
}

void WorldSession::ResetSkill(Packet & packet)
{
	int bySkillCount = _player->skillManager.getSkillsCount();
	for (int i = 0; i < bySkillCount; i++)
	{
		int skillID = _player->skillManager.getSkillsInfos()[i].tblidx;
		SendUpdateSkillPassiveAtributeByID(skillID, true);
	}	
	sql::ResultSet* result = sDB.executes("DELETE FROM `skills` WHERE `owner_id` = '%d';", _player->charid);
	if (result != NULL)
		delete result;

	sUG_SKILL_INIT_REQ *req = (sUG_SKILL_INIT_REQ*)packet.GetPacketBuffer();
	//Delet All Skills
	sGU_SKILL_INIT_RES SkillReset;
	SkillReset.wOpCode = GU_SKILL_INIT_RES;
	SkillReset.wPacketSize = sizeof(sGU_SKILL_INIT_RES) - 2;
	SkillReset.wResultCode = GAME_SUCCESS;
	SendPacket((char*)&SkillReset, sizeof(sGU_SKILL_INIT_RES));

	sGU_SKILL_INIT_NFY skill;
	skill.wOpCode = GU_SKILL_INIT_NFY;
	skill.wPacketSize = sizeof(sGU_SKILL_INIT_NFY) - 2;
	skill.wResultCode = GAME_SUCCESS;
	SendPacket((char*)&skill, sizeof(sGU_SKILL_INIT_NFY));

	//Update Char SP
	sGU_UPDATE_CHAR_SP sp;
	sp.wOpCode = GU_UPDATE_CHAR_SP;
	sp.wPacketSize = sizeof(sGU_UPDATE_CHAR_SP) - 2;
	sp.dwSpPoint = _player->GetPcProfile()->byLevel;
	_player->GetPcProfile()->dwSpPoint = sp.dwSpPoint;
	SendPacket((char*)&sp, sizeof(sGU_UPDATE_CHAR_SP));

	sDB.UpdateSPPoint(_player->GetPcProfile()->dwSpPoint, _player->charid);
	// Learn BASE SKILL
	NewbieTable* pNewBieTable = sTBM.GetNewbieTable();
	sNEWBIE_TBLDAT* pNewbieTbldat = reinterpret_cast<sNEWBIE_TBLDAT*>(pNewBieTable->GetNewbieTbldat(_player->GetAttributesManager()->PlayerRaceID, _player->GetAttributesManager()->PlayerClassID));
	for (int i = 0; i < 7; i++)
	{
		if (pNewbieTbldat->aSkillTblidx[i] != -1)
		{
			//LearnSkill(pNewbieTbldat->aSkillTblidx[i]);
			sGU_SKILL_LEARN_RES res;
			res.wOpCode = GU_SKILL_LEARN_RES;
			res.wPacketSize = sizeof(sGU_SKILL_LEARN_RES) - 2;
			res.wResultCode = GAME_SUCCESS;

			sGU_SKILL_LEARNED_NFY nfy;
			nfy.bySlot = i + 1;//Need set frist skill to 0 when Reset skills;
			nfy.skillId = pNewbieTbldat->aSkillTblidx[i];
			nfy.wOpCode = GU_SKILL_LEARNED_NFY;
			nfy.wPacketSize = sizeof(sGU_SKILL_LEARNED_NFY) - 2;
			nfy.wResultCode = GAME_SUCCESS;
			
			SendPacket((char*)&res, sizeof(sGU_SKILL_LEARN_RES));
			SendPacket((char*)&nfy, sizeof(sGU_SKILL_LEARNED_NFY));
			sDB.LearnSkill(pNewbieTbldat->aSkillTblidx[i], _player->GetCharacterID(), nfy.bySlot);
			//Load skill for can use after that
			_player->skillManager.LoadSkill(_player->charid);
			SendAvatarSkillInfo();
			SendUpdateSkillPassiveAtributeByID(pNewbieTbldat->aSkillTblidx[i], false);
		}
	}
}


void WorldSession::LearnHtb(TBLIDX htbIdx, BYTE slot)
{
	sGU_HTB_LEARN_RES res;
	res.wOpCode = GU_HTB_LEARN_RES;
	res.wPacketSize = sizeof(sGU_HTB_LEARN_RES) - 2;
	res.wResultCode = GAME_SUCCESS;
	res.skillId = htbIdx;
	res.bySkillSlot = slot;// _player->skillManager.getSkillsCount() + 1;
	res.unknown = 0;
	_player->HTBID = res.skillId;
	SendPacket((char*)&res, sizeof(sGU_HTB_LEARN_RES));

	sDB.addhtb(htbIdx, _player->GetCharacterID(), slot);
}