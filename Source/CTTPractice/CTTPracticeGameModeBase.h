// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Templates/SubclassOf.h"
#include "CTTPractice/CTTStruct.h"
#include "CTTPracticeGameModeBase.generated.h"

/**
 * 
 */
class UCTTUICommonResource;
class UCTTDataTableManager;

UCLASS()
class CTTPRACTICE_API ACTTPracticeGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;

	const UCTTUICommonResource* GetUICommonResource() const { return UICommonResource; }
	int32 GetCollectItemNumber() const { return CollectItemNumber; }

	void SpawnItem(const FCTTWorldItemSetupData& SpawnData);
	FCTTItemSpawnOffsetData* GetItemSpawnOffsetData(const FName& ItemName) const;

	void MoveActorZAxis(const FName& SwitchName, float DeltaTime);

	UDataTable* GetStaticCameraDataTable() const { return StaticCameraDataTable; }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 PlayerInitialLifeCount = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CoinInitialLifeCount = 0;

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UDataTable* WorldItemSetupDataTable;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UDataTable* ItemDataTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UDataTable* ItemSpawnOffsetDataTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UDataTable* SwitchMovementDataTable;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float SwitchMovementSpeed = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UDataTable* StaticCameraDataTable;

private:
	TMap<FName, TMap<FName, FVector>> SwitchMovementDataMap;
	const FName SOCKETNAME_WEAPON = TEXT("Socket_Weapon");
};
