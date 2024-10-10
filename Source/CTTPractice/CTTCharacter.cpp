// Fill out your copyright notice in the Description page of Project Settings.


#include "CTTCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "CTTCameraActor.h"
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

	PlayerInputComponent->BindAction("MoveCameraCloser", IE_Pressed, this, &ACTTCharacter::MoveCameraCloser);
	PlayerInputComponent->BindAction("MoveCameraAway", IE_Pressed, this, &ACTTCharacter::MoveCameraAway);

	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &ACTTCharacter::Attack);
}

void ACTTCharacter::SetCharacterAttack(bool InbCanAttack)
{
	bCanAttack = InbCanAttack;
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
	if (false == CameraActor.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("CameraActor is not Valid"));
		return;
	}

	FRotator CameraRotation = CameraActor->GetActorRotation();
	FRotator YawRotation(0, CameraRotation.Yaw, 0);

	FVector CameraForward = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	FVector CameraRight = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	FVector ForwardMovement = CameraForward * VerticalMovementInput;
	FVector RightMovement = CameraRight * HorizontalMovementInput;
	FVector MovementDirection = ForwardMovement + RightMovement;

	MovementDirection.Normalize();
	Speed = MovementDirection.Size();

	if (true == MovementDirection.IsZero())
	{
		return;
	}
	
	AddMovementInput(MovementDirection, Speed);

	FRotator NewRotation = MovementDirection.Rotation();
	SetActorRotation(FRotator(0.0f, NewRotation.Yaw, 0.0f));
}

void ACTTCharacter::RotateCamera(float InputValue)
{
	if (InputValue != 0.0f && 
		true == CameraActor.IsValid())
	{
		CameraActor->RotateCamera(InputValue);
	}
}

void ACTTCharacter::MoveCameraCloser()
{
	if (false == CameraActor.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("CameraActor is not Valid"));
		return;
	}

	CameraActor->MoveCameraCloser();
}

void ACTTCharacter::MoveCameraAway()
{
	if (false == CameraActor.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("CameraActor is not Valid"));
		return;
	}

	CameraActor->MoveCameraAway();
}

void ACTTCharacter::Attack()
{
	//UE_LOG(LogTemp, Error, TEXT("Attack"));

	if (false == bCanAttack)
	{
		UE_LOG(LogTemp, Error, TEXT("bCanAttack is false"));
		return;
	}

	bCanAttack = false;
}
