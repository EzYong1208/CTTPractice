// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CTTPractice/CTTDatatableHeader.h"
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
	void SwitchToNPCCameraByName(FName NPCName);
	
	ACTTCharacterFollowCamera* GetCharacterFollowCamera() const;

private:
	void LoadNPCActorData();
	const FCTTSpringArmData* GetNPCActorData(const FName& RowName) const;
	void SetViewTargetToCamera(AActor* CameraActor);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ACTTCharacterFollowCamera> CharacterFollowCameraClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ACTTNPCFollowCamera> NPCFollowCameraClass;

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
    float FadeOutTime = 0.f;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    float FadeInTime = 0.f;

private:
	UPROPERTY()
	ACTTCharacterFollowCamera* CharacterFollowCamera = nullptr;

	UPROPERTY()
	ACTTNPCFollowCamera* NPCFollowCamera = nullptr;

	// EzYong TODO : NPCActor뿐만 아니라 다른 액터들도 이런 맵이 필요할거 같은데 다른 클래스에서 이걸 총괄해야할 것 같음.
	TMap<FName, TWeakObjectPtr<AActor>> NPCActorMap;
	TMap<FName, FCTTSpringArmData> NPCActorDataMap;
	static constexpr float CAMERA_BLEND_TIME = 1.f;
};
