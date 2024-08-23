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
		UE_LOG(LogTemp, Warning, TEXT("ItemSwitcher or EmptyImage is nullptr"));
		return;
	}

	ItemSwitcher->SetActiveWidget(EmptyImage);
}

void UCTTCollectItemWidget::SetToCollect()
{
	if (!IsValid(ItemSwitcher) ||
		!IsValid(CollectImage))
	{
		UE_LOG(LogTemp, Warning, TEXT("ItemSwitcher or CollectImage is nullptr"));
		return;
	}

	ItemSwitcher->SetActiveWidget(CollectImage);
}

void UCTTCollectItemWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);


}
