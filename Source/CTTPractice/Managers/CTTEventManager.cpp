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
}

void UCTTEventManager::HandleCollisionEvent()
{
	// EzYong TODO : 데이터 테이블에서 해당 아이템 이름에 맞는 이벤트 데이터 검색
	// 조건 클래스 인스턴스 생성(CTTConditionBase) 후 조건검사
	// 액션 클래스 인스턴스 생성(CTTActionBase) 후 실행

	// EzYong TODO : 우선은 ACTTCollectibleItem을 상속받은 액터들만 사용하게 설정

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

void UCTTEventManager::RemoveActor(AActor* ActorToRemove)
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
			ActorToRemove->Destroy();
			UE_LOG(LogTemp, Log, TEXT("Actor %s destroyed"), *ActorToRemove->GetName());
		}
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
