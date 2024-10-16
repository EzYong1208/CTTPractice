// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CTTPractice/CTTStruct.h"
#include "Components/ActorComponent.h"
#include "CTTSocketAttachmentComponent.generated.h"

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

private:
	TMap<FName, TMap<FName, UStaticMesh*>> SocketMeshMap;
};
