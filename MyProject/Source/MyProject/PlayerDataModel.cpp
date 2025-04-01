// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerDataModel.h"
UPlayerDataModel::UPlayerDataModel() : PlayerDataTable(nullptr)
{
    PlayerDataTable = nullptr;
}

void UPlayerDataModel::Initialize(UDataTable* DataTable, UGameEventManager* EventsManager)
{
    //  GetObjectReferenceByPath(TEXT("/Game/Data/DT_PlayerData.DT_PlayerData"));

    PlayerDataTable = DataTable;
    EventManager = EventsManager;

    if (PlayerDataTable)
    {
        int32 RowCount = PlayerDataTable->GetRowMap().Num();
        UE_LOG(LogTemp, Log, TEXT("Total Rows in PlayerDataTable: %d"), RowCount);
    }
    if (EventManager)
    {
        UE_LOG(LogTemp, Log, TEXT("EventManager is not null 1"));

    }
    else
    {
        UE_LOG(LogTemp, Log, TEXT("EventManager is  null 1"));
    }

}


void UPlayerDataModel::GetAllPlayers()
{
    if (!PlayerDataTable)
    {
        UE_LOG(LogTemp, Warning, TEXT("PlayerDataTable is null."));
        //  return;
    }

    UE_LOG(LogTemp, Warning, TEXT("Get Player %d"), ConnectedPlayers.Num());

    static const FString ContextString(TEXT("Player Data Context"));
    TArray<FPlayerData*> AllRows;
    PlayerDataTable->GetAllRows(ContextString, AllRows);
    ConnectedPlayers.Empty();
    DisconnectedPlayers.Empty();
    for (FPlayerData* Row : AllRows)
    {
        if (Row && Row->IsConnected)
        {
            UE_LOG(LogTemp, Log, TEXT("Connected"));

            ConnectedPlayers.Add(*Row);
        }
        else if (Row && !Row->IsConnected)
        {
            UE_LOG(LogTemp, Log, TEXT("Disconnected"));


            DisconnectedPlayers.Add(*Row);
        }

    }
    if (EventManager)
    {
        UE_LOG(LogTemp, Warning, TEXT("Data Broadcasted from PlayerDatamodel list %d"), ConnectedPlayers.Num());

        EventManager->OnPlayerDataEvent.Broadcast(ConnectedPlayers, DisconnectedPlayers);
        UE_LOG(LogTemp, Warning, TEXT("Data Broadcasted"));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("GameInsatnec is null"));

    }
    UWorld* World = GetWorld();
    if (World)
    {
        UE_LOG(LogTemp, Warning, TEXT("World is not null"));

    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("World is  null"));

    }
    World->GetTimerManager().SetTimer(TimerHandle, this, &UPlayerDataModel::OnTimerExpire, 5.0f, true);

}





  

bool UPlayerDataModel::GetPlayerConnectionStatus(const FString& Nickname) const
{
    if (!PlayerDataTable)
    {
        UE_LOG(LogTemp, Warning, TEXT("PlayerDataTable is null."));
        return false;
    }

    static const FString ContextString(TEXT("Player Data Context"));

    for (const auto& Row : PlayerDataTable->GetRowMap())
    {

        FPlayerData* PlayerData = (FPlayerData*)Row.Value;
        if (PlayerData && PlayerData->Nickname == Nickname)
        {

            return PlayerData->IsConnected;
        }
    }

    UE_LOG(LogTemp, Warning, TEXT("Player with nickname %s not found in data table"), *Nickname);
    return false;
}

FPlayerData UPlayerDataModel::GetRandomPlayer()
{
    if (ConnectedPlayers.Num() == 0 && DisconnectedPlayers.Num() == 0)
    {
        return FPlayerData(); // Return a default-constructed FPlayerData
    }

    bool bChooseConnected = FMath::RandBool();
    FPlayerData Data;
    if (bChooseConnected && ConnectedPlayers.Num() == 0)
    {
        bChooseConnected = false;
    }
    else if (!bChooseConnected && DisconnectedPlayers.Num() == 0)
    {
        bChooseConnected = true;
    }

    if (bChooseConnected)
    {
        int32 RandomIndex = FMath::RandRange(0, ConnectedPlayers.Num() - 1);
         Data =  ConnectedPlayers[RandomIndex];
        ConnectedPlayers.RemoveAt(RandomIndex);
        Data.IsConnected = false;
        DisconnectedPlayers.Add(Data);
        return Data;


    }
    else
    {
        int32 RandomIndex = FMath::RandRange(0, DisconnectedPlayers.Num() - 1);

            Data = DisconnectedPlayers[RandomIndex];
        DisconnectedPlayers.RemoveAt(RandomIndex);
        Data.IsConnected = true;
        ConnectedPlayers.Add(Data);
        return Data;

    }

}

