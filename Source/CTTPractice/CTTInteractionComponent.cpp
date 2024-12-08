// Fill out your copyright notice in the Description page of Project Settings.


#include "CTTInteractionComponent.h"
#include "CTTInteractableComponent.h"
#include "DrawDebugHelpers.h"
#include "CTTInteractableActor.h"
#include "Components/CapsuleComponent.h"

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
	AActor* Owner = GetOwner();
	UCapsuleComponent* CapsuleComponent = Owner->FindComponentByClass<UCapsuleComponent>();
	if (nullptr == CapsuleComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("CapsuleComponent is nullptr"));
		return;
	}
	CapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &UCTTInteractionComponent::OnOverlapBegin);
	CapsuleComponent->OnComponentEndOverlap.AddDynamic(this, &UCTTInteractionComponent::OnOverlapEnd);
}


// Called every frame
void UCTTInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	// 상호작용 중이라면 Delegate 호출
	if (bIsInteracting && CurrentInteractable)
	{
		CurrentInteractable->OnInteractDelegate.Broadcast();
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

	ACTTInteractableActor* CurrentInteractableActor = Cast<ACTTInteractableActor>(PreviousClosestInteractable);
	if (nullptr == CurrentInteractableActor)
	{
		UE_LOG(LogTemp, Error, TEXT("CurrentInteractableActor is nullptr"));
		return;
	}

	UCTTInteractableComponent* Interactable = CurrentInteractableActor->FindComponentByClass<UCTTInteractableComponent>();
	if (!Interactable)
	{
		return;
	}

	CurrentInteractable = Interactable;
	CurrentInteractable->OnEnterInteractDelegate.Broadcast(FCTTInteractionInfo(this));
	UE_LOG(LogTemp, Warning, TEXT("OnEnterInteractDelegate Broadcast"));
	bIsInteracting = true;
	AdjustCharacterPositionToInteractableActor(CurrentInteractableActor);
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

void UCTTInteractionComponent::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor->IsA<ACTTInteractableActor>())
	{
		OverlappingInteractables.Add(OtherActor, FVector::Dist(GetOwner()->GetActorLocation(), OtherActor->GetActorLocation()));
	}

	FindClosestInteractable();
}

void UCTTInteractionComponent::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	OverlappingInteractables.Remove(OtherActor);
	ACTTInteractableActor* NewInteractable = Cast<ACTTInteractableActor>(OtherActor);
	if (nullptr != NewInteractable)
	{
		NewInteractable->SetInteractionWidgetComponentVisibility(false);
	}
}

void UCTTInteractionComponent::FindClosestInteractable()
{
	if (OverlappingInteractables.Num() > 0)
	{
		float MinDistance = FLT_MAX;
		AActor* ClosestInteractable = nullptr;

		for (auto& Pair : OverlappingInteractables)
		{
			if (Pair.Value < MinDistance)
			{
				MinDistance = Pair.Value;
				ClosestInteractable = Pair.Key;
			}
		}

		if (PreviousClosestInteractable)
		{
			ACTTInteractableActor* OldInteractable = Cast<ACTTInteractableActor>(PreviousClosestInteractable);
			if (OldInteractable)
			{
				OldInteractable->SetInteractionWidgetComponentVisibility(false);
			}
		}

		PreviousClosestInteractable = ClosestInteractable;
		if (ClosestInteractable)
		{
			ACTTInteractableActor* NewInteractable = Cast<ACTTInteractableActor>(ClosestInteractable);
			if (NewInteractable)
			{
				NewInteractable->SetInteractionWidgetComponentVisibility(true);
			}
		}
	}
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

	// TODO : 부드럽게 이동하는거 생각하기
	FVector DirectionToNPC = (InteractableActor->GetActorLocation() - GetOwner()->GetActorLocation()).GetSafeNormal();
	FVector NewPosition = GetOwner()->GetActorLocation() + DirectionToNPC * (CurrentDistance - MinInteractionDistance);

	GetOwner()->SetActorLocation(NewPosition);

	UE_LOG(LogTemp, Warning, TEXT("Character moved to NPC at adjusted distance: %f"), MinInteractionDistance);
}
