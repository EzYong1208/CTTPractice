// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CTTFollowCamera.generated.h"

struct FCTTSpringArmData;
class USpringArmComponent;
class UCameraComponent;
class ACTTCharacter;

UCLASS()
class CTTPRACTICE_API ACTTFollowCamera : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACTTFollowCamera();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	void InitializeCameraComponents();
	void UpdateCameraLocation(float DeltaTime);
	void UpdateSpringArmData(const FCTTSpringArmData& SpringArmData);
	void SetTarget(AActor* NewTarget);

public:
	const USpringArmComponent* GetSpringArmComponent() const;
	const UCameraComponent* GetCameraComponent() const;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float InitialSpringArmLength = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	FRotator InitialSpringArmRotation = FRotator(0.f, 0.f, 0.f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float RotationSpeed = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float CameraZoomSpeed = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float MinSpringArmLength = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float MaxSpringArmLength = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float CameraMoveDistance = 0.f;

	FVector OwnerLocation = FVector(0.f, 0.f, 0.f);
	float TargetArmLength = 0.f;

	UPROPERTY()
	USpringArmComponent* SpringArmComponent = nullptr;

	UPROPERTY()
	UCameraComponent* CameraComponent = nullptr;

	UPROPERTY()
	AActor* TargetActor = nullptr;
};
