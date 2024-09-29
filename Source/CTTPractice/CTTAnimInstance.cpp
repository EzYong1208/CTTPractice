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

	//FName CurrentState = GetCurrentStateName(ANIMINSTANCE_MACHINEINDEX);

	//if (CurrentState != CurrentStateName)
	//{
	//	UpdateSocketAttachments();
	//}

    // TODO: 애니메이션 제어가 완료되면 수정
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

    // TODO: 현재 또는 다음에 진행될 애니메이션 이름을 인자로 보내고 UCTTSocketAttachmentComponent 에서 그 애니메이션 이름에 맞는 메시들을 설정하게끔 설정
    // FName Current나 NextAnimationName = 애니메이션이름 가져올수 있는 함수();
    // SocketAttachmentComponent->SetMeshByName(AnimationName);
}
