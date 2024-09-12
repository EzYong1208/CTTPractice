// Fill out your copyright notice in the Description page of Project Settings.


#include "CTTSocketAttachmentComponent.h"
#include "Engine/DataTable.h"

// Sets default values
UCTTSocketAttachmentComponent::UCTTSocketAttachmentComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	// ������Ʈ�� �����ϴ� �뵵�� �𸮾� ������ new�� �ƴ϶� CreateDefaultSubobject
	// ���ڿ� ���� ���Ϳ� ���� ������Ʈ�� �����ϱ� ���� �ؽð� ������ ���
	// �ٸ� ������Ʈ�� �ߺ����� �ʴ� ������ ���� �����ؾ� ��
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
