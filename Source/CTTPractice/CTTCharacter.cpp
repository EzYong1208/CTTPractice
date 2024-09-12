// Fill out your copyright notice in the Description page of Project Settings.


#include "CTTCharacter.h"
#include "CTTSocketAttachmentComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ACTTCharacter::ACTTCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SocketAttachmentComponent = CreateDefaultSubobject<UCTTSocketAttachmentComponent>(TEXT("SocketAttachmentComponent"));

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));

	SpringArmComponent->SetupAttachment(RootComponent);
	CameraComponent->SetupAttachment(SpringArmComponent);
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

}

// Called to bind functionality to input
void ACTTCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveUpDown"), this, &ACTTCharacter::MoveUpDown);
	PlayerInputComponent->BindAxis(TEXT("MoveLeftRight"), this, &ACTTCharacter::MoveLeftRight);

	PlayerInputComponent->BindAxis(TEXT("TurnCamera"), this, &ACTTCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis(TEXT("LookUpCamera"), this, &ACTTCharacter::AddControllerPitchInput);
}

void ACTTCharacter::MoveUpDown(float InputValue)
{
	AddMovementInput(GetActorForwardVector(), InputValue);
}

void ACTTCharacter::MoveLeftRight(float InputValue)
{
	AddMovementInput(GetActorRightVector(), InputValue);
}

void ACTTCharacter::TurnCamera(float InputValue)
{
	AddControllerYawInput(InputValue);
}

