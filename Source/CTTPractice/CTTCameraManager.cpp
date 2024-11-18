// Fill out your copyright notice in the Description page of Project Settings.


#include "CTTCameraManager.h"
#include "CTTCharacterFollowCamera.h"
#include "CTTNPCFollowCamera.h"
#include "CTTNPCActor.h"
#include "CTTPracticeGameModeBase.h"
#include "Kismet/GameplayStatics.h"

void UCTTCameraManager::InitializeCameras()
{
	if (false == IsValid(CharacterFollowCameraClass))
	{
		UE_LOG(LogTemp, Error, TEXT("CharacterFollowCameraClass is invalid"));
		return;
	}

	CharacterFollowCamera = GetWorld()->SpawnActor<ACTTCharacterFollowCamera>(CharacterFollowCameraClass, FVector::ZeroVector, FRotator::ZeroRotator/*, SpawnParams*/);
	if (!IsValid(CharacterFollowCamera))
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to spawn CharacterFollowCamera"));
		return;
	}

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (nullptr == PlayerController)
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerController is nullptr"));
		return;
	}

	PlayerController->SetViewTargetWithBlend(Cast<AActor>(CharacterFollowCamera), 0.f);

	SpawnNPCFollowCameras();
}

void UCTTCameraManager::SwitchToFollowCamera()
{
	SetViewTargetToCamera(Cast<AActor>(CharacterFollowCamera));
}

void UCTTCameraManager::SwitchToNPCCameraByName(FName CameraName)
{
	TWeakObjectPtr<ACTTNPCFollowCamera> NPCCamera = FindNPCFollowCameraByName(CameraName);

	if (false == NPCCamera.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("NPCCamera is invalid"));
		return;
	}

	SetViewTargetToCamera(Cast<AActor>(NPCCamera.Get()));
}

TWeakObjectPtr<ACTTNPCFollowCamera> UCTTCameraManager::FindNPCFollowCameraByName(FName CameraName) const
{
	const TWeakObjectPtr<ACTTNPCFollowCamera>* CameraPtr = NPCFollowCameraMap.Find(CameraName);

	if (nullptr == CameraPtr)
	{
		UE_LOG(LogTemp, Error, TEXT("NPCCamera Name: %s is nullptr"), *CameraName.ToString());
		return nullptr;
	}

	if (false == CameraPtr->IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("NPCCamera Name: %s not found"), *CameraName.ToString());
		return nullptr;
	}

	return CameraPtr->Get();
}

void UCTTCameraManager::SetViewTargetToCamera(AActor* CameraActor)
{
	if (nullptr == CameraActor)
	{
		UE_LOG(LogTemp, Error, TEXT("CameraActor is nullptr"));
		return;
	}

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (nullptr == PlayerController)
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerController is nullptr"));
		return;
	}

	PlayerController->SetViewTargetWithBlend(CameraActor, CAMERA_BLEND_TIME);
}

void UCTTCameraManager::SpawnNPCFollowCameras()
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACTTNPCActor::StaticClass(), FoundActors);

	for (AActor* Actor : FoundActors)
	{
		ACTTNPCActor* NPCActor = Cast<ACTTNPCActor>(Actor);
		if (nullptr == NPCActor)
		{
			UE_LOG(LogTemp, Error, TEXT("NPCActor is nullptr"));
			return;
		}

		TSubclassOf<ACTTNPCFollowCamera> NPCFollowCameraClass = NPCActor->NPCFollowCameraClass;
		if (nullptr == NPCFollowCameraClass)
		{
			UE_LOG(LogTemp, Error, TEXT("NPCFollowCameraClass is nullptr"));
			return;
		}

		FActorSpawnParameters SpawnParams;
		ACTTNPCFollowCamera* SpawnedCamera = GetWorld()->SpawnActor<ACTTNPCFollowCamera>(NPCFollowCameraClass, NPCActor->GetActorLocation(), NPCActor->GetActorRotation(), SpawnParams);
		if (nullptr == SpawnedCamera)
		{
			UE_LOG(LogTemp, Error, TEXT("SpawnedCamera is nullptr"));
			return;
		}

		SpawnedCamera->SetTarget(NPCActor);
		NPCFollowCameraMap.Add(NPCActor->GetNPCName(), SpawnedCamera);
	}
}
