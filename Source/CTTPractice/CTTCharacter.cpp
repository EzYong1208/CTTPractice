// Fill out your copyright notice in the Description page of Project Settings.


#include "CTTCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ACTTCharacter::ACTTCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACTTCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACTTCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateMoveVector(DeltaTime);
}

// Called to bind functionality to input
void ACTTCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveUpDown"), this, &ACTTCharacter::MoveUpDown);
	PlayerInputComponent->BindAxis(TEXT("MoveLeftRight"), this, &ACTTCharacter::MoveLeftRight);

	// TODO : 카메라 세팅 후 정리하기
	//// 카메라
	//PlayerInputComponent->BindAction("RotateCameraLeft", IE_Pressed, CameraControl, &UCTTCameraControlComponent::RotateCameraLeft);
	//PlayerInputComponent->BindAction("RotateCameraRight", IE_Pressed, CameraControl, &UCTTCameraControlComponent::RotateCameraRight);
	//PlayerInputComponent->BindAction("MoveCameraCloser", IE_Pressed, CameraControl, &UCTTCameraControlComponent::MoveCameraCloser);
	//PlayerInputComponent->BindAction("MoveCameraAway", IE_Pressed, CameraControl, &UCTTCameraControlComponent::MoveCameraAway);
}

void ACTTCharacter::MoveUpDown(float InputValue)
{
	VerticalMovementInput = InputValue;
}

void ACTTCharacter::MoveLeftRight(float InputValue)
{
	HorizontalMovementInput = InputValue;
}

void ACTTCharacter::UpdateMoveVector(float DeltaTime)
{
	//float MoveAngle = VerticalMovementInput 더하기 HorizontalMovementInput;
	//AddMovementInput(GetDirection(MoveAngle), Speed);

	FVector ForwardVector = GetActorForwardVector() * VerticalMovementInput;
	FVector RightVector = GetActorRightVector() * HorizontalMovementInput;
	FVector MovementDirection = ForwardVector + RightVector;

	if (true == MovementDirection.IsZero())
	{
		return;
	}

	MovementDirection.Normalize();
	AddMovementInput(MovementDirection, Speed);
}

FVector GetDirection(float Angle)
{
	FVector ResultDirection;

	// 현재 카메라의 Direction을 upvector를 기준으로 Angle 만큼 회전시켜서 ResultDirection을 return
	// 카메라의 2dDirection 기준으로 내 컨트롤
	// 컨트롤러의 방향값의 월드에서 벡터값

	return ResultDirection;
}