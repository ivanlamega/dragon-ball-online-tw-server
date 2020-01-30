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
	if (NTL_TS_T_ID_INVALID == mobTblidx)
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

void QuestManager::AddObjectQuest(TBLIDX objTblidx, NTL_TS_T_ID questId)
{
	m_pObjectQuestList.insert(std::pair<TBLIDX, NTL_TS_T_ID>(objTblidx, questId));
}

NTL_TS_T_ID	QuestManager::FindQuestByObject(TBLIDX objTblidx)
{
	if (NTL_TS_T_ID_INVALID == objTblidx)
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