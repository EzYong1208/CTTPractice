// Fill out your copyright notice in the Description page of Project Settings.


#include "CTTPractice/Actor/Camera/CTTFollowCamera.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "CTTPractice/CTTDatatableHeader.h"

// Sets default values
ACTTFollowCamera::ACTTFollowCamera()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(RootComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent);
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
}

void ACTTFollowCamera::InitializeCameraComponents()
{
	SpringArmComponent->TargetArmLength = InitialSpringArmLength;
	TargetArmLength = InitialSpringArmLength;
	SpringArmComponent->SetRelativeRotation(InitialSpringArmRotation);
}

void ACTTFollowCamera::UpdateCameraLocation(float DeltaTime)
{
	if (nullptr == TargetActor)
	{
		//UE_LOG(LogTemp, Error, TEXT("TargetActor is nullptr"));
		return;
	}

	FVector TargetLocation = TargetActor->GetActorLocation();
	FRotator SpringArmRotation = SpringArmComponent->GetComponentRotation();
	FVector CameraLocation = TargetLocation - SpringArmRotation.Vector() * SpringArmComponent->TargetArmLength;

	SpringArmComponent->SetWorldLocation(CameraLocation);
}

void ACTTFollowCamera::UpdateSpringArmData(const FCTTSpringArmData& SpringArmData)
{
	SpringArmComponent->TargetArmLength = SpringArmData.SpringArmLength;
	SpringArmComponent->SetWorldRotation(SpringArmData.SpringArmRotation);
}

void ACTTFollowCamera::SetTarget(AActor* NewTarget)
{
	TargetActor = NewTarget;
}

const USpringArmComponent* ACTTFollowCamera::GetSpringArmComponent() const
{
	if (nullptr == SpringArmComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("SpringArmComponent is nullptr"));
		return nullptr;
	}

	return SpringArmComponent;
}

const UCameraComponent* ACTTFollowCamera::GetCameraComponent() const
{
	if (nullptr == CameraComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("CameraComponent is nullptr"));
		return nullptr;
	}

	return CameraComponent;
}
