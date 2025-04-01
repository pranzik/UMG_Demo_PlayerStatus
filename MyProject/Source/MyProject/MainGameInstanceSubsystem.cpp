// Fill out your copyright notice in the Description page of Project Settings.

#include "MainGameInstanceSubsystem.h"
#include "DataParser.h"

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
		ConvertFromLatex();
		InitializeModel();

	}
}

void UMainGameInstanceSubsystem::ConvertFromLatex()
{

	FString LatexData = TEXT("\\begin{tabular}{|c|c|c|}\n\\hline\nNickname & Level & IsConnected \\\n\\hline\nPlayerOne & 5 & true \\\nPlayerTwo & 10 & false \\\n\\hline\n\\end{tabular}");

		UDataParser* Parser = NewObject<UDataParser>(this); // 'this' is the Outer object (e.g., GameMode)
		if (Parser)
		{
			Parser->ParseLatexAndPopulateDataTable(LatexData, DataTable);
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



