#include <Game\Object\Manager\Fight.h>
#include <TableAll.h>
#include <Game\Object\Player.h>
#include <Game\Object\Mob.h>
#include <World.h>

//----------------------------------------
//	Constructor
//----------------------------------------
FightManager::FightManager()
{

}
//----------------------------------------
//	Destructor
//----------------------------------------
FightManager::~FightManager()
{

}
//----------------------------------------
//	Can we damage ou target ?
//	Need to check if the flag is set to attackable etc
//----------------------------------------
bool FightManager::canTakeDamage(Object& Attacker, Object& Target)
{
	if (Target.GetTypeId() == eOBJTYPE::OBJTYPE_MOB || Target.GetTypeId() == OBJTYPE_PC)
	{
		
	}
	return false;
}
//----------------------------------------
//	Get the amount of level between us and mob
//----------------------------------------
int FightManager::GetLevelDiff()
{
	int levelDiff = plr->GetPcProfile()->byLevel - mob->GetMobData().Level;

	return levelDiff;
}
//----------------------------------------
//	Get the amount of physical random damage
//----------------------------------------
float FightManager::GetRandomDamagePercent(float damage, int min, int max)
{
	int resultRand = min + rand() % (max + 1 - min);
	float damageRand = (static_cast<float>(resultRand) * damage) / 100;
	float damageTotal = damage + damageRand;
	sLog.outBasic("damage %f resultRand %d damageRand %f damageTotal %f min %d max %d", damage, resultRand, damageRand, damageTotal, min, max);
	return damageTotal;
}
//----------------------------------------
//	Get the amount of physical damage
//----------------------------------------
float FightManager::CalculePhysicalDamage(float attackerOffence, DWORD attackerLevel, float targetDefence)
{
	float damage = 0;
	sFORMULA_TBLDAT* formula = (sFORMULA_TBLDAT*)sTBM.GetFormulaTable()->FindData(3100);
	if (formula)
	{
		sLog.outBasic("1 physical attack %f level %d", attackerOffence, attackerLevel);
		damage = (targetDefence + attackerLevel * formula->afRate[0]);
		damage = (1 - (targetDefence / damage));
		damage = attackerOffence * damage;
		sLog.outBasic("damage %f mob defense %f", damage, targetDefence);
		float percent = damage * 1 / attackerOffence;
		float lastDamage = damage * (1 + percent);
		sLog.outBasic("percent %f last damage %f", percent, lastDamage);
		//return damage;
	}
	damage = GetRandomDamagePercent(damage, -10, 10);
	return damage;
}
//----------------------------------------
//	Get the amount of energy damage
//----------------------------------------
float FightManager::CalculeEnergyDamage(float attackerOffence, DWORD attackerLevel, float targetDefence)
{
	float damage = 0;
	sFORMULA_TBLDAT* formula = (sFORMULA_TBLDAT*)sTBM.GetFormulaTable()->FindData(3300);
	if (formula)
	{
		sLog.outBasic("1 energy attack %f level %d", attackerOffence, attackerLevel);
		damage = (targetDefence + attackerLevel * formula->afRate[0]);
		damage = (1 - (targetDefence / damage));
		damage = attackerOffence * damage;
		sLog.outBasic("damage %f mob defense %f", damage, targetDefence);
		float percent = damage * 1 / attackerOffence;
		float lastDamage = damage * (1 + percent);
		sLog.outBasic("percent %f last damage %f", percent, lastDamage);
		//return damage;
	}
	damage = GetRandomDamagePercent(damage, -10, 10);
	return damage;
}
//----------------------------------------
//	Get the percent of attack success
//----------------------------------------
int FightManager::CalculeAttackSuccess(int attAttackRate, int defDodgeRate, BYTE attLevel, BYTE defLevel)
{
	// = fRate1 * ( 공격자 Last_Attack_Rate / ( 공격자 Last_Attack_Rate + 방어자 Last_Dodge_Rate) ) * ( ( 공격자 Level + 1 ) / ( 공격자 Level + 방어자 Level ) ) * 100   (단, 최대 99%)
	float attackRate = static_cast<float>(attAttackRate);
	float dodgeRate = static_cast<float>(defDodgeRate);
	float attackLevel = static_cast<float>(attLevel);
	float deffenLevel = static_cast<float>(defLevel);
	float attackSuccess = 0;
	sFORMULA_TBLDAT* formula = (sFORMULA_TBLDAT*)sTBM.GetFormulaTable()->FindData(3700);
	if (formula)
	{
		attackSuccess = formula->afRate[0] * (attackRate / (attackRate + dodgeRate)) * ((attackLevel + 1) / (attackLevel + deffenLevel)) * 100;
		sLog.outBasic("attack Success %f", attackSuccess);
		sLog.outBasic("attackRate %f dodgeRate %f attLevel %f defLevel %f rate1 %f", attackRate, dodgeRate, attackLevel, deffenLevel, formula->afRate[0]);

	}
	if (attackSuccess > 99.0f)
	{
		attackSuccess = 99.0f;
	}
	return static_cast<int>(attackSuccess);
}
//----------------------------------------
//	Get the percent of critical damage
//----------------------------------------
DWORD FightManager::CalculePhysicalCriticalDamage(float damage, float PhysicalCriticalRange)
{
	float percentDamage = PhysicalCriticalRange * damage / 100.0f;
	float newDamage = damage + percentDamage;
	sLog.outBasic("Percent damage added %f damage with percent %f newdamage %f", PhysicalCriticalRange, percentDamage, newDamage);
	return newDamage;
}
DWORD FightManager::CalculeEnergyCriticalDamage(float damage, float energyCriticalRange)
{
	float percentDamage = energyCriticalRange * damage / 100.0f;
	float newDamage = damage + percentDamage;
	sLog.outBasic("Percent damage added %f damage with percent %f newdamage %f", energyCriticalRange, percentDamage, newDamage);
	return newDamage;
}
//----------------------------------------
//	Get the percent of critical attack success
//----------------------------------------
int FightManager::CalculePhysicalCriticalSuccess(WORD attPhysicalCriticalRate, WORD deffPhysicalCriticalDefenceRate)
{
	//fRate1 * ( 공격자 Character(Monster)_Physical_Critical_Rate / ( 공격자 Character(Monster)_Physical_Critical_Rate + 방어자 Character(Monster)_Physical_Critical_Defence_Rate * fRate2 ) )  최대 90
	//plr->GetPcProfile()->avatarAttribute.wLastPhysicalCriticalRate - (mob->GetMobData().);
	int physicalCriticalSuccess = 0;
	sFORMULA_TBLDAT* formula = (sFORMULA_TBLDAT*)sTBM.GetFormulaTable()->FindData(4400);
	if (formula)
	{
		sLog.outBasic("physicalCriticalSuccess tblidx %d attPhysicalCriticalRate %d deffPhysicalCriticalDefenceRate %d", formula->tblidx, attPhysicalCriticalRate, deffPhysicalCriticalDefenceRate);
		physicalCriticalSuccess = formula->afRate[2] * (attPhysicalCriticalRate / (attPhysicalCriticalRate + deffPhysicalCriticalDefenceRate * formula->afRate[3]));
		sLog.outBasic("physicalCriticalSuccess total %d rate3 %f rate4 %f", physicalCriticalSuccess, formula->afRate[2], formula->afRate[3]);
	}
	if (physicalCriticalSuccess > 90)
	{
		physicalCriticalSuccess = 90;
	}
	return physicalCriticalSuccess;

}
//----------------------------------------
//	Get the percent of critical attack success
//----------------------------------------
int FightManager::CalculeEnergyCriticalSuccess(WORD attEnergyCriticalRate, WORD deffEnergyCriticalDefenceRate)
{
	//fRate1 * ( 공격자 Character(Monster)_Physical_Critical_Rate / ( 공격자 Character(Monster)_Physical_Critical_Rate + 방어자 Character(Monster)_Physical_Critical_Defence_Rate * fRate2 ) )  최대 90
	int energyCriticalSuccess = 0;
	sFORMULA_TBLDAT* formula = (sFORMULA_TBLDAT*)sTBM.GetFormulaTable()->FindData(4500);
	if (formula)
	{
		sLog.outBasic("energyCriticalSuccess tblidx %d attEnergyCriticalRate %d deffEnergyCriticalDefenceRate %d", formula->tblidx, attEnergyCriticalRate, deffEnergyCriticalDefenceRate);
		energyCriticalSuccess = formula->afRate[0] * (attEnergyCriticalRate / (attEnergyCriticalRate + deffEnergyCriticalDefenceRate * formula->afRate[1]));
		sLog.outBasic("energyCriticalSuccess total %d rate1 %f rate2 %f", energyCriticalSuccess, formula->afRate[0], formula->afRate[1]);
	}
	if (energyCriticalSuccess > 90)
	{
		energyCriticalSuccess = 90;
	}
	return energyCriticalSuccess;
}
//----------------------------------------
//	Get amount of damage to do
//	@param id - boolean to say if we are caster or cac
//----------------------------------------
void FightManager::GetPlayerDamage(bool caster, eOBJTYPE ObjectTypeId)
{
	attackValue = 0;
	if (caster == false)
	{		
		if (ObjectTypeId == OBJTYPE_MOB)
		{		
			float damage = CalculePhysicalDamage(plr->GetPcProfile()->avatarAttribute.wLastPhysicalOffence, plr->GetPcProfile()->byLevel,
				mob->GetMobData().Basic_physical_defence);
			attackValue = damage;
		}
		if (ObjectTypeId == OBJTYPE_PC)
		{
			/*float attack = plr->GetPcProfile()->avatarAttribute.wLastPhysicalOffence;
			int TotalAttack = attack + plrTarget->GetPcProfile()->avatarAttribute.wLastPhysicalDefence;
			float FinalPercent = attack * 100 / TotalAttack;*/
			float damage = CalculePhysicalDamage(plr->GetPcProfile()->avatarAttribute.wLastPhysicalOffence,
				plr->GetPcProfile()->byLevel,
				plrTarget->GetPcProfile()->avatarAttribute.wLastPhysicalDefence);
			attackValue = damage;//attack * FinalPercent / 100;
		}
	}
	else
	{			
		if (ObjectTypeId == OBJTYPE_MOB)
		{
			float damage = CalculeEnergyDamage(plr->GetPcProfile()->avatarAttribute.wLastEnergyOffence, plr->GetPcProfile()->byLevel,
				mob->GetMobData().Basic_energy_defence);
			attackValue = damage;
		}
		if (ObjectTypeId == OBJTYPE_PC)
		{
			/*float attack = plr->GetPcProfile()->avatarAttribute.wLastEnergyOffence;
			int TotalAttack = attack + plrTarget->GetPcProfile()->avatarAttribute.wLastEnergyDefence;
			float FinalPercent = attack * 100 / TotalAttack;*/
			float damage = CalculeEnergyDamage(plr->GetPcProfile()->avatarAttribute.wLastEnergyOffence, plr->GetPcProfile()->byLevel,
				plrTarget->GetPcProfile()->avatarAttribute.wLastEnergyDefence);
			attackValue = damage;// attack* FinalPercent / 100;
		}
	}
}
//----------------------------------------
//	Get if our attack will be critical
//	@param id - boolean to say if we are caster or cac
//----------------------------------------
void FightManager::GetPlayerCriticAttack(bool caster, eOBJTYPE ObjectTypeId)
{
	int CritChance = 0; 
	int num = rand() % 100;
	if (caster == false)
	{		
		if (ObjectTypeId == OBJTYPE_MOB)
		{
			CritChance = CalculePhysicalCriticalSuccess(plr->GetPcProfile()->avatarAttribute.wLastPhysicalCriticalRate, mob->GetMobData().physicalCriticalDefenseRate);
				//plr->GetPcProfile()->avatarAttribute.wLastPhysicalCriticalRate - (mob->GetMobData().Block_rate / 100);
		}
		if (ObjectTypeId == OBJTYPE_PC)
		{
			CritChance = CalculePhysicalCriticalSuccess(plr->GetPcProfile()->avatarAttribute.wLastPhysicalCriticalRate, plrTarget->GetPcProfile()->avatarAttribute.physicalCriticalDefenceRate);
				//plr->GetPcProfile()->avatarAttribute.wLastPhysicalCriticalRate - (plrTarget->GetPcProfile()->avatarAttribute.wLastBlockRate / 100);
		}
	}
	else
	{		
		if (ObjectTypeId == OBJTYPE_MOB)
		{
			CritChance = CalculeEnergyCriticalSuccess(plr->GetPcProfile()->avatarAttribute.wLastEnergyCriticalRate, mob->GetMobData().energyCriticalDefenseRate); 
			//plr->GetPcProfile()->avatarAttribute.wLastEnergyCriticalRate - (mob->GetMobData().Block_rate / 100);
		}
		if (ObjectTypeId == OBJTYPE_PC)
		{
			CritChance = CalculeEnergyCriticalSuccess(plr->GetPcProfile()->avatarAttribute.wLastEnergyCriticalRate, plrTarget->GetPcProfile()->avatarAttribute.energyCriticalDefenceRate); 
			//plr->GetPcProfile()->avatarAttribute.wLastEnergyCriticalRate - (plrTarget->GetPcProfile()->avatarAttribute.wLastBlockRate / 100);
		}
	}
	//(CritChance > 0) ? CritChance *= 1 : CritChance *= -1;
	if (num <= CritChance && CritChance > 0)
	{
		attackResult = eBATTLE_ATTACK_RESULT::BATTLE_ATTACK_RESULT_CRITICAL_HIT;
		//attackValue *= 2;
		if (caster == false)
		{
			attackValue = CalculePhysicalCriticalDamage(attackValue, plr->GetPcProfile()->avatarAttribute.fLastPhysicalCriticalRange);
		}
		else
		{
			attackValue = CalculeEnergyCriticalDamage(attackValue, plr->GetPcProfile()->avatarAttribute.fLastEnergyCriticalRange);
		}
	}
	//std::cout << "CritChance = " << CritChance << std::endl;
}
//----------------------------------------
//	Get the player hit change
//----------------------------------------
void FightManager::GetPlayerHitChance(eOBJTYPE ObjectTypeId)
{
	srand(time(NULL));

	if (ObjectTypeId == OBJTYPE_MOB)
	{
		int HitRate = plr->GetPcProfile()->avatarAttribute.wLastAttackRate;
		int DodgeRate = mob->GetMobData().Dodge_rate;
		//float TotalHitPercent = HitRate + DodgeRate;
		float TotalHitRatePercent = CalculeAttackSuccess(HitRate, DodgeRate, plr->GetPcProfile()->byLevel, mob->GetMobData().Level);//HitRate * 100 / TotalHitPercent;
		int RandomHit = rand() % 100;
		if (RandomHit <= TotalHitRatePercent && TotalHitRatePercent > 0)
		{
			attackResult = eBATTLE_ATTACK_RESULT::BATTLE_ATTACK_RESULT_HIT;
		}
	}
	if (ObjectTypeId == OBJTYPE_PC)
	{
		int HitRate = plr->GetPcProfile()->avatarAttribute.wLastAttackRate;
		int DodgeRate = plrTarget->GetPcProfile()->avatarAttribute.wLastDodgeRate;
		//float TotalHitPercent = HitRate + DodgeRate;
		float TotalHitRatePercent = CalculeAttackSuccess(HitRate, DodgeRate, plr->GetPcProfile()->byLevel, plrTarget->GetPcProfile()->byLevel);// HitRate * 100 / TotalHitPercent;
		int RandomHit = rand() % 100;
		if (RandomHit <= TotalHitRatePercent && TotalHitRatePercent > 0)
		{
			attackResult = eBATTLE_ATTACK_RESULT::BATTLE_ATTACK_RESULT_HIT;
		}
	}	
}
//----------------------------------------
//	Perform an auto attack from an object
//	@param id - Attacker - Target as Object
//----------------------------------------
bool FightManager::HandleDamage(Object& Attacker, Object& Target)
{
	mutexFight.lock();
	if (Target.GetIsDead() == true)
	{
		mutexFight.unlock();
		return false;
	}
	mob = reinterpret_cast<Mob*>(&Target); //May Mob Target info
	plr = reinterpret_cast<Player*>(&Attacker);  //MyPlayer Info
	plrTarget = reinterpret_cast<Player*>(&Target); //My Target Infos
	TargetInfo = reinterpret_cast<Object*>(&Target);	//Object Info
	if (Target.GetTypeId() == OBJTYPE_PC)
	{
		plr = reinterpret_cast<Player*>(&Attacker);
		plrTarget = reinterpret_cast<Player*>(&Target);
		float distance = NtlGetDistance(plr->GetVectorPosition().x, plr->GetVectorPosition().z, plrTarget->GetVectorPosition().x, plrTarget->GetVectorPosition().z);
		if (distance < plr->GetPcProfile()->avatarAttribute.fLastAttackRange + 2 && plrTarget->GetAttributesManager()->IsinPVP == true ||
			distance < plr->GetPcProfile()->avatarAttribute.fLastAttackRange + 2 && plrTarget->GetAttributesManager()->PlayerInFreeBatle == true && plr->GetAttributesManager()->PlayerInFreeBatle == true)
		{
			//printf("distncia do player %f \n", distance);
			/// can now continue attack verification for player
			HandlePlrFight();
			attackCount++;
		}
	
	}
	if (Target.GetTypeId() == OBJTYPE_MOB)
	{
		plr = reinterpret_cast<Player*>(&Attacker);
		mob = reinterpret_cast<Mob*>(&Target);
		float distance = NtlGetDistance(plr->GetVectorPosition().x, plr->GetVectorPosition().z, mob->GetMobData().curPos.x, mob->GetMobData().curPos.z);
		if (distance < plr->GetPcProfile()->avatarAttribute.fLastAttackRange + 2)
		{
			/// can now continue attack verification for player
			HandlePlrFight();
			attackCount++;
		}
	}	
	mutexFight.unlock();
	return true;
}
//----------------------------------------
//	Handle an spin attack from a player
//----------------------------------------
bool FightManager::HandlePlrSpinAttack(Object* target, Player* player)
{
	plr = player;
	switch (target->GetTypeId())
	{
		case OBJTYPE_MOB:
		{
			Mob* MobInfo = static_cast<Mob*>(target);
			if (MobInfo != NULL)
			{
				plr->GetAttributesManager()->spinInfo.damage = CalculePhysicalDamage(
					plr->GetPcProfile()->avatarAttribute.wLastPhysicalOffence,
					plr->GetPcProfile()->byLevel,
					MobInfo->GetMobData().Basic_physical_defence);
				plr->GetAttributesManager()->spinInfo.damage = plr->CalculeSkillDamage(plr->GetAttributesManager()->spinInfo.bySkill_Effect_Type,
					plr->GetAttributesManager()->spinInfo.SkillValue, plr->GetAttributesManager()->spinInfo.damage);

					//printf("Player Attack MOB \n");
				if (MobInfo->attackers == 0)
				MobInfo->attackers = plr->GetHandle();
				MobInfo->TakeDamage(plr->GetAttributesManager()->spinInfo.damage);
				MobInfo->SetIsFighting(true);

				SendCharSpecialAttacNfy(MobInfo->GetHandle(), plr->GetAttributesManager()->spinInfo.skillId, plr->GetAttributesManager()->spinInfo.damage);

				if (MobInfo->GetIsDead() == true)
				{
					return true;
				}
				sLog.outDebug("-----OBJTYPE_MOB-----");
			}
			break;
		}
	}
	return false;
}
//----------------------------------------
//	Handle an attack from a player
//----------------------------------------
void FightManager::HandlePlrFight()
{
	if (attackCount > BATTLE_MAX_CHAIN_ATTACK_COUNT || attackCount <= 0)
		attackCount = BATTLE_CHAIN_ATTACK_START;
	//Type Atack
	bool isCaster = false;
	if (plr->GetMyClass() == ePC_CLASS::PC_CLASS_HUMAN_FIGHTER || 
		plr->GetMyClass() == ePC_CLASS::PC_CLASS_NAMEK_FIGHTER || 
		plr->GetMyClass() == ePC_CLASS::PC_CLASS_MIGHTY_MAJIN ||
		plr->GetMyClass() == ePC_CLASS::PC_CLASS_STREET_FIGHTER ||
		plr->GetMyClass() == ePC_CLASS::PC_CLASS_SWORD_MASTER ||
		plr->GetMyClass() == ePC_CLASS::PC_CLASS_DARK_WARRIOR ||
		plr->GetMyClass() == ePC_CLASS::PC_CLASS_SHADOW_KNIGHT ||
		plr->GetMyClass() == ePC_CLASS::PC_CLASS_ULTI_MA ||
		plr->GetMyClass() == ePC_CLASS::PC_CLASS_GRAND_MA)
		isCaster = false;
	else
		isCaster = true;

	sGU_CHAR_ACTION_ATTACK res;

	attackResult = eBATTLE_ATTACK_RESULT::BATTLE_ATTACK_RESULT_DODGE;
	guardType = eDBO_GUARD_TYPE::DBO_GUARD_TYPE_INVALID;
	attackValue = 0;
	reflectedDamage = 0;
	
	GetPlayerDamage(isCaster, TargetInfo->GetTypeId());
	GetPlayerHitChance(TargetInfo->GetTypeId());
	if (attackValue <= 0 || attackValue > 1000000000)
	{
		attackValue = 1;
	}
	if (attackResult != eBATTLE_ATTACK_RESULT::BATTLE_ATTACK_RESULT_DODGE)
	{
		GetPlayerCriticAttack(isCaster, TargetInfo->GetTypeId());
		if (attackResult == eBATTLE_ATTACK_RESULT::BATTLE_ATTACK_RESULT_BLOCK)
		{
			attackValue /= 2;
		}
	}
	else
		attackValue = 0;
	
	res.bChainAttack = true;
	res.byAttackResult = attackResult;
	res.byBlockedAction = -1;
	res.dwLpEpEventId = 700121;
	res.fReflectedDamage = reflectedDamage;
	res.byAttackSequence = attackCount;
	res.hSubject = plr->GetHandle();
	res.hTarget = mob->GetHandle();
	res.vShift = plr->GetVectorPosition();
	res.wAttackResultValue = attackValue;
	res.bRecoveredLP = false;
	res.wRecoveredLpValue = 0;
	res.bRecoveredEP = false;
	res.wRecoveredEpValue = 0;
	res.wOpCode = GU_CHAR_ACTION_ATTACK;
	res.wPacketSize = sizeof(sGU_CHAR_ACTION_ATTACK) - 2;		

	if (attackResult != eBATTLE_ATTACK_RESULT::BATTLE_ATTACK_RESULT_DODGE)
	{
		
		if (plrTarget->GetTypeId() == OBJTYPE_MOB)
		{
			//printf("Player Attack MOB \n");
			if (mob->attackers == 0)
			mob->attackers = plr->GetHandle();
			mob->TakeDamage(attackValue);
			mob->SetIsFighting(true);
		}
		if (TargetInfo->GetTypeId() == OBJTYPE_PC)
		{			
			//printf("Player Attack Player \n");
			if (mob->attackers == 0)
			mob->attackers = plrTarget->GetHandle();
			plrTarget->TakeDamage(attackValue);
		}		
	}

	plr->SendPacket((char*)&res, sizeof(sGU_CHAR_ACTION_ATTACK));
	plr->SendToPlayerList((char*)&res, sizeof(sGU_CHAR_ACTION_ATTACK));
}

void FightManager::SendCharSpecialAttacNfy(HOBJECT target, TBLIDX skillTblidx, DWORD damage)
{
	sGU_CHAR_SPECIAL_ATTACK_NFY nfy;
	memset(&nfy, 0, sizeof sGU_CHAR_SPECIAL_ATTACK_NFY);
	nfy.wOpCode = GU_CHAR_SPECIAL_ATTACK_NFY;
	nfy.wPacketSize = sizeof(sGU_CHAR_SPECIAL_ATTACK_NFY) - 2;
	nfy.hTarget = target;
	nfy.hSubject = plr->GetHandle();
	nfy.unknown = 0;
	nfy.unknown2 = 1;
	nfy.skillTblidx = skillTblidx;//510044;
	nfy.specialResult = 0;
	nfy.damage = damage;
	nfy.pos.x = dbo_move_float_to_pos(plr->GetVectorPosition().x);
	nfy.pos.y = dbo_move_float_to_pos(plr->GetVectorPosition().y);
	nfy.pos.z = dbo_move_float_to_pos(plr->GetVectorPosition().z);

	plr->SendPacket((char*)&nfy, sizeof(sGU_CHAR_SPECIAL_ATTACK_NFY));
}