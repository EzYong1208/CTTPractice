// Fill out your copyright notice in the Description page of Project Settings.


#include "CTTItem.h"

// Sets default values
ACTTItem::ACTTItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACTTItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACTTItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACTTItem::InitializeItem(const FCTTItemData& ItemData)
{
	if (ItemData.StaticMesh)
	{
		UStaticMeshComponent* StaticMeshComponent = NewObject<UStaticMeshComponent>(this, UStaticMeshComponent::StaticClass(), TEXT("StaticMeshComponent"));
		if (StaticMeshComponent)
		{
			StaticMeshComponent->SetStaticMesh(ItemData.StaticMesh);
			StaticMeshComponent->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
			StaticMeshComponent->RegisterComponent();
		}
	}
	else if (ItemData.SkeletalMesh)
	{
		USkeletalMeshComponent* SkeletalMeshComponent = NewObject<USkeletalMeshComponent>(this, USkeletalMeshComponent::StaticClass(), TEXT("SkeletalMeshComponent"));
		if (SkeletalMeshComponent)
		{
			SkeletalMeshComponent->SetSkeletalMesh(ItemData.SkeletalMesh);
			SkeletalMeshComponent->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
			SkeletalMeshComponent->RegisterComponent();
		}
	}
}
