// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Components/SlateWrapperTypes.h"
#include "CTTWidgetStruct.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct CTTPRACTICE_API FCTTWidgetGroup
{
    GENERATED_BODY()

    UPROPERTY()
    TArray<UUserWidget*> Widgets;

	UPROPERTY()
	ESlateVisibility GroupVisibility = ESlateVisibility::Collapsed;
};
