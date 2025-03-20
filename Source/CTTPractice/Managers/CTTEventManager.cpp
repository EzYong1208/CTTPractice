// Fill out your copyright notice in the Description page of Project Settings.


#include "CTTPractice/Managers/CTTEventManager.h"
#include "CTTPractice/Event/CTTActionBase.h"
#include "CTTPractice/Event/CTTConditionBase.h"
#include "Kismet/GameplayStatics.h"
#include "CTTPractice/CTTGameInstance.h"
#include "CTTPractice/Managers/CTTDatatableManager.h"
#include "CTTPractice/Actor/CollectibleItem/CTTCollectibleItem.h"
#include "CTTPractice/Managers/CTTActionManager.h"
#include "EngineUtils.h"

void UCTTEventManager::Initialize()
{
	UCTTGameInstance* GameInstance = Cast<UCTTGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (!GameInstance)
	{
		UE_LOG(LogTemp, Error, TEXT("GameInstance is nullptr"));
		return;
	}

	const UCTTDatatableManager* DatatableManager = GameInstance->GetDatatableManager();
	if (!DatatableManager)
	{
		UE_LOG(LogTemp, Error, TEXT("DatatableManager is nullptr"));
		return;
	}

	const UDataTable* EventActionDataTable = DatatableManager->GetEventActionDataTable();
	if (!EventActionDataTable)
	{
		UE_LOG(LogTemp, Error, TEXT("EventActionDataTable is nullptr"));
		return;
	}

	EventActionDataMap.Empty();

	TArray<FName> RowNames = EventActionDataTable->GetRowNames();
	for (const FName& RowName : RowNames)
	{
		FCTTEventActionData* EventData = EventActionDataTable->FindRow<FCTTEventActionData>(RowName, TEXT(""));
		if (!EventData)
		{
			continue;
		}

		if (EventData->ItemName != NAME_None && EventData->EventName != NAME_None)
		{
			if (EventActionDataMap.Contains(EventData->ItemName))
			{
				EventActionDataMap[EventData->ItemName].Add(*EventData);
			}
			else
			{
				EventActionDataMap.Add(EventData->ItemName, { *EventData });
			}
		}
	}

	for (const auto& Entry : EventActionDataMap)
	{
		UE_LOG(LogTemp, Log, TEXT("ItemName: %s has %d events"), *Entry.Key.ToString(), Entry.Value.Num());
	}

	SetIdleActionForAllCollectibleItems();

	OnWorldPostActorTickHandle = FWorldDelegates::OnWorldPostActorTick.AddUObject(this, &UCTTEventManager::OnWorldPostActorTick);
}

void UCTTEventManager::Shutdown()
{
	if (false == OnWorldPostActorTickHandle.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("OnWorldPostActorTickHandle is invalid"));
		return;
	}

	FWorldDelegates::OnWorldPostActorTick.Remove(OnWorldPostActorTickHandle);
	OnWorldPostActorTickHandle.Reset();
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

	FName ItemName = CollectibleItem->GetItemName();

	TArray<FCTTEventActionData>* EventList = EventActionDataMap.Find(ItemName);
	if (!EventList)
	{
		UE_LOG(LogTemp, Warning, TEXT("No events found for item: %s"), *ItemName.ToString());
		return;
	}

	const FCTTEventActionData* MatchingEvent = nullptr;
	for (const FCTTEventActionData& EventData : *EventList)
	{
		if (EventData.EventName == EventName)
		{
			MatchingEvent = &EventData;
			break;
		}
	}

	if (!MatchingEvent)
	{
		UE_LOG(LogTemp, Warning, TEXT("No matching event found for item: %s, Event: %s"), *ItemName.ToString(), *EventName.ToString());
		return;
	}
	if (!IsValid(MatchingEvent->ConditionClass))
	{
		UE_LOG(LogTemp, Error, TEXT("ConditionClass is invalid for event: %s"), *EventName.ToString());
		return;
	}

	UCTTConditionBase* ConditionInstance = NewObject<UCTTConditionBase>(this, MatchingEvent->ConditionClass);
	if (nullptr == ConditionInstance)
	{
		UE_LOG(LogTemp, Error, TEXT("ConditionInstance is nullptr"));
		return;
	}

	bool bConditionSatisfied = ConditionInstance->CheckCondition_Implementation(CollidedActor);
	if (!bConditionSatisfied)
	{
		UE_LOG(LogTemp, Log, TEXT("Condition not satisfied for event: %s"), *EventName.ToString());
		return;
	}

	StartActionsFromEvent(Actor, CollidedActor, EventName);
}

void UCTTEventManager::ExecuteAction(AActor* TargetActor, const FCTTActionData& ActionData)
{
	if (!IsValid(ActionData.ActionClass))
	{
		UE_LOG(LogTemp, Error, TEXT("ExecuteAction: ActionClass is invalid!"));
		return;
	}

	UCTTGameInstance* GameInstance = Cast<UCTTGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (!GameInstance)
	{
		UE_LOG(LogTemp, Error, TEXT("ExecuteAction: GameInstance is nullptr"));
		return;
	}

	UCTTActionManager* ActionManager = GameInstance->GetActionManager();
	if (!ActionManager)
	{
		UE_LOG(LogTemp, Error, TEXT("ExecuteAction: ActionManager is nullptr"));
		return;
	}

	UCTTActionBase* ActionInstance = ActionManager->GetActionInstanceByClass(ActionData.ActionClass);
	if (!ActionInstance)
	{
		UE_LOG(LogTemp, Error, TEXT("ExecuteAction: Failed to retrieve action instance for class: %s"), *ActionData.ActionClass->GetName());
		return;
	}

	ActionInstance->InitializeWithActionData(ActionData);
	ActionInstance->Execute_Implementation(TargetActor);
}

