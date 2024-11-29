// Fill out your copyright notice in the Description page of Project Settings.


#include "CTTInteractionComponent.h"
#include "CTTInteractableComponent.h"
#include "DrawDebugHelpers.h"
#include "CTTInteractableActor.h"

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

	ACTTInteractableActor* ClosestInteractableActor = nullptr;

	for (const FHitResult& Hit : HitResults)
	{
		if (Hit.GetActor() && Hit.GetActor() != GetOwner())
		{
			float Distance = FVector::Dist(Start, Hit.ImpactPoint);
			if (ClosestDistance < 0 || Distance < ClosestDistance)
			{
				ClosestDistance = Distance;
				ClosestHit = Hit;

				ACTTInteractableActor* InteractableActor = Cast<ACTTInteractableActor>(Hit.GetActor());
				if (nullptr != InteractableActor)
				{
					ClosestInteractableActor = InteractableActor;
				}
			}
		}
	}

	if (ClosestDistance >= 0)
	{
		OutHitResult = ClosestHit;
		if (nullptr != ClosestInteractableActor)
		{
			AdjustCharacterPositionToInteractableActor(ClosestInteractableActor, ClosestDistance);
		}

		return true;
	}

	UE_LOG(LogTemp, Warning, TEXT("No closest hit detected."));
	return false;
}

void UCTTInteractionComponent::AdjustCharacterPositionToInteractableActor(ACTTInteractableActor* InteractableActor, float CurrentDistance)
{
	if (nullptr == InteractableActor)
	{
		UE_LOG(LogTemp, Error, TEXT("InteractableActor is nullptr"));
		return;
	}

	float MinInteractionDistance = InteractableActor->GetMinInteractionDistance();
	if (CurrentDistance <= MinInteractionDistance)
	{
		return;
	}

	// TODO : 부드럽게 이동하는거 생각하기
	FVector DirectionToNPC = (InteractableActor->GetActorLocation() - GetOwner()->GetActorLocation()).GetSafeNormal();
	FVector NewPosition = GetOwner()->GetActorLocation() + DirectionToNPC * (CurrentDistance - MinInteractionDistance);
	
	GetOwner()->SetActorLocation(NewPosition);

	UE_LOG(LogTemp, Warning, TEXT("Character moved to NPC at adjusted distance: %f"), MinInteractionDistance);
}
