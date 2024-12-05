// Fill out your copyright notice in the Description page of Project Settings.


#include "CTTInteractableActor.h"
#include "CTTInteractableComponent.h"
#include "Components/WidgetComponent.h"

// Sets default values
ACTTInteractableActor::ACTTInteractableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	InteractableComponent = CreateDefaultSubobject<UCTTInteractableComponent>(TEXT("Interactable"));

	InteractableComponent->OnEnterInteractDelegate.AddDynamic(this, &ACTTInteractableActor::OnEnterInteract);
	InteractableComponent->OnInteractDelegate.AddDynamic(this, &ACTTInteractableActor::OnInteract);
	InteractableComponent->OnExitInteractDelegate.AddDynamic(this, &ACTTInteractableActor::OnExitInteract);

	InteractionRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("InteractionRoot"));
	RootComponent = InteractionRootComponent;

	InteractionWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("InteractionWidget"));
	InteractionWidgetComponent->SetupAttachment(InteractionRootComponent);
}

// Called when the game starts or when spawned
void ACTTInteractableActor::BeginPlay()
{
	Super::BeginPlay();

	InteractionWidgetComponent = FindComponentByClass<UWidgetComponent>();
	if (nullptr == InteractionWidgetComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("InteractionWidgetComponent is nullptr"));
		return;
	}
	InteractionWidgetComponent->SetVisibility(false);
}

// Called every frame
void ACTTInteractableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACTTInteractableActor::OnEnterInteract(const FCTTInteractionInfo& InteractionInfo)
{
	if (nullptr == InteractionWidgetComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("InteractionWidgetComponent is nullptr"));
		return;
	}
	InteractionWidgetComponent->SetVisibility(true);
}

void ACTTInteractableActor::OnInteract()
{

}

void ACTTInteractableActor::OnExitInteract()
{
	if (nullptr == InteractionWidgetComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("InteractionWidgetComponent is nullptr"));
		return;
	}
	InteractionWidgetComponent->SetVisibility(false);
}

