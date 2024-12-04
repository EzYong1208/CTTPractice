// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CTTPractice/CTTStruct.h"
#include "CTTDatatableManager.generated.h"

/**
 * 
 */

UCLASS(Blueprintable)
class CTTPRACTICE_API UCTTDatatableManager : public UObject
{
	GENERATED_BODY()

public:
#pragma region DATATABLE_ITEM
	TArray<const FCTTWorldItemSetupData*> GetWorldItemSetupRows() const;
	TArray<const FCTTSwitchMovementData*> GetSwitchMovementRows() const;
	UDataTable* GetItemDataTable() const {return ItemDataTable;}
	FCTTItemSpawnOffsetData* GetItemSpawnOffsetData(const FName& ItemName) const;
#pragma endregion
	void GetSocketMeshData(TMap<FName, TMap<FName, UStaticMesh*>>& OutSocketMeshMap) const;

protected:
	// TODO : 아이템 데이터테이블들은 개편필요(아이템 클래스를 수정할 예정)
#pragma region DATATABLE_ITEM
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    UDataTable* WorldItemSetupDataTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    UDataTable* ItemDataTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    UDataTable* SwitchMovementDataTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    UDataTable* ItemSpawnOffsetDataTable;
#pragma endregion

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SocketMesh")
    UDataTable* SocketMeshDataTable;

	int32 i = 0;
};
