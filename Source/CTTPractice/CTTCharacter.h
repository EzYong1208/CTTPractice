// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CTTCharacter.generated.h"

class UCTTSocketAttachmentComponent;
class UCTTCameraControlComponent;

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
	UPROPERTY(VisibleAnywhere)
	UCTTSocketAttachmentComponent* SocketAttachmentComponent;

	UPROPERTY(VisibleAnywhere)
	UCTTCameraControlComponent* CameraControlComponent;

private:
	void MoveUpDown(float InputValue);
	void MoveLeftRight(float InputValue);
};
