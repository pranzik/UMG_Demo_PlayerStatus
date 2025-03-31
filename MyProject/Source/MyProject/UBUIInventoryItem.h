#pragma once

#include "CoreMinimal.h"
#include "PlayerData.h" 
#include "UObject/NoExportTypes.h"
#include "UBUIInventoryItem.generated.h"

/**
 * @class UBUIInventoryItem
 * @brief Represents an inventory item for a player.
 *
 * This class stores player data and provides methods to access it.
 */
UCLASS(Blueprintable)
class MYPROJECT_API UBUIInventoryItem : public UObject
{
    GENERATED_BODY()

public:
    /**
     * @brief Gets the player data.
     * @return The player data.
     */
    UFUNCTION(BlueprintCallable)
    FPlayerData GetPlayerData() const;

    /**
     * @brief Sets the player data.
     * @param NewData The new player data.
     */
    void SetPlayerData(const FPlayerData& NewData);

private:
    FPlayerData playerData; ///< The player data.
};