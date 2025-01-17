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

void UCTTEventManager::HandleCollisionEvent(ACTTCharacter* Character, AActor* OtherActor)
{
	if (nullptr == Character)
	{
		return;
	}
	if (nullptr == OtherActor)
	{
		return;
	}

	// EzYong TODO : ������ ���̺��� �ش� ������ �̸��� �´� �̺�Ʈ ������ �˻�
	// ���� Ŭ���� �ν��Ͻ� ����(CTTConditionBase) �� ���ǰ˻�
	// �׼� Ŭ���� �ν��Ͻ� ����(CTTActionBase) �� ����

	// EzYong TODO : �켱�� ACTTCollectibleItem�� ��ӹ��� ���͵鸸 ����ϰ� ����
	ACTTCollectibleItem* CollectibleItem = Cast<ACTTCollectibleItem>(OtherActor);
	if (nullptr == CollectibleItem)
	{
		UE_LOG(LogTemp, Error, TEXT("CollectibleItem is nullptr"));
		return;
	}


}

void UCTTEventManager::Test()
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

	// EzYong TODO 
	// �������̸�		/ �׼��̸� / �� ���������̺�
	// coin			addcoin		1
	// coinstack	addcoin		5
	// �� �����ص� ���������̺��� �ε�
	//DatatableManager->GetItemDataTable();



}

