// Fill out your copyright notice in the Description page of Project Settings.


#include "CTTKinopioFace.h"
#include "Engine/DataTable.h"

// Sets default values
ACTTKinopioFace::ACTTKinopioFace()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// 컴포넌트를 생성하는 용도로 언리얼 엔진은 new가 아니라 CreateDefaultSubobject
	// 문자열 값은 액터에 속한 컴포넌트를 구별하기 위한 해시값 생성에 사용
	// 다른 컴포넌트와 중복되지 않는 유일한 값을 지정해야 함
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

