// Fill out your copyright notice in the Description page of Project Settings.


#include "RocketManager.h"
#include "Rocket.h"

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

}

// Called every frame
void ARocketManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SpawnTimer += DeltaTime;
	if (SpawnTimer >= SpawnInterval)
	{
		SpawnRockets();
		SpawnTimer = 0;
	}
}

void ARocketManager::SpawnRockets() {
	float SpawnZ = FMath::RandRange(SpawnMinZ, SpawnMaxZ);
	FVector SpawnVector = FVector(SpawnX, SpawnY, SpawnZ);
	FTransform SpawnTransform = FTransform(SpawnVector);
	//ARocket R = ARocket(SpawnDelay, SpeedFactor);
	ARocket* Rocket = GetWorld()->SpawnActor<ARocket>(RocketClass, SpawnTransform);
	Rocket->Initialize(SpawnDelay, SpeedFactor);
}