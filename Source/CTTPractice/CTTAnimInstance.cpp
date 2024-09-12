// Fill out your copyright notice in the Description page of Project Settings.


#include "CTTAnimInstance.h"
#include "CTTSocketAttachmentComponent.h"

void UCTTAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

}

void UCTTAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	FName CurrentState = GetCurrentStateName(ANIMINSTANCE_MACHINEINDEX);

	if (CurrentState != CurrentStateName)
	{
        UpdateSocketAttachments();
	}

    AActor* OwningActor = GetOwningActor();
}

void UCTTAnimInstance::UpdateSocketAttachments()
{
    AActor* OwningActor = GetOwningActor();
    if (nullptr == OwningActor)
    {
        UE_LOG(LogTemp, Error, TEXT("OwningActor is nullptr"));
        return;
    }

    UCTTSocketAttachmentComponent* SocketAttachmentComponent = OwningActor->FindComponentByClass<UCTTSocketAttachmentComponent>();
    if (nullptr == SocketAttachmentComponent)
    {
        UE_LOG(LogTemp, Error, TEXT("SocketAttachmentComponent is nullptr"));
        return;
    }

    FName CurrentState = GetCurrentStateName(ANIMINSTANCE_MACHINEINDEX);
    SocketAttachmentComponent->SetMeshByName(CurrentState);

    CurrentStateName = CurrentState;
}
