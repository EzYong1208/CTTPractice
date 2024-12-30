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

	// EzYong TODO : NPCActor�Ӹ� �ƴ϶� �ٸ� ���͵鵵 �̷� ���� �ʿ��Ұ� ������ �ٸ� Ŭ�������� �̰� �Ѱ��ؾ��� �� ����.
	TMap<FName, TWeakObjectPtr<AActor>> NPCActorMap;
	TMap<FName, FCTTSpringArmData> NPCActorDataMap;
	static constexpr float CAMERA_BLEND_TIME = 1.f;
};
