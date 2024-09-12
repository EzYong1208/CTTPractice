// Copyright Epic Games, Inc. All Rights Reserved.


#include "CTTCollectItemWidget.h"
#include "CTTCollectItemData.h"
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

	UCTTCollectItemData* ItemData = Cast<UCTTCollectItemData>(ListItemObject);
	if (nullptr == ItemData)
	{
		return;
	}

	SetToEmpty();

	FDelegateHandle Handle = ItemData->OnChangeCollectItemStateDelegate.AddUObject(this, &UCTTCollectItemWidget::OnChangeCollectItem);
	if (!Handle.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to bind delegate."));
	}
	CollectItemData = ItemData;
}


void UCTTCollectItemWidget::NativeDestruct()
{
	if (nullptr == CollectItemData)
	{
		return;
	}

	CollectItemData->OnChangeCollectItemStateDelegate.RemoveAll(this);

	Super::NativeDestruct();
}

void UCTTCollectItemWidget::OnChangeCollectItem(bool bIsCollected)
{
	if (!IsValid(ItemSwitcher))
	{
		UE_LOG(LogTemp, Warning, TEXT("ItemSwitcher is nullptr"));
		return;
	}
	if (!IsValid(CollectImage))
	{
		UE_LOG(LogTemp, Warning, TEXT("CollectImage is nullptr"));
		return;
	}
	if (!IsValid(EmptyImage))
	{
		UE_LOG(LogTemp, Warning, TEXT("EmptyImage is nullptr"));
		return;
	}

	if (bIsCollected)
	{
		ItemSwitcher->SetActiveWidget(CollectImage);
	}
	else
	{
		ItemSwitcher->SetActiveWidget(EmptyImage);
	}
}
