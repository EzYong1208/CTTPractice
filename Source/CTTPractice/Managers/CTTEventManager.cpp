// Fill out your copyright notice in the Description page of Project Settings.


#include "CTTPractice/Managers/CTTEventManager.h"
#include "CTTPractice/Event/CTTActionBase.h"
#include "CTTPractice/Event/CTTConditionBase.h"
#include "Kismet/GameplayStatics.h"
#include "CTTPractice/CTTGameInstance.h"
#include "CTTPractice/Managers/CTTDatatableManager.h"

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

