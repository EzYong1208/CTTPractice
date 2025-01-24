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

	TArray<AActor*> FoundItems;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACTTCollectibleItem::StaticClass(), FoundItems);
	for (AActor* Actor : FoundItems)
	{
		ACTTCollectibleItem* CollectibleItem = Cast<ACTTCollectibleItem>(Actor);
		if (!CollectibleItem)
		{
			continue;
		}

		FName ItemName = CollectibleItem->GetItemName();

		// EzYong TODO : �̺�Ʈ �����Ϳ��� �̸��� �ش��ϴ� ������ ã�� ��Ī�� �����Ͱ� �ִٸ� �ʿ� �߰��ϱ�

	}
}

void UCTTEventManager::Update(float DeltaTime)
{

}

void UCTTEventManager::HandleCollisionEvent()
{
	// EzYong TODO : ������ ���̺��� �ش� ������ �̸��� �´� �̺�Ʈ ������ �˻�
	// ���� Ŭ���� �ν��Ͻ� ����(CTTConditionBase) �� ���ǰ˻�
	// �׼� Ŭ���� �ν��Ͻ� ����(CTTActionBase) �� ����

	// EzYong TODO : �켱�� ACTTCollectibleItem�� ��ӹ��� ���͵鸸 ����ϰ� ����

}

void UCTTEventManager::ExecuteAction(const FCTTActionData& ActionData)
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

	ActionInstance->Execute_Implementation();
}

void UCTTEventManager::StartActionsFromEvent(AActor* ItemActor, AActor* OtherActor, FName EventName)
{
	ACTTCollectibleItem* CollectibleItem = Cast<ACTTCollectibleItem>(ItemActor);
	if (nullptr == CollectibleItem)
	{
		UE_LOG(LogTemp, Error, TEXT("CollectibleItem is nullptr"));
		return;
	}

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
		if (CollectibleItem->GetItemName() == EventData->ItemName &&
			EventName == EventData->EventClass)
		{
			CollectibleItem->StartActions(EventData->Actions);
			break;
		}
	}
}
