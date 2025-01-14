// Fill out your copyright notice in the Description page of Project Settings.


#include "CTTPractice/Event/CTTConditionBase.h"

bool UCTTConditionBase::CheckCondition_Implementation(AActor* Actor) const
{
	UE_LOG(LogTemp, Error, TEXT("CheckCondition_Implementation in UCTTConditionBase is called directly"));

	return false;
}

bool UCTTConditionBase_ActorName::CheckCondition_Implementation(AActor* Actor) const
{
	if (nullptr == Actor)
	{
		UE_LOG(LogTemp, Error, TEXT("Actor is nullptr"));
		return false;
	}

	if (ActorName == Actor->GetFName())
	{
		return true;
	}

	return false;
}
