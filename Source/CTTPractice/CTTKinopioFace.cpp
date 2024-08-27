// Fill out your copyright notice in the Description page of Project Settings.


#include "CTTKinopioFace.h"
#include "Engine/DataTable.h"

// Sets default values
UCTTKinopioFace::UCTTKinopioFace()
{
	PrimaryComponentTick.bCanEverTick = false;

	// ������Ʈ�� �����ϴ� �뵵�� �𸮾� ������ new�� �ƴ϶� CreateDefaultSubobject
	// ���ڿ� ���� ���Ϳ� ���� ������Ʈ�� �����ϱ� ���� �ؽð� ������ ���
	// �ٸ� ������Ʈ�� �ߺ����� �ʴ� ������ ���� �����ؾ� ��
	Face = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FACE"));
}

void UCTTKinopioFace::BeginPlay()
{
	Super::BeginPlay();

	UDataTable* DataTable = LoadObject<UDataTable>(nullptr, TEXT("DataTable'/Game/Table/KinopioFaceDataTable.KinopioFaceDataTable'"));

	if (nullptr == DataTable)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to load FaceDataTable"));
		return;
	}

	FaceDataTable = DataTable;
}

void UCTTKinopioFace::SetFaceMesh(FName RowName)
{
	if (nullptr == FaceDataTable)
	{
		UE_LOG(LogTemp, Error, TEXT("FaceDataTable is nullptr"));
		return;
	}

	FCTTKinopioFaceData* FaceData = FaceDataTable->FindRow<FCTTKinopioFaceData>(RowName, TEXT(""));

	if (nullptr == FaceData)
	{
		UE_LOG(LogTemp, Error, TEXT("FaceData is nullptr"));
		return;
	}

	if (ECTTFaceType::None == FaceData->FaceType)
	{
		UE_LOG(LogTemp, Error, TEXT("No face mesh assigned for None type"));
		return;
	}

	if (FaceData->FaceMesh)
	{
		Face->SetStaticMesh(FaceData->FaceMesh);
		AttachFaceMeshToSocket();
	}
}

void UCTTKinopioFace::AttachFaceMeshToSocket()
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
	
	Face->AttachToComponent(SkeletalMeshComponent, FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("Socket_Head"));
}

