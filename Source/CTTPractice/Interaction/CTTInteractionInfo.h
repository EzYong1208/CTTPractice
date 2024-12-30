// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Components/SlateWrapperTypes.h"
#include "CTTPractice/CTTEnum.h"
#include "CTTInteractionInfo.generated.h"

/**
 * 
 */

class UCTTInteractionComponent;

USTRUCT(BlueprintType)
struct CTTPRACTICE_API FCTTInteractionInfo
{
	GENERATED_BODY()

	FCTTInteractionInfo()
		: Interactor(nullptr) {}
	FCTTInteractionInfo(UCTTInteractionComponent* Interactor)
		: Interactor(Interactor) {}
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCTTInteractionComponent* Interactor;
};
