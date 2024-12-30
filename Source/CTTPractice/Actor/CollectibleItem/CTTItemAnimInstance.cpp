// Fill out your copyright notice in the Description page of Project Settings.


#include "CTTPractice/Actor/CollectibleItem/CTTItemAnimInstance.h"
#include "CTTPractice/Actor/CollectibleItem/CTTItem.h"

void UCTTItemAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

}

void UCTTItemAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	ACTTItem* OwnerItem = Cast<ACTTItem>(GetOwningActor());
	if (nullptr == OwnerItem)
	{
		return;
	}

    bIsDead = OwnerItem->CheckItemDead();
}

void UCTTItemAnimInstance::AnimNotify_DieEnd()
{
	UE_LOG(LogTemp, Error, TEXT("AnimNotify_DieEnd"));

    ACTTItem* OwnerItem = Cast<ACTTItem>(GetOwningActor());
    if (nullptr == OwnerItem)
    {
        return;
    }

    OwnerItem->HandleDeath();
}
