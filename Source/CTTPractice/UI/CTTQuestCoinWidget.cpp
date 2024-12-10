// Fill out your copyright notice in the Description page of Project Settings.


#include "CTTPractice/UI/CTTQuestCoinWidget.h"
#include "Components/Image.h"
#include "Components/ScaleBox.h"
#include "CTTPractice/CTTEnum.h"
#include "CTTPractice/CTTPracticeGameModeBase.h"
#include "CTTPractice/CTTGameInstance.h"
#include "CTTPractice/UI/CTTUICommonResource.h"
#include "Kismet/GameplayStatics.h"

void UCTTQuestCoinWidget::NativeConstruct()
{
	Super::NativeConstruct();

	InitializeGoalCoinNumber();
	OnChangeQuestCoinCount(CurrentCoinCout);
}

void UCTTQuestCoinWidget::NativeDestruct()
{

	Super::NativeDestruct();
}

void UCTTQuestCoinWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UCTTQuestCoinWidget::OnChangeQuestCoinCount(int32 QuestCoinCount)
{
	ACTTPracticeGameModeBase* GameMode = Cast<ACTTPracticeGameModeBase>(UGameplayStatics::GetGameMode(this));
	if (!IsValid(GameMode))
	{
		return;
	}

	const UCTTUICommonResource* UICommonResource = GameMode->GetUICommonResource();
	if (!IsValid(UICommonResource))
	{
		return;
	}

	if (QuestCoinCount < 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("QuestCoinCount range is 0 ~ 99"));
		QuestCoinCount = 0;
	}

	CurrentCoinCout = FMath::Min(CurrentCoinCout + QuestCoinCount, GoalCoinCount);
	SetNumber(CurrentCoinCout);

	if (CurrentCoinCout >= 10 && IsValid(CurrentDigitTen))
	{
		int32 Ten = CurrentCoinCout / 10;
		UTexture2D* Texture = UICommonResource->GetNumberTexture(ECTTNumberImageType::CoinNumber, Ten);
		CurrentDigitTen->SetBrushFromTexture(Texture);
	}
	if (IsValid(CurrentDigitOne))
	{
		int32 One = CurrentCoinCout % 10;
		UTexture2D* Texture = UICommonResource->GetNumberTexture(ECTTNumberImageType::CoinNumber, One);
		CurrentDigitOne->SetBrushFromTexture(Texture);
	}
}

void UCTTQuestCoinWidget::SetNumber(int32 Number)
{
	if (Number < 10)
	{
		CurrentDigitTenBox->SetVisibility(ESlateVisibility::Collapsed);
		CurrentDigitOneBox->SetVisibility(ESlateVisibility::Visible);
	}
	else if (Number < 100)
	{
		CurrentDigitTenBox->SetVisibility(ESlateVisibility::Visible);
		CurrentDigitOneBox->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		CurrentDigitTenBox->SetVisibility(ESlateVisibility::Collapsed);
		CurrentDigitOneBox->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UCTTQuestCoinWidget::InitializeGoalCoinNumber()
{
	if (GoalCoinCount < 10)
	{
		CurrentDigitTenBox->SetVisibility(ESlateVisibility::Collapsed);
		CurrentDigitOneBox->SetVisibility(ESlateVisibility::Visible);
	}
	else if (GoalCoinCount < 100)
	{
		CurrentDigitTenBox->SetVisibility(ESlateVisibility::Visible);
		CurrentDigitOneBox->SetVisibility(ESlateVisibility::Visible);
	}

	ACTTPracticeGameModeBase* GameMode = Cast<ACTTPracticeGameModeBase>(UGameplayStatics::GetGameMode(this));
	if (!IsValid(GameMode))
	{
		return;
	}

	const UCTTUICommonResource* UICommonResource = GameMode->GetUICommonResource();
	if (!IsValid(UICommonResource))
	{
		return;
	}

	if (GoalCoinCount >= 10 && IsValid(GoalDigitTen))
	{
		int32 Ten = GoalCoinCount / 10;
		UTexture2D* Texture = UICommonResource->GetNumberTexture(ECTTNumberImageType::CoinNumber, Ten);
		GoalDigitTen->SetBrushFromTexture(Texture);
	}
	if (IsValid(GoalDigitOne))
	{
		int32 One = GoalCoinCount % 10;
		UTexture2D* Texture = UICommonResource->GetNumberTexture(ECTTNumberImageType::CoinNumber, One);
		GoalDigitOne->SetBrushFromTexture(Texture);
	}
}
