// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CTTActionBase.generated.h"

/**
 * 
 */

UCLASS(Abstract)
class CTTPRACTICE_API UCTTActionBase : public UObject
{
	GENERATED_BODY()

public:
	void Execute() {}
	virtual void Execute_Implementation() {}
};

UCLASS()
class CTTPRACTICE_API UCTTActionBase_AddCoin : public UCTTActionBase
{
	GENERATED_BODY()

public:
	virtual void Execute_Implementation() override;

private:
	int32 CoinAmount = 0;
};