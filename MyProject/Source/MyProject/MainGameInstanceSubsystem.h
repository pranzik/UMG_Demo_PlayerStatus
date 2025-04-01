// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GameEventManager.h"
#include "PlayerDataModel.h"
#include "MainGameInstanceSubsystem.generated.h"

/**
 * @class UMainGameInstanceSubsystem
 * @brief Manages the game instance subsystem, including event management and player data.
 */
UCLASS(Blueprintable)
class MYPROJECT_API UMainGameInstanceSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    /**
     * @brief Initializes the subsystem.
     * @param Collection The collection of subsystems.
     */
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;

    /**
     * @brief Deinitializes the subsystem.
     */
    virtual void Deinitialize() override;

    UPROPERTY()
    UGameEventManager* EventManager; ///< Manages game events.

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    UDataTable* DataTable; ///< The DataTable containing player data.

    UPROPERTY()
    UPlayerDataModel* PlayerDataModel; ///< Manages player data.

private:
    /**
     * @brief Initializes the player data model and event manager.
     */
    void InitializeModel();
    void ConvertFromLatex();
    /**
     * @brief Determines whether the subsystem should be created.
     * @param Outer The outer object.
     * @return True if the subsystem should be created, false otherwise.
     */
    bool ShouldCreateSubsystem(UObject* Outer) const;
};