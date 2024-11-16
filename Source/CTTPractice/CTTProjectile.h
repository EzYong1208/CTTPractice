// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CTTPractice/CTTStruct.h"
#include "CTTProjectile.generated.h"

class ACTTCharacter;
class USphereComponent;

UCLASS()
class CTTPRACTICE_API ACTTProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACTTProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	void UpdateProjectileMovement(float DeltaTime);
	void InitializeProjectile(const FCTTProjectileData& ProjectileData);

	void FollowCharacter(ACharacter* Character);
	void StopFollowingCharacter();

private:
	FName Name;
	FVector PositionOffset;
	FRotator RotationOffset;
	float SphereRadius = 0.f;
	float MaxDistance = 0.f;
	bool bIsFollowingCharacter = true;

private:
	UPROPERTY()
	USphereComponent* CollisionSphereComponent;

	UPROPERTY()
	TWeakObjectPtr<ACTTCharacter> AttachedCharacter;
};
