// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CTTPractice/CTTStruct.h"
#include "CTTInteractionComponent.generated.h"

class ACTTInteractableActor;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CTTPRACTICE_API UCTTInteractionComponent : public UActorComponent
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
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	void ToggleInteraction();
	void BeginInteraction();
	void EndInteraction();

	const bool GetIsInteracting() const { return bIsInteracting; }

private:
	bool DetectInteractable(FHitResult& OutHitResult);
	bool FindClosestOverlap(const TArray<FOverlapResult>& OverlapResults, const FVector& Start, FHitResult& OutHitResult);
	void AdjustCharacterPositionToInteractableActor(TWeakObjectPtr<ACTTInteractableActor> InteractableActor);
	void PeriodicDetectInteractable();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CapsuleRadius = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CapsuleHalfHeight = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DetectHeight = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DetectDistance = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float InteractionCooldownTime = 0.f;

private:
	bool bIsInteracting = false;
	TMap<TWeakObjectPtr<ACTTInteractableActor>, float> OverlappingInteractables;
	TWeakObjectPtr<ACTTInteractableActor> ClosestInteractable;
	TWeakObjectPtr<ACTTInteractableActor> PreviousClosestInteractable;
	FTimerHandle DetectInteractableTimerHandle;
};
