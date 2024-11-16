// Fill out your copyright notice in the Description page of Project Settings.


#include "CTTProjectile.h"
#include "CTTCharacter.h"
#include "Components/SphereComponent.h"
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
}

// Called every frame
void ACTTProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (true == bIsFollowingCharacter &&
		true == AttachedCharacter.IsValid())
	{
		const FVector HeadLocation = AttachedCharacter->GetActorLocation() + PositionOffset;
		SetActorLocation(HeadLocation);

		const FRotator CharacterRotation = AttachedCharacter->GetActorRotation();
		SetActorRotation(CharacterRotation);
	}
	else
	{
		UpdateProjectileMovement(DeltaTime);
	}

	UE_LOG(LogTemp, Log, TEXT("Current Location: %s"), *GetActorLocation().ToString());
}

void ACTTProjectile::UpdateProjectileMovement(float DeltaTime)
{

}

void ACTTProjectile::InitializeProjectile(const FCTTProjectileData& ProjectileData)
{
	USkeletalMeshComponent* SkeletalMeshComponent = NewObject<USkeletalMeshComponent>(this, USkeletalMeshComponent::StaticClass(), TEXT("SkeletalMeshComponent"));

	if (false == IsValid(SkeletalMeshComponent))
	{
		UE_LOG(LogTemp, Warning, TEXT("SkeletalMeshComponent NewObject failed"));
		return;
	}

	SkeletalMeshComponent->SetSkeletalMesh(ProjectileData.SkeletalMesh);

	if (ProjectileData.AnimBlueprintClass)
	{
		SkeletalMeshComponent->SetAnimInstanceClass(ProjectileData.AnimBlueprintClass);
	}

	if (IsValid(SkeletalMeshComponent))
	{
		SkeletalMeshComponent->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
		SkeletalMeshComponent->RegisterComponent();
		SkeletalMeshComponent->SetRelativeLocation(ProjectileData.MeshLocation);
		FRotator Rotation = FRotator::MakeFromEuler(ProjectileData.RotationOffset);
		SkeletalMeshComponent->SetRelativeRotation(Rotation);
	}

	CollisionSphereComponent->SetSphereRadius(ProjectileData.SphereRadius);
	Name = ProjectileData.Name;
	PositionOffset = ProjectileData.PositionOffset;
	RotationOffset = FRotator::MakeFromEuler(ProjectileData.RotationOffset);
	MaxDistance = ProjectileData.MaxDistance;
}

void ACTTProjectile::FollowCharacter(ACharacter* Character)
{
	if (nullptr == Character)
	{
		return;
	}
	
	AttachedCharacter = Cast<ACTTCharacter>(Character);
	bIsFollowingCharacter = true;
}

void ACTTProjectile::StopFollowingCharacter()
{
	bIsFollowingCharacter = false;
}
