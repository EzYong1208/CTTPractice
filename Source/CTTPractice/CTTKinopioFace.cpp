// Fill out your copyright notice in the Description page of Project Settings.


#include "CTTKinopioFace.h"
#include "Engine/DataTable.h"

// Sets default values
UCTTKinopioFace::UCTTKinopioFace()
{
	PrimaryComponentTick.bCanEverTick = false;

	// 컴포넌트를 생성하는 용도로 언리얼 엔진은 new가 아니라 CreateDefaultSubobject
	// 문자열 값은 액터에 속한 컴포넌트를 구별하기 위한 해시값 생성에 사용
	// 다른 컴포넌트와 중복되지 않는 유일한 값을 지정해야 함
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

