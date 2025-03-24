// Fill out your copyright notice in the Description page of Project Settings.


#include "CTTPractice/Event/CTTActionBase.h"
#include "CTTPractice/CTTGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "CTTPractice/Managers/CTTEventManager.h"
#include "CTTPractice/Actor/CollectibleItem/CTTCollectibleItem.h"

void UCTTActionBase_AddCoin::InitializeWithActionData(const FCTTActionData& InActionData)
{
	CoinAmount = InActionData.ActionParameter.IntValue;

	UE_LOG(LogTemp, Warning, TEXT("UCTTActionBase_AddCoin InitializeWithActionData called"));
}

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

void UCTTActionBase_FillCollectItem::InitializeWithActionData(const FCTTActionData& InActionData)
{
	UE_LOG(LogTemp, Warning, TEXT("UCTTActionBase_FillCollectItem InitializeWithActionData called"));
}

void UCTTActionBase_FillCollectItem::Execute_Implementation(AActor* Actor)
{
	UCTTGameInstance* GameInstance = Cast<UCTTGameInstance>(UGameplayStatics::GetGameInstance(this));
	if (!IsValid(GameInstance))
	{
		UE_LOG(LogTemp, Warning, TEXT("GameInstance is InValid"));
		return;
	}

	ACTTCollectibleItem_CollectItem* Item = Cast<ACTTCollectibleItem_CollectItem>(Actor);
	if (!Item)
	{
		UE_LOG(LogTemp, Warning, TEXT("ACTTCollectibleItem_CollectItem: Invalid Actor"));
		return;
	}

	int32 CollectItemIndex = Item->GetCollectItemIndex();

	GameInstance->SetCollectItemStatus(CollectItemIndex, true);
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

void UCTTActionBase_Rotate::InitializeWithActionData(const FCTTActionData& InActionData)
{
	RotateSpeed = InActionData.ActionParameter.IntValue;
	RotateDuration = InActionData.Duration;

	UE_LOG(LogTemp, Warning, TEXT("UCTTActionBase_Rotate InitializeWithActionData called"));
}

void UCTTActionBase_Rotate::Pause_Implementation(AActor* Actor)
{
	ACTTCollectibleItem* Item = Cast<ACTTCollectibleItem>(Actor);
	if (!Item)
	{
		UE_LOG(LogTemp, Warning, TEXT("UCTTActionBase_Rotate::Stop: Invalid Actor"));
		return;
	}

	Item->SetRotation(0.f, 0.f);
	UE_LOG(LogTemp, Log, TEXT("UCTTActionBase_Rotate: Stopped rotation"));
}

void UCTTActionBase_Rotate::Resume_Implementation(AActor* Actor)
{
	ACTTCollectibleItem* Item = Cast<ACTTCollectibleItem>(Actor);
	if (!Item)
	{
		UE_LOG(LogTemp, Warning, TEXT("UCTTActionBase_Rotate::Stop: Invalid Actor"));
		return;
	}

	Item->SetRotation(RotateSpeed, RotateDuration);
	UE_LOG(LogTemp, Log, TEXT("Rotate Action Resumed"));
}

void UCTTActionBase_Rotate::Execute_Implementation(AActor* Actor)
{
	ACTTCollectibleItem* Item = Cast<ACTTCollectibleItem>(Actor);
	if (!Item)
	{
		UE_LOG(LogTemp, Warning, TEXT("UCTTActionBase_Rotate: Actor is not a CollectibleItem"));
		return;
	}

	Item->SetRotation(RotateSpeed, RotateDuration);
}

void UCTTActionBase_Jump::InitializeWithActionData(const FCTTActionData& InActionData)
{
	JumpSpeed = InActionData.ActionParameter.IntValue;

	UE_LOG(LogTemp, Warning, TEXT("UCTTActionBase_Jump InitializeWithActionData called"));
}

void UCTTActionBase_Jump::Execute_Implementation(AActor* Actor)
{
	ACTTCollectibleItem* Item = Cast<ACTTCollectibleItem>(Actor);
	if (!Item)
	{
		UE_LOG(LogTemp, Error, TEXT("UCTTActionBase_Jump: Actor is not a CollectibleItem!"));
		return;
	}

	Item->SetJump(JumpSpeed);
}
