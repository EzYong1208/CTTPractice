// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CTTPractice/Event/CTTActionBase.h"
#include "CTTActionManager.generated.h"

/**
 * 
 */

UCLASS(Blueprintable)
class CTTPRACTICE_API UCTTActionManager : public UObject
{
	GENERATED_BODY()

public:
	void Initialize();
	void Shutdown();

public:
	UCTTActionBase* GetActionInstanceByClass(TSubclassOf<UCTTActionBase> ActionClass);

private:
	ECTTActionType ConvertActionClassToType(TSubclassOf<UCTTActionBase> ActionClass);
	
private:
	UPROPERTY()
	TMap<ECTTActionType, TSubclassOf<UCTTActionBase>> ActionClassMap;

	UPROPERTY()
    TMap<ECTTActionType, UCTTActionBase*> ActionInstances;
};
