// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CTTPractice/Actor/Camera/CTTFollowCamera.h"
#include "CTTNPCFollowCamera.generated.h"

UCLASS()
class CTTPRACTICE_API ACTTNPCFollowCamera : public ACTTFollowCamera
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACTTNPCFollowCamera();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
