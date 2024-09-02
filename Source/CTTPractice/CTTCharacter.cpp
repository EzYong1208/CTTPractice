// Fill out your copyright notice in the Description page of Project Settings.


#include "CTTCharacter.h"
#include "CTTSocketAttachmentComponent.h"

// Sets default values
ACTTCharacter::ACTTCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SocketAttachmentComponent = CreateDefaultSubobject<UCTTSocketAttachmentComponent>(TEXT("SocketAttachmentComponent"));
}

// Called when the game starts or when spawned
void ACTTCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (SocketAttachmentComponent)
	{
		SocketAttachmentComponent->SetMeshByName(TEXT("FaceData_Happy"));
	}
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

