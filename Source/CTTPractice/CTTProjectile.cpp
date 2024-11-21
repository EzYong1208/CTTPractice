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

	// 초기 Z 높이 오프셋 적용
	float InitialZHeight = GetActorLocation().Z;
	float ZOffset = PositionOffset.Z;
	float FixedInitialHeight = InitialZHeight + ZOffset;

	// 최대 이동시간 계산
	float TimeToReachHighest = InitialVerticalVelocity / -PROJECTILE_GRAVITY;
	float HighestHeight = FixedInitialHeight + (InitialVerticalVelocity * TimeToReachHighest) + (0.5f * PROJECTILE_GRAVITY * FMath::Square(TimeToReachHighest));

	// 전체 비행시간
	float TimeToFall = FMath::Sqrt(2 * HighestHeight / -PROJECTILE_GRAVITY);
	float TotalFlightTime = TimeToReachHighest + TimeToFall;

	// 최대 이동거리 계산
	MaxTravelDistance = InitialForwardSpeed * TotalFlightTime;
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
	for (AActor* OverlappingActor : GetOverlappingActors())
	{
		CheckOverlap(OverlappingActor);
	}

	FVector PreviousLocation = GetActorLocation();

	CurrentTime += DeltaTime;

	FVector Gravity(0, 0, PROJECTILE_GRAVITY * DeltaTime);
	Velocity += Gravity;
	FVector NewLocation = GetActorLocation() + Velocity * DeltaTime;

	SetActorLocation(NewLocation);

	float DistanceThisFrame = FVector::Dist(PreviousLocation, NewLocation);
	CurrentTravelDistance += DistanceThisFrame;

	if (CurrentTravelDistance >= MaxTravelDistance)
	{
		UE_LOG(LogTemp, Warning, TEXT("Projectile reached maximum travel distance"));

		ChangeState(ECTTProjectileState::Destroy);
	}
}

void ACTTProjectile::HandleStateDestroy(float DeltaTime)
{
	Destroy();
}

void ACTTProjectile::CheckOverlap(AActor* OtherActor)
{
	if (nullptr == OtherActor)
	{
		return;
	}

	ACTTMapObject* MapObject = Cast<ACTTMapObject>(OtherActor);
	if (nullptr == MapObject)
	{
		return;
	}

	if (CollisionSphereComponent->IsOverlappingActor(OtherActor))
	{
		UE_LOG(LogTemp, Warning, TEXT("Projectile is overlapping with %s"), *OtherActor->GetName());

		MapObject->HandleCollisionEvent(CollisionType);
		ChangeState(ECTTProjectileState::Destroy);
	}
}

TArray<AActor*> ACTTProjectile::GetOverlappingActors() const
{
	TArray<AActor*> OverlappingActors;
	CollisionSphereComponent->GetOverlappingActors(OverlappingActors);
	return OverlappingActors;
}
