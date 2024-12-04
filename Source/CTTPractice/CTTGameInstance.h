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

UCLASS()
class CTTPRACTICE_API UCTTGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	virtual void Init() override;

public:
	void InitializeCollectItem(int32 CollectItemNumber, bool CollectItemInitialState);

	int32 GetPlayerLifeCount() const { return PlayerLifeCount; }
	int32 GetCoinCount() const { return CoinCount; }
	int32 GetNextCollectItemStatusIndex() { return CurrentCollectItemStatusIndex++; };

	void SetPlayerLifeCount(int32 InPlayerLifeCount);
	void SetCoinCount(int32 InCoinCount);
	void SetCollectItemStatus(int32 InIndex, bool bInEnable);

	FCTTOnChangePlayerLifeCount& OnChangePlayerLifeCount() { return OnChangePlayerLifeCountDelegate; }
	FCTTOnChangeCoinCount& OnChangeCoinCount() { return OnChangeCoinCountDelegate; }
	FCTTOnChangeCollectItem& OnChangeCollectItem() { return OnChangeCollectItemDelegate; }

public:
	void InitializeManagers();

	UCTTCameraManager* GetCameraManager() const { return CameraManagerInstance; }
	UCTTDatatableManager* GetDatatableManager() const { return DatatableManagerInstance; }
	UCTTUIManager* GetUIManager() const { return UIManagerInstance; }

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UCTTCameraManager> CameraManagerClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UCTTDatatableManager> DatatableManagerClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UCTTUIManager> UIManagerClass;

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
};
