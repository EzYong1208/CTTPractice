// Fill out your copyright notice in the Description page of Project Settings.


#include "CTTCameraControlComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values for this component's properties
UCTTCameraControlComponent::UCTTCameraControlComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCTTCameraControlComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	InitializeCameraComponents();
	TargetArmLength = InitialSpringArmLength;
}


// Called every frame
void UCTTCameraControlComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	CameraMovement(DeltaTime);
}

void UCTTCameraControlComponent::InitializeCameraComponents()
{
	TWeakObjectPtr<USpringArmComponent> SpringArmComponent = GetSpringArmComponent();

	SpringArmComponent->TargetArmLength = InitialSpringArmLength;
}

void UCTTCameraControlComponent::CameraMovement(float DeltaTime)
{
	TWeakObjectPtr<USpringArmComponent> SpringArmComponent = GetSpringArmComponent();

	float CurrentTargetArmLength = SpringArmComponent->TargetArmLength;
	float NewTargetArmLength = FMath::FInterpTo(CurrentTargetArmLength, TargetArmLength, DeltaTime, CameraZoomSpeed);
	SpringArmComponent->TargetArmLength = NewTargetArmLength;
}

void UCTTCameraControlComponent::RotateCamera(float InputValue)
{
	TWeakObjectPtr<USpringArmComponent> SpringArmComponent = GetSpringArmComponent();

	FRotator RotationDelta(0.0f, InputValue * 2.f * GetWorld()->DeltaTimeSeconds * RotationSpeed, 0.0f);
	FRotator NewRotation = SpringArmComponent->GetComponentRotation() + RotationDelta;

	SpringArmComponent->SetWorldRotation(NewRotation);
}

void UCTTCameraControlComponent::MoveCameraCloser()
{
	TWeakObjectPtr<USpringArmComponent> SpringArmComponent = GetSpringArmComponent();

	TargetArmLength = FMath::Clamp(SpringArmComponent->TargetArmLength - CameraMoveDistance, MinSpringArmLength, MaxSpringArmLength);
}

void UCTTCameraControlComponent::MoveCameraAway()
{
	TWeakObjectPtr<USpringArmComponent> SpringArmComponent = GetSpringArmComponent();

	TargetArmLength = FMath::Clamp(SpringArmComponent->TargetArmLength + CameraMoveDistance, MinSpringArmLength, MaxSpringArmLength);
}

TWeakObjectPtr<USpringArmComponent> UCTTCameraControlComponent::GetSpringArmComponent() const
{
	AActor* Owner = GetOwner();
	if (nullptr == Owner)
	{
		UE_LOG(LogTemp, Error, TEXT("Owner is nullptr"));
		return nullptr;
	}

	USpringArmComponent* SpringArmComponent = Cast<USpringArmComponent>(Owner->GetComponentByClass(USpringArmComponent::StaticClass()));
	if (nullptr == SpringArmComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("SpringArmComponent is nullptr"));
		return nullptr;
	}

	return TWeakObjectPtr<USpringArmComponent>(SpringArmComponent);
}

