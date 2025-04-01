#include "DataParser.h"

void UDataParser::ParseLatexAndPopulateDataTable(const FString& LatexString, UDataTable* DataTable)
{
    if (!DataTable) return;

    // Split the string into lines
    TArray<FString> Lines;
    LatexString.ParseIntoArrayLines(Lines);

    // Process each line
    for (const FString& Line : Lines)
    {
        // Skip header or non-data lines
        if (Line.Contains("begin") || Line.Contains("end") || Line.Contains("hline") || Line.Contains("Nickname"))
            continue;

        // Split by "&" to get columns, then trim whitespace and remove "|"
        TArray<FString> Columns;
        Line.ParseIntoArray(Columns, TEXT("&"));
        if (Columns.Num() == 3) // Ensure we have Nickname, Level, IsConnected
        {
            FPlayerData NewRow;
            NewRow.Nickname = Columns[0].TrimStartAndEnd().Replace(TEXT("|"), TEXT(""));
            NewRow.Level = FCString::Atoi(*Columns[1].TrimStartAndEnd());
            NewRow.IsConnected = Columns[2].TrimStartAndEnd().Replace(TEXT("|"), TEXT("")) == "true";

            // Add to Data Table using Nickname as the RowName
            FName RowName = FName(*NewRow.Nickname);
            DataTable->AddRow(RowName, NewRow);
        }
    }
}