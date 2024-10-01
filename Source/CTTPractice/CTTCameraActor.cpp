// Fill out your copyright notice in the Description page of Project Settings.


#include "CTTCameraActor.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"

ACTTCameraActor::ACTTCameraActor()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ACTTCameraActor::BeginPlay()
{
	Super::BeginPlay();

	InitializeCameraComponents();
}

void ACTTCameraActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACTTCameraActor::InitializeCameraComponents()
{
	// TODO : 정리하기
	if (nullptr == OwningCharacter)
	{
		UE_LOG(LogTemp, Error, TEXT("OwningCharacter is nullptr"));
		return;
	}

	USpringArmComponent* SpringArmComponent = Cast<USpringArmComponent>(OwningCharacter->GetComponentByClass(USpringArmComponent::StaticClass()));
	if (nullptr == SpringArmComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("SpringArmComponent is nullptr"));
		return;
	}

	AttachToComponent(SpringArmComponent, FAttachmentTransformRules::SnapToTargetIncludingScale);
}

void ACTTCameraActor::CameraMovement(float DeltaTime)
{

}

void ACTTCameraActor::RotateCameraLeft()
{

}
