// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CTTPractice/CTTEnum.h"
#include "CTTPractice/UI/CTTNumberImageList.h"
#include "CTTUICommonResource.generated.h"

/**
 * 
 */

UCLASS(Blueprintable)
class CTTPRACTICE_API UCTTUICommonResource : public UObject
{
	GENERATED_BODY()

public:
	UTexture2D* GetNumberTexture(ECTTNumberImageType NumberImageType, int32 Number) const;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<ECTTNumberImageType, FCTTNumberImageList> NumberImageMap;
};
