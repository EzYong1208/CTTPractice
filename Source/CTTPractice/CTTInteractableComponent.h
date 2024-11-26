// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CTTPractice/CTTStruct.h"
#include "CTTInteractableComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCTTOnEnterInteract, const FCTTInteractionInfo&, InteractionInfo);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCTTOnInteract);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCTTOnExitInteract);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CTTPRACTICE_API UCTTInteractableComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCTTInteractableComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	FCTTOnEnterInteract OnEnterInteractDelegate;
	FCTTOnInteract OnInteractDelegate;
	FCTTOnExitInteract OnExitInteractDelegate;
};
