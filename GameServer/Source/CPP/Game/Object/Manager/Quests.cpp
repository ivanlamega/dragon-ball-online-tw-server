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
	if (INVALID_TBLIDX == mobTblidx)
	{
		return INVALID_TBLIDX;
	}

	MOBQUESTIT iter;
	iter = m_pMobQuestList.find(mobTblidx);
	if (MobQuestEnd() == iter)
	{
		return INVALID_TBLIDX;
	}

	return (NTL_TS_T_ID)iter->second;
}