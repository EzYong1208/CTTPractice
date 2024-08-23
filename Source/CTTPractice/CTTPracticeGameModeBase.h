// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Templates/SubclassOf.h"
#include "CTTPracticeGameModeBase.generated.h"

/**
 * 
 */

DECLARE_MULTICAST_DELEGATE_OneParam(FCTTOnChangePlayerLifeCount, int32);
DECLARE_MULTICAST_DELEGATE_OneParam(FCTTOnChangeCoinCount, int32);
DECLARE_MULTICAST_DELEGATE_TwoParams(FCTTOnChangeCollectItem, int32, bool);

class UCTTUICommonResource;

UCLASS()
class CTTPRACTICE_API ACTTPracticeGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;

	const UCTTUICommonResource* GetUICommonResource() const { return UICommonResource; }

	int32 GetPlayerLifeCount() const { return PlayerLifeCount; }
	int32 GetCoinCount() const { return CoinCount; }

	void SetPlayerLifeCount(int32 InPlayerLifeCount);
	FCTTOnChangePlayerLifeCount& OnChangePlayerLifeCount() { return OnChangePlayerLifeCountDelegate; }
	void SetCoinCount(int32 InCoinCount);
	FCTTOnChangeCoinCount& OnChangeCoinCount() { return OnChangeCoinCountDelegate; }
	void SetCollectItemStatus(int32 InIndex, bool bInEnable);
	FCTTOnChangeCollectItem& OnChangeCollectItem() { return OnChangeCollectItemDelegate; }

protected:
	// 유저정보 만들기 전까지 임시 [8/17/2024 EzYong-Laptop]
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 PlayerInitialLifeCount = 0;

	UPROPERTY(BlueprintReadWrite)
	int32 PlayerLifeCount = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CoinInitialLifeCount = 0;

	UPROPERTY(BlueprintReadWrite)
	int32 CoinCount = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool CollectItemInitialState = false;

	UPROPERTY(BlueprintReadWrite)
	bool CollectItemState = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UCTTUICommonResource> UICommonResourceClass;

	UPROPERTY()
	UCTTUICommonResource* UICommonResource = nullptr;

	FCTTOnChangePlayerLifeCount OnChangePlayerLifeCountDelegate;
	FCTTOnChangeCoinCount OnChangeCoinCountDelegate;
	FCTTOnChangeCollectItem OnChangeCollectItemDelegate;
};
