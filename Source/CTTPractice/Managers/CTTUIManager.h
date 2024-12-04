// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CTTPractice/CTTStruct.h"
#include "CTTUIManager.generated.h"

/**
 * 
 */

class UCTTUIScreenWidget;

UCLASS(Blueprintable)
class CTTPRACTICE_API UCTTUIManager : public UObject
{
	GENERATED_BODY()
	
public:
    void InitializeUIManager();

    void RegisterUIToGroup(UUserWidget* Widget);
    void ShowUIGroup(FName GroupName);
    void HideUIGroup(FName GroupName);

private:
    void SetGroupVisibility(FName GroupName, ESlateVisibility Visibility);

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<TSubclassOf<UCTTUIScreenWidget>> WidgetBlueprintsToRegister;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName InitialUIGroupName;

private:
    UPROPERTY()
    TMap<FName, FCTTWidgetGroup> UIGroups;
};
