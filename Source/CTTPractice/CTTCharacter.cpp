// Fill out your copyright notice in the Description page of Project Settings.


#include "CTTCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
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
	PlayerInputComponent->BindAxis(TEXT("RotateCamera"), this, &ACTTCharacter::RotateCamera);

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
	UCameraComponent* CameraComponent = Cast<UCameraComponent>(GetComponentByClass(UCameraComponent::StaticClass()));

	if (CameraComponent == nullptr)
	{
		return;
	}

	FRotator CameraRotation = CameraComponent->GetComponentRotation();
	FRotator YawRotation(0, CameraRotation.Yaw, 0);

	FVector CameraForward = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	FVector CameraRight = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	FVector ForwardMovement = CameraForward * VerticalMovementInput;
	FVector RightMovement = CameraRight * HorizontalMovementInput;
	FVector MovementDirection = ForwardMovement + RightMovement;
	
	if (true == MovementDirection.IsZero())
	{
		return;
	}
	
	MovementDirection.Normalize();

	AddMovementInput(MovementDirection, Speed);

	FRotator NewRotation = MovementDirection.Rotation();
	SetActorRotation(FRotator(0.0f, NewRotation.Yaw, 0.0f));
}

void ACTTCharacter::RotateCamera(float InputValue)
{
	if (InputValue != 0.0f)
	{
		USpringArmComponent* SpringArmComponent = Cast<USpringArmComponent>(GetComponentByClass(USpringArmComponent::StaticClass()));

		FRotator RotationDelta(0.0f, InputValue * 2.f * GetWorld()->DeltaTimeSeconds * CAMERA_ROTATE_SPEED, 0.0f);
		FRotator NewRotation = SpringArmComponent->GetComponentRotation() + RotationDelta;

		SpringArmComponent->SetWorldRotation(NewRotation);
	}
}