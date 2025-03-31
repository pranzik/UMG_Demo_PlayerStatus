// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerUIWidget.h"
#include "UBUIInventoryItem.h"



void UPlayerUIWidget::NativeConstruct()
{
    Super::NativeConstruct();


}



void UPlayerUIWidget::OnClickExpandConnectedPlayers() 
{
    UE_LOG(LogTemp, Warning, TEXT("Connected Players Expand Button Pressed"));

}
void UPlayerUIWidget::OnClickExpandDisconnectedPlayers()
{
    UE_LOG(LogTemp, Warning, TEXT("Disconnected Players Expand Button Pressed"));

}

void UPlayerUIWidget::Init(UGameEventManager* EventsManager)
{
    EventManager = EventsManager;
}

void UPlayerUIWidget::UpdatePlayerLists(TArray<FPlayerData>& ConnectedPlayer, TArray<FPlayerData>& DisconnectedPlayer)
{
    ConnectedPlayers = ConnectedPlayer;
    DisconnectedPlayers = DisconnectedPlayer;

    for (const FPlayerData& PlayerData : ConnectedPlayers)
    {
            UBUIInventoryItem* data = NewObject<UBUIInventoryItem>();
            data->SetPlayerData(PlayerData);
            ConnectedInventory.Add(data);
    }

    for (const FPlayerData& PlayerData : DisconnectedPlayers)
    {

        UBUIInventoryItem* data = NewObject<UBUIInventoryItem>();
        data->SetPlayerData(PlayerData);
        DisconnectedInventory.Add(data);
    }
    ConnectedPlayersList->SetListItems(ConnectedInventory);
    DisconnectedPlayersList->SetListItems(DisconnectedInventory);

}




void UPlayerUIWidget::MoveElementBetweenScrollBoxes(FPlayerData* PlayerData)
{

    int32 Index;
    bool PreviousStatus =  !(PlayerData->IsConnected);
    UBUIInventoryItem* WidgetToMove = nullptr;

    if (PreviousStatus)
    {
        Index = ConnectedPlayers.IndexOfByPredicate([PlayerData](const FPlayerData& Data) { return Data.Nickname == PlayerData->Nickname; });
      
        if (Index != INDEX_NONE)
        {
            ConnectedPlayers.RemoveAt(Index);
            DisconnectedPlayers.Add(*PlayerData);
            UE_LOG(LogTemp, Warning, TEXT("  found in connected %s"), *PlayerData->Nickname);


             WidgetToMove = ConnectedInventory[Index];
            DisconnectedInventory.Add(WidgetToMove);
            ConnectedInventory.RemoveAt(Index);
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("not found in disconnected %s"), *PlayerData->Nickname);


        }
    }
    else
    {
        Index = DisconnectedPlayers.IndexOfByPredicate([PlayerData](const FPlayerData& Data) { return Data.Nickname == PlayerData->Nickname; });
        if (Index != INDEX_NONE)
        {
            DisconnectedPlayers.RemoveAt(Index);
            ConnectedPlayers.Add(*PlayerData);
            UE_LOG(LogTemp, Warning, TEXT(" found in disconnected %s"), *PlayerData->Nickname);

             WidgetToMove = DisconnectedInventory[Index];
            ConnectedInventory.Add(WidgetToMove);
            DisconnectedInventory.RemoveAt(Index);

        }else
        {
            UE_LOG(LogTemp, Warning, TEXT("not found in disconnected %s"), *PlayerData->Nickname);

        }
    }
    UListView* SourceScrollBox = PreviousStatus ? ConnectedPlayersList : DisconnectedPlayersList;
    UListView* TargetScrollBox = PreviousStatus ? DisconnectedPlayersList : ConnectedPlayersList;

    TArray<UBUIInventoryItem*> SourceScrollBoxArray = PreviousStatus ? ConnectedInventory : DisconnectedInventory;
    TArray<UBUIInventoryItem*> TargetScrollBoxArray = PreviousStatus ? DisconnectedInventory : ConnectedInventory;

    UE_LOG(LogTemp, Warning, TEXT("Index: %d number of items %d"), Index, SourceScrollBox->GetListItems().Num());

    if (SourceScrollBox && TargetScrollBox && Index >= 0 && Index < SourceScrollBox->GetListItems().Num())
    {
          UE_LOG(LogTemp, Warning, TEXT("widget move "));

        if (WidgetToMove)
        {
            UE_LOG(LogTemp, Warning, TEXT("widget move  inside if condition "));

            SourceScrollBox->RemoveItem(WidgetToMove);

            TargetScrollBox->AddItem(WidgetToMove);
        }
        else {
            UE_LOG(LogTemp, Warning, TEXT("widgetToMove "));

        }

    }

}

