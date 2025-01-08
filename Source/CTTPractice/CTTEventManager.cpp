// Fill out your copyright notice in the Description page of Project Settings.


#include "CTTEventManager.h"
#include "CTTActionBase.h"
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
	// 아이템이름		/ 액션이름 / 값 데이터테이블
	// coin			addcoin		1
	// coinstack	addcoin		5
	// 를 정리해둔 데이터테이블을 로드
	//DatatableManager->GetItemDataTable();



}