void UPlayerDataModel::OnTimerExpire()
{

    UE_LOG(LogTemp, Warning, TEXT("10 seconds have passed!"));

    FPlayerData TempPlayer = GetRandomPlayer();
    bool TempBool = TempPlayer.IsConnected;

    UE_LOG(LogTemp, Warning, TEXT("10seconds have passed! %s %s"), *TempPlayer.Nickname, TempBool ? TEXT("true") : TEXT("false"));
    FPlayerData* playerData = &TempPlayer;
   // UpdatePlayerConnectionStatus(TempPlayer);
    if (EventManager)
    {
        UE_LOG(LogTemp, Warning, TEXT(" not null eventMananger "));

        if (EventManager->OnStatusChange.IsBound())
        {
            UE_LOG(LogTemp, Warning, TEXT(" Status is bound "));
            EventManager->OnStatusChange.Broadcast(playerData);
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT(" Status is not bound "));
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("null eventMananger "));
    }

}



//void UPlayerDataModel::GetObjectReferenceByPath(const FString& AssetPath)
//{
//    // Get the AssetRegistry module
//    FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
//    IAssetRegistry& AssetRegistry = AssetRegistryModule.Get();
//
//    FAssetData AssetData = AssetRegistry.GetAssetByObjectPath(*AssetPath);
//
//    if (AssetData.IsValid())
//    {
//        UObject* Asset = AssetData.GetAsset();
//
//        if (Asset)
//        {
//            UE_LOG(LogTemp, Log, TEXT("Successfully found asset: %s"), *Asset->GetName());
//            PlayerDataTable = Cast<UDataTable>(Asset);
//            if (PlayerDataTable)
//            {
//                UE_LOG(LogTemp, Log, TEXT("Successfully found and cast asset: %s"), *PlayerDataTable->GetName());
//            }
//            else
//            {
//
//                FGenericPlatformMisc::RequestExit(false);
//                UE_LOG(LogTemp, Warning, TEXT("Asset found but could not be cast to UPlayerDataModel: %s"), *Asset->GetName());
//            }
//        }
//        else
//        {
//            UE_LOG(LogTemp, Warning, TEXT("Asset found but failed to load: %s"), *AssetPath);
//        }
//    }
//    else
//    {
//        UE_LOG(LogTemp, Error, TEXT("Asset not found at path: %s"), *AssetPath);
//    }
//}
void UPlayerDataModel::UpdatePlayerConnectionStatus(const FPlayerData& Data) //TFunction<void()> CompletionCallback)
{
    if (!PlayerDataTable)
    {
        UE_LOG(LogTemp, Warning, TEXT("PlayerDataTable is null."));
        return;
    }

    static const FString ContextString(TEXT("Player Data Context"));
    bool bFound = false;
    UE_LOG(LogTemp, Warning, TEXT("Change data from playerData "));

    for (const auto& Row : PlayerDataTable->GetRowMap())
    {
        UE_LOG(LogTemp, Warning, TEXT(" inside for loop "));

        FPlayerData* PlayerData = (FPlayerData*)Row.Value;
        if (PlayerData && PlayerData->Nickname == Data.Nickname)
        {
            PlayerData->IsConnected = (Data.IsConnected);
            bFound = true;
            UE_LOG(LogTemp, Warning, TEXT(" found the playerData match "));

            if (EventManager)
            {
                UE_LOG(LogTemp, Warning, TEXT(" not null eventMananger "));

                EventManager->OnStatusChange.Broadcast(PlayerData);
                break;

            }
            else
            {
                UE_LOG(LogTemp, Warning, TEXT("null eventMananger "));


            }

        }

    }

    /* if (!bFound)
     {
         UE_LOG(LogTemp, Warning, TEXT("Player with nickname %s not found in data table"), Data);
     }*/
}


