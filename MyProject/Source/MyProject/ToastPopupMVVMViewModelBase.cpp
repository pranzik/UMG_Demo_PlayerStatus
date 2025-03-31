// Fill out your copyright notice in the Description page of Project Settings.


#include "ToastPopupMVVMViewModelBase.h"
#include "GameEventManager.h"
#include "Kismet/GameplayStatics.h"

 UToastPopupMVVMViewModelBase::UToastPopupMVVMViewModelBase()
{
	 UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(GetWorld());
	 if (GameInstance) {
		 UMainGameInstanceSubsystem* GameInstanceSubsystem = GameInstance->GetSubsystem<UMainGameInstanceSubsystem>();

		 if (GameInstanceSubsystem)
		 {
			 UGameEventManager* EventManager = GameInstanceSubsystem->EventManager;
			 if (EventManager)
			 {
				 EventManager->ActivateToast.AddUObject(this, &UToastPopupMVVMViewModelBase::RecieveStruct);
			 }
			 else
			 {
				 UE_LOG(LogTemp, Error, TEXT("EventManager is null in GameInstanceSubsystem."));
			 }
		 }
		 else
		 {
			 UE_LOG(LogTemp, Error, TEXT("GameInstanceSubsystem is null in GameInstance."));
		 }
	 }
	 else
	 {
		 UE_LOG(LogTemp, Error, TEXT("Gameinstance is null"));

	 }
 }



 void UToastPopupMVVMViewModelBase::SetPlayerName(const FText& playerName)
 {
	 if (UE_MVVM_SET_PROPERTY_VALUE(PlayerName, playerName))
	 {
		 UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetPlayerName);
		
		 TriggerNotification.Broadcast();
	 }
 }

 void UToastPopupMVVMViewModelBase::RecieveStruct(FPlayerData* structData)
 {


	 FText playerStatus = structData->IsConnected ? FText::FromString(TEXT("Connected")) : FText::FromString(TEXT("Disconnected"));
	 FText name = FText::FromString(structData->Nickname);

	 FText message = FText::Format(
		 NSLOCTEXT("YourNamespace", "PlayerStatusMessage", "{0} has {1}"),
		 name,
		 playerStatus
	 );
	 SetPlayerName(message);
 }



