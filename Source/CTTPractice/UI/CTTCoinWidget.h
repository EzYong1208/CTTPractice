// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"
#include "CTTCoinWidget.generated.h"

/**
 * 
 */
class UScaleBox;
class UImage;

UCLASS(Abstract)
class CTTPRACTICE_API UCTTCoinWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void OnChangeCoinCount(int32 CoinCount);
	void SetNumber(int32 Number);


	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetOptional))
	UScaleBox* DigitTenBox = nullptr;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetOptional))
	UScaleBox* DigitOneBox = nullptr;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetOptional))
	UImage* DigitTen = nullptr;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetOptional))
	UImage* DigitOne = nullptr;

	FDelegateHandle OnChangeCoinCountHandle;
};
