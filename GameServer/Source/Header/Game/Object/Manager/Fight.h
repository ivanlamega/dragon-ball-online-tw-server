#ifndef __FIGHT_H
#define __FIGHT_H

#pragma once

#include <Define.h>
#include <Game\Object\Object.h>
#include <NtlBattle.h>
#include <NtlSkill.h>

class Player;
class Mob;

class FightManager
{
public:
	FightManager();
	~FightManager();

	//	------------------------------------------------------------------------
	// LOGIC
	//	------------------------------------------------------------------------
	bool					canTakeDamage(Object& Attacker, Object& Target);
	bool					HandleDamage(Object& Attacker, Object& Target);
	void					HandlePlrFight();
	void					HandleFight(Mob* mob, Player* plr);

	void					GetPlayerDamage(bool caster);
	void					GetPlayerCriticAttack(bool caster);
	void					GetPlayerHitChance();
	int						GetLevelDiff();
private:
	Player*					plr;
	Player*					plrTarget;
	Mob*					mob;
	Object*					AttackerInfo;
	Object*					TargetInfo;
	BYTE					attackCount;

	DWORD					attackValue;
	DWORD					reflectedDamage;
	eBATTLE_ATTACK_RESULT	attackResult;
	eDBO_GUARD_TYPE			guardType;
	std::mutex				mutexFight;
};

#endif