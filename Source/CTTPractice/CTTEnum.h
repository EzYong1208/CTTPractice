// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CTTEnum.generated.h"

/**
 * 
 */


UENUM()
enum class ECTTNumberImageType : uint8
{
	None,
	PlayerLifeNumber,
	CoinNumber,
};

UENUM(BlueprintType)
enum class ECTTFaceType : uint8
{
	None,
	General,
	Smile,
	Happy,
	Ecstatic,
	Gloomy,
	Surprised,
	Astonished,
};