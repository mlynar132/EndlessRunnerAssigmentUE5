// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RocketManager.generated.h"

class AEndlessRunnerGameModeBase;

UCLASS()
class ENDLESSRUNNER_API ARocketManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARocketManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SpawnRockets();

private:
	UPROPERTY(EditAnywhere)
	float SpawnInterval;

	UPROPERTY(EditAnywhere)
	float SpawnDelay;

	UPROPERTY(EditAnywhere)
	float SpawnAmount;

	UPROPERTY(EditAnywhere)
	float SpeedFactor;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class ARocket> RocketClass;

	UPROPERTY(EditAnywhere)
	float SpawnMinZ;

	UPROPERTY(EditAnywhere)
	float SpawnMaxZ;

	UPROPERTY(EditAnywhere)
	float SpawnX;

	UPROPERTY(EditAnywhere)
	float SpawnY;

	float SpawnTimer = 0;

	float CalculateSpawnInterval(float gameTime);

	float CalculateSpawnDelay(float gameTime);

	float CalculateSpeedFactor(float gameTime);

	AEndlessRunnerGameModeBase* GameMode;
};
