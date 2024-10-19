// Fill out your copyright notice in the Description page of Project Settings.


#include "CTTItemAnimInstance.h"
#include "CTTItem.h"

void UCTTItemAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

}

void UCTTItemAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

    ACTTItem* OwningCharacter = Cast<ACTTItem>(GetOwningActor());
    if (nullptr == OwningCharacter)
    {
        return;
    }

    bIsDead = OwningCharacter->CheckItemDead();
}

void UCTTItemAnimInstance::AnimNotify_DieEnd()
{
	UE_LOG(LogTemp, Error, TEXT("AnimNotify_DieEnd"));

    ACTTItem* OwnerItem = Cast<ACTTItem>(GetOwningActor());
    if (nullptr == OwnerItem)
    {
        return;
    }

    // TODO : 아이템 스폰하는 기능 추가? 여기서? 좀 더 고민

    OwnerItem->Destroy();
}
