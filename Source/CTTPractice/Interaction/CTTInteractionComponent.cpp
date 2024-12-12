// Fill out your copyright notice in the Description page of Project Settings.


#include "CTTPractice/Interaction/CTTInteractionComponent.h"
#include "CTTPractice/Interaction/CTTInteractableActor.h"
#include "Components/CapsuleComponent.h"
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
	// 상호작용 중이라면 Delegate 호출
	if (bIsInteracting/* && CurrentInteractable*/)
	{
		PreviousClosestInteractable->OnInteractDelegate.Broadcast();
	}
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

	//ACTTInteractableActor* CurrentInteractableActor = Cast<ACTTInteractableActor>(PreviousClosestInteractable);
	//if (nullptr == CurrentInteractableActor)
	//{
	//	UE_LOG(LogTemp, Error, TEXT("CurrentInteractableActor is nullptr"));
	//	return;
	//}

	////UCTTInteractableComponent* Interactable = CurrentInteractableActor->FindComponentByClass<UCTTInteractableComponent>();
	////if (!Interactable)
	////{
	////	return;
	////}

	////CurrentInteractable = Interactable;
	//PreviousClosestInteractable->OnEnterInteractDelegate.Broadcast(FCTTInteractionInfo(this));
	//UE_LOG(LogTemp, Warning, TEXT("OnEnterInteractDelegate Broadcast"));
	//bIsInteracting = true;
	////AdjustCharacterPositionToInteractableActor(CurrentInteractableActor);

	FHitResult HitResult;
	bool bHit = DetectInteractable(HitResult);
	//if (bHit)
	//{
	//	PreviousClosestInteractable->OnEnterInteractDelegate.Broadcast(FCTTInteractionInfo(this));
	//	UE_LOG(LogTemp, Warning, TEXT("OnEnterInteractDelegate Broadcast"));
	//	bIsInteracting = true;
	//}
}

void UCTTInteractionComponent::EndInteraction()
{
	if (PreviousClosestInteractable.IsValid())
	{
		PreviousClosestInteractable->OnExitInteractDelegate.Broadcast();
	}

	bIsInteracting = false;

	UE_LOG(LogTemp, Warning, TEXT("EndInteraction"));
}

bool UCTTInteractionComponent::DetectInteractable(FHitResult& OutHitResult)
{
	AActor* Owner = GetOwner();
	if (!Owner)
	{
		UE_LOG(LogTemp, Warning, TEXT("No Owner detected."));
		return false;
	}

	FVector Start = Owner->GetActorLocation() + FVector::UpVector * DetectHeight;
	FVector ForwardVector = Owner->GetActorForwardVector();
	FVector End = Start + ForwardVector * DetectDistance;

	FCollisionShape CapsuleShape = FCollisionShape::MakeCapsule(CapsuleRadius, CapsuleHalfHeight);
	FVector CapsuleCenter = (Start + End) * 0.5f;
	FQuat CapsuleRotation = FRotationMatrix::MakeFromX(ForwardVector).ToQuat();

	DrawDebugCapsule(GetWorld(), CapsuleCenter, CapsuleHalfHeight, CapsuleRadius, CapsuleRotation, FColor::Blue, false, 1.0f);

	TArray<FOverlapResult> OverlapResults;
	bool bHit = GetWorld()->OverlapMultiByChannel(
		OverlapResults,
		CapsuleCenter,
		CapsuleRotation,
		ECollisionChannel::ECC_WorldDynamic,
		CapsuleShape
	);

	if (bHit)
	{
		bool bHasValidHit = FindClosestOverlap(OverlapResults, Start, OutHitResult);
		if (bHasValidHit)
		{
			return true;
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("No hit detected within capsule."));
	return false;
}

bool UCTTInteractionComponent::FindClosestOverlap(const TArray<FOverlapResult>& OverlapResults, const FVector& Start, FHitResult& OutHitResult)
{
	float ClosestDistance = -1.0f;
	ACTTInteractableActor* ClosestInteractableActor = nullptr;
	FHitResult ClosestHit;

	for (const FOverlapResult& OverlapResult : OverlapResults)
	{
		AActor* OverlappedActor = OverlapResult.GetActor();
		if (OverlappedActor && OverlappedActor != GetOwner())
		{
			ACTTInteractableActor* InteractableActor = Cast<ACTTInteractableActor>(OverlappedActor);
			if (nullptr == InteractableActor)
			{
				continue;
			}

			FVector ActorLocation = OverlappedActor->GetActorLocation();
			float Distance = FVector::Dist(Start, ActorLocation);

			if (ClosestDistance < 0 || Distance < ClosestDistance)
			{
				ClosestDistance = Distance;

				ClosestHit = FHitResult();
				ClosestHit.Actor = OverlappedActor;
				ClosestHit.Location = ActorLocation;
				ClosestInteractableActor = InteractableActor;
			}
		}
	}

	if (ClosestDistance >= 0)
	{
		OutHitResult = ClosestHit;
		if (AActor* HitActor = OutHitResult.GetActor())
		{
			UE_LOG(LogTemp, Log, TEXT("Closest hit detected: %s"), *HitActor->GetName());
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("OutHitResult Actor is nullptr"));
		}

		return true;
	}

	UE_LOG(LogTemp, Warning, TEXT("No closest hit detected."));
	return false;
}

void UCTTInteractionComponent::AdjustCharacterPositionToInteractableActor(ACTTInteractableActor* InteractableActor)
{
	if (nullptr == InteractableActor)
	{
		UE_LOG(LogTemp, Error, TEXT("InteractableActor is nullptr"));
		return;
	}

	float CurrentDistance = FVector::Dist(GetOwner()->GetActorLocation(), InteractableActor->GetActorLocation());
	float MinInteractionDistance = InteractableActor->GetMinInteractionDistance();
	if (CurrentDistance <= MinInteractionDistance)
	{
		return;
	}

	// EzYong TODO : 부드럽게 이동하는거 생각하기
	FVector DirectionToNPC = (InteractableActor->GetActorLocation() - GetOwner()->GetActorLocation()).GetSafeNormal();
	FVector NewPosition = GetOwner()->GetActorLocation() + DirectionToNPC * (CurrentDistance - MinInteractionDistance);

	GetOwner()->SetActorLocation(NewPosition);

	UE_LOG(LogTemp, Warning, TEXT("Character moved to NPC at adjusted distance: %f"), MinInteractionDistance);
}
