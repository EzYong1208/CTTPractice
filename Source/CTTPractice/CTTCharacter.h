// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CTTCharacter.generated.h"

class ACTTCameraActor;

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

public:
	float GetCharacterSpeed() const { return Speed; }
	bool CheckCharacterAttack() const { return bCanAttack; }

	void SetCharacterAttack(bool InbCanAttack);

protected:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	float Speed = 0.f;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	bool bCanAttack = true;

private:
	void MoveUpDown(float InputValue);
	void MoveLeftRight(float InputValue);

	void UpdateMoveVector(float DeltaTime);

	void Attack();

private:
	float VerticalMovementInput = 0.f;
	float HorizontalMovementInput = 0.f;
};
