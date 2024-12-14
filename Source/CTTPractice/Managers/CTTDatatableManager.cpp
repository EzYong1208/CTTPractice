// Fill out your copyright notice in the Description page of Project Settings.


#include "CTTPractice/Managers/CTTDatatableManager.h"

TArray<const FCTTWorldItemSetupData*> UCTTDatatableManager::GetWorldItemSetupRows() const
{
	TArray<const FCTTWorldItemSetupData*> Rows;
	if (WorldItemSetupDataTable)
	{
		TArray<FName> RowNames = WorldItemSetupDataTable->GetRowNames();
		for (const FName& RowName : RowNames)
		{
			const FCTTWorldItemSetupData* RowData = WorldItemSetupDataTable->FindRow<FCTTWorldItemSetupData>(RowName, TEXT(""));
			if (RowData)
			{
				Rows.Add(RowData);
			}
		}
	}
	return Rows;
}

TArray<const FCTTSwitchMovementData*> UCTTDatatableManager::GetSwitchMovementRows() const
{
	TArray<const FCTTSwitchMovementData*> Rows;
	if (SwitchMovementDataTable)
	{
		TArray<FName> RowNames = SwitchMovementDataTable->GetRowNames();
		for (const FName& RowName : RowNames)
		{
			const FCTTSwitchMovementData* Row = SwitchMovementDataTable->FindRow<FCTTSwitchMovementData>(RowName, TEXT(""));
			if (Row)
			{
				Rows.Add(Row);
			}
		}
	}
	return Rows;
}

FCTTItemSpawnOffsetData* UCTTDatatableManager::GetItemSpawnOffsetData(const FName& ItemName) const
{
	if (!IsValid(ItemSpawnOffsetDataTable))
	{
		UE_LOG(LogTemp, Error, TEXT("ItemSpawnOffsetDataTable is InValid"));
		return nullptr;
	}

	TArray<FName> RowNames = ItemSpawnOffsetDataTable->GetRowNames();
	for (const FName& RowName : RowNames)
	{
		FCTTItemSpawnOffsetData* SpawnOffsetData = ItemSpawnOffsetDataTable->FindRow<FCTTItemSpawnOffsetData>(RowName, TEXT(""));
		if (ItemName == SpawnOffsetData->ItemName)
		{
			return SpawnOffsetData;
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("There is no item to spawn"));
	return nullptr;
}

const void UCTTDatatableManager::GetSocketMeshData(TMap<FName, TMap<FName, UStaticMesh*>>& OutSocketMeshMap) const
{
	if (false == IsValid(SocketMeshDataTable))
	{
		UE_LOG(LogTemp, Error, TEXT("SocketMeshDataTable is Invalid"));
		return;
	}

	TArray<FName> RowNames = SocketMeshDataTable->GetRowNames();
	for (const FName& RowName : RowNames)
	{
		FCTTSocketMeshData* MeshData = SocketMeshDataTable->FindRow<FCTTSocketMeshData>(RowName, TEXT(""));
		if (MeshData)
		{
			OutSocketMeshMap.FindOrAdd(MeshData->AnimationName).Add(MeshData->SocketName, MeshData->Mesh);
		}
	}
}

const void UCTTDatatableManager::GetNPCSpringArmDataMap(TMap<FName, FCTTSpringArmData>& OutNPCSpringArmDataMap) const
{
	if (!NPCCameraSpringArmDataTable)
	{
		UE_LOG(LogTemp, Error, TEXT("NPCCameraSpringArmDataTable is not assigned!"));
		return;
	}

	TArray<FName> RowNames = NPCCameraSpringArmDataTable->GetRowNames();
	for (const FName& RowName : RowNames)
	{
		const FCTTSpringArmData* SpringArmData = NPCCameraSpringArmDataTable->FindRow<FCTTSpringArmData>(RowName, TEXT(""));

		if (SpringArmData)
		{
			OutNPCSpringArmDataMap.Add(RowName, *SpringArmData);
		}
	}
}