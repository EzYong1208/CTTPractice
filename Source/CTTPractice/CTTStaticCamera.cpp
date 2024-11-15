// Fill out your copyright notice in the Description page of Project Settings.


#include "CTTStaticCamera.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACTTStaticCamera::ACTTStaticCamera()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ACTTStaticCamera::BeginPlay()
{
	Super::BeginPlay();


}

void ACTTStaticCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACTTStaticCamera::SetCameraID(int32 InCamerID)
{
	CameraID = InCamerID;
}

void ACTTStaticCamera::ActivateCamera()
{
	
}
