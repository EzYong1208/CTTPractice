// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CTTItemAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class CTTPRACTICE_API UCTTItemAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

public:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	bool bIsDead = false;

private:
	UFUNCTION()
	void AnimNotify_DieEnd();
	
};
