// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CTTCollectItemData.generated.h"

/**
 * 
 */

DECLARE_MULTICAST_DELEGATE_OneParam(FCTTOnCollectItemStateChanged, bool);

UCLASS(Blueprintable)
class CTTPRACTICE_API UCTTCollectItemData : public UObject
{
public:
	GENERATED_BODY()

	void SetCollect();
	void SetEmpty();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsCollected = false;

	FCTTOnCollectItemStateChanged OnChangeCollectItemStateDelegate;
};
