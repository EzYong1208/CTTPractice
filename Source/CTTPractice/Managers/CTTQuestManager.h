// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CTTPractice/CTTStruct.h"
#include "CTTQuestManager.generated.h"

/**
 * 
 */

UCLASS(Blueprintable)
class CTTPRACTICE_API UCTTQuestManager : public UObject
{
	GENERATED_BODY()
	
public:
	void StartQuest(FCTTQuestData QuestData);
	void UpdateQuestProgress(FName QuestName, int32 Progress);
	bool IsQuestComplete(FName QuestName) const;
	void CompleteQuest(FName QuestName);

private:
	TMap<FName, FCTTQuestData> ActiveQuests;

	int32 i = 0;
};
