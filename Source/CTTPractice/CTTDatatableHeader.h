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

// EzYong TODO : CollectItem �ϼ� �� �����ϱ�
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
class UCTTConditionBase;

USTRUCT(BlueprintType)
struct FCTTParameter
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ECTTParameterType ParameterType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "ParameterType == ECTTParameterType::Int", EditConditionHides))
	int32 IntValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "ParameterType == ECTTParameterType::Float", EditConditionHides))
	float FloatValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "ParameterType == ECTTParameterType::Bool", EditConditionHides))
	bool BoolValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "ParameterType == ECTTParameterType::Name"/*, EditConditionHides*/))
	FName NameValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "ParameterType == ECTTParameterType::Actor", EditConditionHides))
    TSubclassOf<AActor> ActorClass;

	// meta = (EditCondition = "���ǽ�")
	// EditCondition�� Ư�� ������ true �϶��� �ش� ������Ƽ�� Ȱ��ȭ(���� ����) �ϰų� ǥ���ϵ��� �����ϴ� ��Ÿ �±�
	// EditConditionHides�� EditCondition�� �Բ� ���, ������ ������ ��� �ش� ������Ƽ�� ������ ����
	// EditConditionHides�� ������ ������ ������ ��� ������ �����, ������ �ش� ������Ƽ�� ��Ȱ��ȭ�� ���·� ����
};

USTRUCT(BlueprintType)
struct FCTTActionData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UCTTActionBase> ActionClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FCTTParameter ActionParameter;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float StartTime;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Duration;
};

USTRUCT(BlueprintType)
struct FCTTEventActionData : public FTableRowBase
{
    GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ItemName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName EventName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UCTTConditionBase> ConditionClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FCTTParameter ConditionParameter;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FCTTActionData> Actions;
};