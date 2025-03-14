// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "CTTGameInstance.generated.h"

/**
 * 
 */

DECLARE_MULTICAST_DELEGATE_OneParam(FCTTOnChangePlayerLifeCount, int32);
DECLARE_MULTICAST_DELEGATE_OneParam(FCTTOnChangeCoinCount, int32);
DECLARE_MULTICAST_DELEGATE_TwoParams(FCTTOnChangeCollectItem, int32, bool);

class UCTTCameraManager;
class UCTTDatatableManager;
class UCTTUIManager;
class UCTTQuestManager;
class UCTTEventManager;
class UCTTActionManager;

UCLASS()
class CTTPRACTICE_API UCTTGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	virtual void Init() override;
	virtual void Shutdown() override;

public:
	void InitializeCollectItem(int32 CollectItemNumber, bool CollectItemInitialState);

	const int32 GetPlayerLifeCount() const { return PlayerLifeCount; }
	const int32 GetCoinCount() const { return CoinCount; }
	const int32 GetNextCollectItemStatusIndex() { return CurrentCollectItemStatusIndex++; };

	void SetPlayerLifeCount(int32 InPlayerLifeCount);
	void SetCoinCount(int32 InCoinCount);
	void SetCollectItemStatus(int32 InIndex, bool bInEnable);

	FCTTOnChangePlayerLifeCount& OnChangePlayerLifeCount() { return OnChangePlayerLifeCountDelegate; }
	FCTTOnChangeCoinCount& OnChangeCoinCount() { return OnChangeCoinCountDelegate; }
	FCTTOnChangeCollectItem& OnChangeCollectItem() { return OnChangeCollectItemDelegate; }

public:
	void InitializeManagers();
	void ShutdownManagers();

	UCTTCameraManager* GetCameraManager() const;
	UCTTDatatableManager* GetDatatableManager() const;
	UCTTUIManager* GetUIManager() const;
	UCTTQuestManager* GetQuestManager() const;
	UCTTEventManager* GetEventManager() const;
	UCTTActionManager* GetActionManager() const;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UCTTCameraManager> CameraManagerClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UCTTDatatableManager> DatatableManagerClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UCTTUIManager> UIManagerClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UCTTQuestManager> QuestManagerClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UCTTEventManager> EventManagerClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UCTTActionManager> ActionManagerClass;

protected:
	UPROPERTY(BlueprintReadWrite)
	int32 PlayerLifeCount = 0;

	UPROPERTY(BlueprintReadWrite)
	int32 CoinCount = 0;

	UPROPERTY()
	int32 CurrentCollectItemStatusIndex = 0;

	UPROPERTY()
	TArray<bool> CollectItemStates;

	FCTTOnChangePlayerLifeCount OnChangePlayerLifeCountDelegate;
	FCTTOnChangeCoinCount OnChangeCoinCountDelegate;
	FCTTOnChangeCollectItem OnChangeCollectItemDelegate;

private:
	UPROPERTY()
	UCTTCameraManager* CameraManagerInstance = nullptr;

	UPROPERTY()
	UCTTDatatableManager* DatatableManagerInstance = nullptr;

	UPROPERTY()
	UCTTUIManager* UIManagerInstance = nullptr;

	UPROPERTY()
	UCTTQuestManager* QuestManagerInstance = nullptr;

	UPROPERTY()
	UCTTEventManager* EventManagerInstance = nullptr;

	UPROPERTY()
	UCTTActionManager* ActionManagerInstance = nullptr;
};
