// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "PlayerData.generated.h"

/**
 * @struct FPlayerData
 * @brief Represents player data stored in a DataTable.
 *
 * This struct is used to define player-related data, such as nickname, level, and connection status.
 */
USTRUCT(BlueprintType)
struct MYPROJECT_API FPlayerData : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Nickname; ///< The player's nickname.

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Level; ///< The player's level.

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool IsConnected; ///< Whether the player is connected.
};