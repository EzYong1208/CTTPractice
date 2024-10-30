// Fill out your copyright notice in the Description page of Project Settings.


#include "CTTCharacter.h"
#include "CTTItem.h"
#include "Camera/CameraComponent.h"
#include "CTTCameraControlComponent.h"
#include "Components/CapsuleComponent.h"
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

	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &ACTTCharacter::Attack);


	UCTTCameraControlComponent* CameraControlComponent = FindComponentByClass<UCTTCameraControlComponent>();
	if (nullptr == CameraControlComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("CameraControlComponent is nullptr"));
		return;
	}
	PlayerInputComponent->BindAxis(TEXT("RotateCamera"), CameraControlComponent, &UCTTCameraControlComponent::RotateCamera);
	PlayerInputComponent->BindAction("MoveCameraCloser", IE_Pressed, CameraControlComponent, &UCTTCameraControlComponent::MoveCameraCloser);
	PlayerInputComponent->BindAction("MoveCameraAway", IE_Pressed, CameraControlComponent, &UCTTCameraControlComponent::MoveCameraAway);
}

void ACTTCharacter::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	ACTTItem* Item = Cast<ACTTItem>(OtherActor);
	if (nullptr == Item)
	{
		return;
	}
	
	OverlappingItem = Item;
	ECTTItemCollisionType CollisionType = Item->GetCollisionType();
	switch (CollisionType)
	{
	case ECTTItemCollisionType::Interactable:
		break;

	case ECTTItemCollisionType::Collectible:
		OverlappingItem->CollectAction();
		break;

	case ECTTItemCollisionType::Ladder:
		bIsInLadder = true;
		break;
	}
}

void ACTTCharacter::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);

	ACTTItem* Item = Cast<ACTTItem>(OtherActor);
	if (Item && OverlappingItem == Item)
	{
		OverlappingItem = nullptr;
		UE_LOG(LogTemp, Error, TEXT("NotifyActorEndOverlap"));
	}
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
	UCameraComponent* CameraComponent = Cast<UCameraComponent>(GetComponentByClass(UCameraComponent::StaticClass()));
	if (nullptr == CameraComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("CameraComponent is nullptr"));
		return;
	}

	FRotator CameraRotation = CameraComponent->GetComponentRotation();
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

void ACTTCharacter::Attack()
{
	if (false == bCanAttack)
	{
		UE_LOG(LogTemp, Error, TEXT("bCanAttack is false"));
		return;
	}

	if (OverlappingItem)
	{
		OverlappingItem->DoAction();
	}

	bCanAttack = false;
}