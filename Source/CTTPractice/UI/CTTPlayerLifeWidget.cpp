// Copyright Epic Games, Inc. All Rights Reserved.


#include "CTTPlayerLifeWidget.h"
#include "Components/Image.h"
#include "CTTPractice/CTTEnum.h"
#include "CTTPractice/CTTPracticeGameModeBase.h"
#include "CTTPractice/CTTGameInstance.h"
#include "CTTPractice/UI/CTTUICommonResource.h"
#include "Kismet/GameplayStatics.h"


void UCTTPlayerLifeWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UCTTGameInstance* GameInstance = Cast<UCTTGameInstance>(UGameplayStatics::GetGameInstance(this));
	if (IsValid(GameInstance))
	{
		// OnChangePlayerLifeCountDelegate 델리게이트에 함수를 바인딩
		OnChangePlayerLifeCountHandle = GameInstance->OnChangePlayerLifeCount().AddUObject(this, &UCTTPlayerLifeWidget::OnChangePlayerLifeCount);
	}
}


void UCTTPlayerLifeWidget::NativeDestruct()
{
	UCTTGameInstance* GameInstance = Cast<UCTTGameInstance>(UGameplayStatics::GetGameInstance(this));
	if (IsValid(GameInstance) && OnChangePlayerLifeCountHandle.IsValid())
	{
		GameInstance->OnChangePlayerLifeCount().Remove(OnChangePlayerLifeCountHandle);
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

	if (PlayerLifeCount < 0 ||
		PlayerLifeCount >= 10)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerLifeCount range is 0 ~ 9"));
		PlayerLifeCount = 0;
	}

	UTexture2D* Texture = UICommonResource->GetNumberTexture(ECTTNumberImageType::PlayerLifeNumber, PlayerLifeCount);

	if (IsValid(LifeNumber))
	{
		LifeNumber->SetBrushFromTexture(Texture);
	}
}
