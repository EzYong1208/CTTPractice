// Fill out your copyright notice in the Description page of Project Settings.


#include "CTTPractice/Event/CTTActionBase.h"
#include "CTTPractice/CTTGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "CTTPractice/Managers/CTTEventManager.h"

void UCTTActionBase_AddCoin::Execute_Implementation(AActor* Actor)
{
	UCTTGameInstance* GameInstance = Cast<UCTTGameInstance>(UGameplayStatics::GetGameInstance(this));
	if (!IsValid(GameInstance))
	{
		UE_LOG(LogTemp, Warning, TEXT("GameInstance is InValid"));
		return;
	}

	int32 CurrentCoinCount = GameInstance->GetCoinCount();
	GameInstance->SetCoinCount(CurrentCoinCount + CoinAmount);
}

void UCTTActionBase_AddCoin::InitializeWithActionData(const FCTTActionData& InActionData)
{
	ActionData = InActionData;
	CoinAmount = InActionData.ActionParameter.IntValue;

	UE_LOG(LogTemp, Warning, TEXT("UCTTActionBase_AddCoin InitializeWithActionData called"));
}

void UCTTActionBase_Die::Execute_Implementation(AActor* Actor)
{
	UCTTGameInstance* GameInstance = Cast<UCTTGameInstance>(UGameplayStatics::GetGameInstance(this));
	if (!IsValid(GameInstance))
	{
		UE_LOG(LogTemp, Warning, TEXT("GameInstance is InValid"));
		return;
	}

	UCTTEventManager* EventManager = GameInstance->GetEventManager();
	if (nullptr == EventManager)
	{
		UE_LOG(LogTemp, Error, TEXT("EventManager is nullptr"));
		return;
	}

	EventManager->AddActorToPendingKill(Actor);
}
