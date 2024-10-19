// Fill out your copyright notice in the Description page of Project Settings.


#include "CTTItem.h"
#include "Components/SphereComponent.h"

// Sets default values
ACTTItem::ACTTItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionSphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphereComponent"));
	SetRootComponent(CollisionSphereComponent);
}

// Called when the game starts or when spawned
void ACTTItem::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACTTItem::PostInitializeComponents()
{
	Super::PostInitializeComponents();

}

// Called every frame
void ACTTItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACTTItem::InitializeItem(const FCTTItemData& ItemData)
{
	UMeshComponent* MeshComponent = nullptr;

	if (ItemData.StaticMesh)
	{
		MeshComponent = NewObject<UStaticMeshComponent>(this, UStaticMeshComponent::StaticClass(), TEXT("StaticMeshComponent"));
		if (false == IsValid(MeshComponent))
		{
			UE_LOG(LogTemp, Warning, TEXT("StaticMeshComponent NewObject failed"));
			return;
		}

		UStaticMeshComponent* StaticMeshComponent = Cast<UStaticMeshComponent>(MeshComponent);
		StaticMeshComponent->SetStaticMesh(ItemData.StaticMesh);
	}
	else if (ItemData.SkeletalMesh)
	{
		MeshComponent = NewObject<USkeletalMeshComponent>(this, USkeletalMeshComponent::StaticClass(), TEXT("SkeletalMeshComponent"));
		if (false == IsValid(MeshComponent))
		{
			UE_LOG(LogTemp, Warning, TEXT("SkeletalMeshComponent NewObject failed"));
			return;
		}

		USkeletalMeshComponent* SkeletalMeshComponent = Cast<USkeletalMeshComponent>(MeshComponent);
		SkeletalMeshComponent->SetSkeletalMesh(ItemData.SkeletalMesh);

		if (ItemData.AnimBlueprintClass)
		{
			SkeletalMeshComponent->SetAnimInstanceClass(ItemData.AnimBlueprintClass);
		}
	}

	if (IsValid(MeshComponent))
	{
		MeshComponent->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
		MeshComponent->RegisterComponent();
		MeshComponent->SetRelativeLocation(ItemData.MeshLocation);
		MeshComponent->SetWorldScale3D(ItemData.Scale);
	}

	CollisionSphereComponent->SetSphereRadius(ItemData.SphereRadius);
	ItemName = ItemData.ItemName;
}

void ACTTItem::DoAction()
{
	UE_LOG(LogTemp, Error, TEXT("ACTTItem DoAction"));
	bIsDead = true;
}
