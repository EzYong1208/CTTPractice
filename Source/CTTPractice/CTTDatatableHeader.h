// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Components/SlateWrapperTypes.h"
#include "CTTPractice/CTTEnum.h"
#include "CTTDatatableHeader.generated.h"

/**
 * 
 */

// EzYong TODO : CollectItem 완성 후 수정하기
USTRUCT(BlueprintType)
struct CTTPRACTICE_API FCTTCollectData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ECTTCollectType ActionType = ECTTCollectType::None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 IncreaseAmount = 0;
};

USTRUCT(BlueprintType)
struct CTTPRACTICE_API FCTTSocketMeshData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName AnimationName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName SocketName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMesh* Mesh;
};

USTRUCT(BlueprintType)
struct CTTPRACTICE_API FCTTItemData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMesh* StaticMesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMesh* SkeletalMesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<UAnimInstance> AnimBlueprintClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SphereRadius = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector MeshLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Scale = FVector(1.f, 1.f, 1.f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ECTTCollisionType CollisionType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsWeapon = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FCTTCollectData CollectData;
};

USTRUCT(BlueprintType)
struct CTTPRACTICE_API FCTTWorldItemSetupData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Position;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Rotation;
};

USTRUCT(BlueprintType)
struct CTTPRACTICE_API FCTTItemSpawnOffsetData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName SpawnItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector SpawnPositionOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector SpawnRotationOffset;
};

USTRUCT(BlueprintType)
struct CTTPRACTICE_API FCTTSwitchMovementData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName TriggerItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ActorName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector TargetLocation;
};

USTRUCT(BlueprintType)
struct CTTPRACTICE_API FCTTProjectileData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMesh* SkeletalMesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<UAnimInstance> AnimBlueprintClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector MeshLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector PositionOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector RotationOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SphereRadius = 0.f;

};

USTRUCT(BlueprintType)
struct CTTPRACTICE_API FCTTQuestData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName QuestName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 GoalCount = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CurrentProgress = 0;
};

USTRUCT(BlueprintType)
struct CTTPRACTICE_API FCTTSpringArmData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SpringArmLength = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FRotator SpringArmRotation;
};

class UCTTActionBase;

USTRUCT(BlueprintType)
struct FCTTCollectibleActionData : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName CollectibleItemName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<UCTTActionBase> ActionClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Number;
};