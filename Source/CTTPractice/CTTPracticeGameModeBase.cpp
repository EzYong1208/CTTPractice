// Copyright Epic Games, Inc. All Rights Reserved.


#include "CTTPracticeGameModeBase.h"
#include "CTTPractice/UI/CTTUICommonResource.h"
#include "CTTPractice/CTTItem.h"
#include "EngineUtils.h" 

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
	TArray<FName> ItemNames = WorldItemSetupDataTable->GetRowNames();
	for (const FName& RowName : ItemNames)
	{
		FCTTWorldItemSetupData* SpawnData = WorldItemSetupDataTable->FindRow<FCTTWorldItemSetupData>(RowName, TEXT(""));
		if (SpawnData)
		{
			SpawnItem(*SpawnData);
		}
	}

	TArray<FName> SwitchNames = SwitchMovementDataTable->GetRowNames();
	for (int32 i = 0; i < SwitchNames.Num(); ++i)
	{
		FCTTSwitchMovementData* SwitchMovementData = SwitchMovementDataTable->FindRow<FCTTSwitchMovementData>(SwitchNames[i], TEXT(""));
		if (SwitchMovementData)
		{
			SwitchMovementDataMap.FindOrAdd(SwitchMovementData->TriggerItemName).Add(SwitchMovementData->ActorName, SwitchMovementData->TargetLocation);
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

void ACTTPracticeGameModeBase::SpawnItem(const FCTTWorldItemSetupData& SpawnData)
{
	TArray<FName> RowNames = ItemDataTable->GetRowNames();
	for (const FName& RowName : RowNames)
	{
		FCTTItemData* ItemData = ItemDataTable->FindRow<FCTTItemData>(RowName, TEXT(""));
		if (SpawnData.ItemName == ItemData->ItemName)
		{
			FRotator SpawnRotation = FRotator::MakeFromEuler(SpawnData.Rotation);
			ACTTItem* NewItem = GetWorld()->SpawnActor<ACTTItem>(ACTTItem::StaticClass(), SpawnData.Position, SpawnRotation);
			if (!IsValid(NewItem))
			{
				UE_LOG(LogTemp, Error, TEXT("Failed to spawn ACTTItem"));
				return;
			}

			NewItem->InitializeItem(*ItemData);
			break;
		}
	}
}

FCTTItemSpawnOffsetData* ACTTPracticeGameModeBase::GetItemSpawnOffsetData(const FName& ItemName) const
{
	if (!IsValid(ItemSpawnOffsetDataTable))
	{
		UE_LOG(LogTemp, Error, TEXT("ItemSpawnOffsetDataTable is InValid"));
		return nullptr;
	}

	TArray<FName> RowNames = ItemSpawnOffsetDataTable->GetRowNames();
	for (const FName& RowName : RowNames)
	{
		FCTTItemSpawnOffsetData* SpawnOffsetData = ItemSpawnOffsetDataTable->FindRow<FCTTItemSpawnOffsetData>(RowName, TEXT(""));
		if (ItemName == SpawnOffsetData->ItemName)
		{
			return SpawnOffsetData;
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("There is no item to spawn"));
	return nullptr;
}

void ACTTPracticeGameModeBase::MoveActorZAxis(const FName& SwitchName, float DeltaTime)
{
	TMap<FName, FVector>* MovementDataMapPtr = SwitchMovementDataMap.Find(SwitchName);
	if (!MovementDataMapPtr)
	{
		UE_LOG(LogTemp, Warning, TEXT("No movement data found for SwitchName: %s"), *SwitchName.ToString());
		return;
	}

	TMap<FName, FVector>& ActorLocationMap = *MovementDataMapPtr;

	for (const auto& ActorEntry : ActorLocationMap)
	{
		const FName& ActorName = ActorEntry.Key;
		FVector TargetLocation = ActorEntry.Value;

		AActor* TargetActor = nullptr;
		for (TActorIterator<AActor> Iter(GetWorld()); Iter; ++Iter)
		{
			FName WorldActorName;
			WorldActorName = Iter->GetFName();

			if (Iter->GetFName() == ActorName)
			{
				TargetActor = *Iter;
				break;
			}
		}

		FVector CurrentLocation = TargetActor->GetActorLocation();

		if (CurrentLocation.Z >= TargetLocation.Z)
		{
			continue;
		}

		CurrentLocation.Z += SwitchMovementSpeed * DeltaTime;
		if (CurrentLocation.Z > TargetLocation.Z)
		{
			CurrentLocation.Z = TargetLocation.Z;
		}

		TargetActor->SetActorLocation(CurrentLocation);
	}
}
