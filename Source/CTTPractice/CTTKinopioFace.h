// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameFramework/Actor.h"
#include "CTTPractice/CTTEnum.h"
#include "CTTKinopioFace.generated.h"

USTRUCT(BlueprintType)
struct CTTPRACTICE_API FCTTKinopioFaceData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ECTTFaceType FaceType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMesh* FaceMesh;
};


UCLASS(Blueprintable)
class CTTPRACTICE_API ACTTKinopioFace : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACTTKinopioFace();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    UFUNCTION(BlueprintCallable)
    void SetFaceMesh(FName RowName);

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Face;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UDataTable* FaceDataTable;
};
