// Copyright Epic Games, Inc. All Rights Reserved.


#include "CTTCollectItemListWidget.h"
#include "CTTCollectItemWidget.h"
#include "CTTCollectItemData.h"
#include "Components/ListView.h"
#include "CTTPractice/CTTPracticeGameModeBase.h"
#include "Kismet/GameplayStatics.h"


void UCTTCollectItemListWidget::InitializeCollectItemList()
{
	if (!CollectItemListView)
	{
		UE_LOG(LogTemp, Warning, TEXT("CollectItemListView is nullptr"));
		return;
	}

	CollectItemListView->ClearListItems();

	for (int32 i = 0; i < ACTTPracticeGameModeBase::COLLECTITEM_NUMBER; ++i)
	{
		UCTTCollectItemData* NewItem = NewObject<UCTTCollectItemData>();
		CollectItemListView->AddItem(NewItem);

		UE_LOG(LogTemp, Warning, TEXT("Address of NewItem %d: %p"), i, NewItem);
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

	InitializeCollectItemList();
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

	UObject* ItemObject = CollectItemListView->GetItemAt(ItemIndex);
	if (!IsValid(ItemObject))
	{
		UE_LOG(LogTemp, Warning, TEXT("Item at index %d is not valid"), ItemIndex);
		return;
	}

	UCTTCollectItemData* TargetItem = Cast<UCTTCollectItemData>(CollectItemListView->GetItemAt(ItemIndex));
	if (!IsValid(TargetItem))
	{
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("Address of TargetItem %d: %p"), ItemIndex, TargetItem);

	if (bIsCollected)
	{
		TargetItem->SetCollect();
	}
	else
	{
		TargetItem->SetEmpty();
	}

	CollectItemListView->RequestRefresh();
}
