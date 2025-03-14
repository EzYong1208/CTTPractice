// Fill out your copyright notice in the Description page of Project Settings.


#include "CTTGameInstance.h"
#include "CTTPractice/Managers/CTTCameraManager.h"
#include "CTTPractice/Managers/CTTDatatableManager.h"
#include "CTTPractice/Managers/CTTUIManager.h"
#include "CTTPractice/Managers/CTTQuestManager.h"
#include "CTTPractice/Managers/CTTEventManager.h"
#include "CTTPractice/Managers/CTTActionManager.h"

void UCTTGameInstance::Init()
{
    Super::Init();
    
}

void UCTTGameInstance::Shutdown()
{
	ShutdownManagers();

	Super::Shutdown();
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
	if (IsValid(DatatableManagerClass))
	{
		DatatableManagerInstance = NewObject<UCTTDatatableManager>(this, DatatableManagerClass);
	}

	if (IsValid(CameraManagerClass))
	{
		CameraManagerInstance = NewObject<UCTTCameraManager>(this, CameraManagerClass);
		CameraManagerInstance->InitializeCameras();
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

	if (IsValid(EventManagerClass))
	{
		EventManagerInstance = NewObject<UCTTEventManager>(this, EventManagerClass);
		EventManagerInstance->Initialize();
	}

	if (IsValid(ActionManagerClass))
	{
		ActionManagerInstance = NewObject<UCTTActionManager>(this, ActionManagerClass);
		ActionManagerInstance->Initialize();
	}
}

void UCTTGameInstance::ShutdownManagers()
{
	if (IsValid(ActionManagerInstance))
	{
		ActionManagerInstance->Shutdown();
		ActionManagerInstance = nullptr;
	}

	if (IsValid(EventManagerInstance))
	{
		EventManagerInstance->Shutdown();
		EventManagerInstance = nullptr;
	}

	if (IsValid(QuestManagerInstance))
	{
		QuestManagerInstance = nullptr;
	}

	if (IsValid(UIManagerInstance))
	{
		UIManagerInstance->Shutdown();
		UIManagerInstance = nullptr;
	}

	if (IsValid(CameraManagerInstance))
	{
		CameraManagerInstance->Shutdown();
		CameraManagerInstance = nullptr;
	}

	if (IsValid(DatatableManagerInstance))
	{
		DatatableManagerInstance->Shutdown();
		DatatableManagerInstance = nullptr;
	}
}

UCTTCameraManager* UCTTGameInstance::GetCameraManager() const
{
	if (nullptr == CameraManagerInstance)
	{
		UE_LOG(LogTemp, Error, TEXT("CameraManagerInstance is nullptr"));
		return nullptr;
	}

	return CameraManagerInstance;
}

UCTTDatatableManager* UCTTGameInstance::GetDatatableManager() const
{
	if (nullptr == DatatableManagerInstance)
	{
		UE_LOG(LogTemp, Error, TEXT("DatatableManagerInstance is nullptr"));
		return nullptr;
	}

	return DatatableManagerInstance;
}

UCTTUIManager* UCTTGameInstance::GetUIManager() const
{
	if (nullptr == UIManagerInstance)
	{
		UE_LOG(LogTemp, Error, TEXT("UIManagerInstance is nullptr"));
		return nullptr;
	}

	return UIManagerInstance;
}

UCTTQuestManager* UCTTGameInstance::GetQuestManager() const
{
	if (nullptr == QuestManagerInstance)
	{
		UE_LOG(LogTemp, Error, TEXT("QuestManagerInstance is nullptr"));
		return nullptr;
	}

	return QuestManagerInstance;
}

UCTTEventManager* UCTTGameInstance::GetEventManager() const
{
	if (nullptr == EventManagerInstance)
	{
		UE_LOG(LogTemp, Error, TEXT("EventManagerInstance is nullptr"));
		return nullptr;
	}

	return EventManagerInstance;
}

UCTTActionManager* UCTTGameInstance::GetActionManager() const
{
	if (nullptr == ActionManagerInstance)
	{
		UE_LOG(LogTemp, Error, TEXT("ActionManagerInstance is nullptr"));
		return nullptr;
	}

	return ActionManagerInstance;
}

void UCTTGameInstance::InitializeCollectItem(int32 CollectItemNumber, bool CollectItemInitialState)
{
	CollectItemStates.SetNum(CollectItemNumber);
	for (int32 i = 0; i < CollectItemStates.Num(); ++i)
	{
		CollectItemStates[i] = CollectItemInitialState;
	}
}
