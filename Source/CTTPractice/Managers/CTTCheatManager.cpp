// Copyright Epic Games, Inc. All Rights Reserved.


#include "CTTCheatManager.h"
#include "CTTPractice/CTTPracticeGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "CTTPractice/CTTItem.h"
#include "Engine/World.h"


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

void UCTTCheatManager::SpawnItem(FName ItemName)
{
	// TODO : ������ ���̺� �ε� (�ӽ÷� ��� ���� �Է�)
	UDataTable* ItemDataTable = LoadObject<UDataTable>(nullptr, TEXT("/Game/Table/ItemDataTable.ItemDataTable"));

	FCTTItemData* ItemData = ItemDataTable->FindRow<FCTTItemData>(ItemName, TEXT(""));

	if (nullptr == ItemData)
	{
		UE_LOG(LogTemp, Warning, TEXT("ItemData is nullptr"));
		return;
	}

	// TODO : ������ ��� ���� (�ӽ÷� ��� ���� �Է�)
	FVector Location = FVector(100.f, 100.0f, 100.0f);

	// ������ ����
	ACTTItem* NewItem = GetWorld()->SpawnActor<ACTTItem>(ACTTItem::StaticClass(), Location, FRotator::ZeroRotator);
	if (!IsValid(NewItem))
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to spawn ACTTItem"));
		return;
	}

	NewItem->InitializeItem(*ItemData);
}
