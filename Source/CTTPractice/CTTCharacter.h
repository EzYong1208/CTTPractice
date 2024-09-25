// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CTTCharacter.generated.h"

class UCTTSocketAttachmentComponent;
class UCTTCameraControlComponent;
//class USpringArmComponent;
//class UCameraComponent;

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

	//UPROPERTY(VisibleAnywhere)
	//USpringArmComponent* SpringArmComponent;

	//UPROPERTY(VisibleAnywhere)
	//UCameraComponent* CameraComponent;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//float RotationSpeed = 0.f;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//float CameraRotationAngle = 0.f;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//float MinSpringArmLength = 0.f;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//float MaxSpringArmLength = 0.f;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//float CameraMoveDistance = 0.f;

	//float GoalRotationValue = 0.f;
	//float TargetArmLength = 0.f;

private:
	void MoveUpDown(float InputValue);
	void MoveLeftRight(float InputValue);
	//void CameraMovement(float DeltaTime);
	//void RotateCameraLeft();
	//void RotateCameraRight();
	//void MoveCameraCloser();
	//void MoveCameraAway();
};
