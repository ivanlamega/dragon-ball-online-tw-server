#include <Manager\Quests.h>
#include <Game\Object\Player.h>

void QuestManager::AddQuest(QuestData newQuest)
{
	if (QuestDat.size() < MAX_QUEST_SLOT)
	{
		QuestDat.push_back(newQuest);
	}
}

bool QuestManager::DeleteQuest(int questId)
{
	for (std::vector<QuestData>::iterator iter = QuestDat.begin(); iter != QuestDat.end(); ++iter)
	{
		if (iter->QuestID == questId)
		{
			QuestDat.erase(iter);
			DeleteMobsQuest(questId);
			return true;
		}
	}
	return false;
}

QuestData* QuestManager::FindQuestById(int questId)
{
	for (std::vector<QuestData>::size_type i = 0; i != QuestDat.size(); i++)
	{
		if (QuestDat[i].QuestID == questId)
		{
			return &QuestDat[i];
		}
	}
	return NULL;
}

void QuestManager::AddMobQuest(TBLIDX mobTblidx, NTL_TS_T_ID questId)
{
	m_pMobQuestList.insert(std::pair<TBLIDX, NTL_TS_T_ID>(mobTblidx, questId));

}

NTL_TS_T_ID	QuestManager::FindQuestByMob(TBLIDX mobTblidx)
{
	if (INVALID_TBLIDX == mobTblidx)
	{
		return NTL_TS_T_ID_INVALID;
	}

	MOBQUESTIT iter;
	iter = m_pMobQuestList.find(mobTblidx);
	if (MobQuestEnd() == iter)
	{
		return NTL_TS_T_ID_INVALID;
	}

	return (NTL_TS_T_ID)iter->second;
}

void QuestManager::DeleteMobsQuest(NTL_TS_T_ID questId)
{
	for (auto it = m_pMobQuestList.begin(); it != m_pMobQuestList.end(); ++it)
	{
		if (it->second == questId)
		{
			sLog.outBasic("Deleted mob %d of quest %d", it->second, it->first);
			m_pMobQuestList.erase(it->first);
			sLog.outBasic("Deleted!");
		}
	}	
}

void QuestManager::DeleteMobQuest(TBLIDX mobTblidx)
{
	m_pMobQuestList.erase(mobTblidx);
	sLog.outBasic("Mob % deleted from list", mobTblidx);
}

void QuestManager::AddObjectQuest(TBLIDX objTblidx, NTL_TS_T_ID questId)
{
	m_pObjectQuestList.insert(std::pair<TBLIDX, NTL_TS_T_ID>(objTblidx, questId));
}

NTL_TS_T_ID	QuestManager::FindQuestByObject(TBLIDX objTblidx)
{
	if (INVALID_TBLIDX == objTblidx)
	{
		return NTL_TS_T_ID_INVALID;
	}

	OBJECTQUESTIT iter;
	iter = m_pObjectQuestList.find(objTblidx);
	if (ObjectQuestEnd() == iter)
	{
		return NTL_TS_T_ID_INVALID;
	}

	return (NTL_TS_T_ID)iter->second;
}

void QuestManager::AddObjectTrigger(TBLIDX objTblidx, NTL_TS_T_ID triggerId, TBLIDX worldTblidx)
{
	WORLDTRIGGERIT iter;
	iter = m_pWorldTriggerList.find(worldTblidx);
	if (WorldTriggerEnd() == iter)
	{
		//m_pWorldTriggerList.insert(std::pair<TBLIDX, OBJECTTRIGGER>(worldTblidx, OBJECTTRIGGER()));
		m_pWorldTriggerList[worldTblidx] = OBJECTTRIGGER();
		m_pWorldTriggerList[worldTblidx].insert(std::pair<TBLIDX, NTL_TS_T_ID>(objTblidx, triggerId));
	}
	else
	{
		m_pWorldTriggerList[worldTblidx].insert(std::pair<TBLIDX, NTL_TS_T_ID>(objTblidx, triggerId));
	}

	//m_pObjectTriggerList.insert(std::pair<TBLIDX, NTL_TS_T_ID>(objTblidx, triggerId));
}

NTL_TS_T_ID QuestManager::FindTriggerByObject(TBLIDX objTblidx, TBLIDX worldTblidx)
{
	if (INVALID_TBLIDX == worldTblidx)
	{
		return NTL_TS_T_ID_INVALID;
	}

	if (INVALID_TBLIDX == objTblidx)
	{
		return NTL_TS_T_ID_INVALID;
	}

	WORLDTRIGGERIT iterWorld;
	iterWorld = m_pWorldTriggerList.find(worldTblidx);
	if (WorldTriggerEnd() == iterWorld)
	{
		return NTL_TS_T_ID_INVALID;
	}
	
	OBJECTTRIGGERIT iter;
	iter = iterWorld->second.find(objTblidx);
	if (iterWorld->second.end() == iter)
	{
		return NTL_TS_T_ID_INVALID;
	}

	return (NTL_TS_T_ID)iter->second;
}

void QuestManager::AddItemGiveQuest(TBLIDX itemTblidx, NTL_TS_T_ID questId)
{
	m_pItemGiveQuestList.insert(std::pair<TBLIDX, NTL_TS_T_ID>(itemTblidx, questId));
}

NTL_TS_T_ID QuestManager::FindQuestByItemGive(TBLIDX itemTblidx)
{
	if (INVALID_TBLIDX == itemTblidx)
	{
		return NTL_TS_T_ID_INVALID;
	}

	ITEMGIVEQUESTIT iter;
	iter = m_pItemGiveQuestList.find(itemTblidx);
	if (ItemGiveQuestEnd() == iter)
	{
		return NTL_TS_T_ID_INVALID;
	}

	return (NTL_TS_T_ID)iter->second;
}

void QuestManager::AddNPCSpawnedQuest(HOBJECT NPCHandle, NTL_TS_T_ID questId)
{
	m_pNPCSpawnedQuestList.insert(std::pair<HOBJECT, NTL_TS_T_ID>(NPCHandle, questId));
}

NTL_TS_T_ID QuestManager::FindQuestByNPCSpawned(HOBJECT NPCHandle)
{
	if (-1 == NPCHandle)
	{
		return NTL_TS_T_ID_INVALID;
	}

	NPCSPAWNEDQUESTIT iter;
	iter = m_pNPCSpawnedQuestList.find(NPCHandle);
	if (NPCSpawnedQuestEnd() == iter)
	{
		return NTL_TS_T_ID_INVALID;
	}

	return (NTL_TS_T_ID)iter->second;
}