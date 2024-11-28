// Fill out your copyright notice in the Description page of Project Settings.


#include "CTTCharacter.h"
#include "CTTItem.h"
#include "CTTCameraManager.h"
#include "CTTPractice/CTTGameInstance.h"
#include "Camera/CameraComponent.h"
#include "CTTCharacterFollowCamera.h"
#include "CTTProjectile.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "CTTPractice/CTTPracticeGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "CTTInteractionComponent.h"

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

	UCTTInteractionComponent* InteractionComponent = FindComponentByClass<UCTTInteractionComponent>();
	if (nullptr == InteractionComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("InteractionComponent is nullptr"));
		return;
	}

	PlayerInputComponent->BindAction("Interaction", IE_Pressed, InteractionComponent, &UCTTInteractionComponent::ToggleInteraction);
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
	ECTTCollisionType ItemCollisionType = Item->GetCollisionType();
	switch (ItemCollisionType)
	{
	case ECTTCollisionType::Interactable:
		break;

	case ECTTCollisionType::Collectible:
		OverlappingItem->CollectAction();
		break;

	case ECTTCollisionType::Ladder:
		//bIsInLadder = true;
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
	UCTTGameInstance* GameInstance = Cast<UCTTGameInstance>(UGameplayStatics::GetGameInstance(this));
	if (nullptr == GameInstance)
	{
		UE_LOG(LogTemp, Error, TEXT("GameInstance is nullptr"));
		return;
	}

	UCTTCameraManager* CameraManager = GameInstance->GetCameraManager();
	if (nullptr == CameraManager)
	{
		UE_LOG(LogTemp, Error, TEXT("CameraManager is nullptr"));
		return;
	}

	ACTTCharacterFollowCamera* FollowCamera = CameraManager->GetFollowCamera();
	if (nullptr == FollowCamera)
	{
		UE_LOG(LogTemp, Error, TEXT("FollowCamera is nullptr"));
		return;
	}

	UCameraComponent* CameraComponent = FollowCamera->GetCameraComponent();
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

void ACTTCharacter::RotateCamera(float InputValue)
{
	UCTTGameInstance* GameInstance = Cast<UCTTGameInstance>(UGameplayStatics::GetGameInstance(this));
	if (nullptr == GameInstance)
	{
		UE_LOG(LogTemp, Error, TEXT("GameInstance is nullptr"));
		return;
	}

	UCTTCameraManager* CameraManager = GameInstance->GetCameraManager();
	if (nullptr == CameraManager)
	{
		UE_LOG(LogTemp, Error, TEXT("CameraManager is nullptr"));
		return;
	}

	ACTTCharacterFollowCamera* FollowCamera = CameraManager->GetFollowCamera();
	if (nullptr == FollowCamera)
	{
		UE_LOG(LogTemp, Error, TEXT("FollowCamera is nullptr"));
		return;
	}

	FollowCamera->RotateCamera(InputValue);
}

void ACTTCharacter::MoveCameraCloser()
{
	UCTTGameInstance* GameInstance = Cast<UCTTGameInstance>(UGameplayStatics::GetGameInstance(this));
	if (nullptr == GameInstance)
	{
		UE_LOG(LogTemp, Error, TEXT("GameInstance is nullptr"));
		return;
	}

	UCTTCameraManager* CameraManager = GameInstance->GetCameraManager();
	if (nullptr == CameraManager)
	{
		UE_LOG(LogTemp, Error, TEXT("CameraManager is nullptr"));
		return;
	}

	ACTTCharacterFollowCamera* FollowCamera = CameraManager->GetFollowCamera();
	if (nullptr == FollowCamera)
	{
		UE_LOG(LogTemp, Error, TEXT("FollowCamera is nullptr"));
		return;
	}

	FollowCamera->MoveCameraCloser();
}

void ACTTCharacter::MoveCameraAway()
{
	UCTTGameInstance* GameInstance = Cast<UCTTGameInstance>(UGameplayStatics::GetGameInstance(this));
	if (nullptr == GameInstance)
	{
		UE_LOG(LogTemp, Error, TEXT("GameInstance is nullptr"));
		return;
	}

	UCTTCameraManager* CameraManager = GameInstance->GetCameraManager();
	if (nullptr == CameraManager)
	{
		UE_LOG(LogTemp, Error, TEXT("CameraManager is nullptr"));
		return;
	}

	ACTTCharacterFollowCamera* FollowCamera = CameraManager->GetFollowCamera();
	if (nullptr == FollowCamera)
	{
		UE_LOG(LogTemp, Error, TEXT("FollowCamera is nullptr"));
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

		bool bSpawnProjectileSuccess = SpawnProjectile();
		if (false == bSpawnProjectileSuccess)
		{
			UE_LOG(LogTemp, Error, TEXT("SpawnedProjectile has failed"));
			return;
		}

		bIsHolding = true;
	}
	else
	{
		if (nullptr == SpawnedProjectile)
		{
			UE_LOG(LogTemp, Error, TEXT("SpawnedProjectile is nullptr"));
			return;
		}

		SpawnedProjectile->StopFollowingCharacter();
		bIsHolding = false;
		SpawnedProjectile = nullptr;
	}
}

bool ACTTCharacter::SpawnProjectile()
{
	if (nullptr == ProjectileClass)
	{
		UE_LOG(LogTemp, Error, TEXT("ProjectileClass is nullptr"));
		return false;
	}

	const ACTTProjectile* DefaultProjectile = ProjectileClass->GetDefaultObject<ACTTProjectile>();
	if (nullptr == DefaultProjectile)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to get default object for ProjectileClass"));
		return false;
	}

	FVector PositionOffset = DefaultProjectile->PositionOffset;
	FVector SpawnLocation = GetActorLocation() + PositionOffset;
	FRotator SpawnRotation = FRotator::ZeroRotator;
	ACTTProjectile* NewProjectile = GetWorld()->SpawnActor<ACTTProjectile>(ProjectileClass, SpawnLocation, SpawnRotation);
	if (false == IsValid(NewProjectile))
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to spawn NewProjectile"));
		return false;
	}

	NewProjectile->FollowCharacter(this);
	SpawnedProjectile = NewProjectile;

	return true;
}