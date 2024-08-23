// Copyright Epic Games, Inc. All Rights Reserved.


#include "CTTCollectItemListWidget.h"
#include "CTTCollectItemWidget.h"
#include "Components/ListView.h"
#include "CTTPractice/CTTPracticeGameModeBase.h"
#include "Kismet/GameplayStatics.h"


void UCTTCollectItemListWidget::InitializeCollectItemList(int32 NumberOfItems)
{
	if (!CollectItemListView)
	{
		UE_LOG(LogTemp, Warning, TEXT("CollectItemListView is nullptr"));
		return;
	}

	CollectItemListView->ClearListItems();

	UClass* EntryWidgetClass = UCTTCollectItemWidget::StaticClass();

	if (!IsValid(EntryWidgetClass))
	{
		UE_LOG(LogTemp, Warning, TEXT("EntryWidgetClass is nullptr"));
		return;
	}

	for (int32 i = 0; i < NumberOfItems; ++i)
	{
		UCTTCollectItemWidget* NewItem = CreateWidget<UCTTCollectItemWidget>(this, EntryWidgetClass);

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

	InitializeCollectItemList(3);
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
		UE_LOG(LogTemp, Warning, TEXT("CollectItemListView is nullptr"));
		return;
	}

	TArray<UUserWidget*> DisplayedWidgets = CollectItemListView->GetDisplayedEntryWidgets();

	if (DisplayedWidgets.Num() <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("No widgets are currently displayed in the CollectItemListView"));
		return;
	}

	if (ItemIndex < 0 ||
		DisplayedWidgets.Num() - 1 < ItemIndex)
	{
		UE_LOG(LogTemp, Warning, TEXT("ItemIndex is out of range"));
		return;
	}

	UCTTCollectItemWidget* TargetItem = Cast<UCTTCollectItemWidget>(DisplayedWidgets[ItemIndex]);

	if (!IsValid(TargetItem))
	{
		UE_LOG(LogTemp, Warning, TEXT("TargetItem is nullptr"));
		return;
	}

	if (bIsCollected)
	{
		TargetItem->SetToCollect();
		return;
	}
	else
	{
		TargetItem->SetToEmpty();
		return;
	}
}
