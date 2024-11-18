// Fill out your copyright notice in the Description page of Project Settings.


#include "CTTMapObject.h"
#include "Components/BoxComponent.h"

// Sets default values
ACTTMapObject::ACTTMapObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACTTMapObject::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACTTMapObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACTTMapObject::HandleCollisionEvent(ECTTCollisionType InCollisionType)
{
    switch (InCollisionType)
    {
    case ECTTCollisionType::Buff:
    {
        if (ECTTCollisionType::Block == CollisionType)
        {
            Destroy();
        }
        else if (ECTTCollisionType::HardBlock == CollisionType)
        {
            Destroy();
        }
    }
        break;

    case ECTTCollisionType::Projectile:
        if (ECTTCollisionType::Block == CollisionType)
        {
            Destroy();
        }
        else if (ECTTCollisionType::HardBlock == CollisionType)
        {

        }
        break;
    }
}
