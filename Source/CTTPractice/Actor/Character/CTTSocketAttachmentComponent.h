// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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

private:
	void LoadSocketMeshData();

private:
	TMap<FName, TMap<FName, TWeakObjectPtr<UStaticMesh>>> SocketMeshMap;
};
