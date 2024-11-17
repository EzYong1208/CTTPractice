// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CTTNPCActor.generated.h"

class ACTTNPCFollowCamera;

UCLASS()
class CTTPRACTICE_API ACTTNPCActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACTTNPCActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	FName GetNPCName() const { return NPCName; }

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ACTTNPCFollowCamera> NPCFollowCameraClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName NPCName;

private:
	UPROPERTY()
	ACTTNPCFollowCamera* NPCFollowCamera = nullptr;
};
