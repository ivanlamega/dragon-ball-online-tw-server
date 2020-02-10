#ifndef __MOB_H
#define __MOB_H

#pragma once

#include <Game\Object\Object.h>
#include <Game\Maps\MapReference.h>
#include <TableAll.h>

class Mob : public Object
{
public:
	explicit Mob();
	~Mob();

	void				CleanupsBeforeDelete();
	void				AddToWorld() override;
	void				RemoveFromWorld() override;
	void				Update(uint32 update_diff, uint32 time);
	bool				Create(sSPAWN_TBLDAT* spawnTbl, sMOB_TBLDAT* mobTbl);
	bool                Create(sMOB_TBLDAT * mobTbl, SpawnMOB spawnInfo);
	MonsterData			GetMobData()const;
	MobReference		&GetMapRef();

	void				BuildPacketForSpawn(SpawnMOB& spawn);
	//	------------------------------------------------------------------------
	// LOGIC
	//	------------------------------------------------------------------------
	void				Regen();
	void				Respawn();
	void				MoveToPoint();
	void				CheckAgro();
	virtual void		TakeDamage(uint32 amount) override;

	void				SendDeath();

	bool				GetIsSpawn() { return GetMobData().isSpawned; }
	void				SetIsSpawn(bool val) { me.isSpawned = val; }

	bool				GetInitialSpawn() { return GetMobData().initialSpawn; }
	void				SetInitialSpawn(bool val) { me.initialSpawn = val; }
	//	------------------------------------------------------------------------
	// LIST
	//	------------------------------------------------------------------------
	void				SendToPlayerList(char* data, size_t size);
	//	------------------------------------------------------------------------
	// GETTER
	//	------------------------------------------------------------------------
	virtual DWORD		GetPowerLevel() override;

	virtual void UpdateState(eCHARSTATE _state) override;
private:
	MonsterData			me;
	MobReference		m_MobRef;
	time_t				respawnTime;
	DWORD				MobSkill;
	DWORD				TimmerReg;
	DWORD				TimmerMove;
	DWORD				TimmerAgro;
	bool                spawnOnce;
	//	------------------------------------------------------------------------
	// MOVEMENT
	//	------------------------------------------------------------------------
	//int					lastMoveTime;	
	int					randMove;
	int					AttackChain;
	int					UpdateFollowtime;
	int					RandValue;
	int					BossEventRandom;
	//	------------------------------------------------------------------------
	// SYSTEM
	//	------------------------------------------------------------------------
	std::mutex			mutexMob;
public: // TEMP
	HOBJECT				attackers;
};

#endif