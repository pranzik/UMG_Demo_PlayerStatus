#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PlayerData.h"
#include "Engine/AssetManager.h"
#include <Kismet/GameplayStatics.h>
#include "GameEventManager.h"
#include "PlayerDataModel.generated.h"

/**
 * @class UPlayerDataModel
 * @brief Manages player data and connection status using a DataTable.
 * 
 * This class handles player data, including connection status, and provides methods to interact with the data.
 */
UCLASS()
class MYPROJECT_API UPlayerDataModel : public UObject
{
    GENERATED_BODY()

public:
    UPlayerDataModel();

    /**
     * @brief Initializes the PlayerDataModel with a DataTable and EventManager.
     * @param DataTable The DataTable containing player data.
     * @param EventsManager The EventManager to handle game events.
     */
    void Initialize(UDataTable* DataTable, UGameEventManager* EventsManager);

    /**
     * @brief Updates the connection status of a player.
     * @param Data The player data to update.
     */
    void UpdatePlayerConnectionStatus(const FPlayerData& Data);

    /**
     * @brief Retrieves all players from the DataTable and categorizes them as connected or disconnected.
     */
    void GetAllPlayers();

    /**
     * @brief Retrieves an object reference by its asset path.
     * @param AssetPath The path to the asset.
     */
   // void GetObjectReferenceByPath(const FString& AssetPath);

    /**
     * @brief Gets the connection status of a player by their nickname.
     * @param Nickname The nickname of the player.
     * @return True if the player is connected, false otherwise.
     */
    bool GetPlayerConnectionStatus(const FString& Nickname) const;

    /**
     * @brief Retrieves a random player from the connected or disconnected list.
     * @return A random player's data.
     */
    FPlayerData GetRandomPlayer();

    /**
     * @brief Called when a timer expires to update player status.
     */
    void OnTimerExpire();

    UPROPERTY()
    UGameEventManager* EventManager; ///< Manages game events.

    UDataTable* PlayerDataTable; ///< The DataTable containing player data.

private:
    UPROPERTY()
    TArray<FPlayerData> ConnectedPlayers; ///< List of connected players.

    UPROPERTY()
    TArray<FPlayerData> DisconnectedPlayers; ///< List of disconnected players.

    FTimerHandle TimerHandle; ///< Timer handle for periodic updates.
};