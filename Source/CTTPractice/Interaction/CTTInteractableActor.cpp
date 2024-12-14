// Fill out your copyright notice in the Description page of Project Settings.


#include "CTTPractice/Interaction/CTTInteractableActor.h"
#include "Components/WidgetComponent.h"
#include "Components/CapsuleComponent.h"

// Sets default values
ACTTInteractableActor::ACTTInteractableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	OnEnterInteractDelegate.AddDynamic(this, &ACTTInteractableActor::OnEnterInteract);
	OnInteractDelegate.AddDynamic(this, &ACTTInteractableActor::OnInteract);
	OnExitInteractDelegate.AddDynamic(this, &ACTTInteractableActor::OnExitInteract);

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	RootComponent = CapsuleComponent;

	InteractionWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("InteractionWidget"));
	InteractionWidgetComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ACTTInteractableActor::BeginPlay()
{
	Super::BeginPlay();

	InteractionWidgetComponent = FindComponentByClass<UWidgetComponent>();
	SetInteractionWidgetComponentVisibility(false);
}

// Called every frame
void ACTTInteractableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACTTInteractableActor::OnEnterInteract(const FCTTInteractionInfo& InteractionInfo)
{
	SetInteractionWidgetComponentVisibility(false);
}

void ACTTInteractableActor::OnInteract()
{

}

void ACTTInteractableActor::OnExitInteract()
{
	
}

void ACTTInteractableActor::SetInteractionWidgetComponentVisibility(bool bNewVisibility)
{
	if (nullptr == InteractionWidgetComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("InteractionWidgetComponent is nullptr"));
		return;
	}
	InteractionWidgetComponent->SetVisibility(bNewVisibility);
}

