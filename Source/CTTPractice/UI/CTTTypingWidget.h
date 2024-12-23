// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CTTTypingWidget.generated.h"

/**
 * 
 */

class UTextBlock;

UCLASS()
class CTTPRACTICE_API UCTTTypingWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
    virtual void NativeConstruct() override;

public:
    UPROPERTY(meta = (BindWidget))
    UTextBlock* TypingTextBlock;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText FullText;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float TypingSpeed = 0.f;

private:
    void UpdateTypingText();

private:
    FString CurrentString;
    int32 CurrentIndex = 0;
    FTimerHandle TypingTimerHandle;
};
