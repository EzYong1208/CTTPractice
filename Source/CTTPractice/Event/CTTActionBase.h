// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CTTPractice/CTTDatatableHeader.h"
#include "CTTActionBase.generated.h"

/**
 * 
 */

UCLASS(Abstract)
class CTTPRACTICE_API UCTTActionBase : public UObject
{
	GENERATED_BODY()

public:
	virtual void Execute_Implementation(AActor* Actor) {}
	virtual void InitializeWithActionData(const FCTTActionData& InActionData) {}

protected:
	FCTTActionData ActionData;
};

UCLASS()
class CTTPRACTICE_API UCTTActionBase_AddCoin : public UCTTActionBase
{
	GENERATED_BODY()

public:
	virtual void Execute_Implementation(AActor* Actor) override;
	virtual void InitializeWithActionData(const FCTTActionData& InActionData) override;

private:
	int32 CoinAmount = 0;
};

UCLASS()
class CTTPRACTICE_API UCTTActionBase_Die : public UCTTActionBase
{
	GENERATED_BODY()

public:
	virtual void Execute_Implementation(AActor* Actor) override;
};