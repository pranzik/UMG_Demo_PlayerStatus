// Fill out your copyright notice in the Description page of Project Settings.


#include "MainHud.h"

void AMainHud::BeginPlay()
{

	UGameInstance* GameInstance =UGameplayStatics::GetGameInstance(GetWorld());
	UMainGameInstanceSubsystem* GameInstanceSubsystem = GameInstance->GetSubsystem<UMainGameInstanceSubsystem>();

	GameEventManager = GameInstanceSubsystem->EventManager;

	if (GameInstanceSubsystem)
	{
		UE_LOG(LogTemp, Warning, TEXT("GameInstance is not null "));

	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("GameInstance is  null "));
	}
	InitializeViewModels(GameInstanceSubsystem, GameInstanceSubsystem->PlayerDataModel);
}
void AMainHud::InitializeViewModels(UMainGameInstanceSubsystem* GameInstanceSubsystem, UPlayerDataModel* DataModel)
{
	UE_LOG(LogTemp, Warning, TEXT("MyHud call received"));

	ViewModel = NewObject<UViewModels>(this, UViewModels::StaticClass());

	if (ViewModel)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerDataModel is not null.4"));
		ViewModel->Initialize(PlayerUIWidgetClass, GameInstanceSubsystem, DataModel);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to create ViewModel"));
	}
	
}


