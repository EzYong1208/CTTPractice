// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"
#include "CTTPlayerLifeWidget.generated.h"

/**
 * 
 */
class UImage;

UCLASS(Abstract)
class CTTPRACTICE_API UCTTPlayerLifeWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void OnChangePlayerLifeCount(int32 PlayerLifeCount);

	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetOptional))
	UImage* LifeNumber = nullptr;

	FDelegateHandle OnChangePlayerLifeCountHandle;
};
