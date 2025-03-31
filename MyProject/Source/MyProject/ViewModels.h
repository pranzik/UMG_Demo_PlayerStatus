#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PlayerUIWidget.h"
#include "GameEventManager.h"
#include "MainGameInstanceSubsystem.h"
#include "ViewModels.generated.h"

/**
 * @class UViewModels
 * @brief Manages the view models for the UI.
 *
 * This class handles the logic for updating player lists and moving elements between UI components.
 */
UCLASS()
class MYPROJECT_API UViewModels : public UObject
{
    GENERATED_BODY()

    /**
     * @brief Initializes the view model.
     */
    void Init();

    /**
     * @brief Updates the player lists in the UI.
     * @param ConnectedPlayer List of connected players.
     * @param DisconnectedPlayer List of disconnected players.
     */
    void UpdatePlayerLists(TArray<FPlayerData>& ConnectedPlayer, TArray<FPlayerData>& DisconnectedPlayer);

    /**
     * @brief Moves a player element between connected and disconnected lists.
     * @param PlayerData The player data to move.
     */
    void MoveElementBetweenScrollBoxes(FPlayerData* PlayerData);

    /**
     * @brief Activates the UI and initializes the player lists.
     */
    void ActivateUI();

    /**
     * @brief Retrieves the connected and disconnected player lists.
     */
    void GetConnectedDisconnectedList();

    /**
     * @brief Initializes the widget.
     */
    void InitializeWidget();

    UPlayerUIWidget* PlayerUIWidget; ///< The player UI widget.

    UPROPERTY()
    UGameEventManager* EventManager; ///< Manages game events.

    UMainGameInstanceSubsystem* GameInstanceSubsystem; ///< The game instance subsystem.

    UPlayerDataModel* PlayerDataModel; ///< The player data model.

public:
    /**
     * @brief Initializes the view model with the UI widget class, game instance, and data model.
     * @param UIWidgetClass The UI widget class.
     * @param Instance The game instance subsystem.
     * @param DataModel The player data model.
     */
    void Initialize(UPlayerUIWidget* UIWidgetClass, UMainGameInstanceSubsystem* Instance, UPlayerDataModel* DataModel);
};