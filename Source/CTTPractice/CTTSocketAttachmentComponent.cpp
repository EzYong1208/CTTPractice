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
}

void UCTTSocketAttachmentComponent::SetMeshByName(FName RowName)
{
	if (nullptr == SocketMeshDataTable)
	{
		UE_LOG(LogTemp, Error, TEXT("SocketMeshDataTable is nullptr"));
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

    TArray<FCTTSocketMeshData*> MatchingMeshData;
    TArray<FName> RowNames = SocketMeshDataTable->GetRowNames();

    for (int32 i = 0; i < RowNames.Num(); ++i)
    {
        FCTTSocketMeshData* MeshData = SocketMeshDataTable->FindRow<FCTTSocketMeshData>(RowNames[i], TEXT(""));

        if (nullptr == MeshData || 
            MeshData->AnimationName != RowName)
        {
            continue;
        }

        MatchingMeshData.Add(MeshData);
    }

    TArray<UStaticMeshComponent*> StaticMeshComponents;
    Owner->GetComponents<UStaticMeshComponent>(StaticMeshComponents);

    for (int32 i = 0; i < MatchingMeshData.Num(); ++i)
    {
        FCTTSocketMeshData* MeshData = MatchingMeshData[i];

        if (nullptr == MeshData->Mesh)
        {
            continue;
        }

        for (int32 j = 0; j < StaticMeshComponents.Num(); ++j)
        {
            UStaticMeshComponent* StaticMesh = StaticMeshComponents[j];

            if (nullptr == StaticMesh)
            {
                continue;
            }

            if (MeshData->SocketName == StaticMesh->GetFName())
            {
                StaticMesh->SetStaticMesh(MeshData->Mesh);
                StaticMesh->AttachToComponent(SkeletalMeshComponent, FAttachmentTransformRules::SnapToTargetIncludingScale, MeshData->SocketName);
                break;
            }
        }
    }
}
