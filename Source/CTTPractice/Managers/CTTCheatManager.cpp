// Copyright Epic Games, Inc. All Rights Reserved.


#include "CTTCheatManager.h"
#include "CTTPractice/CTTPracticeGameModeBase.h"
#include "Kismet/GameplayStatics.h"


void UCTTCheatManager::SetPlayerLife(int32 Life)
{
	ACTTPracticeGameModeBase* GameMode = Cast<ACTTPracticeGameModeBase>(UGameplayStatics::GetGameMode(this));
	if (!IsValid(GameMode))
	{
		UE_LOG(LogTemp, Warning, TEXT("GameMode is InValid"));
		return;
	}

	GameMode->SetPlayerLifeCount(Life);
}

void UCTTCheatManager::SetCoin(int32 Coin)
{
	ACTTPracticeGameModeBase* GameMode = Cast<ACTTPracticeGameModeBase>(UGameplayStatics::GetGameMode(this));
	if (!IsValid(GameMode))
	{
		UE_LOG(LogTemp, Warning, TEXT("GameMode is InValid"));
		return;
	}

	GameMode->SetCoinCount(Coin);
}

void UCTTCheatManager::SetCollectItem(int32 Index, bool bEnable)
{
	ACTTPracticeGameModeBase* GameMode = Cast<ACTTPracticeGameModeBase>(UGameplayStatics::GetGameMode(this));
	if (!IsValid(GameMode))
	{
		UE_LOG(LogTemp, Warning, TEXT("GameMode is InValid"));
		return;
	}

	GameMode->SetCollectItemStatus(Index, bEnable);
}
