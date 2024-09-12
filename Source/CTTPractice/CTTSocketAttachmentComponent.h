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
	UStaticMesh* FaceMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMesh* HandLMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMesh* HandRMesh;
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

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* FaceMesh;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* HandLMesh;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* HandRMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UDataTable* SocketMeshDataTable;

	const FName SOCKETNAME_FACE = TEXT("Socket_Head");
	const FName SOCKETNAME_HANDL = TEXT("Socket_HandL");
	const FName SOCKETNAME_HANDR = TEXT("Socket_HandR");
};
