// Copyright Epic Games, Inc. All Rights Reserved.


#include "CTTCoinWidget.h"
#include "Components/Image.h"
#include "Components/ScaleBox.h"
#include "CTTPractice/CTTEnum.h"
#include "CTTPractice/CTTPracticeGameModeBase.h"
#include "CTTPractice/CTTGameInstance.h"
#include "CTTPractice/UI/CTTUICommonResource.h"
#include "Kismet/GameplayStatics.h"


void UCTTCoinWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UCTTGameInstance* GameInstance = Cast<UCTTGameInstance>(UGameplayStatics::GetGameInstance(this));
	if (IsValid(GameInstance))
	{
		// OnChangeCoinCountDelegate 델리게이트에 함수를 바인딩
		OnChangeCoinCountHandle = GameInstance->OnChangeCoinCount().AddUObject(this, &UCTTCoinWidget::OnChangeCoinCount);
	}
}

void UCTTCoinWidget::NativeDestruct()
{
	UCTTGameInstance* GameInstance = Cast<UCTTGameInstance>(UGameplayStatics::GetGameInstance(this));
	if (IsValid(GameInstance) && OnChangeCoinCountHandle.IsValid())
	{
		GameInstance->OnChangeCoinCount().Remove(OnChangeCoinCountHandle);
	}

	Super::NativeDestruct();
}

void UCTTCoinWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UCTTCoinWidget::OnChangeCoinCount(int32 CoinCount)
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

	if (CoinCount < 0 ||
		CoinCount >= 100)
	{
		UE_LOG(LogTemp, Warning, TEXT("CoinCount range is 0 ~ 99"));
		CoinCount = 0;
	}

	SetNumber(CoinCount);

	if (CoinCount >= 10
		&& IsValid(DigitTen))
	{
		int32 Ten = CoinCount / 10;
		UTexture2D* Texture = UICommonResource->GetNumberTexture(ECTTNumberImageType::CoinNumber, Ten);
		DigitTen->SetBrushFromTexture(Texture);
	}
	if (IsValid(DigitOne))
	{
		int32 One = CoinCount % 10;
		UTexture2D* Texture = UICommonResource->GetNumberTexture(ECTTNumberImageType::CoinNumber, One);
		DigitOne->SetBrushFromTexture(Texture);
	}
}

void UCTTCoinWidget::SetNumber(int32 Number)
{
	if (Number < 10)
	{
		DigitTenBox->SetVisibility(ESlateVisibility::Collapsed);
		DigitOneBox->SetVisibility(ESlateVisibility::Visible);
	}
	else if (Number < 100)
	{
		DigitTenBox->SetVisibility(ESlateVisibility::Visible);
		DigitOneBox->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		DigitTenBox->SetVisibility(ESlateVisibility::Collapsed);
		DigitOneBox->SetVisibility(ESlateVisibility::Collapsed);
	}
}
