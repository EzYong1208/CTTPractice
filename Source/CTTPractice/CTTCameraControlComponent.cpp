// Fill out your copyright notice in the Description page of Project Settings.


#include "CTTCameraControlComponent.h"
//#include "GameFramework/SpringArmComponent.h"
//#include "Camera/CameraComponent.h"

// Sets default values for this component's properties
UCTTCameraControlComponent::UCTTCameraControlComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	//PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCTTCameraControlComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	//InitializeCameraComponents();
	//
	//TargetArmLength = InitialSpringArmLength;
	//GoalRotation = InitialSpringArmRotation;
}


// Called every frame
void UCTTCameraControlComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCTTCameraControlComponent::InitializeCameraComponents()
{
	//AActor* Owner = GetOwner();
	//if (nullptr == Owner)
	//{
	//	UE_LOG(LogTemp, Error, TEXT("Owner is nullptr"));
	//	return;
	//}
	//
	//SpringArmComponent = NewObject<USpringArmComponent>(this, USpringArmComponent::StaticClass(), TEXT("SpringArmComponent"));
	//if (nullptr == SpringArmComponent)
	//{
	//	UE_LOG(LogTemp, Error, TEXT("SpringArmComponent NewObject has failed"));
	//	return;
	//}
	//SpringArmComponent->RegisterComponent();
	//SpringArmComponent->AttachToComponent(Owner->GetRootComponent(), FAttachmentTransformRules::SnapToTargetIncludingScale);
	//SpringArmComponent->TargetArmLength = InitialSpringArmLength;
	//SpringArmComponent->SetRelativeRotation(InitialSpringArmRotation);

	//UObject* OuterObject = SpringArmComponent->GetOuter();
	//UE_LOG(LogTemp, Warning, TEXT("SpringArmComponent's Outer: %s"), *OuterObject->GetName());
	//
	//CameraComponent = NewObject<UCameraComponent>(this, UCameraComponent::StaticClass(), TEXT("CameraComponent"));
	//if (nullptr == CameraComponent)
	//{
	//	UE_LOG(LogTemp, Error, TEXT("CameraComponent NewObject has failed"));
	//	return;
	//}
	//CameraComponent->RegisterComponent();
	//CameraComponent->AttachToComponent(SpringArmComponent, FAttachmentTransformRules::SnapToTargetIncludingScale);
	//
	//OuterObject = CameraComponent->GetOuter();
	//UE_LOG(LogTemp, Warning, TEXT("CameraComponent's Outer: %s"), *OuterObject->GetName());
}

void UCTTCameraControlComponent::CameraMovement(float DeltaTime)
{
	//FRotator CurrentRotation = SpringArmComponent->GetRelativeRotation();
	//FRotator NewRotation = FMath::RInterpTo(CurrentRotation, GoalRotation, DeltaTime, RotationSpeed);
	//SpringArmComponent->SetRelativeRotation(NewRotation);
	//
	//float CurrentTargetArmLength = SpringArmComponent->TargetArmLength;
	//float NewTargetArmLength = FMath::FInterpTo(CurrentTargetArmLength, TargetArmLength, DeltaTime, CameraZoomSpeed);
	//SpringArmComponent->TargetArmLength = NewTargetArmLength;
}

void UCTTCameraControlComponent::RotateCameraLeft()
{
	//GoalRotation.Yaw += CameraRotationAngle;
}

void UCTTCameraControlComponent::RotateCameraRight()
{
	//GoalRotation.Yaw -= CameraRotationAngle;
}

void UCTTCameraControlComponent::MoveCameraCloser()
{
	//TargetArmLength = FMath::Clamp(SpringArmComponent->TargetArmLength - CameraMoveDistance, MinSpringArmLength, MaxSpringArmLength);
}

void UCTTCameraControlComponent::MoveCameraAway()
{
	//TargetArmLength = FMath::Clamp(SpringArmComponent->TargetArmLength + CameraMoveDistance, MinSpringArmLength, MaxSpringArmLength);
}

