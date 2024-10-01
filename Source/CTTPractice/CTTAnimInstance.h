// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CTTAnimInstance.generated.h"

/**
 * 
 */

class UCTTSocketAttachmentComponent;

UCLASS()
class CTTPRACTICE_API UCTTAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

public:
	void SetSpeed(float InSpeed);

private:
	void UpdateSocketAttachments();

	FName CurrentStateName;

protected:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	float Speed = 0.f;
};
