// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Components/ActorComponent.h"
#include "CTTPractice/CTTEnum.h"
#include "CTTSocketAttachmentComponent.generated.h"

USTRUCT(BlueprintType)
struct CTTPRACTICE_API FCTTSocketMeshData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName AnimationName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName SocketName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMesh* Mesh;
};

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CTTPRACTICE_API UCTTSocketAttachmentComponent : public UActorComponent
{
	GENERATED_BODY()
	
public:
	UCTTSocketAttachmentComponent();

	virtual void BeginPlay() override;

public:	
    UFUNCTION(BlueprintCallable)
    void SetMeshByName(FName RowName);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UDataTable* SocketMeshDataTable;
};
