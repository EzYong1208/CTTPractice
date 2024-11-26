// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CTTPractice/CTTStruct.h"
#include "CTTInteractableInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCTTInteractableInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CTTPRACTICE_API ICTTInteractableInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void OnEnterInteract(const FCTTInteractionInfo& InteractionInfo) = 0;
	virtual void OnInteract() = 0;
	virtual void OnExitInteract() = 0;
};
