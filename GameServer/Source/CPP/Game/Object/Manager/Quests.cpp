#include <Manager\Quests.h>
#include <Game\Object\Player.h>

void QuestManager::AddQuest(QuestData newQuest)
{
	QuestDat.push_back(newQuest);
}

void QuestManager::DeleteQuest(int questId)
{
	for (std::vector<QuestData>::iterator iter = QuestDat.begin(); iter != QuestDat.end(); ++iter)
	{
		if (iter->QuestID == questId)
		{
			QuestDat.erase(iter);
			break;
		}
	}
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