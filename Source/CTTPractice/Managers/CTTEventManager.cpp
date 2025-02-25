// Fill out your copyright notice in the Description page of Project Settings.


#include "CTTPractice/Managers/CTTEventManager.h"
#include "CTTPractice/Event/CTTActionBase.h"
#include "CTTPractice/Event/CTTConditionBase.h"
#include "Kismet/GameplayStatics.h"
#include "CTTPractice/CTTGameInstance.h"
#include "CTTPractice/Managers/CTTDatatableManager.h"
#include "CTTPractice/Actor/CollectibleItem/CTTCollectibleItem.h"

void UCTTEventManager::Initialize()
{
	UCTTGameInstance* GameInstance = Cast<UCTTGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (!GameInstance)
	{
		UE_LOG(LogTemp, Error, TEXT("GameInstance is nullptr"));
		return;
	}

	const UCTTDatatableManager* DatatableManager = GameInstance->GetDatatableManager();
	if (nullptr == DatatableManager)
	{
		UE_LOG(LogTemp, Error, TEXT("DatatableManager is nullptr"));
		return;
	}

	const UDataTable* EventActionDataTable = DatatableManager->GetEventActionDataTable();
	TArray<FName> RowNames = EventActionDataTable->GetRowNames();
	for (const FName& RowName : RowNames)
	{
		FCTTEventActionData* EventData = EventActionDataTable->FindRow<FCTTEventActionData>(RowName, TEXT(""));
		if (!EventData)
		{
			continue;
		}

		if (EventData->ItemName != NAME_None && 
			EventData->EventName != NAME_None)
		{
			EventActionDataMap.Add(EventData->ItemName, *EventData);
		}
	}

	GetWorld()->GetTimerManager().SetTimer(DestroyTimerHandle, this, &UCTTEventManager::CheckAndDestroyPendingActors, 0.1f, true);
}

void UCTTEventManager::HandleCollisionEvent(AActor* Actor, AActor* CollidedActor, FName EventName)
{
	if (nullptr == Actor)
	{
		UE_LOG(LogTemp, Error, TEXT("Actor is nullptr"));
		return;
	}
	if (nullptr == CollidedActor)
	{
		UE_LOG(LogTemp, Error, TEXT("CollidedActor is nullptr"));
		return;
	}

	ACTTCollectibleItem* CollectibleItem = Cast<ACTTCollectibleItem>(Actor);
	if (nullptr == CollectibleItem)
	{
		UE_LOG(LogTemp, Error, TEXT("Actor is not CollectibleItem"));
		return;
	}

	FName ItemName = CollectibleItem->GetFName();
	bool bHasEventData = EventActionDataMap.Contains(ItemName);
	if (false == bHasEventData)
	{
		return;
	}

	const FCTTEventActionData& EventData = EventActionDataMap[ItemName];
	UCTTConditionBase* ConditionInstance = NewObject<UCTTConditionBase>(this, EventData.ConditionClass);
	if (nullptr == ConditionInstance)
	{
		UE_LOG(LogTemp, Error, TEXT("ConditionInstance is nullptr"));
		return;
	}

	bool bConditionSatisfied = ConditionInstance->CheckCondition_Implementation(CollidedActor);
	if (!bConditionSatisfied)
	{
		return;
	}

	StartActionsFromEvent(Actor, CollidedActor, EventName);
}

void UCTTEventManager::ExecuteAction(AActor* TargetActor, const FCTTActionData& ActionData)
{
	if (!IsValid(ActionData.ActionClass))
	{
		UE_LOG(LogTemp, Error, TEXT("ActionClass is invalid"));
		return;
	}

	UCTTActionBase* ActionInstance = NewObject<UCTTActionBase>(this, ActionData.ActionClass);
	if (!ActionInstance)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to create ActionInstance"));
		return;
	}

	ActionInstance->Execute_Implementation(TargetActor);
}

void UCTTEventManager::AddActorToPendingKill(AActor* ActorToRemove)
{
	if (!ActorToRemove)
	{
		UE_LOG(LogTemp, Error, TEXT("Actor is invalid"));
		return;
	}

	FName ActorName = ActorToRemove->GetFName();
	if (EventActionDataMap.Contains(ActorName))
	{
		EventActionDataMap.Remove(ActorName);

		if (IsValid(ActorToRemove))
		{
			PendingKillActors.Enqueue(ActorToRemove);
			UE_LOG(LogTemp, Log, TEXT("Actor %s moved to PendingKillActor Array"), *ActorToRemove->GetName());
		}
	}
}

void UCTTEventManager::CheckAndDestroyPendingActors()
{
	AActor* Actor = nullptr;
	while (PendingKillActors.Dequeue(Actor))
	{
		ACTTCollectibleItem* CollectibleItem = Cast<ACTTCollectibleItem>(Actor);
		if (nullptr == CollectibleItem)
		{
			UE_LOG(LogTemp, Error, TEXT("Actor is not CollectibleItem"));
			continue;
		}

		FName ItemName = CollectibleItem->GetItemName();
		CollectibleItem->Destroy();
		UE_LOG(LogTemp, Log, TEXT("Actor %s has Destroyed"), *ItemName.ToString());
	}
}

void UCTTEventManager::StartActionsFromEvent(AActor* ItemActor, AActor* OtherActor, FName EventName)
{
	ACTTCollectibleItem* CollectibleItem = Cast<ACTTCollectibleItem>(ItemActor);
	if (nullptr == CollectibleItem)
	{
		UE_LOG(LogTemp, Error, TEXT("CollectibleItem is nullptr"));
		return;
	}

	if (EventActionDataMap.Contains(CollectibleItem->GetItemName()))
	{
		const FCTTEventActionData& EventData = EventActionDataMap[CollectibleItem->GetItemName()];
		if (EventData.EventName == EventName)
		{
			CollectibleItem->StartActions(EventData.Actions);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No event data found for item: %s"), *CollectibleItem->GetItemName().ToString());
	}
}
