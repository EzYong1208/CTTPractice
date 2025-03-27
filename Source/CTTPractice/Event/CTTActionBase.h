// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CTTPractice/CTTDatatableHeader.h"
#include "CTTActionBase.generated.h"

/**
 * 
 */

UCLASS(Abstract)
class CTTPRACTICE_API UCTTActionBase : public UObject
{
	GENERATED_BODY()

public:
	virtual void InitializeWithActionData(const FCTTActionData& InActionData) {}
	virtual void Execute_Implementation(AActor* Actor) {}
	virtual void Pause_Implementation(AActor* Actor) {}
	virtual void Resume_Implementation(AActor* Actor) {}


	// EzYong TODO : ���ο� �׼� �ڽ� Ŭ���� �߰� �� Enum �߰� �� ActionManager�� ActionClassMap�� �߰� �ʿ���
	// EzYong TODO : ���ο� �׼� �ڽ� Ŭ���� �߰� �� �����ؾ��ϴµ� ������ �� �־ ���������� �� �ɸ��� ����� �κ��� �� �߰� �ʿ�
	static constexpr int32 TotalActionClassCount = 6;
	static_assert(static_cast<int32>(ECTTActionType::MAX) - 1 == TotalActionClassCount,
		"Action class count does not match ECTTActionType enum count! Please update TotalActionClassCount!");
};

UCLASS()
class CTTPRACTICE_API UCTTActionBase_SpawnActor : public UCTTActionBase
{
	GENERATED_BODY()

public:
	virtual void InitializeWithActionData(const FCTTActionData& InActionData) override;
	virtual void Execute_Implementation(AActor* Actor) override;
	virtual void Pause_Implementation(AActor* Actor) override {}
	virtual void Resume_Implementation(AActor* Actor) override {}

private:
	TSubclassOf<AActor> ActorClassToSpawn;
};

UCLASS()
class CTTPRACTICE_API UCTTActionBase_AddCoin : public UCTTActionBase
{
	GENERATED_BODY()

public:
	virtual void InitializeWithActionData(const FCTTActionData& InActionData) override;
	virtual void Execute_Implementation(AActor* Actor) override;
	virtual void Pause_Implementation(AActor* Actor) override {}
	virtual void Resume_Implementation(AActor* Actor) override {}

private:
	int32 CoinAmount = 0;
};

UCLASS()
class CTTPRACTICE_API UCTTActionBase_FillCollectItem : public UCTTActionBase
{
	GENERATED_BODY()

public:
	virtual void InitializeWithActionData(const FCTTActionData& InActionData) override;
	virtual void Execute_Implementation(AActor* Actor) override;
	virtual void Pause_Implementation(AActor* Actor) override {}
	virtual void Resume_Implementation(AActor* Actor) override {}
};

UCLASS()
class CTTPRACTICE_API UCTTActionBase_Die : public UCTTActionBase
{
	GENERATED_BODY()

public:
	virtual void InitializeWithActionData(const FCTTActionData& InActionData) override {};
	virtual void Execute_Implementation(AActor* Actor) override;
	virtual void Pause_Implementation(AActor* Actor) override {}
	virtual void Resume_Implementation(AActor* Actor) override {}
};

UCLASS()
class CTTPRACTICE_API UCTTActionBase_Rotate : public UCTTActionBase
{
	GENERATED_BODY()

public:
	virtual void InitializeWithActionData(const FCTTActionData& InActionData) override;
	virtual void Execute_Implementation(AActor* Actor) override;
	virtual void Pause_Implementation(AActor* Actor) override;
	virtual void Resume_Implementation(AActor* Actor) override;

private:
	int32 RotateSpeed = 0;
	int32 RotateDuration = 0;
};

UCLASS()
class CTTPRACTICE_API UCTTActionBase_Jump : public UCTTActionBase
{
	GENERATED_BODY()

public:
	virtual void InitializeWithActionData(const FCTTActionData& InActionData) override;
	virtual void Execute_Implementation(AActor* Actor) override;
	virtual void Pause_Implementation(AActor* Actor) override {}
	virtual void Resume_Implementation(AActor* Actor) override {}

private:
	float JumpSpeed = 0.f;
};