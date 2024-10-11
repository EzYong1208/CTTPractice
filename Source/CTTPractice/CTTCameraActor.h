// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraActor.h"
#include "CTTCameraActor.generated.h"

/**
 * 
 */

class ACharacter;

UCLASS(Blueprintable)
class CTTPRACTICE_API ACTTCameraActor : public ACameraActor
{
	GENERATED_BODY()

public:
	ACTTCameraActor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime);

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	float Speed = 0.f;
};
