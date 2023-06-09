// Fill out your copyright notice in the Description page of Project Settings.


#include "RocketManager.h"
#include "Rocket.h"
#include "EndlessRunnerGameModeBase.h"
#include "GenericPlatform/GenericPlatformMath.h"

// Sets default values
ARocketManager::ARocketManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

}

// Called when the game starts or when spawned
void ARocketManager::BeginPlay()
{
	Super::BeginPlay();

	GameMode = GetWorld()->GetAuthGameMode<AEndlessRunnerGameModeBase>();
}

// Called every frame
void ARocketManager::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	SpawnTimer += DeltaTime;
	if (SpawnTimer >= CalculateSpawnInterval(GameMode->GetGameTime())) {
		SpawnRockets();
		SpawnTimer = 0;
	}
}

void ARocketManager::SpawnRockets() {
	float SpawnZ = FMath::RandRange(SpawnMinZ, SpawnMaxZ);
	FVector SpawnVector = FVector(SpawnX, SpawnY, SpawnZ);
	FTransform SpawnTransform = FTransform(SpawnVector);
	ARocket* Rocket = GetWorld()->SpawnActor<ARocket>(RocketClass, SpawnTransform);
	Rocket->Initialize(SpawnDelay, CalculateSpeedFactor(GameMode->GetGameTime()), this);
}

float ARocketManager::CalculateSpawnInterval(float gameTime) {
	return FGenericPlatformMath::Pow(0.995, gameTime);
}

float ARocketManager::CalculateSpawnDelay(float gameTime) {
	return 1; //dummy function for now it's not being used beacue i like Spawn Delay of 1 but it might change and i want to have this function already created.
}

float ARocketManager::CalculateSpeedFactor(float gameTime) {
	return 2 * FGenericPlatformMath::LogX(3, gameTime + 15);
}

void ARocketManager::AddRocketToSet(ARocket* rocket) {
	Rockets.Add(rocket);
}

void ARocketManager::RemoveRocketFromSet(ARocket* rocket) {
	Rockets.Remove(rocket);
	rocket->Disable();
}

ARocket* ARocketManager::GetRandomRocketFromSet() {
	int32 length = Rockets.Num();
	
	if(length==0)
		return nullptr;

	int32 i = 0;
	int32 x = rand() % length;
	for(auto& Elem : Rockets) {
		if(x == i) {
			return Elem;
		}
		i++;
	}

	return nullptr;
}