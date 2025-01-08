// Fill out your copyright notice in the Description page of Project Settings.


#include "CTTActionBase.h"
#include "CTTPractice/CTTGameInstance.h"
#include "Kismet/GameplayStatics.h"

void UCTTActionBase_AddCoin::Execute_Implementation()
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
