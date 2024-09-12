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

private:
	void UpdateSocketAttachments();

protected:
	UPROPERTY(EditAnyWhere)
	FName CurrentStateName;

	static constexpr int32 ANIMINSTANCE_MACHINEINDEX = 0;
};
