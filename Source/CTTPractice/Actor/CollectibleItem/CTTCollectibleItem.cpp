// Fill out your copyright notice in the Description page of Project Settings.


#include "CTTPractice/Actor/CollectibleItem/CTTCollectibleItem.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "CTTPractice/CTTGameInstance.h"
#include "CTTPractice/Managers/CTTEventManager.h"
#include "CTTPractice/Event/CTTEventNames.h"
#include "CTTPractice/Event/CTTActionBase.h"

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
	
    if (nullptr == CapsuleComponent)
    {
        UE_LOG(LogTemp, Error, TEXT("CapsuleComponent is nullptr"));
        return;
    }

    CapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &ACTTCollectibleItem::OnOverlapBegin);
}

void ACTTCollectibleItem::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);

    if (nullptr == CapsuleComponent)
    {
        UE_LOG(LogTemp, Error, TEXT("CapsuleComponent is nullptr"));
        return;
    }

    CapsuleComponent->OnComponentBeginOverlap.RemoveDynamic(this, &ACTTCollectibleItem::OnOverlapBegin);
}

// Called every frame
void ACTTCollectibleItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    UpdateRotation(DeltaTime);
    UpdateJump(DeltaTime);

    if (true == bActionRequired)
    {
        UpdateActions(DeltaTime);
    }
    else
    {
        UpdateIdleAction(DeltaTime);
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

void ACTTCollectibleItem::UpdateActions(float DeltaTime)
{
    CurrentTime += DeltaTime;

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

void ACTTCollectibleItem::SetIdleAction(const FCTTActionData& InIdleAction)
{
    IdleAction.ActionClass = InIdleAction.ActionClass;
    IdleAction.ActionParameter = InIdleAction.ActionParameter;
    IdleAction.StartTime = InIdleAction.StartTime;
    IdleAction.Duration = InIdleAction.Duration;

    if (!IsValid(IdleAction.ActionClass))
    {
        UE_LOG(LogTemp, Error, TEXT("SetIdleAction: IdleAction.ActionClass became invalid after assignment!"));
    }
    else
    {
        UE_LOG(LogTemp, Log, TEXT("SetIdleAction: Assigned %s"), *IdleAction.ActionClass->GetName());
    }
}

void ACTTCollectibleItem::StopIdleAction()
{
    bIsIdleActionActive = false;
    UE_LOG(LogTemp, Log, TEXT("ACTTCollectibleItem: IdleAction Stopped"));
}

void ACTTCollectibleItem::SetRotation(float InRotateSpeed, float InRotateDuration)
{
    RotateSpeed = InRotateSpeed;
    RotateDuration = InRotateDuration;
}

void ACTTCollectibleItem::SetJump(float InJumpSpeed)
{
    if (true == bIsJumping)
    {
        return;
    }

    JumpSpeed = InJumpSpeed;
    ElapsedTime = 0.0f;
    bIsJumping = true;
    StartLocation = GetActorLocation();

    UE_LOG(LogTemp, Warning, TEXT("ACTTCollectibleItem: Jump Started!"));
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

    StopIdleAction();
    EventManager->HandleCollisionEvent(this, OtherActor, CTTEventNames::CollisionEvent);
}

void ACTTCollectibleItem::UpdateIdleAction(float DeltaTime)
{
    if (bIsIdleActionActive)
    {
        return;
    }

    CurrentTime += DeltaTime;

    if (!IsValid(IdleAction.ActionClass))
    {
        // EzYong TODO : 수정 필요
        //UE_LOG(LogTemp, Error, TEXT("UpdateIdleAction: IdleAction.ActionClass is invalid before execution!"));
        return;
    }

    UE_LOG(LogTemp, Log, TEXT("UpdateIdleAction: Executing %s"), *IdleAction.ActionClass->GetName());

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

    if (IdleAction.StartTime <= CurrentTime)
    {
        EventManager->ExecuteAction(this, IdleAction);
        bIsIdleActionActive = true;

        if (!IsValid(IdleAction.ActionClass))
        {
            UE_LOG(LogTemp, Error, TEXT("UpdateIdleAction: IdleAction.ActionClass became invalid after execution!"));
        }
        else
        {
            UE_LOG(LogTemp, Log, TEXT("UpdateIdleAction: IdleAction.ActionClass is still valid after execution!"));
        }

        CurrentTime = 0.0f;
    }
}

void ACTTCollectibleItem::UpdateRotation(float DeltaTime)
{
    if (RotateSpeed <= 0.0f)
    {
        return;
    }

    FRotator NewRotation = GetActorRotation();
    NewRotation.Yaw += RotateSpeed * DeltaTime;
    SetActorRotation(NewRotation);

    RotateDuration -= DeltaTime;
    if (RotateDuration <= 0.0f)
    {
        RotateSpeed = 0.0f;
        UE_LOG(LogTemp, Warning, TEXT("ACTTCollectibleItem: Rotation Stopped"));
    }
}

void ACTTCollectibleItem::UpdateJump(float DeltaTime)
{
    if (false == bIsJumping)
    {
        return;
    }

    ElapsedTime += DeltaTime;

    float NewHeight = JumpSpeed * ElapsedTime - 0.5f * Gravity * ElapsedTime * ElapsedTime;
    FVector NewLocation = StartLocation;
    NewLocation.Z += NewHeight;

    if (NewLocation.Z <= StartLocation.Z)
    {
        NewLocation.Z = StartLocation.Z;
        ElapsedTime = 0.0f;
        bIsJumping = false;

        StartLocation = FVector::ZeroVector;
        UE_LOG(LogTemp, Warning, TEXT("ACTTCollectibleItem: Jump Ended!"));
    }

    SetActorLocation(NewLocation);
}
