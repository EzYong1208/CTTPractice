// Fill out your copyright notice in the Description page of Project Settings.


#include "CTTCharacter.h"
#include "CTTSocketAttachmentComponent.h"
#include "CTTCameraControlComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ACTTCharacter::ACTTCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SocketAttachmentComponent = CreateDefaultSubobject<UCTTSocketAttachmentComponent>(TEXT("SocketAttachmentComponent"));
	CameraControlComponent = CreateDefaultSubobject<UCTTCameraControlComponent>(TEXT("CameraControlComponent"));
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

	CameraControlComponent->CameraMovement(DeltaTime);
}

// Called to bind functionality to input
void ACTTCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveUpDown"), this, &ACTTCharacter::MoveUpDown);
	PlayerInputComponent->BindAxis(TEXT("MoveLeftRight"), this, &ACTTCharacter::MoveLeftRight);

	PlayerInputComponent->BindAction("RotateCameraLeft", IE_Pressed, CameraControlComponent, &UCTTCameraControlComponent::RotateCameraLeft);
	PlayerInputComponent->BindAction("RotateCameraRight", IE_Pressed, CameraControlComponent, &UCTTCameraControlComponent::RotateCameraRight);
	PlayerInputComponent->BindAction("MoveCameraCloser", IE_Pressed, CameraControlComponent, &UCTTCameraControlComponent::MoveCameraCloser);
	PlayerInputComponent->BindAction("MoveCameraAway", IE_Pressed, CameraControlComponent, &UCTTCameraControlComponent::MoveCameraAway);
}

void ACTTCharacter::MoveUpDown(float InputValue)
{
	AddMovementInput(GetActorForwardVector(), InputValue);
}

void ACTTCharacter::MoveLeftRight(float InputValue)
{
	AddMovementInput(GetActorRightVector(), InputValue);
}
