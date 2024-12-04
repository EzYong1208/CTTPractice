// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CTTUIScreenWidget.generated.h"

/**
 * 
 */
UCLASS()
class CTTPRACTICE_API UCTTUIScreenWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	FName GetUIGroupName() const { return UIGroupName; }

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName UIGroupName;
};
