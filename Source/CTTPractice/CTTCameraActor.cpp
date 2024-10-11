// Fill out your copyright notice in the Description page of Project Settings.


#include "CTTCameraActor.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"

ACTTCameraActor::ACTTCameraActor()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ACTTCameraActor::BeginPlay()
{
	Super::BeginPlay();

}

void ACTTCameraActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
