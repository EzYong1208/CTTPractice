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
	AttachMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ATTACHMESH"));
}

void UCTTSocketAttachmentComponent::BeginPlay()
{
	Super::BeginPlay();

	//UDataTable* DataTable = LoadObject<UDataTable>(nullptr, TEXT("DataTable'/Game/Table/KinopioFaceDataTable.KinopioFaceDataTable'"));

	//if (nullptr == DataTable)
	//{
	//	UE_LOG(LogTemp, Error, TEXT("Failed to load SocketMeshDataTable"));
	//	return;
	//}

	//SocketMeshDataTable = DataTable;
}

void UCTTSocketAttachmentComponent::SetMeshByName(FName RowName)
{
	//if (nullptr == SocketMeshDataTable)
	//{
	//	UE_LOG(LogTemp, Error, TEXT("SocketMeshDataTable is nullptr"));
	//	return;
	//}

	//FCTTSocketMeshData* FaceData = SocketMeshDataTable->FindRow<FCTTSocketMeshData>(RowName, TEXT(""));

	//if (nullptr == FaceData)
	//{
	//	UE_LOG(LogTemp, Error, TEXT("FaceData is nullptr"));
	//	return;
	//}

	//if (ECTTFaceType::None == FaceData->FaceType)
	//{
	//	UE_LOG(LogTemp, Error, TEXT("No face mesh assigned for None type"));
	//	return;
	//}

	//if (FaceData->Mesh)
	//{
	//	Face->SetStaticMesh(FaceData->Mesh);
	//	AttachMeshToSocket();
	//}
}

void UCTTSocketAttachmentComponent::AttachMeshToSocket(FName SocketName, UStaticMesh* Mesh)
{
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
	
	AttachMesh->SetStaticMesh(Mesh);
	AttachMesh->AttachToComponent(SkeletalMeshComponent, FAttachmentTransformRules::SnapToTargetIncludingScale, SocketName);
}

