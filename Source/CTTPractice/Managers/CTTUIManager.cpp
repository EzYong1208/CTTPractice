// Fill out your copyright notice in the Description page of Project Settings.


#include "CTTPractice/Managers/CTTUIManager.h"
#include "CTTPractice/UI/CTTUIScreenWidget.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"

void UCTTUIManager::InitializeUIManager()
{
	for (TSubclassOf<UCTTUIScreenWidget> WidgetClass : WidgetBlueprintsToRegister)
	{
		if (false == WidgetClass)
		{
			UE_LOG(LogTemp, Error, TEXT("WidgetClass is nullptr"));
			continue;
		}

		UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), WidgetClass);
		if (nullptr == Widget)
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to create widget from class: %s"), *WidgetClass->GetName());
			continue;
		}

		RegisterUIToGroup(Widget);
	}

	ShowUIGroup(InitialUIGroupName);
}

void UCTTUIManager::RegisterUIToGroup(UUserWidget* Widget)
{
	if (nullptr == Widget)
	{
		UE_LOG(LogTemp, Error, TEXT("Widget is nullptr"));
		return;
	}

	UCTTUIScreenWidget* ScreenWidget = Cast<UCTTUIScreenWidget>(Widget);
	if (ScreenWidget)
	{
		FName GroupName = ScreenWidget->GetUIGroupName();
		bool bGroupExists = UIGroups.Contains(GroupName);

		if (!bGroupExists)
		{
			UIGroups.Add(GroupName, FCTTWidgetGroup());
		}

		UIGroups[GroupName].Widgets.Add(Widget);
	}
}

void UCTTUIManager::ShowUIGroup(FName GroupName)
{
	bool bGroupExists = UIGroups.Contains(GroupName);
	if (!bGroupExists)
	{
		UE_LOG(LogTemp, Warning, TEXT("GroupName '%s' doesn't exist"), *GroupName.ToString());
		return;
	}

	FCTTWidgetGroup& Group = UIGroups[GroupName];
	for (UUserWidget* Widget : Group.Widgets)
	{
		if (Widget &&
			false == Widget->IsInViewport())
		{
			Widget->AddToViewport();
		}
	}

	SetGroupVisibility(GroupName, ESlateVisibility::Visible);
}

void UCTTUIManager::HideUIGroup(FName GroupName)
{
	SetGroupVisibility(GroupName, ESlateVisibility::Collapsed);
}

void UCTTUIManager::SetGroupVisibility(FName GroupName, ESlateVisibility Visibility)
{
	bool bGroupExists = UIGroups.Contains(GroupName);
	if (!bGroupExists)
	{
		UE_LOG(LogTemp, Warning, TEXT("GroupName '%s' doesn't exist"), *GroupName.ToString());
		return;
	}

	FCTTWidgetGroup& Group = UIGroups[GroupName];
	for (UUserWidget* Widget : Group.Widgets)
	{
		if (Widget)
		{
			Widget->SetVisibility(Visibility);
		}
	}

	Group.GroupVisibility = Visibility;
}
