// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CTTConditionBase.generated.h"

/**
 * 
 */

UCLASS(Abstract)
class CTTPRACTICE_API UCTTConditionBase : public UObject
{
	GENERATED_BODY()
	
public:
	virtual bool CheckCondition_Implementation(AActor* Actor) const;
	bool GetConditionSatisfied() const { return bConditionSatisfied; }

protected:
	bool bConditionSatisfied = false;
};

UCLASS()
class CTTPRACTICE_API UCTTConditionBase_ActorName : public UCTTConditionBase
{
	GENERATED_BODY()

public:
	virtual bool CheckCondition_Implementation(AActor* Actor) const override;

private:
	FName ActorName;
};

UCLASS()
class CTTPRACTICE_API UCTTConditionBase_Player : public UCTTConditionBase
{
	GENERATED_BODY()

public:
	virtual bool CheckCondition_Implementation(AActor* Actor) const override;
};

UCLASS()
class CTTPRACTICE_API UCTTConditionBase_CheckCharacterCollision : public UCTTConditionBase
{
	GENERATED_BODY()

public:
	virtual bool CheckCondition_Implementation(AActor* Actor) const override;
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
