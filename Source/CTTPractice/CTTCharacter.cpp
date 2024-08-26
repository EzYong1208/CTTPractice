// Fill out your copyright notice in the Description page of Project Settings.


#include "CTTCharacter.h"
#include "CTTKinopioFace.h"

// Sets default values
ACTTCharacter::ACTTCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ACTTCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	FName FaceSocket(TEXT("Socket_Head"));

	if (!GetMesh()->DoesSocketExist(FaceSocket))
	{
		UE_LOG(LogTemp, Error, TEXT("FaceSocket does not exist"));
		return;
	}

	if (!IsValid(FaceClass))
	{
		UE_LOG(LogTemp, Error, TEXT("FaceClass is invalid"));
		return;
	}

	FVector SocketLocation = GetMesh()->GetSocketLocation(FaceSocket);
	FRotator SocketRotation = GetMesh()->GetSocketRotation(FaceSocket);
	FaceActor = GetWorld()->SpawnActor<ACTTKinopioFace>(FaceClass, SocketLocation, SocketRotation);

	if (nullptr == FaceActor)
	{
		UE_LOG(LogTemp, Error, TEXT("FaceActor is nullptr"));
		return;
	}

	FaceActor->SetFaceMesh(FName(TEXT("FaceData_Happy")));
	FaceActor->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepWorldTransform, FaceSocket);
}

// Called when the game starts or when spawned
void ACTTCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACTTCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACTTCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

