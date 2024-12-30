// Fill out your copyright notice in the Description page of Project Settings.


#include "CTTPractice/Managers/CTTCameraManager.h"
#include "CTTPractice/Actor/Camera/CTTCharacterFollowCamera.h"
#include "CTTPractice/Actor/Camera/CTTNPCFollowCamera.h"
#include "CTTPractice/Interaction/CTTNPCActor.h"
#include "CTTPractice/CTTPracticeGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "CTTPractice/CTTGameInstance.h"
#include "CTTPractice/Managers/CTTDatatableManager.h"

void UCTTCameraManager::InitializeCameras()
{
	if (false == IsValid(CharacterFollowCameraClass))
	{
		UE_LOG(LogTemp, Error, TEXT("CharacterFollowCameraClass is invalid"));
		return;
	}

	CharacterFollowCamera = GetWorld()->SpawnActor<ACTTCharacterFollowCamera>(CharacterFollowCameraClass, FVector::ZeroVector, FRotator::ZeroRotator);
	if (!IsValid(CharacterFollowCamera))
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to spawn CharacterFollowCamera"));
		return;
	}

	if (false == IsValid(NPCFollowCameraClass))
	{
		UE_LOG(LogTemp, Error, TEXT("NPCFollowCameraClass is invalid"));
		return;
	}

	NPCFollowCamera = GetWorld()->SpawnActor<ACTTNPCFollowCamera>(NPCFollowCameraClass, FVector::ZeroVector, FRotator::ZeroRotator);
	if (!IsValid(NPCFollowCamera))
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to spawn NPCFollowCamera"));
		return;
	}

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (nullptr == PlayerController)
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerController is nullptr"));
		return;
	}

	PlayerController->SetViewTargetWithBlend(CharacterFollowCamera, 0.f);

	LoadNPCActorData();
}

void UCTTCameraManager::SwitchToFollowCamera()
{
	SetViewTargetToCamera(CharacterFollowCamera);
}

void UCTTCameraManager::SwitchToNPCCameraByName(FName NPCName)
{
	const FCTTSpringArmData* SpringArmData = GetNPCActorData(NPCName);
	if (nullptr == SpringArmData)
	{
		UE_LOG(LogTemp, Error, TEXT("SpringArmData is nullptr"));
		return;
	}

	TWeakObjectPtr<AActor>* NPCActor = NPCActorMap.Find(NPCName);
	if (nullptr == NPCActor)
	{
		UE_LOG(LogTemp, Error, TEXT("NPCActor is nullptr"));
		return;
	}

	NPCFollowCamera->SetTarget(NPCActor->Get());
	NPCFollowCamera->UpdateSpringArmData(*SpringArmData);
	SetViewTargetToCamera(NPCFollowCamera);
}

ACTTCharacterFollowCamera* UCTTCameraManager::GetCharacterFollowCamera() const
{
	if (nullptr == CharacterFollowCamera)
	{
		UE_LOG(LogTemp, Error, TEXT("CharacterFollowCamera is nullptr"));
		return nullptr;
	}

	return CharacterFollowCamera;
}

void UCTTCameraManager::LoadNPCActorData()
{
	UCTTGameInstance* GameInstance = Cast<UCTTGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (!GameInstance)
	{
		UE_LOG(LogTemp, Error, TEXT("GameInstance is nullptr"));
		return;
	}

	const UCTTDatatableManager* DatatableManager = GameInstance->GetDatatableManager();
	if (nullptr == DatatableManager)
	{
		UE_LOG(LogTemp, Error, TEXT("DatatableManager is nullptr"));
		return;
	}

	DatatableManager->GetNPCSpringArmDataMap(NPCActorDataMap);

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACTTNPCActor::StaticClass(), FoundActors);

	for (AActor* Actor : FoundActors)
	{
		ACTTNPCActor* NPCActor = Cast<ACTTNPCActor>(Actor);
		if (nullptr == NPCActor)
		{
			UE_LOG(LogTemp, Error, TEXT("NPCActor is nullptr"));
			continue;
		}

		NPCActorMap.Add(NPCActor->GetNPCName(), NPCActor);
	}
}

const FCTTSpringArmData* UCTTCameraManager::GetNPCActorData(const FName& RowName) const
{
	const FCTTSpringArmData* SpringArmData = NPCActorDataMap.Find(RowName);

	if (SpringArmData)
	{
		return SpringArmData;
	}

	UE_LOG(LogTemp, Warning, TEXT("No SpringArmData found for RowName: %s"), *RowName.ToString());
	return nullptr;
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

	APlayerCameraManager* CameraManager = PlayerController->PlayerCameraManager;
	if (nullptr == CameraManager)
	{
		UE_LOG(LogTemp, Error, TEXT("CameraManager is nullptr"));
		return;
	}

	// 페이드인아웃
	CameraManager->StartCameraFade(0.f, 1.f, FadeOutTime, FLinearColor::Black, false, true);

	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [PlayerController, CameraActor, CameraManager, this]()
		{
			PlayerController->SetViewTargetWithBlend(CameraActor, 0.f);
			CameraManager->StartCameraFade(1.f, 0.f, FadeInTime, FLinearColor::Black, false, true);

		}, FadeOutTime, false);
}
