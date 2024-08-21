// Copyright Epic Games, Inc. All Rights Reserved.


#include "CTTCollectItemWidget.h"
#include "Components/Image.h"
#include "Components/WidgetSwitcher.h"
#include "CTTPractice/CTTPracticeGameModeBase.h"
#include "Kismet/GameplayStatics.h"

void UCTTCollectItemWidget::SetToEmpty()
{
	if (!IsValid(ItemSwitcher) ||
		!IsValid(EmptyImage))
	{
		return;
	}

	ItemSwitcher->SetActiveWidget(EmptyImage);
}

void UCTTCollectItemWidget::SetToCollect()
{
	if (!IsValid(ItemSwitcher) ||
		!IsValid(CollectImage))
	{
		return;
	}

	ItemSwitcher->SetActiveWidget(CollectImage);
}