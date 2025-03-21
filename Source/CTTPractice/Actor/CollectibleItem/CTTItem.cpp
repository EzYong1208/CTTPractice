// Fill out your copyright notice in the Description page of Project Settings.


#include "CTTPractice/Actor/CollectibleItem/CTTItem.h"
#include "Components/SphereComponent.h"
#include "CTTPractice/CTTPracticeGameModeBase.h"
#include "CTTPractice/CTTGameInstance.h"
#include "CTTPractice/Managers/CTTDatatableManager.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACTTItem::ACTTItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionSphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphereComponent"));
	SetRootComponent(CollisionSphereComponent);
}

// Called when the game starts or when spawned
void ACTTItem::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACTTItem::PostInitializeComponents()
{
	Super::PostInitializeComponents();

}

// Called every frame
void ACTTItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ACTTPracticeGameModeBase* GameMode = Cast<ACTTPracticeGameModeBase>(UGameplayStatics::GetGameMode(this));
	if (false == IsValid(GameMode))
	{
		UE_LOG(LogTemp, Error, TEXT("GameMode is InValid"));
		return;
	}
	GameMode->MoveActorZAxis(ItemName, DeltaTime);
}

void ACTTItem::InitializeItem(const FCTTItemData& ItemData, int32 CollectIndex)
{
	UMeshComponent* MeshComponent = nullptr;

	if (ItemData.StaticMesh)
	{
		MeshComponent = NewObject<UStaticMeshComponent>(this, UStaticMeshComponent::StaticClass(), TEXT("StaticMeshComponent"));
		if (false == IsValid(MeshComponent))
		{
			UE_LOG(LogTemp, Warning, TEXT("StaticMeshComponent NewObject failed"));
			return;
		}

		UStaticMeshComponent* StaticMeshComponent = Cast<UStaticMeshComponent>(MeshComponent);
		StaticMeshComponent->SetStaticMesh(ItemData.StaticMesh);
	}
	else if (ItemData.SkeletalMesh)
	{
		MeshComponent = NewObject<USkeletalMeshComponent>(this, USkeletalMeshComponent::StaticClass(), TEXT("SkeletalMeshComponent"));
		if (false == IsValid(MeshComponent))
		{
			UE_LOG(LogTemp, Warning, TEXT("SkeletalMeshComponent NewObject failed"));
			return;
		}

		USkeletalMeshComponent* SkeletalMeshComponent = Cast<USkeletalMeshComponent>(MeshComponent);
		SkeletalMeshComponent->SetSkeletalMesh(ItemData.SkeletalMesh);

		if (ItemData.AnimBlueprintClass)
		{
			SkeletalMeshComponent->SetAnimInstanceClass(ItemData.AnimBlueprintClass);
		}
	}

	if (IsValid(MeshComponent))
	{
		MeshComponent->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
		MeshComponent->RegisterComponent();
		MeshComponent->SetRelativeLocation(ItemData.MeshLocation);
		MeshComponent->SetWorldScale3D(ItemData.Scale);
	}

	CollisionSphereComponent->SetSphereRadius(ItemData.SphereRadius);
	FName CollisionTypeName; 
	CollisionTypeName = ChangeItemCollisionTypeEnumToFName(ItemData.CollisionType);
	CollisionSphereComponent->SetCollisionProfileName(CollisionTypeName);

	ItemName = ItemData.ItemName;
	CollisionType = ItemData.CollisionType;
	CollectData = ItemData.CollectData;

	if (ECTTCollisionType::Collectible == ItemData.CollisionType &&
		ECTTCollectType::CollectItem == CollectData.ActionType)
	{
		CollectItemIndex = CollectIndex;
	}
	else
	{
		CollectItemIndex = NON_COLLECTIBLE_ITEM_INDEX;
	}
}

void ACTTItem::DoAction()
{
	UE_LOG(LogTemp, Error, TEXT("ACTTItem DoAction"));
	bIsDead = true;
}

void ACTTItem::HandleDeath()
{
	ACTTPracticeGameModeBase* GameMode = Cast<ACTTPracticeGameModeBase>(UGameplayStatics::GetGameMode(this));
	if (false == IsValid(GameMode))
	{
		UE_LOG(LogTemp, Error, TEXT("GameMode is InValid"));
		return;
	}

	UCTTGameInstance* GameInstance = Cast<UCTTGameInstance>(UGameplayStatics::GetGameInstance(this));
	if (nullptr == GameInstance)
	{
		UE_LOG(LogTemp, Error, TEXT("GameInstance is nullptr"));
		return;
	}

	const FCTTItemSpawnOffsetData* SpawnOffsetData = GameInstance->GetDatatableManager()->GetItemSpawnOffsetData(ItemName);
	if (nullptr != SpawnOffsetData)
	{
		FCTTWorldItemSetupData SpawnData;
		SpawnData.ItemName = SpawnOffsetData->SpawnItemName;
		SpawnData.Position = GetActorLocation() + SpawnOffsetData->SpawnPositionOffset;
		SpawnData.Rotation = GetActorRotation().Euler() + SpawnOffsetData->SpawnRotationOffset;


		GameMode->SpawnItem(SpawnData);
	}

	Destroy();
}

void ACTTItem::CollectAction()
{
	if (bIsDead)
	{
		return;
	}

	UCTTGameInstance* GameInstance = Cast<UCTTGameInstance>(GetGameInstance());
	if (!IsValid(GameInstance))
	{
		return;
	}

	switch (CollectData.ActionType)
	{
	case ECTTCollectType::Coin:
		GameInstance->SetCoinCount(GameInstance->GetCoinCount() + CollectData.IncreaseAmount);
		break;

	case ECTTCollectType::Life:
		GameInstance->SetPlayerLifeCount(GameInstance->GetPlayerLifeCount() + CollectData.IncreaseAmount);
		break;

	case ECTTCollectType::CollectItem:
		if (CollectItemIndex >= 0)
		{
			GameInstance->SetCollectItemStatus(CollectItemIndex, true);
		}
		break;
	}

	Destroy();
}

FName ACTTItem::ChangeItemCollisionTypeEnumToFName(ECTTCollisionType CollisionTypeEnum) const
{
	FName CollisionTypeName;

	switch (CollisionTypeEnum)
	{
	case ECTTCollisionType::Ignore:
		CollisionTypeName = TEXT("Ignore");
		UE_LOG(LogTemp, Warning, TEXT("CollisionTypeName is Ignore"));
		break;

	case ECTTCollisionType::Block:
		CollisionTypeName = TEXT("Block");
		UE_LOG(LogTemp, Warning, TEXT("CollisionTypeName is Block"));
		break;

	case ECTTCollisionType::Interactable:
		CollisionTypeName = TEXT("Interactable");
		UE_LOG(LogTemp, Warning, TEXT("CollisionTypeName is Interactable"));
		break;

	case ECTTCollisionType::Collectible:
		CollisionTypeName = TEXT("Collectible");
		UE_LOG(LogTemp, Warning, TEXT("CollisionTypeName is Collectible"));
		break;

	case ECTTCollisionType::Ladder:
		CollisionTypeName = TEXT("Ladder");
		UE_LOG(LogTemp, Warning, TEXT("CollisionTypeName is Ladder"));
		break;
	}

	return CollisionTypeName;
}
