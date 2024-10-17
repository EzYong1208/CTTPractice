// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CTTPractice/CTTStruct.h"
#include "GameFramework/Actor.h"
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

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	void InitializeItem(const FCTTItemData& ItemData);

private:
	UPROPERTY()
	USphereComponent* CollisionSphereComponent;
};
