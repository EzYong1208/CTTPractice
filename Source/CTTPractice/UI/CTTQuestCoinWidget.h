// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CTTQuestCoinWidget.generated.h"

/**
 * 
 */
class UScaleBox;
class UImage;

UCLASS()
class CTTPRACTICE_API UCTTQuestCoinWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void OnChangeQuestCoinCount(int32 QuestCoinCount);
	void SetNumber(int32 Number);

private:
	void InitializeGoalCoinNumber();

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetOptional))
	UScaleBox* CurrentDigitTenBox = nullptr;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetOptional))
	UScaleBox* CurrentDigitOneBox = nullptr;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetOptional))
	UScaleBox* GoalDigitTenBox = nullptr;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetOptional))
	UScaleBox* GoalDigitOneBox = nullptr;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetOptional))
	UImage* CurrentDigitTen = nullptr;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetOptional))
	UImage* CurrentDigitOne = nullptr;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetOptional))
	UImage* GoalDigitTen = nullptr;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetOptional))
	UImage* GoalDigitOne = nullptr;

	FDelegateHandle OnChangeQuestCoinCountHandle;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int32 GoalCoinCount = 0;

private:
	int32 CurrentCoinCout = 0;
};
