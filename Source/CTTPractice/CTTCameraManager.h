// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "CTTCameraManager.generated.h"

/**
 * 
 */

class ACTTStaticCamera;
class ACTTFollowCamera;

UCLASS()
class CTTPRACTICE_API UCTTCameraManager : public UWorldSubsystem
{
	GENERATED_BODY()
	
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

public:
	void InitializeCameras();
	void SwitchToCameraByID(int32 CameraID);
	void SwitchToFollowCamera();
	void SetViewTargetToCamera(AActor* CameraActor);

	TWeakObjectPtr<ACTTFollowCamera> GetFollowCamera() const { return FollowCamera; }

private:
	TWeakObjectPtr<ACTTStaticCamera> FindStaticCameraByID(int32 CameraID) const;

private:
	UPROPERTY()
	TMap<int32, TWeakObjectPtr<ACTTStaticCamera>> StaticCameraMap;

	UPROPERTY()
	TWeakObjectPtr<ACTTFollowCamera> FollowCamera;

	static constexpr float CAMERA_BLEND_TIME = 1.f;
};
