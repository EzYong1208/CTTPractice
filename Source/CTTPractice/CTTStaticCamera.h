// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Camera/CameraComponent.h"
#include "CTTPractice/CTTStruct.h"
#include "CTTStaticCamera.generated.h"

/**
 * 
 */
UCLASS()
class CTTPRACTICE_API ACTTStaticCamera : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ACTTStaticCamera();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	void SetCameraID(int32 InCamerID);
	void ActivateCamera();

	int32 GetCameraID() const { return CameraID; }

private:
	int32 CameraID = 0;

	UPROPERTY()
    UCameraComponent* CameraComponent;
};
