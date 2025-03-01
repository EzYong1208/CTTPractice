// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Templates/SubclassOf.h"
#include "CTTPracticeGameModeBase.generated.h"

/**
 * 
 */

struct FCTTWorldItemSetupData;
class UCTTUICommonResource;

UCLASS()
class CTTPRACTICE_API ACTTPracticeGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	const UCTTUICommonResource* GetUICommonResource() const;
	int32 GetCollectItemNumber() const { return CollectItemNumber; }

	void SpawnItem(const FCTTWorldItemSetupData& SpawnData);

	void MoveActorZAxis(const FName& SwitchName, float DeltaTime);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 PlayerInitialLifeCount = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CoinInitialCount = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CollectItemNumber = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool CollectItemInitialState = false;

	UPROPERTY()
	TArray<bool> CollectItemStates;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UCTTUICommonResource> UICommonResourceClass;

	UPROPERTY()
	UCTTUICommonResource* UICommonResource = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float SwitchMovementSpeed = 0.f;

private:
	TMap<FName, TMap<FName, FVector>> SwitchMovementDataMap;
	const FName SOCKETNAME_WEAPON = TEXT("Socket_Weapon");
};
