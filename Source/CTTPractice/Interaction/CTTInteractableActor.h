// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CTTPractice/CTTStruct.h"
#include "CTTInteractableActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCTTOnEnterInteract, const FCTTInteractionInfo&, InteractionInfo);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCTTOnInteract);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCTTOnExitInteract);

class UWidgetComponent;

UCLASS()
class CTTPRACTICE_API ACTTInteractableActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACTTInteractableActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION(BlueprintCallable)
	virtual void OnEnterInteract(const FCTTInteractionInfo& InteractionInfo);

	UFUNCTION(BlueprintCallable)
	virtual void OnInteract();

	UFUNCTION(BlueprintCallable)
	virtual void OnExitInteract();

	float GetMinInteractionDistance() const { return MinInteractionDistance; }
	void SetInteractionWidgetComponentVisibility(bool bNewVisibility);

public:
	FCTTOnEnterInteract OnEnterInteractDelegate;
	FCTTOnInteract OnInteractDelegate;
	FCTTOnExitInteract OnExitInteractDelegate;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MinInteractionDistance = 0.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    UWidgetComponent* InteractionWidgetComponent;
};
