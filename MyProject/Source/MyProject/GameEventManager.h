// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "GameEventManager.generated.h"

// Forward declaration of FPlayerData
struct FPlayerData;

/**
 * @brief Delegate for broadcasting player data events.
 * @param ConnectedPlayers List of connected players.
 * @param DisconnectedPlayers List of disconnected players.
 */
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnPlayerDataEvent, TArray<FPlayerData>&, TArray<FPlayerData>&);

/**
 * @brief Delegate for broadcasting player status changes.
 * @param PlayerData The player data whose status changed.
 */
DECLARE_MULTICAST_DELEGATE_OneParam(FOnStatusChange, FPlayerData*);

/**
 * @brief Delegate for notifying when a UI widget is added.
 * @param Widget The UI widget that was added.
 */
DECLARE_MULTICAST_DELEGATE_OneParam(FUIWidgetAdded, class UPlayerUIWidget*);

/**
 * @brief Delegate for activating view models.
 * @param EventManager The event manager to use for activation.
 */
DECLARE_MULTICAST_DELEGATE_OneParam(FActivateViewModels, class UGameEventManager*);

/**
 * @brief Delegate for activating toast notifications.
 * @param PlayerData The player data to display in the toast.
 */
DECLARE_MULTICAST_DELEGATE_OneParam(FActivateToast, FPlayerData*);

/**
 * @class UGameEventManager
 * @brief Manages game events and delegates for player data, UI, and toast notifications.
 */
UCLASS()
class MYPROJECT_API UGameEventManager : public UObject
{
    GENERATED_BODY()

public:
    FOnPlayerDataEvent OnPlayerDataEvent; ///< Delegate for player data events.
    FOnStatusChange OnStatusChange; ///< Delegate for player status changes.
    FUIWidgetAdded UIWidgetAdded; ///< Delegate for UI widget additions.
    FActivateViewModels ActivateViewModels; ///< Delegate for activating view models.
    FActivateToast ActivateToast; ///< Delegate for activating toast notifications.
};