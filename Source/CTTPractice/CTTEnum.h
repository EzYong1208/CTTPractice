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
	MAX
};

UENUM()
enum class ECTTCollisionType : uint8
{
	None,
	Buff,
	Projectile,
	Ignore,
	Interactable,
	Collectible,
	Ladder,
	Map,
	Block,
	HardBlock,
	MAX
};

UENUM()
enum class ECTTCollectType : uint8
{
    None,
    Coin,
    Life,
    CollectItem,
	Weapon,
	MAX
};

UENUM()
enum class ECTTProjectileState : uint8
{
    None,
	Attached,
	Move,
	Destroy,
	MAX
};

UENUM()
enum class ECTTParameterType : uint8
{
	None,
	Int,
	Float,
	Bool,
	Name,
	Actor,
	MAX
};

UENUM()
enum class ECTTActionType : uint8
{
	None,
	SpawnActor,
	AddCoin,
	FillCollectItem,
	Die,
	Rotate,
	Jump,
	MAX
};