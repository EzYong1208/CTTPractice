// Fill out your copyright notice in the Description page of Project Settings.


#include "CTTPractice/Event/CTTConditionBase.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"

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

bool UCTTConditionBase_Player::CheckCondition_Implementation(AActor* Actor) const
{
	if (nullptr == Actor)
	{
		UE_LOG(LogTemp, Error, TEXT("Actor is nullptr"));
		return false;
	}

	APawn* Pawn = Cast<APawn>(Actor);
	if (nullptr == Pawn)
	{
		UE_LOG(LogTemp, Error, TEXT("Pawn is nullptr"));
		return false;
	}

	AController* CurrentController = Pawn->GetController();
	if (nullptr == CurrentController)
	{
		UE_LOG(LogTemp, Error, TEXT("CurrentController is nullptr"));
		return false;
	}

	if (true == CurrentController->IsPlayerController())
	{
		return true;
	}

	return false;
}

bool UCTTConditionBase_CheckCharacterCollision::CheckCondition_Implementation(AActor* Actor) const
{
	if (nullptr == Actor)
	{
		UE_LOG(LogTemp, Error, TEXT("Actor is nullptr"));
		return false;
	}

	ACharacter* Character = Cast<ACharacter>(Actor);
	if (nullptr == Character)
	{
		UE_LOG(LogTemp, Error, TEXT("Actor is not Character"));
		return false;
	}

	UCapsuleComponent* CharacterCapsule = Character->GetCapsuleComponent();
	if (nullptr == CharacterCapsule)
	{
		UE_LOG(LogTemp, Error, TEXT("CharacterCapsule is nullptr"));
		return false;
	}

	return true;
}
