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
	MonsterData			GetMobData()const;
	MobReference		&GetMapRef();

	void				BuildPacketForSpawn(SpawnMOB& spawn);
	//	------------------------------------------------------------------------
	// LOGIC
	//	------------------------------------------------------------------------
	void				Regen();
	void				Respawn();
	void				MoveToPoint();

	virtual void		TakeDamage(uint32 amount) override;

	void				SendDeath();

	bool				GetIsSpawn() { return GetMobData().isSpawned; }
	void				SetIsSpawn(bool val) { me.isSpawned = val; }
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
	//	------------------------------------------------------------------------
	// MOVEMENT
	//	------------------------------------------------------------------------
	int					lastMoveTime;
	int					randMove;
	//	------------------------------------------------------------------------
	// SYSTEM
	//	------------------------------------------------------------------------
	std::mutex			mutexMob;
public: // TEMP
	HOBJECT				attackers;
};

#endif