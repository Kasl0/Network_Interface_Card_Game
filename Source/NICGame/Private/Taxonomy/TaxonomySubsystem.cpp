// Fill out your copyright notice in the Description page of Project Settings.


#include "Taxonomy/TaxonomySubsystem.h"


void UTaxonomySubsystem::ChangeXAxisValue(int32 Change)
{
	this->PlayersVsWorldAxis += Change;
}

void UTaxonomySubsystem::ChangeYAxisValue(int32 Change)
{
	this->ActingAxis += Change;
}

void UTaxonomySubsystem::SetXAxisValue(int32 Change)
{
	this->PlayersVsWorldAxis = Change;
}

void UTaxonomySubsystem::SetYAxisValue(int32 Change)
{
	this->ActingAxis = Change;
}

void UTaxonomySubsystem::QuestionAnswered(bool Correct)
{
	this->TotalAnswers += 1;
	this->CorrectAnswers += Correct ? 1 : 0;
}

void UTaxonomySubsystem::SetFrameMinigameStatus(FString status)
{
    if (status == "found" && FrameMinigameStatus < 1)
    {
        this->FrameMinigameStatus = std::max(this->FrameMinigameStatus, 1);
        this->PlayersVsWorldAxis += 2;
        this->ActingAxis -= 1; // If found but not completed, the player is an explorer
    }
    else if (status == "completed" && FrameMinigameStatus < 2)
    {
        this->FrameMinigameStatus = 2;
        this->ActingAxis += 3;
    }
}

void UTaxonomySubsystem::SetCableMinigameStatus(FString status)
{
    if (status == "found" && CableMinigameStatus < 1)
    {
        this->CableMinigameStatus = std::max(this->CableMinigameStatus, 1);
        this->PlayersVsWorldAxis += 2;
        this->ActingAxis -= 1; // If found but not completed, the player is an explorer
    }
    else if (status == "completed" && CableMinigameStatus < 2)
    {
        this->CableMinigameStatus = 2;
        this->ActingAxis += 3;
    }
}

void UTaxonomySubsystem::GenerateReport()
{
	FString FilePath = FPaths::Combine(FPlatformProcess::UserDir(), "NICGame/raport.txt");  //Save report in [User]/Documents/NICGame
    FPlatformFileManager::Get().GetPlatformFile().CreateDirectoryTree(*FPaths::GetPath(FilePath));  // Ensure the directory exists

    FString FileContent;

    if (PlayersVsWorldAxis > 0)
    {
        if (ActingAxis > 0)
        {
            FileContent = FString::Printf(
                TEXT("Wyznaczony typ osobowości: Zdobywca\n")
            );
        }
        else
        {
            FileContent = FString::Printf(
                TEXT("Wyznaczony typ osobowości: Odkrywca\n")
            );
        }
    } 
    else
    {
        if (ActingAxis > 0)
        {
            FileContent = FString::Printf(
                TEXT("Wyznaczony typ osobowości: Zabójca\n")
            );
        }
        else
        {
            FileContent = FString::Printf(
                TEXT("Wyznaczony typ osobowości: Społecznik\n")
            );
        }
    }

    FileContent += FString::Printf(
        TEXT("Położenie na układzie współrzędnych osobowości: (%d, %d)\n"),
        PlayersVsWorldAxis, ActingAxis
    );

    FileContent += FString::Printf(
        TEXT("Poprawne odpowiedzi w quizach: %d/%d\n"),
        CorrectAnswers, TotalAnswers
    );

    FileContent += FString::Printf(
        TEXT("Status minigry z ramką: %s\nStatus minigry z topologią sieci: %s\n"),
        FrameMinigameStatus == 0 ? TEXT("nieznaleziona") : (FrameMinigameStatus == 1 ? TEXT("znaleziona") : TEXT("ukończona")),
        CableMinigameStatus == 0 ? TEXT("nieznaleziona") : (CableMinigameStatus == 1 ? TEXT("znaleziona") : TEXT("ukończona"))
    );

    // Save the file
    bool bSuccess = FFileHelper::SaveStringToFile(
        FileContent,
        *FilePath,
        FFileHelper::EEncodingOptions::AutoDetect,
        &IFileManager::Get(),
        FILEWRITE_None
    );

    if (bSuccess)
    {
        UE_LOG(LogTemp, Log, TEXT("Successfully saved report to file: %s"), *FilePath);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to save report to file: %s"), *FilePath);
    }
}
