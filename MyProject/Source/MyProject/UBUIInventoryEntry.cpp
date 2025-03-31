// Fill out your copyright notice in the Description page of Project Settings.


#include "UBUIInventoryEntry.h"
#include "Components/TextBlock.h"


void UUBUIInventoryEntry::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	UBUIInventoryItem* data = Cast<UBUIInventoryItem>(ListItemObject);
	if (data)
	{
		OnDataRecieved(data->GetPlayerData());
		NameLabel->SetText(FText::FromString(data->GetPlayerData().Nickname));
	}
}

void UUBUIInventoryEntry::SetPlayerData(const FPlayerData& NewData)
{

}