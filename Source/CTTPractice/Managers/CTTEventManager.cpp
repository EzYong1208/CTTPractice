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

	// EzYong TODO : 데이터 테이블에서 해당 아이템 이름에 맞는 이벤트 데이터 검색
	// 조건 클래스 인스턴스 생성(CTTConditionBase) 후 조건검사
	// 액션 클래스 인스턴스 생성(CTTActionBase) 후 실행
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

