// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CTTAnimInstance.generated.h"

/**
 * 
 */

class UCTTSocketAttachmentComponent;
class ACTTCharacter;

UCLASS()
class CTTPRACTICE_API UCTTAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	void UpdateSocketAttachments();

	FName CurrentStateName;

protected:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	float Speed = 0.f;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	bool bCanAttack = false;
	
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	bool bIsInAir = false;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	bool bIsInLadder = false;

private:
	UFUNCTION()
	void AnimNotify_AttackEnd();
};
