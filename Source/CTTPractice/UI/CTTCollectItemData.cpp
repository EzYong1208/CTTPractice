// Fill out your copyright notice in the Description page of Project Settings.


#include "CTTCollectItemData.h"

void UCTTCollectItemData::SetCollect()
{
	bIsCollected = true;

	if (OnChangeCollectItemStateDelegate.IsBound())
	{
		OnChangeCollectItemStateDelegate.Broadcast(bIsCollected);
	}
}

void UCTTCollectItemData::SetEmpty()
{
	bIsCollected = false;

	if (OnChangeCollectItemStateDelegate.IsBound())
	{
		OnChangeCollectItemStateDelegate.Broadcast(bIsCollected);
	}
}
