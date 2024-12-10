// Fill out your copyright notice in the Description page of Project Settings.


#include "CTTGameInstance.h"
#include "CTTPractice/Managers/CTTCameraManager.h"
#include "CTTPractice/Managers/CTTDatatableManager.h"
#include "CTTPractice/Managers/CTTUIManager.h"
#include "CTTPractice/Managers/CTTQuestManager.h"

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

	if (IsValid(DatatableManagerClass))
	{
		DatatableManagerInstance = NewObject<UCTTDatatableManager>(this, DatatableManagerClass);
	}

	if (IsValid(UIManagerClass))
	{
		UIManagerInstance = NewObject<UCTTUIManager>(this, UIManagerClass);
		UIManagerInstance->InitializeUIManager();
	}

	if (IsValid(QuestManagerClass))
	{
		QuestManagerInstance = NewObject<UCTTQuestManager>(this, QuestManagerClass);
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
