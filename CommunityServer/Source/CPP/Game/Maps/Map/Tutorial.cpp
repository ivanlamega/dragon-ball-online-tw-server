#include <Game\Maps\Map\Tutorial.h>
#include <Game\Object\Mob.h>
#include <Game\Object\Npc.h>
#include <Game\Object\Player.h>
#include <CommunitySession.h>
#include <Logger.h>

Tutorial::Tutorial(uint32 id) : Map(id)
{
	
}
Tutorial::~Tutorial()
{
	
}
void Tutorial::Update(const uint32& time)
{
}
void Tutorial::ChangeStep(Player* plr, int stape)
{
	//SpawnMOB sMob;
	if (stape == 1)
	{
		/*for (m_mobRefIter = m_mobRefManager.begin(); m_mobRefIter != m_mobRefManager.end(); ++m_mobRefIter)
		{
			Mob* curr_Mob = static_cast<Mob*>(m_mobRefIter->getSource());
			if (curr_Mob && curr_Mob->IsInWorld() && curr_Mob->GetIsDead() == false)
			{
				if (curr_Mob->GetMobData().MonsterID == BEAN_SAIBAMAN)
				{
					SpawnMOB mob = { };
					curr_Mob->BuildPacketForSpawn(sMob);
					plr->SendPacket((char*)&sMob, sizeof(SpawnMOB));
				}
			}
		}*/
	}
	else if (stape == 2)
	{
		/*for (m_mobRefIter = m_mobRefManager.begin(); m_mobRefIter != m_mobRefManager.end(); ++m_mobRefIter)
		{
			Mob* curr_Mob = static_cast<Mob*>(m_mobRefIter->getSource());
			if (curr_Mob && curr_Mob->IsInWorld() && curr_Mob->GetIsDead() == false)
			{
				if (curr_Mob->GetMobData().MonsterID == KOWANGA)
				{
					curr_Mob->BuildPacketForSpawn(sMob);
					plr->SendPacket((char*)&sMob, sizeof(SpawnMOB));
				}
			}
		}*/
	}
	else if (stape == 3)
	{
		/*for (m_mobRefIter = m_mobRefManager.begin(); m_mobRefIter != m_mobRefManager.end(); ++m_mobRefIter)
		{
			Mob* curr_Mob = static_cast<Mob*>(m_mobRefIter->getSource());
			if (curr_Mob && curr_Mob->IsInWorld() && curr_Mob->GetIsDead() == false)
			{
				if (curr_Mob->GetMobData().MonsterID == RIO)
				{
					curr_Mob->BuildPacketForSpawn(sMob);
					plr->SendPacket((char*)&sMob, sizeof(SpawnMOB));
				}
			}
		}*/
	}
	else if (stape == 4)
	{
		/*for (m_npcRefIter = m_npcRefManager.begin(); m_npcRefIter != m_npcRefManager.end(); ++m_npcRefIter)
		{
			Npc* curr_Mob = static_cast<Npc*>(m_npcRefIter->getSource());
			if (curr_Mob && curr_Mob->IsInWorld() && curr_Mob->GetIsDead() == false)
			{
				if (curr_Mob->GetNpcData().MonsterID == SEA_TURTLE)
				{
					SpawnNPC mob;
					curr_Mob->BuildPacketForSpawn(mob);
					plr->SendPacket((char*)&mob, sizeof(SpawnNPC));
				}
			}
		}*/
	}
}