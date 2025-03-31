// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "PlayerData.h"
#include "MainGameInstanceSubsystem.h"
#include "ToastPopupMVVMViewModelBase.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTriggerNotification);


/**
 * @class UToastPopupMVVMViewModelBase
 * @brief ViewModel for the toast popup UI.
 *
 * This class manages the data and events for the toast popup.
 */
UCLASS()
class MYPROJECT_API UToastPopupMVVMViewModelBase : public UMVVMViewModelBase
{
    GENERATED_BODY()

public:
    /**
     * @brief Constructor for the ViewModel.
     */
    UToastPopupMVVMViewModelBase();

    /**
     * @brief Gets the player name.
     * @return The player name as an FText.
     */
    UFUNCTION(BlueprintPure, FieldNotify)
    FText GetPlayerName() const { return PlayerName; }

    /**
     * @brief Sets the player name.
     * @param playerName The new player name to set.
     */
    UFUNCTION(BlueprintCallable)
    void SetPlayerName(const FText& playerName);

    /**
     * @brief Receives player data and updates the toast message.
     * @param structData The player data to process.
     */
    void RecieveStruct(FPlayerData* structData);

    UPROPERTY(BlueprintReadWrite, FieldNotify, Setter = "SetPlayerName", Getter = "GetPlayerName")
    FText PlayerName; ///< The player name to display in the toast.

    UPROPERTY(BlueprintAssignable, Category = "Notification")
    FTriggerNotification TriggerNotification; ///< Delegate to trigger notifications in the UI.
};
