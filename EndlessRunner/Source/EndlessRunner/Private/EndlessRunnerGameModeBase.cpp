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
}

void AEndlessRunnerGameModeBase::Tick(float DeltaTime) {

	Super::Tick(DeltaTime);

	if(!bGamePaused) {
		GameTime += DeltaTime;
		GameScore += DeltaTime;
		if(GEngine) {
			int32 score = FGenericPlatformMath::FloorToInt(GameScore);
			GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Red, FString::Printf(TEXT("SCORE:%d"), score));
		}
	}
}

float AEndlessRunnerGameModeBase::GetGameTime() {
	return GameTime;
}

bool AEndlessRunnerGameModeBase::GetbGamePaused() {
	return bGamePaused;
}

void AEndlessRunnerGameModeBase::SetbGamePaused(bool state) {
	bGamePaused = state;
}