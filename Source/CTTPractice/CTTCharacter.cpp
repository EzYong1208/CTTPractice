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
	SpringArmComponent->SetupAttachment(RootComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent);
}

// Called when the game starts or when spawned
void ACTTCharacter::BeginPlay()
{
	Super::BeginPlay();

	TargetArmLength = SpringArmComponent->TargetArmLength;
}

// Called every frame
void ACTTCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CameraMovement(DeltaTime);
}

// Called to bind functionality to input
void ACTTCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveUpDown"), this, &ACTTCharacter::MoveUpDown);
	PlayerInputComponent->BindAxis(TEXT("MoveLeftRight"), this, &ACTTCharacter::MoveLeftRight);

	// Ä«¸Þ¶ó
	PlayerInputComponent->BindAction(TEXT("RotateCameraLeft"), IE_Pressed, this, &ACTTCharacter::RotateCameraLeft);
	PlayerInputComponent->BindAction(TEXT("RotateCameraRight"), IE_Pressed, this, &ACTTCharacter::RotateCameraRight);
	PlayerInputComponent->BindAction(TEXT("MoveCameraCloser"), IE_Pressed, this, &ACTTCharacter::MoveCameraCloser);
	PlayerInputComponent->BindAction(TEXT("MoveCameraAway"), IE_Pressed, this, &ACTTCharacter::MoveCameraAway);
}

void ACTTCharacter::MoveUpDown(float InputValue)
{
	AddMovementInput(GetActorForwardVector(), InputValue);
}

void ACTTCharacter::MoveLeftRight(float InputValue)
{
	AddMovementInput(GetActorRightVector(), InputValue);
}

void ACTTCharacter::CameraMovement(float DeltaTime)
{
	FRotator CurrentRotation = SpringArmComponent->GetRelativeRotation();
	FRotator TargetRotation(0.0f, GoalRotationValue, 0.0f);

	FRotator NewRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, DeltaTime, RotationSpeed);

	SpringArmComponent->SetRelativeRotation(NewRotation);
	SpringArmComponent->TargetArmLength = FMath::FInterpTo(SpringArmComponent->TargetArmLength, TargetArmLength, DeltaTime, RotationSpeed);
}

void ACTTCharacter::RotateCameraLeft()
{
	GoalRotationValue -= CameraRotationAngle;
}

void ACTTCharacter::RotateCameraRight()
{
	GoalRotationValue += CameraRotationAngle;
}

void ACTTCharacter::MoveCameraCloser()
{
	TargetArmLength = FMath::Clamp(SpringArmComponent->TargetArmLength - CameraMoveDistance, MinSpringArmLength, MaxSpringArmLength);
	UE_LOG(LogTemp, Warning, TEXT("Moving Closer: %f"), TargetArmLength);
}

void ACTTCharacter::MoveCameraAway()
{
	TargetArmLength = FMath::Clamp(SpringArmComponent->TargetArmLength + CameraMoveDistance, MinSpringArmLength, MaxSpringArmLength);
	UE_LOG(LogTemp, Warning, TEXT("Moving Away: %f"), TargetArmLength);
}
