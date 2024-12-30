// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CTTPractice/CTTEnum.h"
#include "CTTMapObject.generated.h"

UCLASS()
class CTTPRACTICE_API ACTTMapObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACTTMapObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	void HandleCollisionEvent(ECTTCollisionType InCollisionType);

public:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	ECTTCollisionType CollisionType = ECTTCollisionType::None;
};
