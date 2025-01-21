// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CTTPractice/CTTDatatableHeader.h"
#include "CTTCollectibleItem.generated.h"

class UCapsuleComponent;
class UCTTActionBase;

UCLASS()
class CTTPRACTICE_API ACTTCollectibleItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACTTCollectibleItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	const FName GetItemName() const { return ItemName; }
	const int32 GetCurrentActionIndex() const { return CurrentActionIndex; }

	void StartActions(const TArray<FCTTActionData>& Actions);
	void UpdateActions();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UCapsuleComponent* CapsuleComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ItemName;
	
	int32 CurrentActionIndex = 0;
	TArray<TSubclassOf<UCTTActionBase>> ActionClasses;

	float CurrentTime = 0.f;
	TArray<FCTTActionData> PendingActions;
	FTimerHandle ActionTimerHandle;
};
