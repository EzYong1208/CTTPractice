// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CTTCollectItemListWidget.generated.h"

/**
 * 
 */
class UListView;
class UCTTCollectItemWidget;

UCLASS(Abstract)
class CTTPRACTICE_API UCTTCollectItemListWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void InitializeCollectItemList(int32 NumberOfItems);

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	void OnChangeCollectItem(int32 ItemIndex, bool bIsCollected);

	UPROPERTY(meta = (BindWidget))
	UListView* CollectItemListView = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UCTTCollectItemWidget> CollectItemWidgetClass;

	FDelegateHandle OnChangeCollectItemHandle;
};
