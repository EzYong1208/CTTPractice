// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "CTTCameraControlComponent.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CTTPRACTICE_API UCTTCameraControlComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCTTCameraControlComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RotationSpeed = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CameraRotationAngle = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MinSpringArmLength = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxSpringArmLength = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CameraMoveDistance = 0.f;

	float GoalRotationValue = 0.f;
	float TargetArmLength = 0.f;

public:
	void CameraMovement(float DeltaTime);
	void RotateCameraLeft();
	void RotateCameraRight();
	void MoveCameraCloser();
	void MoveCameraAway();
};
