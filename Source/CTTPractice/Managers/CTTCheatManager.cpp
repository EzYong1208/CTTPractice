// Copyright Epic Games, Inc. All Rights Reserved.


#include "CTTCheatManager.h"
#include "CTTPractice/CTTGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"


void UCTTCheatManager::SetPlayerLife(int32 Life)
{
	UCTTGameInstance* GameInstance = Cast<UCTTGameInstance>(UGameplayStatics::GetGameInstance(this));
	if (!IsValid(GameInstance))
	{
		UE_LOG(LogTemp, Warning, TEXT("GameInstance is InValid"));
		return;
	}

	GameInstance->SetPlayerLifeCount(Life);
}

void UCTTCheatManager::SetCoin(int32 Coin)
{
	UCTTGameInstance* GameInstance = Cast<UCTTGameInstance>(UGameplayStatics::GetGameInstance(this));
	if (!IsValid(GameInstance))
	{
		UE_LOG(LogTemp, Warning, TEXT("GameInstance is InValid"));
		return;
	}

	GameInstance->SetCoinCount(Coin);
}

void UCTTCheatManager::SetCollectItem(int32 Index, bool bEnable)
{
	UCTTGameInstance* GameInstance = Cast<UCTTGameInstance>(UGameplayStatics::GetGameInstance(this));
	if (!IsValid(GameInstance))
	{
		UE_LOG(LogTemp, Warning, TEXT("GameInstance is InValid"));
		return;
	}

	GameInstance->SetCollectItemStatus(Index, bEnable);
}
