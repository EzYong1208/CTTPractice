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

UENUM()
enum class ECTTItemCollisionType : uint8
{
	None,
	Ignore,
	Block,
	Interactable,
	Collectible,
	Ladder,
};