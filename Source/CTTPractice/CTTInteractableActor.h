// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CTTInteractableInterface.h"
#include "CTTInteractableActor.generated.h"

class UCTTInteractableComponent;
class UWidgetComponent;

UCLASS()
class CTTPRACTICE_API ACTTInteractableActor : public AActor, public ICTTInteractableInterface
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
	virtual void OnEnterInteract(const FCTTInteractionInfo& InteractionInfo) override;

	UFUNCTION(BlueprintCallable)
	virtual void OnInteract() override;

	UFUNCTION(BlueprintCallable)
	virtual void OnExitInteract() override;

	float GetMinInteractionDistance() const { return MinInteractionDistance; }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MinInteractionDistance = 0.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    UWidgetComponent* InteractionWidgetComponent;

private:
	UPROPERTY()
	UCTTInteractableComponent* InteractableComponent = nullptr;

	UPROPERTY()
    USceneComponent* InteractionRootComponent;
};
