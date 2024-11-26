// Fill out your copyright notice in the Description page of Project Settings.


#include "CTTInteractionComponent.h"
#include "CTTInteractableComponent.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
UCTTInteractionComponent::UCTTInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCTTInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UCTTInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	if (false == bIsInteracting)
	{
		return;
	}
	CurrentInteractable->OnInteractDelegate.Broadcast();
}

void UCTTInteractionComponent::BeginInteraction()
{
	UE_LOG(LogTemp, Warning, TEXT("BeginInteraction"));

	FHitResult HitResult;
	bool bIsInteractableDetected = DetectInteractable(HitResult);

	if (false == bIsInteractableDetected)
	{
		return;
	}

	AActor* HitActor = HitResult.GetActor();
	if (nullptr == HitActor)
	{
		return;
	}

	UCTTInteractableComponent* Interactable = HitActor->FindComponentByClass<UCTTInteractableComponent>();
	if (nullptr == Interactable)
	{
		return;
	}

	CurrentInteractable = Interactable;
	CurrentInteractable->OnEnterInteractDelegate.Broadcast(FCTTInteractionInfo(this, HitResult));
	UE_LOG(LogTemp, Warning, TEXT("OnEnterInteractDelegate Broadcast"));
	bIsInteracting = true;
}

void UCTTInteractionComponent::EndInteraction()
{
	if (CurrentInteractable)
	{
		CurrentInteractable->OnExitInteractDelegate.Broadcast();
		CurrentInteractable = nullptr;
	}

	bIsInteracting = false;

	UE_LOG(LogTemp, Warning, TEXT("EndInteraction"));
}

bool UCTTInteractionComponent::DetectInteractable(FHitResult& OutHitResult)
{
	FVector Start = GetComponentLocation() + FVector::UpVector * DetectHeight;
	FVector End = Start + GetForwardVector() * DetectDistance;

	DrawDebugLine(GetWorld(), Start, End, FColor::Red, true);

	bool bHit = GetWorld()->LineTraceSingleByChannel(OutHitResult, Start, End, TraceChannel);

	if (bHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit: %s"), *OutHitResult.GetActor()->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No hit detected."));
	}

	return bHit;
}

