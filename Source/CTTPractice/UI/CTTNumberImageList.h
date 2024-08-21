// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CTTNumberImageList.generated.h"

/**
 * 
 */

class UTexture2D;

USTRUCT(BlueprintType)
struct CTTPRACTICE_API FCTTNumberImageList
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UTexture2D*> Images;
};
