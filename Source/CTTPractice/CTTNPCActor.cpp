// Fill out your copyright notice in the Description page of Project Settings.


#include "CTTNPCActor.h"
#include "CTTNPCFollowCamera.h"
#include "Components/SphereComponent.h"

// Sets default values
ACTTNPCActor::ACTTNPCActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACTTNPCActor::BeginPlay()
{
	Super::BeginPlay();
	
	if (nullptr == NPCFollowCameraClass)
	{
		UE_LOG(LogTemp, Error, TEXT("NPCFollowCameraClass is nullptr"));
		return;
	}

	USphereComponent* SphereComponent = FindComponentByClass<USphereComponent>();
	if (nullptr == SphereComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("SphereComponent is nullptr"));
		return;
	}

	SphereComponent->SetCollisionResponseToChannel(ECC_Visibility, ECR_Overlap);
	SphereComponent->SetCollisionResponseToChannel(ECC_GameTraceChannel7, ECR_Overlap); // DetectInteractable
}

// Called every frame
void ACTTNPCActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACTTNPCActor::OnEnterInteract(const FCTTInteractionInfo& InteractionInfo)
{
	UE_LOG(LogTemp, Warning, TEXT("ENTER"));
}

void ACTTNPCActor::OnInteract()
{
	UE_LOG(LogTemp, Warning, TEXT("KEEP"));
}

void ACTTNPCActor::OnExitInteract()
{
	UE_LOG(LogTemp, Warning, TEXT("EXIT"));
}

