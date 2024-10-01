// Fill out your copyright notice in the Description page of Project Settings.


#include "CTTSocketAttachmentComponent.h"
#include "Engine/DataTable.h"

// Sets default values
UCTTSocketAttachmentComponent::UCTTSocketAttachmentComponent()
    : SocketMeshDataTable(nullptr)
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UCTTSocketAttachmentComponent::BeginPlay()
{
	Super::BeginPlay();

    if (nullptr == SocketMeshDataTable)
    {
        UE_LOG(LogTemp, Error, TEXT("SocketMeshDataTable is nullptr"));
        return;
    }

	TArray<FName> RowNames = SocketMeshDataTable->GetRowNames();
	for (int32 i = 0; i < RowNames.Num(); ++i)
	{
		FCTTSocketMeshData* MeshData = SocketMeshDataTable->FindRow<FCTTSocketMeshData>(RowNames[i], TEXT(""));
		if (MeshData)
		{
			SocketMeshMap.FindOrAdd(MeshData->AnimationName).Add(MeshData->SocketName, MeshData->Mesh);
		}
	}
}

void UCTTSocketAttachmentComponent::SetMeshByName(FName RowName)
{
	if (0 == SocketMeshMap.Num())
	{
		return;
	}

	AActor* Owner = GetOwner();
	if (nullptr == Owner)
	{
		UE_LOG(LogTemp, Error, TEXT("Owner is nullptr"));
		return;
	}

	USkeletalMeshComponent* SkeletalMeshComponent = Owner->FindComponentByClass<USkeletalMeshComponent>();
	if (nullptr == SkeletalMeshComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("SkeletalMeshComponent is nullptr"));
		return;
	}

	TMap<FName, UStaticMesh*> SocketMap = *SocketMeshMap.Find(RowName);

	TArray<UStaticMeshComponent*> StaticMeshComponents;
	Owner->GetComponents<UStaticMeshComponent>(StaticMeshComponents);

	for (int32 i = 0; i < StaticMeshComponents.Num(); ++i)
	{
		UStaticMeshComponent* StaticMesh = StaticMeshComponents[i];
		if (nullptr == StaticMesh)
		{
			UE_LOG(LogTemp, Error, TEXT("OwnerStaticMesh is nullptr"));
			return;
		}

		auto MeshToAttach = SocketMap.Find(StaticMesh->GetFName());
		if (nullptr == MeshToAttach)
		{
			UE_LOG(LogTemp, Error, TEXT("MeshToAttach is nullptr"));
			return;
		}

		StaticMesh->SetStaticMesh(*MeshToAttach);
		StaticMesh->AttachToComponent(SkeletalMeshComponent, FAttachmentTransformRules::SnapToTargetIncludingScale, StaticMesh->GetFName());
	}
}
