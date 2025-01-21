// Fill out your copyright notice in the Description page of Project Settings.


#include "CTTPractice/Actor/CollectibleItem/CTTCollectibleItem.h"
#include "Components/CapsuleComponent.h"

// Sets default values
ACTTCollectibleItem::ACTTCollectibleItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	SetRootComponent(CapsuleComponent);
}

// Called when the game starts or when spawned
void ACTTCollectibleItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACTTCollectibleItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACTTCollectibleItem::StartActions(const TArray<FCTTActionData>& Actions)
{
	CurrentTime = 0.0f;
	PendingActions = Actions;

	GetWorld()->GetTimerManager().SetTimer(ActionTimerHandle, this, &ACTTCollectibleItem::UpdateActions, 0.1f, true);
}

void ACTTCollectibleItem::UpdateActions()
{
    CurrentTime += 0.1f;

	// EzYong TODO : 액션들 수행
}
