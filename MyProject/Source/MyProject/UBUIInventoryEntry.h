#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "UBUIInventoryItem.h"
#include "UBUIInventoryEntry.generated.h"

/**
 * @class UUBUIInventoryEntry
 * @brief Represents an entry in the player inventory list.
 *
 * This class displays player data in a list entry.
 */
UCLASS()
class MYPROJECT_API UUBUIInventoryEntry : public UUserWidget, public IUserObjectListEntry
{
    GENERATED_BODY()

public:
    /**
     * @brief Sets the player data for this entry.
     * @param NewData The player data.
     */
    void SetPlayerData(const FPlayerData& NewData);

protected:
    // IUserObjectListEntry
    virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;
    // IUserObjectListEntry

    UPROPERTY(meta = (BindWidget))
    class UTextBlock* NameLabel; ///< The label displaying the player's name.

    /**
     * @brief Called when player data is received.
     * @param NewData The player data.
     */
    UFUNCTION(BlueprintImplementableEvent, Category = "Data")
    void OnDataRecieved(const FPlayerData& NewData);
};