// Fill out your copyright notice in the Description page of Project Settings.


#include "CTTNPCFollowCamera.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACTTNPCFollowCamera::ACTTNPCFollowCamera()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACTTNPCFollowCamera::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ACTTNPCFollowCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

