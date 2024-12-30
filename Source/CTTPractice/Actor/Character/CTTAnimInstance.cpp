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

    // EzYong TODO : 애니메이션 제어가 완료되면 수정

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

    // EzYong TODO : 현재 또는 다음에 진행될 애니메이션 이름을 인자로 보내고 UCTTSocketAttachmentComponent 에서 그 애니메이션 이름에 맞는 메시들을 설정하게끔 설정
    // FName Current나 NextAnimationName = 애니메이션이름 가져올수 있는 함수();
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
