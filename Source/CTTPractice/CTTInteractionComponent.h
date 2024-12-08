// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "CTTPractice/CTTStruct.h"
#include "CTTInteractionComponent.generated.h"

class UCTTInteractableComponent;
class ACTTInteractableActor;

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
	void ToggleInteraction();
	void BeginInteraction();
	void EndInteraction();

	bool GetIsInteracting() const { return bIsInteracting; }

private:
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void FindClosestInteractable();
	void AdjustCharacterPositionToInteractableActor(ACTTInteractableActor* InteractableActor);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<ECollisionChannel> TraceChannel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CapsuleRadius = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CapsuleHalfHeight = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DetectHeight = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DetectDistance = 0.f;

private:
	bool bIsInteracting = false;
	TMap<AActor*, float> OverlappingInteractables;
	
	UPROPERTY()
	UCTTInteractableComponent* CurrentInteractable = nullptr;

	UPROPERTY()
	AActor* PreviousClosestInteractable = nullptr;
};
