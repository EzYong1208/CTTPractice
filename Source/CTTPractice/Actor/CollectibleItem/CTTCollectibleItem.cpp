// Fill out your copyright notice in the Description page of Project Settings.


#include "CTTPractice/Actor/CollectibleItem/CTTCollectibleItem.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "CTTPractice/CTTGameInstance.h"
#include "CTTPractice/Managers/CTTEventManager.h"
#include "CTTPractice/Event/CTTEventNames.h"

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

    if (true == bActionRequired)
    {
        UpdateActions();
    }
}

void ACTTCollectibleItem::StartActions(const TArray<FCTTActionData>& Actions)
{
	CurrentTime = 0.0f;

	PendingActions.Empty();
	PendingActions = Actions;

	if (PendingActions.Num() > 0)
	{
        bActionRequired = true;
	}
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
    if (!EventManager)
    {
        UE_LOG(LogTemp, Error, TEXT("EventManager is nullptr"));
        return;
    }

    while (Index >= 0)
    {
        if (!PendingActions.IsValidIndex(Index))
        {
            UE_LOG(LogTemp, Error, TEXT("Invalid Index: %d"), Index);
            break;
        }

        const FCTTActionData& ActionData = PendingActions[Index];
        if (ActionData.StartTime <= CurrentTime)
        {
            EventManager->ExecuteAction(this, ActionData);
            PendingActions.RemoveAt(Index);
        }
        --Index;
    }

    if (PendingActions.Num() == 0)
    {
        bActionRequired = false;
        PendingActions.Shrink();
    }
}

void ACTTCollectibleItem::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (!OtherActor ||
        OtherActor == this)
    {
        return;
    }

    UCTTGameInstance* GameInstance = Cast<UCTTGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
    if (!GameInstance)
    {
        UE_LOG(LogTemp, Error, TEXT("GameInstance is nullptr"));
        return;
    }

    UCTTEventManager* EventManager = GameInstance->GetEventManager();
    if (!EventManager)
    {
        UE_LOG(LogTemp, Error, TEXT("EventManager is nullptr"));
        return;
    }

    EventManager->HandleCollisionEvent(this, OtherActor, CTTEventNames::CollisionEvent);
}
