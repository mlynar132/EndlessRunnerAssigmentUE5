// Copyright Epic Games, Inc. All Rights Reserved.


#include "EndlessRunnerGameModeBase.h"
#include "GenericPlatform/GenericPlatformMath.h"

AEndlessRunnerGameModeBase::AEndlessRunnerGameModeBase() {
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bCanEverTick = true;
}

void AEndlessRunnerGameModeBase::StartPlay() {
	//do stuf here
	UE_LOG(LogTemp, Warning, TEXT("Start "));

	Super::StartPlay();
}

void AEndlessRunnerGameModeBase::Tick(float DeltaTime) {

	Super::Tick(DeltaTime);

	if(!bGamePaused) {
		GameTime += DeltaTime;
		GameScore += DeltaTime;
		if(GEngine) {
			int32 score = FGenericPlatformMath::FloorToInt(GameScore);
			GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Red, FString::Printf(TEXT("SCORE:%d"),score));
		}
	}
}

float AEndlessRunnerGameModeBase::GetGameTime() {
	return GameTime;
}

bool AEndlessRunnerGameModeBase::GetIsGamePaused() {
	return bGamePaused;
}

void AEndlessRunnerGameModeBase::SetIsGamePaused(bool state) {
	bGamePaused = state;
}