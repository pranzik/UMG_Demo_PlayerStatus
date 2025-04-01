#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h" // Base class for UObject
#include "Engine/DataTable.h"
#include "PlayerData.h" // Include your struct header
#include "DataParser.generated.h"

UCLASS(BlueprintType)
class MYPROJECT_API UDataParser : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable)
    void ParseLatexAndPopulateDataTable(const FString& LatexString, UDataTable* DataTable);
};