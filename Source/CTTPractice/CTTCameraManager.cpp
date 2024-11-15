// Fill out your copyright notice in the Description page of Project Settings.


#include "CTTCameraManager.h"
#include "CTTFollowCamera.h"
#include "CTTStaticCamera.h"
#include "CTTPracticeGameModeBase.h"
#include "Kismet/GameplayStatics.h"

void UCTTCameraManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

}

void UCTTCameraManager::Deinitialize()
{
	Super::Deinitialize();

	StaticCameraMap.Empty();
	FollowCamera = nullptr;
}

void UCTTCameraManager::InitializeCameras()
{
	TArray<AActor*> FoundCameras;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACTTFollowCamera::StaticClass(), FoundCameras);

	if (FoundCameras.Num() > 0)
	{
		FollowCamera = Cast<ACTTFollowCamera>(FoundCameras[0]);
		if (nullptr == FollowCamera)
		{
			UE_LOG(LogTemp, Error, TEXT("FollowCamera is nullptr"));
			return;
		}
	}

	ACTTPracticeGameModeBase* GameMode = Cast<ACTTPracticeGameModeBase>(UGameplayStatics::GetGameMode(this));
	if (false == IsValid(GameMode))
	{
		UE_LOG(LogTemp, Error, TEXT("GameMode is InValid"));
		return;
	}

	UDataTable* StaticCameraDataTable = GameMode->GetStaticCameraDataTable();
	if (nullptr == StaticCameraDataTable)
	{
		UE_LOG(LogTemp, Error, TEXT("DataTableManager is nullptr"));
		return;
	}

	FCTTStaticCameraData* StaticCameraData = nullptr;
	const int32 RowCount = StaticCameraDataTable->GetRowMap().Num();

	TArray<FName> RowNames = StaticCameraDataTable->GetRowNames();
	for (const FName& RowName : RowNames)
	{
		StaticCameraData = StaticCameraDataTable->FindRow<FCTTStaticCameraData>(RowName, TEXT(""));

		ACTTStaticCamera* NewCamera = GetWorld()->SpawnActor<ACTTStaticCamera>(StaticCameraData->Location, StaticCameraData->Rotation);
		if (!IsValid(NewCamera))
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to spawn ACTTStaticCamera"));
			return;
		}

		StaticCameraMap.Add(StaticCameraData->CameraID, NewCamera);
		NewCamera->SetCameraID(StaticCameraData->CameraID);
	}
}

void UCTTCameraManager::SwitchToCameraByID(int32 CameraID)
{
	TWeakObjectPtr<ACTTStaticCamera> StaticCamera = FindStaticCameraByID(CameraID);

	if (false == StaticCamera.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("StaticCamera is nullptr"));
		return;
	}

	SetViewTargetToCamera(Cast<AActor>(StaticCamera.Get()));	
}

void UCTTCameraManager::SwitchToFollowCamera()
{
	SetViewTargetToCamera(Cast<AActor>(FollowCamera.Get()));
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

	PlayerController->SetViewTargetWithBlend(CameraActor, 1.0f);
}

TWeakObjectPtr<ACTTStaticCamera> UCTTCameraManager::FindStaticCameraByID(int32 CameraID) const
{
	const TWeakObjectPtr<ACTTStaticCamera>* CameraPtr = StaticCameraMap.Find(CameraID);

	if (!CameraPtr)
	{
		UE_LOG(LogTemp, Warning, TEXT("StaticCamera with ID %d not found"), CameraID);
		return nullptr;
	}

	if (false == CameraPtr->IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("StaticCamera with ID %d is invalid"), CameraID);
		return nullptr;
	}

	return CameraPtr->Get();
}
