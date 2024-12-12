// Copyright Epic Games, Inc. All Rights Reserved.


#include "CTTPracticeGameModeBase.h"
#include "CTTPractice/UI/CTTUICommonResource.h"
#include "CTTPractice/CTTItem.h"
#include "CTTPractice/CTTCharacter.h"
#include "CTTPractice/CTTGameInstance.h"
#include "CTTPractice/Managers/CTTDatatableManager.h"
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
		GameInstance->InitializeManagers();

		GameInstance->SetPlayerLifeCount(PlayerInitialLifeCount);
		GameInstance->SetCoinCount(CoinInitialCount);
		GameInstance->InitializeCollectItem(CollectItemNumber, CollectItemInitialState);
	}

	// EzYong TODO : 아이템 스폰
	TArray<const FCTTWorldItemSetupData*> ItemRows = GameInstance->GetDatatableManager()->GetWorldItemSetupRows();
	for (const FCTTWorldItemSetupData* RowData : ItemRows)
	{
		if (RowData)
		{
			SpawnItem(*RowData);
		}
	}

	TArray<const FCTTSwitchMovementData*> SwitchRows = GameInstance->GetDatatableManager()->GetSwitchMovementRows();
	for (const FCTTSwitchMovementData* RowData : SwitchRows)
	{
		if (RowData)
		{
			SwitchMovementDataMap.FindOrAdd(RowData->TriggerItemName).Add(RowData->ActorName, RowData->TargetLocation);
		}
	}
}

void ACTTPracticeGameModeBase::SpawnItem(const FCTTWorldItemSetupData& SpawnData)
{
	UCTTGameInstance* GameInstance = Cast<UCTTGameInstance>(UGameplayStatics::GetGameInstance(this));
	if (nullptr == GameInstance)
	{
		UE_LOG(LogTemp, Error, TEXT("GameInstance is nullptr"));
		return;
	}

	const UDataTable* ItemDataTable = GameInstance->GetDatatableManager()->GetItemDataTable();
	if (nullptr == ItemDataTable)
	{
		UE_LOG(LogTemp, Error, TEXT("ItemDataTable is nullptr"));
		return;
	}

	TArray<FName> RowNames = ItemDataTable->GetRowNames();
	int32 CollectIndex = 0;

	for (const FName& RowName : RowNames)
	{
		FCTTItemData* ItemData = ItemDataTable->FindRow<FCTTItemData>(RowName, TEXT(""));
		if (ItemData && SpawnData.ItemName == ItemData->ItemName)
		{
			FRotator SpawnRotation = FRotator::MakeFromEuler(SpawnData.Rotation);
			ACTTItem* NewItem = GetWorld()->SpawnActor<ACTTItem>(ACTTItem::StaticClass(), SpawnData.Position, SpawnRotation);
			if (!IsValid(NewItem))
			{
				UE_LOG(LogTemp, Error, TEXT("Failed to spawn ACTTItem"));
				return;
			}

			CollectIndex = GameInstance->GetNextCollectItemStatusIndex();
			NewItem->InitializeItem(*ItemData, CollectIndex);

			//if (ItemData->bIsWeapon)
			//{
			//	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
			//	if (IsValid(PlayerController))
			//	{
			//		ACTTCharacter* Character = Cast<ACTTCharacter>(PlayerController->GetCharacter());
			//		if (IsValid(Character))
			//		{
			//			NewItem->AttachToComponent(Character->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, SOCKETNAME_WEAPON);
			//		}
			//	}
			//}

			break;
		}
	}
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
