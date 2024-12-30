// Fill out your copyright notice in the Description page of Project Settings.


#include "CTTPractice/Actor/Character/CTTAnimInstance.h"
#include "CTTPractice/Actor/Character/CTTCharacter.h"
#include "CTTPractice/Actor/Character/CTTSocketAttachmentComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

void UCTTAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

}

void UCTTAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	//FName CurrentState = GetCurrentStateName(ANIMINSTANCE_MACHINEINDEX);

	//if (CurrentState != CurrentStateName)
	//{
	//	UpdateSocketAttachments();
	//}

    // EzYong TODO : �ִϸ��̼� ��� �Ϸ�Ǹ� ����

    ACTTCharacter* OwningCharacter = Cast<ACTTCharacter>(GetOwningActor());
    if (nullptr == OwningCharacter)
    {
        return;
    }

    Speed = OwningCharacter->GetCharacterSpeed();
    bCanAttack = OwningCharacter->CheckCharacterAttack();
    bIsInAir = OwningCharacter->GetCharacterMovement()->IsFalling();
    bIsInLadder = OwningCharacter->CheckCharacterInLadder();
}

void UCTTAnimInstance::UpdateSocketAttachments()
{
   //AActor* OwningActor = GetOwningActor();
   //if (nullptr == OwningActor)
   //{
   //    UE_LOG(LogTemp, Error, TEXT("OwningActor is nullptr"));
   //    return;
   //}

   //UCTTSocketAttachmentComponent* SocketAttachmentComponent = OwningActor->FindComponentByClass<UCTTSocketAttachmentComponent>();
   //if (nullptr == SocketAttachmentComponent)
   //{
   //    UE_LOG(LogTemp, Error, TEXT("SocketAttachmentComponent is nullptr"));
   //    return;
   //}

    //FName CurrentState = GetCurrentStateName(ANIMINSTANCE_MACHINEINDEX);
   //SocketAttachmentComponent->SetMeshByName(CurrentState);

   //CurrentStateName = CurrentState;

    // EzYong TODO : ���� �Ǵ� ������ ����� �ִϸ��̼� �̸��� ���ڷ� ������ UCTTSocketAttachmentComponent ���� �� �ִϸ��̼� �̸��� �´� �޽õ��� �����ϰԲ� ����
    // FName Current�� NextAnimationName = �ִϸ��̼��̸� �����ü� �ִ� �Լ�();
    // SocketAttachmentComponent->SetMeshByName(AnimationName);
}

void UCTTAnimInstance::AnimNotify_AttackEnd()
{
    ACTTCharacter* OwningCharacter = Cast<ACTTCharacter>(GetOwningActor());
    if (nullptr == OwningCharacter)
    {
        return;
    }

    bCanAttack = true;
    OwningCharacter->SetCharacterAttack(bCanAttack);
}
