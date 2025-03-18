// Fill out your copyright notice in the Description page of Project Settings.


#include "CTTPractice/Managers/CTTActionManager.h"

void UCTTActionManager::Initialize()
{
    ActionClassMap =
    {
        { ECTTActionType::AddCoin, UCTTActionBase_AddCoin::StaticClass() },
        { ECTTActionType::FillCollectItem, UCTTActionBase_FillCollectItem::StaticClass() },
        { ECTTActionType::Die, UCTTActionBase_Die::StaticClass() },
        { ECTTActionType::Rotate, UCTTActionBase_Rotate::StaticClass() },
        { ECTTActionType::Jump, UCTTActionBase_Jump::StaticClass() },
    };

    for (const auto& Entry : ActionClassMap)
    {
        if (Entry.Value)
        {
            UCTTActionBase* ActionInstance = NewObject<UCTTActionBase>(this, Entry.Value);
            if (!ActionInstance)
            {
                UE_LOG(LogTemp, Error, TEXT("Failed to create ActionInstance for %s"), *Entry.Value->GetName());
                continue;
            }

            ActionInstances.Add(Entry.Key, ActionInstance);
        }
    }

    static_assert(static_cast<int32>(ECTTActionType::MAX) - 1 == 5, "The number of actions does not match the Enum count!");
}

void UCTTActionManager::Shutdown()
{
    for (auto& Entry : ActionInstances)
    {
        if (Entry.Value)
        {
            Entry.Value->MarkPendingKill();
        }
    }

    ActionInstances.Empty();
}

UCTTActionBase* UCTTActionManager::GetActionInstanceByClass(TSubclassOf<UCTTActionBase> ActionClass)
{
	ECTTActionType ActionType = ConvertActionClassToType(ActionClass);
	if (ActionType == ECTTActionType::None)
	{
		UE_LOG(LogTemp, Error, TEXT("Unknown action class: %s"), *ActionClass->GetName());
		return nullptr;
	}

	UCTTActionBase** ActionPtr = ActionInstances.Find(ActionType);
	if (ActionPtr)
	{
		return *ActionPtr;
	}

	UE_LOG(LogTemp, Error, TEXT("Action type not found in ActionInstances: %s"), *ActionClass->GetName());
	return nullptr;
}

ECTTActionType UCTTActionManager::ConvertActionClassToType(TSubclassOf<UCTTActionBase> ActionClass)
{
    for (const auto& Entry : ActionClassMap)
    {
        if (Entry.Value == ActionClass)
        {
            return Entry.Key;
        }
    }

    UE_LOG(LogTemp, Error, TEXT("Unknown action class: %s"), *ActionClass->GetName());
    return ECTTActionType::None;
}
