#include <Game\Object\Manager\Fight.h>
#include <TableAll.h>
#include <Game\Object\Player.h>
#include <Game\Object\Mob.h>

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
//	Get the amount of physical damage
//----------------------------------------
float FightManager::CalculePhysicalDamage(float attackerOffence, DWORD attackerLevel, float targetDefence)
{
	sFORMULA_TBLDAT* formula = (sFORMULA_TBLDAT*)sTBM.GetFormulaTable()->FindData(3100);
	if (formula)
	{
		sLog.outBasic("1 physical attack %f level %d", attackerOffence, attackerLevel);
		float damage = (targetDefence + attackerLevel * formula->afRate[0]);
		damage = (1 - (targetDefence / damage));
		damage = attackerOffence * damage;
		sLog.outBasic("damage %f mob defense %f", damage, targetDefence);
		float percent = damage * 1 / attackerOffence;
		float lastDamage = damage * (1 + percent);
		sLog.outBasic("percent %f last damage %f", percent, lastDamage);
		return damage;
	}
	return 0.0;
}
//----------------------------------------
//	Get the amount of energy damage
//----------------------------------------
float FightManager::CalculeEnergyDamage(float attackerOffence, DWORD attackerLevel, float targetDefence)
{
	sFORMULA_TBLDAT* formula = (sFORMULA_TBLDAT*)sTBM.GetFormulaTable()->FindData(3300);
	if (formula)
	{
		sLog.outBasic("1 energy attack %f level %d", attackerOffence, attackerLevel);
		float damage = (targetDefence + attackerLevel * formula->afRate[0]);
		damage = (1 - (targetDefence / damage));
		damage = attackerOffence * damage;
		sLog.outBasic("damage %f mob defense %f", damage, targetDefence);
		float percent = damage * 1 / attackerOffence;
		float lastDamage = damage * (1 + percent);
		sLog.outBasic("percent %f last damage %f", percent, lastDamage);
		return damage;
	}
	return 0.0;
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
	int num = rand() % 100 + 1;
	if (caster == false)
	{		
		if (ObjectTypeId == OBJTYPE_MOB)
		{
			CritChance = plr->GetPcProfile()->avatarAttribute.wLastPhysicalCriticalRate - (mob->GetMobData().Block_rate / 100);
		}
		if (ObjectTypeId == OBJTYPE_PC)
		{
			CritChance = plr->GetPcProfile()->avatarAttribute.wLastPhysicalCriticalRate - (plrTarget->GetPcProfile()->avatarAttribute.wLastBlockRate / 100);
		}
	}
	else
	{		
		if (ObjectTypeId == OBJTYPE_MOB)
		{
			CritChance = plr->GetPcProfile()->avatarAttribute.wLastEnergyCriticalRate - (mob->GetMobData().Block_rate / 100);
		}
		if (ObjectTypeId == OBJTYPE_PC)
		{
			CritChance = plr->GetPcProfile()->avatarAttribute.wLastEnergyCriticalRate - (plrTarget->GetPcProfile()->avatarAttribute.wLastBlockRate / 100);
		}
	}
	(CritChance > 0) ? CritChance *= 1 : CritChance *= -1;
	if (num <= CritChance && CritChance > 0)
	{
		attackResult = eBATTLE_ATTACK_RESULT::BATTLE_ATTACK_RESULT_CRITICAL_HIT;
		attackValue *= 2;
	}
	//std::cout << "CritChance = " << CritChance << std::endl;
}
//----------------------------------------
//	Get the player hit change
//----------------------------------------
void FightManager::GetPlayerHitChance(eOBJTYPE ObjectTypeId)
{
	if (ObjectTypeId == OBJTYPE_MOB)
	{
		int HitRate = plr->GetPcProfile()->avatarAttribute.wLastAttackRate;
		int DodgeRate = mob->GetMobData().Dodge_rate;
		float TotalHitPercent = HitRate + DodgeRate;
		float TotalHitRatePercent = HitRate * 100 / TotalHitPercent;
		int RandomHit = rand() % 100;
		if (RandomHit <= TotalHitRatePercent && TotalHitRatePercent > 0)
			attackResult = eBATTLE_ATTACK_RESULT::BATTLE_ATTACK_RESULT_HIT;
	}
	if (ObjectTypeId == OBJTYPE_PC)
	{
		int HitRate = plr->GetPcProfile()->avatarAttribute.wLastAttackRate;
		int DodgeRate = plrTarget->GetPcProfile()->avatarAttribute.wLastDodgeRate;
		float TotalHitPercent = HitRate + DodgeRate;
		float TotalHitRatePercent = HitRate * 100 / TotalHitPercent;
		int RandomHit = rand() % 100;
		if (RandomHit <= TotalHitRatePercent && TotalHitRatePercent > 0)
			attackResult = eBATTLE_ATTACK_RESULT::BATTLE_ATTACK_RESULT_HIT;
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