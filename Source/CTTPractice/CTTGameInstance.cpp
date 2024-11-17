// Fill out your copyright notice in the Description page of Project Settings.


#include "CTTGameInstance.h"
#include "CTTCameraManager.h"

void UCTTGameInstance::Init()
{
    Super::Init();
    
}

void UCTTGameInstance::SetPlayerLifeCount(int32 InPlayerLifeCount)
{
    PlayerLifeCount = InPlayerLifeCount;
    if (OnChangePlayerLifeCountDelegate.IsBound())
	{
		OnChangePlayerLifeCountDelegate.Broadcast(PlayerLifeCount);
	}
}

void UCTTGameInstance::SetCoinCount(int32 InCoinCount)
{
    CoinCount = InCoinCount;
	if (OnChangeCoinCountDelegate.IsBound())
	{
		OnChangeCoinCountDelegate.Broadcast(CoinCount);
	}
}

void UCTTGameInstance::SetCollectItemStatus(int32 InIndex, bool bInEnable)
{
	if (!(InIndex >= 0 && InIndex < CollectItemStates.Num()))
	{
		return;
	}

	CollectItemStates[InIndex] = bInEnable;
	if (OnChangeCollectItemDelegate.IsBound())
	{
		OnChangeCollectItemDelegate.Broadcast(InIndex, CollectItemStates[InIndex]);
	}
}

void UCTTGameInstance::InitializeManagers()
{
	if (IsValid(CameraManagerClass))
	{
		CameraManagerInstance = NewObject<UCTTCameraManager>(this, CameraManagerClass);
		CameraManagerInstance->InitializeCameras();
	}
}

void UCTTGameInstance::InitializeCollectItem(int32 CollectItemNumber, bool CollectItemInitialState)
{
	CollectItemStates.SetNum(CollectItemNumber);
	for (int32 i = 0; i < CollectItemStates.Num(); ++i)
	{
		CollectItemStates[i] = CollectItemInitialState;
	}
}
