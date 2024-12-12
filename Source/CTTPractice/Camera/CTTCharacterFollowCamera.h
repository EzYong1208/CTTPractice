// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CTTPractice/Camera/CTTFollowCamera.h"
#include "CTTCharacterFollowCamera.generated.h"

/**
 * 
 */
UCLASS()
class CTTPRACTICE_API ACTTCharacterFollowCamera : public ACTTFollowCamera
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ACTTCharacterFollowCamera();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	void CameraMovement(float DeltaTime);
	void RotateCamera(float InputValue);
	void MoveCameraCloser();
	void MoveCameraAway();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ACTTCharacter> TargetCharacterClass;
};
