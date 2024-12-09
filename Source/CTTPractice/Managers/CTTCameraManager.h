// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CTTCameraManager.generated.h"

/**
 * 
 */

class ACTTCharacterFollowCamera;
class ACTTNPCFollowCamera;
class UPostProcessVolume;

UCLASS(Blueprintable)
class CTTPRACTICE_API UCTTCameraManager : public UObject
{
	GENERATED_BODY()
	
public:
	void InitializeCameras();

	void SwitchToFollowCamera();
	void SwitchToNPCCameraByName(FName CameraName);
	
	ACTTCharacterFollowCamera* GetFollowCamera() const { return CharacterFollowCamera; }

private:
	TWeakObjectPtr<ACTTNPCFollowCamera> FindNPCFollowCameraByName(FName CameraName) const;
	void SetViewTargetToCamera(AActor* CameraActor);
	void SpawnNPCFollowCameras();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ACTTCharacterFollowCamera> CharacterFollowCameraClass;

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
    float FadeOutTime = 0.f;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    float FadeInTime = 0.f;

private:
	UPROPERTY()
	ACTTCharacterFollowCamera* CharacterFollowCamera = nullptr;

	// EzYong TODO : npc카메라 1개만
	TMap<FName, TWeakObjectPtr<ACTTNPCFollowCamera>> NPCFollowCameraMap;
	static constexpr float CAMERA_BLEND_TIME = 1.f;
};
