// Fill out your copyright notice in the Description page of Project Settings.


#include "CTTPractice/UI/CTTTypingWidget.h"
#include "Components/TextBlock.h"
#include "TimerManager.h"

void UCTTTypingWidget::NativeConstruct()
{
    Super::NativeConstruct();

    CurrentString = "";
    CurrentIndex = 0;

    GetWorld()->GetTimerManager().SetTimer(
        TypingTimerHandle,
        this,
        &UCTTTypingWidget::UpdateTypingText,
        TypingSpeed,
        true
    );
}

void UCTTTypingWidget::UpdateTypingText()
{
    if (CurrentIndex >= FullText.ToString().Len())
    {
        GetWorld()->GetTimerManager().ClearTimer(TypingTimerHandle);
        return;
    }

    CurrentString = FullText.ToString().Left(CurrentIndex + 1);
    if (TypingTextBlock)
    {
        TypingTextBlock->SetText(FText::FromString(CurrentString));
    }

    CurrentIndex++;
}
