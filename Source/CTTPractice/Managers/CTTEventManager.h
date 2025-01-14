// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
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
	void HandleCollisionEvent(ACTTCharacter* Character, AActor* OtherActor);

private:
	void Test();
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