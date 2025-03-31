#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MainGameInstanceSubsystem.h"
#include "PlayerUIWidget.h"
#include "ViewModels.h"
#include "MainHud.generated.h"

/**
 * @class AMainHud
 * @brief The main HUD class for the game.
 *
 * This class initializes the view models and manages the UI widgets.
 */
UCLASS()
class MYPROJECT_API AMainHud : public AHUD
{
    GENERATED_BODY()

    virtual void BeginPlay() override;

    /**
     * @brief Initializes the view models for the HUD.
     * @param GameInstanceSubsystem The game instance subsystem.
     * @param DataModel The player data model.
     */
    void InitializeViewModels(UMainGameInstanceSubsystem* GameInstanceSubsystem, UPlayerDataModel* DataModel);

private:
    UGameEventManager* GameEventManager; ///< Manages game events.
    UViewModels* ViewModel; ///< The view model for the HUD.

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
    UPlayerUIWidget* PlayerUIWidgetClass; ///< The player UI widget class.

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
    UUserWidget* ToastPopup; ///< The toast popup widget.
};