UCTTActionBase* UCTTEventManager::ExecuteActionAndReturn(AActor* TargetActor, const FCTTActionData& ActionData)
{
	if (!IsValid(ActionData.ActionClass))
	{
		UE_LOG(LogTemp, Error, TEXT("ExecuteActionAndReturn: ActionClass is invalid!"));
		return nullptr;
	}

	UCTTGameInstance* GameInstance = Cast<UCTTGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (!GameInstance)
	{
		UE_LOG(LogTemp, Error, TEXT("ExecuteActionAndReturn: GameInstance is nullptr"));
		return nullptr;
	}

	UCTTActionManager* ActionManager = GameInstance->GetActionManager();
	if (!ActionManager)
	{
		UE_LOG(LogTemp, Error, TEXT("ExecuteActionAndReturn: ActionManager is nullptr"));
		return nullptr;
	}

	UCTTActionBase* ActionInstance = ActionManager->GetActionInstanceByClass(ActionData.ActionClass);
	if (!ActionInstance)
	{
		UE_LOG(LogTemp, Error, TEXT("ExecuteActionAndReturn: Failed to retrieve action instance for class: %s"), *ActionData.ActionClass->GetName());
		return nullptr;
	}

	ActionInstance->InitializeWithActionData(ActionData);
	ActionInstance->Execute_Implementation(TargetActor);

	return ActionInstance;
}

void UCTTEventManager::AddActorToPendingKill(AActor* ActorToRemove)
{
	if (!ActorToRemove)
	{
		UE_LOG(LogTemp, Error, TEXT("Actor is invalid"));
		return;
	}

	ACTTCollectibleItem* CollectibleItem = Cast<ACTTCollectibleItem>(ActorToRemove);
	if (nullptr == CollectibleItem)
	{
		UE_LOG(LogTemp, Error, TEXT("Actor is not CollectibleItem"));
		return;
	}

	FName ActorName = CollectibleItem->GetItemName();
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

void UCTTEventManager::SetIdleActionForAllCollectibleItems()
{
	UCTTGameInstance* GameInstance = Cast<UCTTGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (!GameInstance)
	{
		UE_LOG(LogTemp, Error, TEXT("GameInstance is nullptr"));
		return;
	}

	for (TActorIterator<ACTTCollectibleItem> It(GameInstance->GetWorld()); It; ++It)
	{
		ACTTCollectibleItem* CollectibleItem = *It;
		if (!CollectibleItem)
		{
			continue;
		}

		const TArray<FCTTEventActionData>* EventDataArray = EventActionDataMap.Find(CollectibleItem->GetItemName());
		if (!EventDataArray)
		{
			continue;
		}

		for (const FCTTEventActionData& EventData : *EventDataArray)
		{
			if (EventData.EventName == TEXT("Idle"))
			{
				if (!IsValid(EventData.Actions[0].ActionClass))
				{
					UE_LOG(LogTemp, Error, TEXT("SetIdleAction: ActionClass is nullptr for %s"), *EventData.ItemName.ToString());
				}
				else
				{
					UE_LOG(LogTemp, Log, TEXT("SetIdleAction: %s assigned to %s"), *EventData.Actions[0].ActionClass->GetName(), *EventData.ItemName.ToString());
				}

				CollectibleItem->SetIdleAction(EventData.Actions[0]);

				break;
			}
		}
	}
}

void UCTTEventManager::OnWorldPostActorTick(UWorld* World, ELevelTick TickType, float DeltaTime)
{
	if (LEVELTICK_All != TickType)
	{
		UE_LOG(LogTemp, Error, TEXT("TickType is not LEVELTICK_All"));
		return;
	}

	CheckAndDestroyPendingActors();
}

void UCTTEventManager::StartActionsFromEvent(AActor* ItemActor, AActor* OtherActor, FName EventName)
{
	ACTTCollectibleItem* CollectibleItem = Cast<ACTTCollectibleItem>(ItemActor);
	if (nullptr == CollectibleItem)
	{
		UE_LOG(LogTemp, Error, TEXT("CollectibleItem is nullptr"));
		return;
	}

	TArray<FCTTEventActionData>* EventList = EventActionDataMap.Find(CollectibleItem->GetItemName());
	if (!EventList)
	{
		UE_LOG(LogTemp, Warning, TEXT("No events found for item: %s"), *CollectibleItem->GetItemName().ToString());
		return;
	}

	const FCTTEventActionData* MatchingEvent = nullptr;
	for (const FCTTEventActionData& EventData : *EventList)
	{
		if (EventData.EventName == EventName)
		{
			MatchingEvent = &EventData;
			break;
		}
	}

	if (!MatchingEvent)
	{
		UE_LOG(LogTemp, Warning, TEXT("No matching event found for item: %s, Event: %s"), *CollectibleItem->GetItemName().ToString(), *EventName.ToString());
		return;
	}

	if (MatchingEvent->Actions.Num() > 0)
	{
		CollectibleItem->StartActions(MatchingEvent->Actions);
		UE_LOG(LogTemp, Log, TEXT("Started actions for %s with event: %s"), *CollectibleItem->GetItemName().ToString(), *EventName.ToString());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No actions found for event: %s on item: %s"), *EventName.ToString(), *CollectibleItem->GetItemName().ToString());
	}
}
