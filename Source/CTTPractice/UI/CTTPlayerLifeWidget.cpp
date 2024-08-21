// Copyright Epic Games, Inc. All Rights Reserved.


#include "CTTPlayerLifeWidget.h"
#include "Components/Image.h"
#include "CTTPractice/CTTEnum.h"
#include "CTTPractice/CTTPracticeGameModeBase.h"
#include "CTTPractice/UI/CTTUICommonResource.h"
#include "Kismet/GameplayStatics.h"


void UCTTPlayerLifeWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ACTTPracticeGameModeBase* GameMode = Cast<ACTTPracticeGameModeBase>(UGameplayStatics::GetGameMode(this));
	if (IsValid(GameMode))
	{
		// OnChangePlayerLifeCountDelegate 델리게이트에 함수를 바인딩
		OnChangePlayerLifeCountHandle = GameMode->OnChangePlayerLifeCount().AddUObject(this, &UCTTPlayerLifeWidget::OnChangePlayerLifeCount);
	}
}


void UCTTPlayerLifeWidget::NativeDestruct()
{
	ACTTPracticeGameModeBase* GameMode = Cast<ACTTPracticeGameModeBase>(UGameplayStatics::GetGameMode(this));
	if (IsValid(GameMode) && OnChangePlayerLifeCountHandle.IsValid())
	{
		GameMode->OnChangePlayerLifeCount().Remove(OnChangePlayerLifeCountHandle);
	}

	Super::NativeDestruct();
}

void UCTTPlayerLifeWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UCTTPlayerLifeWidget::OnChangePlayerLifeCount(int32 PlayerLifeCount)
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

	UTexture2D* Texture = UICommonResource->GetNumberTexture(ECTTNumberImageType::PlayerLifeNumber, PlayerLifeCount);

	if (IsValid(LifeNumber))
	{
		LifeNumber->SetBrushFromTexture(Texture);
	}
}
