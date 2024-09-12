// Fill out your copyright notice in the Description page of Project Settings.


#include "CTTSocketAttachmentComponent.h"
#include "Engine/DataTable.h"

// Sets default values
UCTTSocketAttachmentComponent::UCTTSocketAttachmentComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	// 컴포넌트를 생성하는 용도로 언리얼 엔진은 new가 아니라 CreateDefaultSubobject
	// 문자열 값은 액터에 속한 컴포넌트를 구별하기 위한 해시값 생성에 사용
	// 다른 컴포넌트와 중복되지 않는 유일한 값을 지정해야 함
	FaceMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FACEMESH"));
	HandLMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HANDLMESH"));
	HandRMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HANDRMESH"));
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

	FCTTSocketMeshData* MeshData = SocketMeshDataTable->FindRow<FCTTSocketMeshData>(RowName, TEXT(""));

	if (nullptr == MeshData)
	{
		UE_LOG(LogTemp, Error, TEXT("MeshData is nullptr"));
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

	if (MeshData->FaceMesh)
	{
		FaceMesh->SetStaticMesh(MeshData->FaceMesh);
		FaceMesh->AttachToComponent(SkeletalMeshComponent, FAttachmentTransformRules::SnapToTargetIncludingScale, SOCKETNAME_FACE);
	}
	if (MeshData->HandLMesh)
	{
		HandLMesh->SetStaticMesh(MeshData->HandLMesh);
		HandLMesh->AttachToComponent(SkeletalMeshComponent, FAttachmentTransformRules::SnapToTargetIncludingScale, SOCKETNAME_HANDL);
	}
	if (MeshData->HandRMesh)
	{
		HandRMesh->SetStaticMesh(MeshData->HandRMesh);
		HandRMesh->AttachToComponent(SkeletalMeshComponent, FAttachmentTransformRules::SnapToTargetIncludingScale, SOCKETNAME_HANDR);
	}
}
