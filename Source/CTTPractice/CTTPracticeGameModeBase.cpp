// Copyright Epic Games, Inc. All Rights Reserved.


#include "CTTPracticeGameModeBase.h"
#include "CTTPractice/UI/CTTUICommonResource.h"
#include "CTTPractice/CTTItem.h"
#include "CTTPractice/CTTCharacter.h"
#include "CTTPractice/CTTGameInstance.h"
#include "EngineUtils.h" 
#include "Kismet/GameplayStatics.h"

void ACTTPracticeGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(UICommonResourceClass))
	{
		UICommonResource = NewObject<UCTTUICommonResource>(this, UICommonResourceClass);
	}

	UCTTGameInstance* GameInstance = Cast<UCTTGameInstance>(UGameplayStatics::GetGameInstance(this));
	if (GameInstance)
	{
		GameInstance->SetPlayerLifeCount(PlayerInitialLifeCount);
		GameInstance->SetCoinCount(CoinInitialLifeCount);
		GameInstance->InitializeCollectItem(CollectItemNumber, CollectItemInitialState);
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

void ACTTPracticeGameModeBase::SpawnItem(const FCTTWorldItemSetupData& SpawnData)
{
	TArray<FName> RowNames = ItemDataTable->GetRowNames();
	int32 CollectIndex = 0;
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

			UCTTGameInstance* GameInstance = Cast<UCTTGameInstance>(GetGameInstance());
			if (GameInstance)
			{
				CollectIndex = GameInstance->GetNextCollectItemStatusIndex();
			}

			NewItem->InitializeItem(*ItemData, CollectIndex);

			if (ItemData->bIsWeapon)
			{
				APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
				if (true == IsValid(PlayerController))
				{
					ACTTCharacter* Character = Cast<ACTTCharacter>(PlayerController->GetCharacter());
					if (IsValid(Character))
					{
						NewItem->AttachToComponent(Character->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, SOCKETNAME_WEAPON);
					}
				}
			}

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

		if (nullptr == TargetActor)
		{
			break;
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
