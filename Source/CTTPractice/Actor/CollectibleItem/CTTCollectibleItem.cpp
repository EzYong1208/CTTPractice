// Fill out your copyright notice in the Description page of Project Settings.


#include "CTTPractice/Actor/CollectibleItem/CTTCollectibleItem.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "CTTPractice/CTTGameInstance.h"
#include "CTTPractice/Managers/CTTEventManager.h"

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

	int32 Index = PendingActions.Num() - 1;

	UCTTGameInstance* GameInstance = Cast<UCTTGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (!GameInstance)
	{
		UE_LOG(LogTemp, Error, TEXT("GameInstance is nullptr"));
		return;
	}

	UCTTEventManager* EventManager = GameInstance->GetEventManager();
	if (nullptr == EventManager)
	{
		UE_LOG(LogTemp, Error, TEXT("EventManager is nullptr"));
		return;
	}

	while (Index >= 0)
	{
		const FCTTActionData& ActionData = PendingActions[Index];
		if (ActionData.StartTime <= CurrentTime)
		{
			EventManager->ExecuteAction(this, ActionData);
			PendingActions.RemoveAt(Index);
		}
		--Index;
	}

	if (0 == PendingActions.Num())
	{
		GetWorld()->GetTimerManager().ClearTimer(ActionTimerHandle);
	}
}
