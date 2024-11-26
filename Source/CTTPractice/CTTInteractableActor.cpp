// Fill out your copyright notice in the Description page of Project Settings.


#include "CTTInteractableActor.h"
#include "CTTInteractableComponent.h"

// Sets default values
ACTTInteractableActor::ACTTInteractableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	InteractableComponent = CreateDefaultSubobject<UCTTInteractableComponent>(TEXT("Interactable"));

	InteractableComponent->OnEnterInteractDelegate.AddDynamic(this, &ACTTInteractableActor::OnEnterInteract);
	InteractableComponent->OnInteractDelegate.AddDynamic(this, &ACTTInteractableActor::OnInteract);
	InteractableComponent->OnExitInteractDelegate.AddDynamic(this, &ACTTInteractableActor::OnExitInteract);
}

// Called when the game starts or when spawned
void ACTTInteractableActor::BeginPlay()
{
	Super::BeginPlay();


}

// Called every frame
void ACTTInteractableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACTTInteractableActor::OnEnterInteract(const FCTTInteractionInfo& InteractionInfo)
{

}

void ACTTInteractableActor::OnInteract()
{

}

void ACTTInteractableActor::OnExitInteract()
{

}

