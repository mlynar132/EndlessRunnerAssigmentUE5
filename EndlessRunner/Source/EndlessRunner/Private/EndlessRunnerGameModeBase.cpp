// Copyright Epic Games, Inc. All Rights Reserved.


#include "EndlessRunnerGameModeBase.h"

#include "MySaveGame.h"
#include "GenericPlatform/GenericPlatformMath.h"
#include "Kismet/GameplayStatics.h"
#include  "Algo/Reverse.h"

AEndlessRunnerGameModeBase::AEndlessRunnerGameModeBase()
{
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bCanEverTick = true;
}

void AEndlessRunnerGameModeBase::StartPlay()
{
	//do stuf here
	UE_LOG(LogTemp, Warning, TEXT("Start "));
	/*FString out;
	ULocalPlayer* p1 = GetGameInstance()->CreateLocalPlayer(0, out, true);
	FString out2;
	ULocalPlayer* p2 = GetGameInstance()->CreateLocalPlayer(3, out2, true);

	int32 id1;
	int32 id2;
	if(p1) {
		UE_LOG(LogTemp, Warning, TEXT("p1"));
		id1 = p1->GetControllerId();
	}
	if(p2) {
		UE_LOG(LogTemp, Warning, TEXT("p2"));
		id2 = p2->GetControllerId();
	}

	UE_LOG(LogTemp, Warning, TEXT("p1%d"), id1);
	UE_LOG(LogTemp, Warning, TEXT("p2%d"), id2);*/
	Super::StartPlay();

	UMySaveGame* SaveGameInstance = Cast<UMySaveGame>(
		UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));
	SaveGameInstance = Cast<UMySaveGame>(UGameplayStatics::LoadGameFromSlot("MySlot", 0));
	HighScores = SaveGameInstance->Scores;
	int one = 0;
	int two = 0;
	int three = 0;
	if (HighScores.Num() >= 1)
	{
		one = HighScores[0];
	}
	if (HighScores.Num() >= 2)
	{
		two = HighScores[1];
	}
	if (HighScores.Num() >= 3)
	{
		three = HighScores[2];
	}
	GEngine->AddOnScreenDebugMessage(-1, 6000.0f, FColor::Green,
	                                 FString::Printf(
		                                 TEXT("Total Scores:%d. Top3: %d, %d, %d"), HighScores.Num(), one, two, three));
}

void AEndlessRunnerGameModeBase::SaveScore()
{
	UMySaveGame* SaveGameInstance = Cast<UMySaveGame>(
		UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));
	SaveGameInstance->Scores.Append(HighScores);
	SaveGameInstance->Scores.Add(GameScore);
	SaveGameInstance->Scores.Sort();
	Algo::Reverse(SaveGameInstance->Scores);
	UGameplayStatics::SaveGameToSlot(SaveGameInstance, TEXT("MySlot"), 0);
}

void AEndlessRunnerGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bGamePaused)
	{
		UWorld* World = GetWorld();
		if (World == nullptr)
		{
			return;
		}
		APlayerController* PlayerController = World->GetFirstPlayerController();
		if (PlayerController == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("DSADASDDD"));
			return;
		}
		GameTime += DeltaTime;
		GameScore += DeltaTime;
		if (GEngine)
		{
			int32 score = FGenericPlatformMath::FloorToInt(GameScore);
			GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Red, FString::Printf(TEXT("SCORE:%d"), score));
		}
	}
}

float AEndlessRunnerGameModeBase::GetGameTime()
{
	return GameTime;
}

bool AEndlessRunnerGameModeBase::GetbGamePaused()
{
	return bGamePaused;
}

void AEndlessRunnerGameModeBase::SetbGamePaused(bool state)
{
	bGamePaused = state;
}

void AEndlessRunnerGameModeBase::DisplayHighScores()
{
	for (int i = 0; i < NumberOfHighScoresToDisplay; i++)
	{
		if (GEngine)
		{
			int32 score = HighScores[i];
			GEngine->AddOnScreenDebugMessage(-1 - i, 0.0f, FColor::Red, FString::Printf(TEXT("SCORE:%d"), score));
		}
	}
}
