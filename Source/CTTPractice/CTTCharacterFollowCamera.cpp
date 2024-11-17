// Fill out your copyright notice in the Description page of Project Settings.


#include "CTTCharacterFollowCamera.h"
#include "CTTCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

ACTTCharacterFollowCamera::ACTTCharacterFollowCamera()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ACTTCharacterFollowCamera::BeginPlay()
{
	Super::BeginPlay();

	if (nullptr == TargetCharacterClass)
	{
		UE_LOG(LogTemp, Error, TEXT("TargetCharacterClass is nullptr"));
		return;
	}

	AActor* NewTarget = Cast<ACTTCharacter>(UGameplayStatics::GetActorOfClass(GetWorld(), TargetCharacterClass));
	if (nullptr == NewTarget)
	{
		UE_LOG(LogTemp, Error, TEXT("TargetActor is nullptr"));
		return;
	}
	SetTarget(NewTarget);
}

void ACTTCharacterFollowCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CameraMovement(DeltaTime);
}

void ACTTCharacterFollowCamera::CameraMovement(float DeltaTime)
{
	float CurrentTargetArmLength = SpringArmComponent->TargetArmLength;
	float NewTargetArmLength = FMath::FInterpTo(CurrentTargetArmLength, TargetArmLength, DeltaTime, CameraZoomSpeed);
	SpringArmComponent->TargetArmLength = NewTargetArmLength;
}

void ACTTCharacterFollowCamera::RotateCamera(float InputValue)
{
	FRotator RotationDelta(0.0f, InputValue * 2.f * GetWorld()->DeltaTimeSeconds * RotationSpeed, 0.0f);
	FRotator NewRotation = SpringArmComponent->GetComponentRotation() + RotationDelta;

	SpringArmComponent->SetWorldRotation(NewRotation);
}

void ACTTCharacterFollowCamera::MoveCameraCloser()
{
	TargetArmLength = FMath::Clamp(SpringArmComponent->TargetArmLength - CameraMoveDistance, MinSpringArmLength, MaxSpringArmLength);
}

void ACTTCharacterFollowCamera::MoveCameraAway()
{
	TargetArmLength = FMath::Clamp(SpringArmComponent->TargetArmLength + CameraMoveDistance, MinSpringArmLength, MaxSpringArmLength);
}
