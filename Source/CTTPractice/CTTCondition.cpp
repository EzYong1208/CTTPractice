// Fill out your copyright notice in the Description page of Project Settings.


#include "CTTCondition.h"
#include "CTTPractice/Actor/CollectibleItem/CTTCollectibleItem.h"

bool UCTTCondition_Name::CheckCondition(AActor* Actor) const
{
	ACTTCollectibleItem* CollectibleItem = Cast<ACTTCollectibleItem>(Actor);

	if (nullptr == CollectibleItem)
	{
		return false;
	}

	if (CollectibleItem->GetItemName() != ActorName)
	{
		return false;
	}

	return true;
}
