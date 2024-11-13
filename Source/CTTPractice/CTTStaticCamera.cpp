// Fill out your copyright notice in the Description page of Project Settings.


#include "CTTStaticCamera.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACTTStaticCamera::ACTTStaticCamera()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ACTTStaticCamera::BeginPlay()
{
	Super::BeginPlay();


}

void ACTTStaticCamera::ActivateCamera()
{
	
}
