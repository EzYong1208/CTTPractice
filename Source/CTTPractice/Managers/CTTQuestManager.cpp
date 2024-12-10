// Fill out your copyright notice in the Description page of Project Settings.


#include "CTTPractice/Managers/CTTQuestManager.h"

void UCTTQuestManager::StartQuest(FCTTQuestData QuestData)
{
	if (!ActiveQuests.Contains(QuestData.QuestName))
	{
		ActiveQuests.Emplace(QuestData.QuestName, QuestData);
	}
}

void UCTTQuestManager::UpdateQuestProgress(FName QuestName, int32 Progress)
{
	FCTTQuestData* QuestData = ActiveQuests.Find(QuestName);
	if (nullptr != QuestData)
	{
		QuestData->CurrentProgress += Progress;
		if (QuestData->CurrentProgress >= QuestData->GoalCount)
		{
			//CompleteQuest(QuestName);
		}
	}
}

bool UCTTQuestManager::IsQuestComplete(FName QuestName) const
{
	const FCTTQuestData* QuestData = ActiveQuests.Find(QuestName);
	bool bIsComplete = false;
	if (QuestData)
	{
		bIsComplete = QuestData->CurrentProgress >= QuestData->GoalCount;
	}

	return bIsComplete;
}

void UCTTQuestManager::CompleteQuest(FName QuestName)
{
	if (ActiveQuests.Contains(QuestName))
	{
		ActiveQuests.Remove(QuestName);
	}
}
