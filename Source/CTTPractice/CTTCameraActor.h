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
	void RotateCamera(float InputValue);
	void MoveCameraCloser();
	void MoveCameraAway();
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float InitialSpringArmLength = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float RotationSpeed = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float CameraZoomSpeed = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float MinSpringArmLength = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float MaxSpringArmLength = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float CameraMoveDistance = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TWeakObjectPtr<ACharacter> OwningCharacter;

private:
	FVector OwnerLocation = FVector(0.f, 0.f, 0.f);
	float TargetArmLength = 0.f;
};
