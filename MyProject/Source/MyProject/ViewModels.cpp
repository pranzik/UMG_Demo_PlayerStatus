// Fill out your copyright notice in the Description page of Project Settings.


#include "ViewModels.h"
#include "PlayerDataModel.h"

void UViewModels::Initialize(UPlayerUIWidget* UIWidgetClass, UMainGameInstanceSubsystem* Instance, UPlayerDataModel* DataModel)
{
    PlayerDataModel = DataModel;
    EventManager = Instance->EventManager;
    if (EventManager)
    {
        UE_LOG(LogTemp, Warning, TEXT("Event manager is not null in viewmodels"));

    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Event manager is  null viewmodels"));

    }
    GameInstanceSubsystem = Instance;
    Init();

    PlayerUIWidget = UIWidgetClass; 
   if(!PlayerUIWidget->IsInViewport())
    {
        PlayerUIWidget->AddToViewport();

       
        if (EventManager)
        {
            ActivateUI();
        }
    }
}

void UViewModels::Init()
{
   
 

    if (EventManager)
    {
        UE_LOG(LogTemp, Log, TEXT("Game found"));

        EventManager->OnPlayerDataEvent.AddUObject(this, &UViewModels::UpdatePlayerLists);
        EventManager->OnStatusChange.RemoveAll(this);
        if (!(EventManager->OnStatusChange.IsBound()))
        {
            UE_LOG(LogTemp, Warning, TEXT("EventManager is subscribe in viewModels "));
            EventManager->OnStatusChange.AddUObject(this, &UViewModels::MoveElementBetweenScrollBoxes);
        }

    }
    else {
        UE_LOG(LogTemp, Log, TEXT("EventManager in PlayerUi widgets not found"));

    }
}


void UViewModels::UpdatePlayerLists(TArray<FPlayerData>& ConnectedPlayer, TArray<FPlayerData>& DisconnectedPlayer)
{
    UE_LOG(LogTemp, Log, TEXT("Update player list called"));

    PlayerUIWidget->UpdatePlayerLists(ConnectedPlayer, DisconnectedPlayer);
}
void UViewModels::MoveElementBetweenScrollBoxes(FPlayerData* PlayerData)
{
    UE_LOG(LogTemp, Warning, TEXT("MoveElementBetweenScrollBoxes %s"), *PlayerData->Nickname);

    PlayerUIWidget->MoveElementBetweenScrollBoxes(PlayerData);
   EventManager->ActivateToast.Broadcast(PlayerData);

}
void UViewModels::ActivateUI()
{

    if (PlayerUIWidget == nullptr)
    {
        UE_LOG(LogTemp, Warning, TEXT("PlayerDataModel is null."));

    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("PlayerDataModel is not null."));

    }

    PlayerUIWidget->Init(EventManager);
   GetConnectedDisconnectedList();
}


void UViewModels::GetConnectedDisconnectedList()
{
    PlayerDataModel->GetAllPlayers();


}

void UViewModels::InitializeWidget()
{
    UE_LOG(LogTemp, Warning, TEXT("Is not destroyed"));

}

