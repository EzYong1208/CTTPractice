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
	void InitializeProjectilePath();
	void FollowCharacter(ACharacter* Character);
	void StopFollowingCharacter();

	void ChangeState(ECTTProjectileState NewState);

private:
	void HandleStateFollowingCharacter(float DeltaTime);
	void HandleStateIndependentMovement(float DeltaTime);
	void HandleStateDestroy(float DeltaTime);

	bool CheckProjectileCollision(const FVector& StartLocation, const FVector& EndLocation);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float InitialForwardSpeed = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float InitialVerticalVelocity = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector PositionOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector RotationOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SphereRadius = 0.f;

private:
	bool bIsFollowingCharacter = true;

	float CurrentTime = 0.f;
	FVector Velocity;
	float CurrentTravelDistance = 0.f;
	float MaxTravelDistance = 0.f;

	static constexpr float PROJECTILE_GRAVITY = -980.f;

private:
	UPROPERTY()
	USphereComponent* CollisionSphereComponent;

	TWeakObjectPtr<ACTTCharacter> AttachedCharacter;
	ECTTProjectileState CurrentState = ECTTProjectileState::FollowingCharacter;
	ECTTCollisionType CollisionType = ECTTCollisionType::Projectile;
};
