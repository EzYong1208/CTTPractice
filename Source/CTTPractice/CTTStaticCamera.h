// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraActor.h"
#include "CTTStaticCamera.generated.h"

/**
 * 
 */
UCLASS()
class CTTPRACTICE_API ACTTStaticCamera : public ACameraActor
{
	GENERATED_BODY()
	
public:
	ACTTStaticCamera();

protected:
	virtual void BeginPlay() override;

public:
	void ActivateCamera();

	int32 GetCameraID() const { return CameraID; }

private:
	int32 CameraID = 0;
};
