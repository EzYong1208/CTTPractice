// Copyright Epic Games, Inc. All Rights Reserved.


#include "CTTPracticeGameModeBase.h"
#include "CTTPractice/UI/CTTUICommonResource.h"
#include "CTTPractice/CTTItem.h"

void ACTTPracticeGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	// 유저정보 만들기 전까지 임시 [8/17/2024 EzYong-Laptop]
	PlayerLifeCount = PlayerInitialLifeCount;
	CoinCount = CoinInitialLifeCount;

	CollectItemStates.SetNum(COLLECTITEM_NUMBER);
	for (int32 i = 0; i < CollectItemStates.Num(); ++i)
	{
		CollectItemStates[i] = CollectItemInitialState;
	}

	if (IsValid(UICommonResourceClass))
	{
		UICommonResource = NewObject<UCTTUICommonResource>(this, UICommonResourceClass);
	}


	// TODO : 아이템 스폰
	TArray<FName> RowNames = ItemSpawnDataTable->GetRowNames();
	for (const FName& RowName : RowNames)
	{
		FCTTItemSpawnData* SpawnData = ItemSpawnDataTable->FindRow<FCTTItemSpawnData>(RowName, TEXT(""));
		if (SpawnData)
		{
			SpawnItem(*SpawnData);
		}
	}
}

void ACTTPracticeGameModeBase::SetPlayerLifeCount(int32 InPlayerLifeCount)
{
	PlayerLifeCount = InPlayerLifeCount;
	if (OnChangePlayerLifeCountDelegate.IsBound())
	{
		OnChangePlayerLifeCountDelegate.Broadcast(PlayerLifeCount);
	}
}

void ACTTPracticeGameModeBase::SetCoinCount(int32 InCoinCount)
{
	CoinCount = InCoinCount;
	if (OnChangeCoinCountDelegate.IsBound())
	{
		OnChangeCoinCountDelegate.Broadcast(CoinCount);
	}
}

void ACTTPracticeGameModeBase::SetCollectItemStatus(int32 InIndex, bool bInEnable)
{
	if (!(InIndex >= 0 && InIndex < CollectItemStates.Num()))
	{
		return;
	}

	CollectItemStates[InIndex] = bInEnable;
	if (OnChangeCollectItemDelegate.IsBound())
	{
		OnChangeCollectItemDelegate.Broadcast(InIndex, CollectItemStates[InIndex]);
	}
}

void ACTTPracticeGameModeBase::SpawnItem(const FCTTItemSpawnData& SpawnData)
{
	FCTTItemData* ItemData = ItemDataTable->FindRow<FCTTItemData>(SpawnData.ItemName, TEXT(""));
	if (ItemData == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("ItemData for '%s' is nullptr"), *SpawnData.ItemName.ToString());
		return;
	}

	FRotator SpawnRotation = FRotator::MakeFromEuler(SpawnData.Rotation);
	ACTTItem* NewItem = GetWorld()->SpawnActor<ACTTItem>(ACTTItem::StaticClass(), SpawnData.Position, SpawnRotation);
	if (!IsValid(NewItem))
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to spawn ACTTItem"));
		return;
	}

	NewItem->InitializeItem(*ItemData);
}
