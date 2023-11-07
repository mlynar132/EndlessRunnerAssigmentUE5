// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EndlessRunnerGameModeBase.generated.h"

/**
 *
 */
UCLASS()
class ENDLESSRUNNER_API AEndlessRunnerGameModeBase : public AGameModeBase {
	GENERATED_BODY()

public:
	AEndlessRunnerGameModeBase();

	virtual void Tick(float DeltaTime) override;
	//virtual ~AEndlessRunnerGameModeBase() = default;

	virtual void StartPlay() override;

	void SaveScore();
	
	float GetGameTime();

	bool GetbGamePaused();

	void SetbGamePaused(bool state);

	void DisplayHighScores();

private:
	float GameTime = 0;

	bool bGamePaused = 0;

	float GameScore = 0;

	TArray<float> HighScores;

	int8 NumberOfHighScoresToDisplay;
	
};