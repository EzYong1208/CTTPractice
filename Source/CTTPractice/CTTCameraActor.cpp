// Fill out your copyright notice in the Description page of Project Settings.


#include "CTTCameraActor.h"
#include "GameFramework/Character.h"

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
	if (OwningCharacter)
	{
		FVector Direction = GetActorForwardVector();
		OwnerLocation = OwningCharacter->GetActorLocation();
		FVector NewCameraLocation = OwnerLocation - (Direction * CameraDistance);

		bool IsSetLocationSuccess = SetActorLocation(NewCameraLocation);
		if (!IsSetLocationSuccess)
		{
			UE_LOG(LogTemp, Error, TEXT("CameraActor SetLocation failed"));
		}
	}

	bool IsRotateSuccess = SetActorRotation(InitialCameraRotation);
	if (false == IsRotateSuccess)
	{
		UE_LOG(LogTemp, Error, TEXT("CameraActor Rotate failed"));
	}
	
	GoalRotation = InitialCameraRotation;
}

void ACTTCameraActor::CameraMovement(float DeltaTime)
{

}

void ACTTCameraActor::RotateCameraLeft()
{

}
