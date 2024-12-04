// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CheatManager.h"
#include "CTTCheatManager.generated.h"

/**
 * 
 */

UCLASS(Blueprintable)
class CTTPRACTICE_API UCTTCheatManager : public UCheatManager
{
	GENERATED_BODY()

	UFUNCTION(exec)
	void SetPlayerLife(int32 Life);

	UFUNCTION(exec)
	void SetCoin(int32 Coin);

	UFUNCTION(exec)
	void SetCollectItem(int32 Index, bool bEnable);

	UFUNCTION(exec)
	void SwitchToFollowCamera();

	UFUNCTION(exec)
	void SwitchToNPCCameraByName(FName CameraName);

	UFUNCTION(exec)
	void ShowUIGroup(FName GroupName);

	UFUNCTION(exec)
	void HideUIGroup(FName GroupName);
};
