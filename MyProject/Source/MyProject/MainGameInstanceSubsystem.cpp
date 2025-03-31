// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameInstanceSubsystem.h"

void UMainGameInstanceSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	UE_LOG(LogTemp, Warning, TEXT("Initialize the subsystem"));
	if (DataTable == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("DataTable is null"));
	}
	else 
	{
		UE_LOG(LogTemp, Warning, TEXT("DataTable is not null"));
		InitializeModel();

	}
}

void UMainGameInstanceSubsystem::Deinitialize()
{
	Super::Deinitialize();
}
void UMainGameInstanceSubsystem::InitializeModel()
{
	if (!EventManager)
	{
		EventManager = NewObject<UGameEventManager>(this, UGameEventManager::StaticClass());
	}
	PlayerDataModel = NewObject<UPlayerDataModel>(this, UPlayerDataModel::StaticClass());

	if (PlayerDataModel)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerDataModel is not null in subsystem"));
	}
	PlayerDataModel->Initialize(DataTable, EventManager);
	EventManager->ActivateViewModels.Broadcast(EventManager);

}

bool UMainGameInstanceSubsystem::ShouldCreateSubsystem(UObject* Outer)const 
{
	if (this->GetClass()->IsInBlueprint() && Super::ShouldCreateSubsystem(Outer))
	{
		return true;
	}
	return false;
}



