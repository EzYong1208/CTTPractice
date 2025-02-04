// Fill out your copyright notice in the Description page of Project Settings.


#include "CTTPractice/Event/CTTActionBase.h"
#include "CTTPractice/CTTGameInstance.h"
#include "Kismet/GameplayStatics.h"

void UCTTActionBase_AddCoin::Execute_Implementation(AActor* Actor)
{
	UCTTGameInstance* GameInstance = Cast<UCTTGameInstance>(UGameplayStatics::GetGameInstance(this));
	if (!IsValid(GameInstance))
	{
		UE_LOG(LogTemp, Warning, TEXT("GameInstance is InValid"));
		return;
	}

	int32 CurrentCoinCount = GameInstance->GetCoinCount();
	GameInstance->SetCoinCount(CurrentCoinCount + CoinAmount);
}

void UCTTActionBase_Die::Execute_Implementation(AActor* Actor)
{
	// EzYong TODO : 이벤트매니저의 맵 내에 있는 액터를 빼고, 액터를 Destroy 시키기

}
