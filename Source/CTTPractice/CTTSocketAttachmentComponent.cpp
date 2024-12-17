// Fill out your copyright notice in the Description page of Project Settings.


#include "CTTSocketAttachmentComponent.h"
#include "CTTPractice/CTTGameInstance.h"
#include "CTTPractice/Managers/CTTDatatableManager.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
UCTTSocketAttachmentComponent::UCTTSocketAttachmentComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UCTTSocketAttachmentComponent::BeginPlay()
{
	Super::BeginPlay();

	LoadSocketMeshData();
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

	TMap<FName, TWeakObjectPtr<UStaticMesh>>* SocketMapPtr = SocketMeshMap.Find(RowName);
	if (SocketMapPtr == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("RowName %s not found in SocketMeshMap"), *RowName.ToString());
		return;
	}

	TMap<FName, TWeakObjectPtr<UStaticMesh>>& SocketMap = *SocketMapPtr;
	TArray<UStaticMeshComponent*> StaticMeshComponents;
	Owner->GetComponents<UStaticMeshComponent>(StaticMeshComponents);

	for (UStaticMeshComponent* StaticMeshComponent : StaticMeshComponents)
	{
		if (StaticMeshComponent == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("StaticMeshComponent is nullptr"));
			continue;
		}

		auto MeshToAttachPtr = SocketMap.Find(StaticMeshComponent->GetFName());
		if (false == MeshToAttachPtr->IsValid())
		{
			UE_LOG(LogTemp, Warning, TEXT("MeshToAttach for Socket %s is invalid"), *StaticMeshComponent->GetFName().ToString());
			continue;
		}

		UStaticMesh* MeshToAttach = MeshToAttachPtr->Get();
		if (MeshToAttach == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("MeshToAttach is nullptr for Socket %s"), *StaticMeshComponent->GetFName().ToString());
			continue;
		}

		StaticMeshComponent->SetStaticMesh(MeshToAttach);
		StaticMeshComponent->AttachToComponent(
			SkeletalMeshComponent,
			FAttachmentTransformRules::SnapToTargetIncludingScale,
			StaticMeshComponent->GetFName()
		);

		UE_LOG(LogTemp, Log, TEXT("Attached %s to socket %s"), *MeshToAttach->GetName(), *StaticMeshComponent->GetFName().ToString());
	}
}

void UCTTSocketAttachmentComponent::LoadSocketMeshData()
{
	UCTTGameInstance* GameInstance = Cast<UCTTGameInstance>(UGameplayStatics::GetGameInstance(this));
	if (nullptr == GameInstance)
	{
		UE_LOG(LogTemp, Error, TEXT("GameInstance is nullptr"));
		return;
	}

	const UCTTDatatableManager* DatatableManager = GameInstance->GetDatatableManager();
	if (nullptr == DatatableManager)
	{
		UE_LOG(LogTemp, Error, TEXT("DatatableManager is nullptr"));
		return;
	}

	DatatableManager->GetSocketMeshData(SocketMeshMap);
}
