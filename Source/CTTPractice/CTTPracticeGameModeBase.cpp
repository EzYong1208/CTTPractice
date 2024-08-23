// Copyright Epic Games, Inc. All Rights Reserved.


#include "CTTPracticeGameModeBase.h"
#include "CTTPractice/UI/CTTUICommonResource.h"


void ACTTPracticeGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	// 유저정보 만들기 전까지 임시 [8/17/2024 EzYong-Laptop]
	PlayerLifeCount = PlayerInitialLifeCount;
	CoinCount = CoinInitialLifeCount;
	CollectItemState = CollectItemInitialState;

	if (IsValid(UICommonResourceClass))
	{
		UICommonResource = NewObject<UCTTUICommonResource>(this, UICommonResourceClass);
	}

}

void ACTTPracticeGameModeBase::SetPlayerLifeCount(int32 InPlayerLifeCount)
{
	PlayerLifeCount = InPlayerLifeCount;
	if (OnChangePlayerLifeCountDelegate.IsBound())
	{
		OnChangePlayerLifeCountDelegate.Broadcast(PlayerLifeCount);
	}
}

void ACTTPracticeGameModeBase::SetCoinCount(int32 InCoinCount)
{
	CoinCount = InCoinCount;
	if (OnChangeCoinCountDelegate.IsBound())
	{
		OnChangeCoinCountDelegate.Broadcast(CoinCount);
	}
}

void ACTTPracticeGameModeBase::SetCollectItemStatus(int32 InIndex, bool bInEnable)
{
	if (OnChangeCollectItemDelegate.IsBound())
	{
		OnChangeCollectItemDelegate.Broadcast(InIndex, bInEnable);
	}
}
