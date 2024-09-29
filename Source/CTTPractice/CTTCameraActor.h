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

public:
	void InitializeCameraComponents();

	void CameraMovement(float DeltaTime);
	void RotateCameraLeft();
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	FRotator InitialCameraRotation = FRotator(0.f, 0.f, 0.f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float RotationSpeed = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float CameraRotationAngle = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ACharacter* OwningCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float CameraDistance = 0.f;

private:
	FVector OwnerLocation = FVector(0.f, 0.f, 0.f);
	FRotator GoalRotation = FRotator(0.f, 0.f, 0.f);
};
