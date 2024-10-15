// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameFramework/Actor.h"
#include "CTTItem.generated.h"

class USkeletalMesh;
class UStaticMesh;
class USphereComponent;

USTRUCT(BlueprintType)
struct CTTPRACTICE_API FCTTItemData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMesh* StaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMesh* SkeletalMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<UAnimInstance> AnimBlueprintClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SphereRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector MeshLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Scale = FVector(1.f, 1.f, 1.f);
};

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

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	void InitializeItem(const FCTTItemData& ItemData);

private:
	UPROPERTY()
	USphereComponent* CollisionSphereComponent;
};
