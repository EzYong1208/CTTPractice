// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "CTTPractice/CTTStruct.h"
#include "CTTInteractionComponent.generated.h"

class UCTTInteractableComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CTTPRACTICE_API UCTTInteractionComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCTTInteractionComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	void BeginInteraction();
	void EndInteraction();

private:
	bool DetectInteractable(FHitResult& OutHitResult);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<ECollisionChannel> TraceChannel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DetectHeight = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DetectDistance = 0.f;

private:
	bool bIsInteracting = false;
	
	UPROPERTY()
	UCTTInteractableComponent* CurrentInteractable = nullptr;
};