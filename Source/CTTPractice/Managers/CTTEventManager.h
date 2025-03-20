// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CTTPractice/CTTDatatableHeader.h"
#include "CTTEventManager.generated.h"

/**
 * 
 */

class AActor;
class ACTTCharacter;

UCLASS(Blueprintable)
class CTTPRACTICE_API UCTTEventManager : public UObject
{
	GENERATED_BODY()
	
public:
	void Initialize();
	void Shutdown();

	void HandleCollisionEvent(AActor* Actor, AActor* CollidedActor, FName EventName);
	void ExecuteAction(AActor* TargetActor, const FCTTActionData& ActionData);
	UCTTActionBase* ExecuteActionAndReturn(AActor* TargetActor, const FCTTActionData& ActionData);

public:
	void AddActorToPendingKill(AActor* ActorToRemove);

private:
	void SetIdleActionForAllCollectibleItems();
	void OnWorldPostActorTick(UWorld* World, ELevelTick TickType, float DeltaTime);
	void CheckAndDestroyPendingActors();
	void StartActionsFromEvent(AActor* ItemActor, AActor* OtherActor, FName EventName);

private:
	TMap<FName, TArray<FCTTEventActionData>> EventActionDataMap;
	TQueue<AActor*> PendingKillActors;
	FDelegateHandle OnWorldPostActorTickHandle;
};
