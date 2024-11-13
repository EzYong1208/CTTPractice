// Fill out your copyright notice in the Description page of Project Settings.


#include "CTTFollowCamera.h"
#include "CTTCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
ACTTFollowCamera::ACTTFollowCamera()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACTTFollowCamera::BeginPlay()
{
	Super::BeginPlay();

	InitializeCameraComponents();
}

// Called every frame
void ACTTFollowCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateCameraLocation(DeltaTime);
	CameraMovement(DeltaTime);
}

void ACTTFollowCamera::InitializeCameraComponents()
{
	SpringArmComponent = FindComponentByClass<USpringArmComponent>();
	CameraComponent = FindComponentByClass<UCameraComponent>();

	SpringArmComponent->TargetArmLength = InitialSpringArmLength;
	TargetArmLength = InitialSpringArmLength;
	SpringArmComponent->SetRelativeRotation(InitialSpringArmRotation);
}

void ACTTFollowCamera::CameraMovement(float DeltaTime)
{
	float CurrentTargetArmLength = SpringArmComponent->TargetArmLength;
	float NewTargetArmLength = FMath::FInterpTo(CurrentTargetArmLength, TargetArmLength, DeltaTime, CameraZoomSpeed);
	SpringArmComponent->TargetArmLength = NewTargetArmLength;
}

void ACTTFollowCamera::UpdateCameraLocation(float DeltaTime)
{
	if (false == TargetCharacter.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("TargetCharacter is not valid"));
		return;
	}

	FVector CharacterLocation = TargetCharacter->GetActorLocation();
	FRotator SpringArmRotation = SpringArmComponent->GetComponentRotation();
	FVector CameraLocation = CharacterLocation - SpringArmRotation.Vector() * SpringArmComponent->TargetArmLength;

	SpringArmComponent->SetWorldLocation(CameraLocation);
}

void ACTTFollowCamera::RotateCamera(float InputValue)
{
	FRotator RotationDelta(0.0f, InputValue * 2.f * GetWorld()->DeltaTimeSeconds * RotationSpeed, 0.0f);
	FRotator NewRotation = SpringArmComponent->GetComponentRotation() + RotationDelta;

	SpringArmComponent->SetWorldRotation(NewRotation);
}

void ACTTFollowCamera::MoveCameraCloser()
{
	TargetArmLength = FMath::Clamp(SpringArmComponent->TargetArmLength - CameraMoveDistance, MinSpringArmLength, MaxSpringArmLength);
}

void ACTTFollowCamera::MoveCameraAway()
{
	TargetArmLength = FMath::Clamp(SpringArmComponent->TargetArmLength + CameraMoveDistance, MinSpringArmLength, MaxSpringArmLength);
}

void ACTTFollowCamera::SetTargetCharacter(ACTTCharacter* NewTarget)
{
	TargetCharacter = NewTarget;
}
