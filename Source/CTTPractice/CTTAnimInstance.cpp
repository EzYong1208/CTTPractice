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

    // TODO: �ִϸ��̼� ��� �Ϸ�Ǹ� ����

	AActor* OwningActor = GetOwningActor();
	if (nullptr == OwningActor)
	{
		UE_LOG(LogTemp, Error, TEXT("UCTTAnimInstance: OwningActor is nullptr"));
		return;
	}

	Speed = OwningActor->GetVelocity().Size();
	//UE_LOG(LogTemp, Warning, TEXT("Current Speed: %f"), Speed);
}

void UCTTAnimInstance::SetSpeed(float InSpeed)
{

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

    // TODO: ���� �Ǵ� ������ ����� �ִϸ��̼� �̸��� ���ڷ� ������ UCTTSocketAttachmentComponent ���� �� �ִϸ��̼� �̸��� �´� �޽õ��� �����ϰԲ� ����
    // FName Current�� NextAnimationName = �ִϸ��̼��̸� �����ü� �ִ� �Լ�();
    // SocketAttachmentComponent->SetMeshByName(AnimationName);
}
