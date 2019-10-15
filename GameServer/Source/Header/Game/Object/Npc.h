#ifndef __NPC_H
#define __NPC_H

#pragma once

#include <Game\Object\Object.h>
#include <Game\Maps\MapReference.h>
#include <TableAll.h>

class Npc : public Object
{
	//CreatureAI* i_AI;  // need it ??
public:
	explicit Npc();
	~Npc();

	void				CleanupsBeforeDelete();
	void				AddToWorld() override;
	void				RemoveFromWorld() override;
	bool				Create(sNPC_TBLDAT* npcTbl, SpawnNPC spawnInfo);
	bool				Create(sSPAWN_TBLDAT* spawnTbl, sNPC_TBLDAT* npcTbl);
	void				Update(uint32 update_diff, uint32 time);
	virtual void		TakeDamage(uint32 amount) override;

	void				BuildPacketForSpawn(SpawnNPC& spawn);
	MonsterData			GetNpcData()const;
	NpcReference		&GetMapRef();

	//	------------------------------------------------------------------------
	// GETTER
	//	------------------------------------------------------------------------
	virtual DWORD		GetPowerLevel() override;

	virtual void UpdateState(eCHARSTATE _state) override;

private:
	MonsterData			me;
	NpcReference		m_NpcRef;
};
#endif