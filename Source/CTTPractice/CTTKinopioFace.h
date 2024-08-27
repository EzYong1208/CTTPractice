// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Components/ActorComponent.h"
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

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CTTPRACTICE_API UCTTKinopioFace : public UActorComponent
{
	GENERATED_BODY()
	
public:
	UCTTKinopioFace();

	virtual void BeginPlay() override;

public:	
    UFUNCTION(BlueprintCallable)
    void SetFaceMesh(FName RowName);

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Face;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UDataTable* FaceDataTable;

private:
	void AttachFaceMeshToSocket();
};
