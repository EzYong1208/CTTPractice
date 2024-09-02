// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "CTTCollectItemWidget.generated.h"

/**
 * 
 */
class UImage;
class UWidgetSwitcher;
class IUserObjectListEntry;
class UCTTCollectItemData;

UCLASS()
class CTTPRACTICE_API UCTTCollectItemWidget : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

public:
	void SetToEmpty();
	void SetToCollect();

protected:
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;
	virtual void NativeDestruct() override;

	void OnChangeCollectItem(bool bIsCollected);

	UPROPERTY(meta = (BindWidget))
    UWidgetSwitcher* ItemSwitcher = nullptr;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetOptional))
	UImage* EmptyImage = nullptr;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetOptional))
	UImage* CollectImage = nullptr;

	UCTTCollectItemData* CollectItemData = nullptr;
};
