// Fill out your copyright notice in the Description page of Project Settings.


#include "CTTProjectile.h"
#include "CTTCharacter.h"
#include "CTTMapObject.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACTTProjectile::ACTTProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionSphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphereComponent"));
	SetRootComponent(CollisionSphereComponent);
}

// Called when the game starts or when spawned
void ACTTProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	CollisionSphereComponent->SetSphereRadius(SphereRadius);

	USkeletalMeshComponent* SkeletalMeshComponent = FindComponentByClass<USkeletalMeshComponent>();
	FRotator Rotation = FRotator::MakeFromEuler(RotationOffset);
	SkeletalMeshComponent->SetRelativeRotation(Rotation);
}

// Called every frame
void ACTTProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	switch (CurrentState)
	{
	case ECTTProjectileState::FollowingCharacter:
		HandleStateFollowingCharacter(DeltaTime);
		break;

	case ECTTProjectileState::IndependentMovement:
		HandleStateIndependentMovement(DeltaTime);
		break;

	case ECTTProjectileState::Destroy:
		HandleStateDestroy(DeltaTime);
		break;

	default:
		break;
	}
}

void ACTTProjectile::InitializeProjectilePath()
{
	FVector ForwardDirection = GetActorForwardVector();
	Velocity = ForwardDirection * InitialForwardSpeed + FVector(0.0f, 0.0f, InitialVerticalVelocity);
	GroundZ = AttachedCharacter->GetActorLocation().Z;
}

void ACTTProjectile::FollowCharacter(ACharacter* Character)
{
	if (nullptr == Character)
	{
		return;
	}

	AttachedCharacter = Cast<ACTTCharacter>(Character);
	ChangeState(ECTTProjectileState::FollowingCharacter);
}

void ACTTProjectile::StopFollowingCharacter()
{
	ChangeState(ECTTProjectileState::IndependentMovement);

	InitializeProjectilePath();
}

void ACTTProjectile::ChangeState(ECTTProjectileState NewState)
{
	if (NewState == CurrentState)
	{
		return;
	}

	CurrentState = NewState;

	switch (CurrentState)
	{
	case ECTTProjectileState::FollowingCharacter:
		bIsFollowingCharacter = true;
		break;

	case ECTTProjectileState::IndependentMovement:
		bIsFollowingCharacter = false;
		break;

	case ECTTProjectileState::Destroy:
		break;

	default:
		break;
	}
}

void ACTTProjectile::HandleStateFollowingCharacter(float DeltaTime)
{
	if (false == AttachedCharacter.IsValid())
	{
		return;
	}

	const FVector HeadLocation = AttachedCharacter->GetActorLocation() + PositionOffset;
	SetActorLocation(HeadLocation);

	const FRotator CharacterRotation = AttachedCharacter->GetActorRotation();
	SetActorRotation(CharacterRotation);
}

void ACTTProjectile::HandleStateIndependentMovement(float DeltaTime)
{
	CurrentTime += DeltaTime;

	FVector Gravity(0, 0, PROJECTILE_GRAVITY * DeltaTime);
	Velocity += Gravity;
	FVector NewLocation = GetActorLocation() + Velocity * DeltaTime;

	SetActorLocation(NewLocation);

	if (GetActorLocation().Z <= GroundZ)
	{
		ChangeState(ECTTProjectileState::Destroy);
	}
}

void ACTTProjectile::HandleStateDestroy(float DeltaTime)
{
	Destroy();
}
