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
	void OnWorldPostActorTick(UWorld* World, ELevelTick TickType, float DeltaTime);
	void CheckAndDestroyPendingActors();
	void StartActionsFromEvent(AActor* ItemActor, AActor* OtherActor, FName EventName);

private:
	TMap<FName, FCTTEventActionData> EventActionDataMap;
	TQueue<AActor*> PendingKillActors;
	FDelegateHandle OnWorldPostActorTickHandle;
};

/* 
EzYong TODO : event - condition - action
event							condition			action
CollectibleItem, 캐릭터 충돌		CI 이름들				액션
								Coin				코인 +1
								CoinStack			코인 +5
								CoinStackBound		코인 +10
								CollectItem			CollectItem Index의 bool true
								Pickaxe				버프 On

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