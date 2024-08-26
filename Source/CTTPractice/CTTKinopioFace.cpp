// Fill out your copyright notice in the Description page of Project Settings.


#include "CTTKinopioFace.h"
#include "Engine/DataTable.h"

// Sets default values
ACTTKinopioFace::ACTTKinopioFace()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// ������Ʈ�� �����ϴ� �뵵�� �𸮾� ������ new�� �ƴ϶� CreateDefaultSubobject
	// ���ڿ� ���� ���Ϳ� ���� ������Ʈ�� �����ϱ� ���� �ؽð� ������ ���
	// �ٸ� ������Ʈ�� �ߺ����� �ʴ� ������ ���� �����ؾ� ��
	Face = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FACE"));
}

// Called when the game starts or when spawned
void ACTTKinopioFace::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACTTKinopioFace::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACTTKinopioFace::SetFaceMesh(FName RowName)
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
		UE_LOG(LogTemp, Warning, TEXT("No face mesh assigned for None type"));
		return;
	}

	if (FaceData->FaceMesh)
	{
		Face->SetStaticMesh(FaceData->FaceMesh);
	}
}

