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
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(this);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent);

	TargetArmLength = SpringArmComponent->TargetArmLength;
}


// Called when the game starts
void UCTTCameraControlComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
    if (CameraComponent)
    {
        FVector InitialCameraLocation = CameraComponent->GetRelativeLocation();
        SpringArmComponent->SetRelativeLocation(InitialCameraLocation);
        SpringArmComponent->SetRelativeRotation(CameraComponent->GetRelativeRotation());
    }
}


// Called every frame
void UCTTCameraControlComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCTTCameraControlComponent::CameraMovement(float DeltaTime)
{
    AActor* Owner = GetOwner();
    if (nullptr == Owner)
    {
        return;
    }

    FVector CharacterLocation = Owner->GetActorLocation();
    FVector InitialCameraLocation = CameraComponent->GetRelativeLocation();
    FVector TargetLocation = CharacterLocation + InitialCameraLocation;

    FVector ForwardVector = SpringArmComponent->GetForwardVector();
    TargetLocation -= (ForwardVector * SpringArmComponent->TargetArmLength);

    FVector NewLocation = FMath::VInterpTo(SpringArmComponent->GetComponentLocation(), TargetLocation, DeltaTime, RotationSpeed);
    SpringArmComponent->SetWorldLocation(NewLocation);

    FVector CameraLocation = CameraComponent->GetComponentLocation();
    UE_LOG(LogTemp, Warning, TEXT("Camera Location: %s"), *CameraLocation.ToString());

    FRotator CurrentRotation = SpringArmComponent->GetComponentRotation();
    FRotator TargetRotation = FRotator(0.0f, GoalRotationValue, 0.0f);
    FRotator NewRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, DeltaTime, RotationSpeed);

    SpringArmComponent->SetWorldRotation(NewRotation);
    SpringArmComponent->TargetArmLength = FMath::FInterpTo(SpringArmComponent->TargetArmLength, TargetArmLength, DeltaTime, RotationSpeed);

	UE_LOG(LogTemp, Warning, TEXT("Current Spring Arm Length: %f"), SpringArmComponent->TargetArmLength);
}

void UCTTCameraControlComponent::RotateCameraLeft()
{
	GoalRotationValue -= CameraRotationAngle;
}

void UCTTCameraControlComponent::RotateCameraRight()
{
	GoalRotationValue += CameraRotationAngle;
}

void UCTTCameraControlComponent::MoveCameraCloser()
{
	TargetArmLength = FMath::Clamp(SpringArmComponent->TargetArmLength - CameraMoveDistance, MinSpringArmLength, MaxSpringArmLength);
	UE_LOG(LogTemp, Warning, TEXT("Moving Closer: %f"), TargetArmLength);
}

void UCTTCameraControlComponent::MoveCameraAway()
{
	TargetArmLength = FMath::Clamp(SpringArmComponent->TargetArmLength + CameraMoveDistance, MinSpringArmLength, MaxSpringArmLength);
	UE_LOG(LogTemp, Warning, TEXT("Moving Away: %f"), TargetArmLength);
}