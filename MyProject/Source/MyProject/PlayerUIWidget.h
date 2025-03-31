#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include <Components/ListView.h>
#include <Components/TextBlock.h>
#include "PlayerDataModel.h"
#include "UBUIInventoryEntry.h"
#include "UBUIInventoryItem.h"
#include "PlayerUIWidget.generated.h"

/**
 * @class UPlayerUIWidget
 * @brief The main UI widget for displaying player data.
 *
 * This widget displays connected and disconnected players and allows interaction with their data.
 */
UCLASS()
class MYPROJECT_API UPlayerUIWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    /**
     * @brief Updates the player lists in the UI.
     * @param ConnectedPlayers List of connected players.
     * @param DisconnectedPlayers List of disconnected players.
     */
    void UpdatePlayerLists(TArray<FPlayerData>& ConnectedPlayers, TArray<FPlayerData>& DisconnectedPlayers);

    /**
     * @brief Initializes the widget with the EventManager.
     * @param EventsManager The EventManager to handle game events.
     */
    void Init(UGameEventManager* EventsManager);

    /**
     * @brief Moves a player element between connected and disconnected lists.
     * @param PlayerData The player data to move.
     */
    void MoveElementBetweenScrollBoxes(FPlayerData* PlayerData);

    UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
    class UListView* ConnectedPlayersList; ///< List of connected players.

    UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
    class UListView* DisconnectedPlayersList; ///< List of disconnected players.

protected:
    virtual void NativeConstruct() override;

private:
    UFUNCTION()
    void OnClickExpandConnectedPlayers(); ///< Called when the connected players expand button is clicked.

    UFUNCTION()
    void OnClickExpandDisconnectedPlayers(); ///< Called when the disconnected players expand button is clicked.

    UPROPERTY()
    TArray<UBUIInventoryItem*> ConnectedInventory; ///< Inventory of connected players.

    UPROPERTY()
    TArray<UBUIInventoryItem*> DisconnectedInventory; ///< Inventory of disconnected players.

    UPROPERTY()
    UGameEventManager* EventManager; ///< Manages game events.

    UPROPERTY()
    TArray<FPlayerData> ConnectedPlayers; ///< List of connected players.

    UPROPERTY()
    TArray<FPlayerData> DisconnectedPlayers; ///< List of disconnected players.
};