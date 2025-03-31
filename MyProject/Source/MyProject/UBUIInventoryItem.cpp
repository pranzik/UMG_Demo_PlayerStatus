// Fill out your copyright notice in the Description page of Project Settings.


#include "UBUIInventoryItem.h"


FPlayerData UBUIInventoryItem::GetPlayerData() const
{
	return playerData;
}

void UBUIInventoryItem::SetPlayerData(const FPlayerData& NewData)
{
	playerData = FPlayerData();
	playerData = NewData;
}
