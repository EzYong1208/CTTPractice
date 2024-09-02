// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Components/ActorComponent.h"
#include "CTTPractice/CTTEnum.h"
#include "CTTSocketAttachmentComponent.generated.h"

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CTTPRACTICE_API UCTTSocketAttachmentComponent : public UActorComponent
{
	GENERATED_BODY()
	
public:
	UCTTSocketAttachmentComponent();

	virtual void BeginPlay() override;

	void AttachMeshToSocket(FName SocketName, UStaticMesh* Mesh);

public:	
    UFUNCTION(BlueprintCallable)
    void SetMeshByName(FName RowName);

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* AttachMesh;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UDataTable* SocketMeshDataTable;
};
