// Fill out your copyright notice in the Description page of Project Settings.


#include "CTTPractice/Managers/CTTDatatableManager.h"

void UCTTDatatableManager::Shutdown()
{
	WorldItemSetupDataTable = nullptr;
	ItemDataTable = nullptr;
	SwitchMovementDataTable = nullptr;
	ItemSpawnOffsetDataTable = nullptr;
	SocketMeshDataTable = nullptr;
	NPCCameraSpringArmDataTable = nullptr;
	EventActionDataTable = nullptr;
}

TArray<const FCTTWorldItemSetupData*> UCTTDatatableManager::GetWorldItemSetupRows() const
{
	TArray<const FCTTWorldItemSetupData*> Rows;
	if (!IsValid(WorldItemSetupDataTable))
	{
		UE_LOG(LogTemp, Error, TEXT("WorldItemSetupDataTable is Invalid"));
		return Rows;
	}

	for (const FName& RowName : WorldItemSetupDataTable->GetRowNames())
	{
		const FCTTWorldItemSetupData* RowData = WorldItemSetupDataTable->FindRow<FCTTWorldItemSetupData>(RowName, TEXT(""));
		if (RowData)
		{
			Rows.Add(RowData);
		}
	}
	return Rows;
}

TArray<const FCTTSwitchMovementData*> UCTTDatatableManager::GetSwitchMovementRows() const
{
	TArray<const FCTTSwitchMovementData*> Rows;
	if (!IsValid(SwitchMovementDataTable))
	{
		UE_LOG(LogTemp, Error, TEXT("SwitchMovementDataTable is Invalid"));
		return Rows;
	}

	for (const FName& RowName : SwitchMovementDataTable->GetRowNames())
	{
		const FCTTSwitchMovementData* Row = SwitchMovementDataTable->FindRow<FCTTSwitchMovementData>(RowName, TEXT(""));
		if (Row)
		{
			Rows.Add(Row);
		}
	}
	return Rows;
}

const UDataTable* UCTTDatatableManager::GetItemDataTable() const
{
	if (!IsValid(ItemDataTable))
	{
		UE_LOG(LogTemp, Error, TEXT("ItemDataTable is nullptr"));
		return nullptr;
	}
	return ItemDataTable;
}

const FCTTItemSpawnOffsetData* UCTTDatatableManager::GetItemSpawnOffsetData(const FName& ItemName) const
{
	if (!IsValid(ItemSpawnOffsetDataTable))
	{
		UE_LOG(LogTemp, Error, TEXT("ItemSpawnOffsetDataTable is Invalid"));
		return nullptr;
	}

	for (const FName& RowName : ItemSpawnOffsetDataTable->GetRowNames())
	{
		const FCTTItemSpawnOffsetData* SpawnOffsetData = ItemSpawnOffsetDataTable->FindRow<FCTTItemSpawnOffsetData>(RowName, TEXT(""));
		if (SpawnOffsetData && SpawnOffsetData->ItemName == ItemName)
		{
			return SpawnOffsetData;
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("No matching item found for ItemName: %s"), *ItemName.ToString());
	return nullptr;
}

void UCTTDatatableManager::GetSocketMeshData(TMap<FName, TMap<FName, TWeakObjectPtr<UStaticMesh>>>& OutSocketMeshMap) const
{
	if (!IsValid(SocketMeshDataTable))
	{
		UE_LOG(LogTemp, Error, TEXT("SocketMeshDataTable is Invalid"));
		return;
	}

	for (const FName& RowName : SocketMeshDataTable->GetRowNames())
	{
		const FCTTSocketMeshData* MeshData = SocketMeshDataTable->FindRow<FCTTSocketMeshData>(RowName, TEXT(""));
		if (MeshData)
		{
			OutSocketMeshMap.FindOrAdd(MeshData->AnimationName).Add(MeshData->SocketName, MeshData->Mesh);
		}
	}
}

void UCTTDatatableManager::GetNPCSpringArmDataMap(TMap<FName, FCTTSpringArmData>& OutNPCSpringArmDataMap) const
{
	if (!IsValid(NPCCameraSpringArmDataTable))
	{
		UE_LOG(LogTemp, Error, TEXT("NPCCameraSpringArmDataTable is Invalid"));
		return;
	}

	for (const FName& RowName : NPCCameraSpringArmDataTable->GetRowNames())
	{
		const FCTTSpringArmData* SpringArmData = NPCCameraSpringArmDataTable->FindRow<FCTTSpringArmData>(RowName, TEXT(""));
		if (SpringArmData)
		{
			OutNPCSpringArmDataMap.Add(RowName, *SpringArmData);
		}
	}
}

const UDataTable* UCTTDatatableManager::GetEventActionDataTable() const
{
	if (!IsValid(EventActionDataTable))
	{
		UE_LOG(LogTemp, Error, TEXT("EventActionDataTable is nullptr"));
		return nullptr;
	}
	return EventActionDataTable;
}
