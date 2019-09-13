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
// ¿Podemos dañar nuestro objetivo?
// Necesito verificar si la bandera está configurada como atacable, etc.
//----------------------------------------
bool FightManager::canTakeDamage(Object& Attacker, Object& Target)
{
	if (Target.GetTypeId() == eOBJTYPE::OBJTYPE_MOB || Target.GetTypeId() == OBJTYPE_PC)
	{
		
	}
	return false;
}
//----------------------------------------
//	Consigue la cantidad de nivel entre nosotros y la mafia.
//----------------------------------------
int FightManager::GetLevelDiff()
{
	int levelDiff = plr->GetPcProfile()->byLevel - mob->GetMobData().Level;

	return levelDiff;
}
//----------------------------------------
//	Consigue la cantidad de daño que hacer
//	@param id - boolean to say if we are caster or cac
//----------------------------------------
void FightManager::GetPlayerDamage(bool caster)
{
	attackValue = 0;
	if (caster == false)
	{
		attackValue = plr->GetPcProfile()->avatarAttribute.wLastPhysicalOffence;
	}
	else
	{		
		attackValue = plr->GetPcProfile()->avatarAttribute.wLastEnergyOffence;
	}
}
//----------------------------------------
//	Obtener si nuestro ataque será crítico.
//	@param id - boolean to say if we are caster or cac
//----------------------------------------
void FightManager::GetPlayerCriticAttack(bool caster)
{
	int CritChance = 0; 
	int num = rand() % 100 + 1;

	if (caster == false)
	{
		CritChance = plr->GetPcProfile()->avatarAttribute.wLastPhysicalCriticalRate - (mob->GetMobData().Block_rate / 100);
	}
	else
	{
		CritChance = plr->GetPcProfile()->avatarAttribute.wLastEnergyCriticalRate - (mob->GetMobData().Block_rate / 100);
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
//	Haz que el jugador golpee el cambio
//----------------------------------------
void FightManager::GetPlayerHitChance()
{
	float percent = ((mob->GetMobData().Dodge_rate - plr->GetPcProfile()->avatarAttribute.wLastAttackRate) / ((0.3605f * mob->GetMobData().Level) + 18.64f) * ((0.335f * plr->GetPcProfile()->byLevel) + 50)) * -1;

	int num = rand() % 100 + 1;
	if (num <= percent && percent > 0)
		attackResult = eBATTLE_ATTACK_RESULT::BATTLE_ATTACK_RESULT_HIT;
	//std::cout << "Hitchance = " << percent << std::endl;
	//std::cout << "Target dodge: " << mob->GetMobData().Dodge_rate << std::endl;
	//if (num <= mob->GetMobData().Block_rate)
		//attackResult = eBATTLE_ATTACK_RESULT::BATTLE_ATTACK_RESULT_BLOCK;
}
//----------------------------------------
//	Realizar un ataque automático desde un objeto.
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
	mob = reinterpret_cast<Mob*>(&Target);
	plr = reinterpret_cast<Player*>(&Attacker);
	plrTarget = reinterpret_cast<Player*>(&Target);
	TargetInfo = reinterpret_cast<Player*>(&Target);
	AttackerInfo = reinterpret_cast<Player*>(&Attacker);
	if (Target.GetTypeId() == OBJTYPE_PC && plr->GetAttributesManager()->PlayerInFreeBatle == true)
	{
		plr = reinterpret_cast<Player*>(&Attacker);
		plrTarget = reinterpret_cast<Player*>(&Target);
		float distance = NtlGetDistance(plr->GetVectorPosition().x, plr->GetVectorPosition().z, plrTarget->GetVectorPosition().x, plrTarget->GetVectorPosition().z);
		if (distance <= (plr->GetPcProfile()->avatarAttribute.fLastAttackRange) + 2)
		{
			/// Ahora puede continuar la verificación de ataque para el jugador.
			HandlePlrFight();
			attackCount++;
		}
	}
	if (Target.GetTypeId() == OBJTYPE_MOB)
	{
		plr = reinterpret_cast<Player*>(&Attacker);
		mob = reinterpret_cast<Mob*>(&Target);
		float distance = NtlGetDistance(plr->GetVectorPosition().x, plr->GetVectorPosition().z, mob->GetMobData().curPos.x, mob->GetMobData().curPos.z);
		if (distance <= (plr->GetPcProfile()->avatarAttribute.fLastAttackRange) + 2)
		{
			/// Ahora puede continuar la verificación de ataque para el jugador.
			HandlePlrFight();
			attackCount++;
		}
	}
	else
	{
		if (NtlGetDistance(plr->GetVectorPosition().x, plr->GetVectorPosition().z, mob->GetMobData().curPos.x, mob->GetMobData().curPos.z) <= mob->GetMobData().Attack_range)
		{
			/// Ahora puede continuar la verificación de ataque para el jugador.
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
	
	GetPlayerDamage(isCaster);
	GetPlayerHitChance();
	if (attackValue <= 0 || attackValue > 1000000000)
	{
		attackValue = 1;
	}
	if (attackResult != eBATTLE_ATTACK_RESULT::BATTLE_ATTACK_RESULT_DODGE)
	{
		GetPlayerCriticAttack(isCaster);
		if (attackResult == eBATTLE_ATTACK_RESULT::BATTLE_ATTACK_RESULT_BLOCK)
		{
			attackValue /= 2;
		}
	}
	else
		attackValue = 0;
	
	res.bChainAttack = true;
	res.byAttackResult = attackResult;
	res.byBlockedAction = guardType;
	res.dwLpEpEventId = 0;
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
	
	plr->SendPacket((char*)&res, sizeof(sGU_CHAR_ACTION_ATTACK));
	plr->SendToPlayerList((char*)&res, sizeof(sGU_CHAR_ACTION_ATTACK));

	if (attackResult != eBATTLE_ATTACK_RESULT::BATTLE_ATTACK_RESULT_DODGE)
	{
		
		if (TargetInfo->GetTypeId() == OBJTYPE_MOB)
		{
			//printf("Player Attack MOB \n");
			if (mob->attackers == 0)
				mob->attackers = plr->GetHandle();
			mob->TakeDamage(attackValue);
		}
		if (TargetInfo->GetTypeId() == OBJTYPE_PC && plr->GetAttributesManager()->PlayerInFreeBatle == true)
		{			
			//printf("Player Attack Player \n");
			if (mob->attackers == 0)
				mob->attackers = plrTarget->GetHandle();
			plrTarget->TakeDamage(attackValue);
		}		
	}
}