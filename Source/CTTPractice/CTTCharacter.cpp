// Fill out your copyright notice in the Description page of Project Settings.


#include "CTTCharacter.h"
#include "CTTItem.h"
#include "Camera/CameraComponent.h"
#include "CTTCameraManager.h"
#include "CTTFollowCamera.h"
#include "CTTProjectile.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "CTTPractice/CTTPracticeGameModeBase.h"
#include "Kismet/GameplayStatics.h"

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

	// TODO : 투사체 함수 수정할 것
	PlayerInputComponent->BindAction("Test", IE_Pressed, this, &ACTTCharacter::Test);

	PlayerInputComponent->BindAxis(TEXT("RotateCamera"), this, &ACTTCharacter::RotateCamera);
	PlayerInputComponent->BindAction("MoveCameraCloser", IE_Pressed, this, &ACTTCharacter::MoveCameraCloser);
	PlayerInputComponent->BindAction("MoveCameraAway", IE_Pressed, this, &ACTTCharacter::MoveCameraAway);
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
	UCTTCameraManager* CameraManager = GetWorld()->GetSubsystem<UCTTCameraManager>();
	if (nullptr == CameraManager)
	{
		UE_LOG(LogTemp, Error, TEXT("CameraManager is nullptr"));
		return;
	}

	TWeakObjectPtr<ACTTFollowCamera> FollowCamera = CameraManager->GetFollowCamera();
	if (false == FollowCamera.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("FollowCamera is not valid"));
		return;
	}

	TWeakObjectPtr<UCameraComponent> CameraComponent = FollowCamera->GetCameraComponent();
	if (false == CameraComponent.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("CameraComponent is not valid"));
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

void ACTTCharacter::RotateCamera(float InputValue)
{
	UCTTCameraManager* CameraManager = GetWorld()->GetSubsystem<UCTTCameraManager>();
	if (nullptr == CameraManager)
	{
		UE_LOG(LogTemp, Error, TEXT("CameraManager is nullptr"));
		return;
	}

	TWeakObjectPtr<ACTTFollowCamera> FollowCamera = CameraManager->GetFollowCamera();
	if (false == FollowCamera.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("FollowCamera is not valid"));
		return;
	}

	FollowCamera->RotateCamera(InputValue);
}

void ACTTCharacter::MoveCameraCloser()
{
	UCTTCameraManager* CameraManager = GetWorld()->GetSubsystem<UCTTCameraManager>();
	if (nullptr == CameraManager)
	{
		UE_LOG(LogTemp, Error, TEXT("CameraManager is nullptr"));
		return;
	}

	TWeakObjectPtr<ACTTFollowCamera> FollowCamera = CameraManager->GetFollowCamera();
	if (false == FollowCamera.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("FollowCamera is not valid"));
		return;
	}

	FollowCamera->MoveCameraCloser();
}

void ACTTCharacter::MoveCameraAway()
{
	UCTTCameraManager* CameraManager = GetWorld()->GetSubsystem<UCTTCameraManager>();
	if (nullptr == CameraManager)
	{
		UE_LOG(LogTemp, Error, TEXT("CameraManager is nullptr"));
		return;
	}

	TWeakObjectPtr<ACTTFollowCamera> FollowCamera = CameraManager->GetFollowCamera();
	if (false == FollowCamera.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("FollowCamera is not valid"));
		return;
	}

	FollowCamera->MoveCameraAway();
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

void ACTTCharacter::Test()
{
	if (false == bIsHolding)
	{
		ACTTPracticeGameModeBase* GameMode = Cast<ACTTPracticeGameModeBase>(UGameplayStatics::GetGameMode(this));
		if (false == IsValid(GameMode))
		{
			UE_LOG(LogTemp, Error, TEXT("GameMode is InValid"));
			return;
		}

		FName TestName = TEXT("Radish");
		SpawnedProjectile = GameMode->SpawnProjectile(this, TestName);
		bIsHolding = true;
	}
	else
	{
		if (false == SpawnedProjectile.IsValid())
		{
			UE_LOG(LogTemp, Error, TEXT("SpawnedProjectile is InValid"));
			return;
		}

		SpawnedProjectile->StopFollowingCharacter();
		bIsHolding = false;
		SpawnedProjectile = nullptr;
	}
}
