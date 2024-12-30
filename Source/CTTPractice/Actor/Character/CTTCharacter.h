// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CTTPractice/CTTEnum.h"
#include "CTTCharacter.generated.h"

class ACTTItem;
class ACTTProjectile;

UCLASS()
class CTTPRACTICE_API ACTTCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACTTCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	//virtual void NotifyActorEndOverlap(AActor* OtherActor) override;


public:
	const float GetCharacterSpeed() const { return Speed; }
	const bool CheckCharacterAttack() const { return bCanAttack; }
	const bool CheckCharacterInLadder() const { return bIsInLadder; }

	void SetCharacterAttack(bool bInCanAttack);
	void ToggleInteraction();

public:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	float Speed = 0.f;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	bool bCanAttack = true;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	bool bIsInLadder = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ACTTProjectile> ProjectileClass;

private:
	void MoveUpDown(float InputValue);
	void MoveLeftRight(float InputValue);
	void UpdateMoveVector(float DeltaTime);

	void RotateCamera(float InputValue);
	void MoveCameraCloser();
	void MoveCameraAway();

	void Attack();
	void Test();

	bool SpawnProjectile();

private:
	ECTTCollisionType CollisionType = ECTTCollisionType::None;
	float VerticalMovementInput = 0.f;
	float HorizontalMovementInput = 0.f;

	// EzYong TODO : 테스트용, 수정 필요
	bool bIsHolding = false;
	bool bCanMove = true;
	bool bCanControlCamera = true;

	UPROPERTY()
	TWeakObjectPtr<ACTTProjectile> SpawnedProjectile = nullptr;

	UPROPERTY()
	ACTTItem* OverlappingItem = nullptr;
};
