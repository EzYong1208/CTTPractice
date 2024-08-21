// Copyright Epic Games, Inc. All Rights Reserved.


#include "CTTCollectItemListWidget.h"
#include "CTTCollectItemWidget.h"
#include "Components/ListView.h"
#include "CTTPractice/CTTPracticeGameModeBase.h"
#include "Kismet/GameplayStatics.h"


void UCTTCollectItemListWidget::InitializeCollectItemList(int32 NumberOfItems)
{
	if (!CollectItemListView || 
		!IsValid(CollectItemWidgetClass))
	{
		return;
	}

	CollectItemListView->ClearListItems();

	for (int32 i = 0; i < NumberOfItems; ++i)
	{
		UCTTCollectItemWidget* NewItem = CreateWidget<UCTTCollectItemWidget>(this, CollectItemWidgetClass);

		if (IsValid(NewItem))
		{
			CollectItemListView->AddItem(NewItem);
		}
	}
}

void UCTTCollectItemListWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ACTTPracticeGameModeBase* GameMode = Cast<ACTTPracticeGameModeBase>(UGameplayStatics::GetGameMode(this));
	if (IsValid(GameMode))
	{
		OnChangeCollectItemHandle = GameMode->OnChangeCollectItem().AddUObject(this, &UCTTCollectItemListWidget::OnChangeCollectItem);
	}

	if (!IsValid(CollectItemWidgetClass))
	{
		return;
	}
	InitializeCollectItemList(5);
}

void UCTTCollectItemListWidget::NativeDestruct()
{
	ACTTPracticeGameModeBase* GameMode = Cast<ACTTPracticeGameModeBase>(UGameplayStatics::GetGameMode(this));
	if (IsValid(GameMode) && OnChangeCollectItemHandle.IsValid())
	{
		GameMode->OnChangeCollectItem().Remove(OnChangeCollectItemHandle);
	}

	Super::NativeDestruct();
}

void UCTTCollectItemListWidget::OnChangeCollectItem(int32 ItemIndex, bool bIsCollected)
{
	if (!CollectItemListView)
	{
		return;
	}

	UCTTCollectItemWidget* TargetItem = Cast<UCTTCollectItemWidget>(CollectItemListView->GetItemAt(ItemIndex));
	if (!IsValid(TargetItem))
	{
		return;
	}

	if (bIsCollected)
	{
		TargetItem->SetToCollect();
	}
	else
	{
		TargetItem->SetToEmpty();
	}
}
