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

/* 
EzYong TODO : event - condition - action
event							condition			action
CollectibleItem, ĳ���� �浹		CI �̸���				�׼�
								Coin				���� +1
								CoinStack			���� +5
								CoinStackBound		���� +10
								CollectItem			CollectItem Index�� bool true
								Pickaxe				���� On

USTRUCT(BlueprintType)
struct CTTPRACTICE_API FCTTCollectData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ECTTCollectType ActionType = ECTTCollectType::None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 IncreaseAmount = 0;
};
*/