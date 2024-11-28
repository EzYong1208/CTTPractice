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

void UCTTInteractionComponent::ToggleInteraction()
{
	if (false == bIsInteracting)
	{
		BeginInteraction();
	}
	else
	{
		EndInteraction();
	}
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
	FVector ForwardVector = GetForwardVector();
	FVector End = Start + ForwardVector * DetectDistance;

	DrawDebugCapsule(GetWorld(), (Start + End) * 0.5f, CapsuleHalfHeight, CapsuleRadius, FRotationMatrix::MakeFromX(ForwardVector).ToQuat(), FColor::Blue, false, 1.0f);

	TArray<FHitResult> HitResults;
	bool bHit = GetWorld()->SweepMultiByChannel(
		HitResults,
		Start,
		End,
		FQuat::Identity,
		TraceChannel,
		FCollisionShape::MakeCapsule(CapsuleRadius, CapsuleHalfHeight)
	);

	if (bHit)
	{
		bool bHasValidHit = FindClosestHit(HitResults, Start, OutHitResult);
		if (true == bHasValidHit)
		{
			return true;
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("No hit detected within capsule."));
	return false;
}

bool UCTTInteractionComponent::FindClosestHit(const TArray<FHitResult>& HitResults, const FVector& Start, FHitResult& OutHitResult)
{
	FHitResult ClosestHit;
	float ClosestDistance = -1.0f;

	for (const FHitResult& Hit : HitResults)
	{
		if (Hit.GetActor() && Hit.GetActor() != GetOwner())
		{
			float Distance = FVector::Dist(Start, Hit.ImpactPoint);
			if (ClosestDistance < 0 || Distance < ClosestDistance)
			{
				ClosestDistance = Distance;
				ClosestHit = Hit;
			}
		}
	}

	if (ClosestDistance >= 0)
	{
		OutHitResult = ClosestHit;
		UE_LOG(LogTemp, Warning, TEXT("Closest Capsule Hit: %s at distance: %f"), *ClosestHit.GetActor()->GetName(), ClosestDistance);
		return true;
	}

	UE_LOG(LogTemp, Warning, TEXT("No closest hit detected."));
	return false;
}
