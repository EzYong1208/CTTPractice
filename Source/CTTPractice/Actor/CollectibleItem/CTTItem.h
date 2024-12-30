// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CTTPractice/CTTDatatableHeader.h"
#include "CTTItem.generated.h"

class USkeletalMesh;
class UStaticMesh;
class USphereComponent;

UCLASS()
class CTTPRACTICE_API ACTTItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACTTItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	void InitializeItem(const FCTTItemData& ItemData, int32 CollectIndex);

	FName GetItemName() const { return ItemName; }
	bool CheckItemDead() const { return bIsDead; }
	ECTTCollisionType GetCollisionType() const { return CollisionType; }
	int32 GetCollectItemIndex() const { return CollectItemIndex; }

	void DoAction();
	void HandleDeath();
	void CollectAction();

public:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	bool bIsDead = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UDataTable* ItemSpawnOffsetDataTable;

private:
	FName ChangeItemCollisionTypeEnumToFName(ECTTCollisionType CollisionTypeEnum) const;

private:
	UPROPERTY()
	USphereComponent* CollisionSphereComponent;

	FName ItemName;
	int32 CollectItemIndex = 0;
	ECTTCollisionType CollisionType;
	FCTTCollectData CollectData;

	static constexpr int32 NON_COLLECTIBLE_ITEM_INDEX = -1;
};
