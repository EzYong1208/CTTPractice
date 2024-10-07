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

	TargetArmLength = InitialSpringArmLength;
}

void ACTTCameraActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CameraMovement(DeltaTime);
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

	SpringArmComponent->TargetArmLength = InitialSpringArmLength;

	AttachToComponent(SpringArmComponent, FAttachmentTransformRules::SnapToTargetIncludingScale);
}

void ACTTCameraActor::CameraMovement(float DeltaTime)
{
	USpringArmComponent* SpringArmComponent = Cast<USpringArmComponent>(OwningCharacter->GetComponentByClass(USpringArmComponent::StaticClass()));
	if (nullptr == SpringArmComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("SpringArmComponent is nullptr"));
		return;
	}

	float CurrentTargetArmLength = SpringArmComponent->TargetArmLength;
	float NewTargetArmLength = FMath::FInterpTo(CurrentTargetArmLength, TargetArmLength, DeltaTime, CameraZoomSpeed);
	SpringArmComponent->TargetArmLength = NewTargetArmLength;
}

void ACTTCameraActor::RotateCamera(float InputValue)
{
	USpringArmComponent* SpringArmComponent = Cast<USpringArmComponent>(OwningCharacter->GetComponentByClass(USpringArmComponent::StaticClass()));
	if (nullptr == SpringArmComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("SpringArmComponent is nullptr"));
		return;
	}

	FRotator RotationDelta(0.0f, InputValue * 2.f * GetWorld()->DeltaTimeSeconds * RotationSpeed, 0.0f);
	FRotator NewRotation = SpringArmComponent->GetComponentRotation() + RotationDelta;

	SpringArmComponent->SetWorldRotation(NewRotation);
}

void ACTTCameraActor::MoveCameraCloser()
{
	USpringArmComponent* SpringArmComponent = Cast<USpringArmComponent>(OwningCharacter->GetComponentByClass(USpringArmComponent::StaticClass()));
	if (nullptr == SpringArmComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("SpringArmComponent is nullptr"));
		return;
	}

	TargetArmLength = FMath::Clamp(SpringArmComponent->TargetArmLength - CameraMoveDistance, MinSpringArmLength, MaxSpringArmLength);
}

void ACTTCameraActor::MoveCameraAway()
{
	USpringArmComponent* SpringArmComponent = Cast<USpringArmComponent>(OwningCharacter->GetComponentByClass(USpringArmComponent::StaticClass()));
	if (nullptr == SpringArmComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("SpringArmComponent is nullptr"));
		return;
	}

	TargetArmLength = FMath::Clamp(SpringArmComponent->TargetArmLength + CameraMoveDistance, MinSpringArmLength, MaxSpringArmLength);
}
