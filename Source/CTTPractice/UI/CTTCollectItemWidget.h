// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"
#include "CTTCollectItemWidget.generated.h"

/**
 * 
 */
class UImage;
class UWidgetSwitcher;

UCLASS(Abstract)
class CTTPRACTICE_API UCTTCollectItemWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetToEmpty();
	void SetToCollect();

protected:
	UPROPERTY(meta = (BindWidget))
    UWidgetSwitcher* ItemSwitcher = nullptr;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetOptional))
	UImage* EmptyImage = nullptr;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetOptional))
	UImage* CollectImage = nullptr;
};
