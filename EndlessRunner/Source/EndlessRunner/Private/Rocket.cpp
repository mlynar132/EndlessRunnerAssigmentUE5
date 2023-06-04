// Fill out your copyright notice in the Description page of Project Settings.


#include "Rocket.h"
#include "Components/CapsuleComponent.h"
#include "DamageableInterface.h"
#include "RocketManager.h"

ARocket::ARocket() {
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = root;
	root->SetMobility(EComponentMobility::Movable);

	IndicatorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Indicator Mesh"));
	IndicatorMesh->SetupAttachment(root);

	TriggerCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Trigger Capsule"));
	TriggerCapsule->SetupAttachment(root);

	RocketMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Rocket Mesh"));
	RocketMesh->SetupAttachment(TriggerCapsule);

	TriggerCapsule->SetGenerateOverlapEvents(true);
	TriggerCapsule->OnComponentBeginOverlap.AddDynamic(this, &ARocket::OnOverlapBegin);

}

void ARocket::BeginPlay() {

	Super::BeginPlay();

}

void ARocket::Initialize(float Delay, float SpeedFactorArg, ARocketManager* rocketManager) {
	
	SpawnDelay = Delay;
	SpeedFactor = SpeedFactorArg;
	RocketManager = rocketManager;
	RocketManager->AddRocketToSet(this);
}

void ARocket::Tick(float DeltaTime) {

	Super::Tick(DeltaTime);
	IndicatorLifetime += DeltaTime;
	if (bMoving)
	{
		Move(DeltaTime);
		return;
	}

	IndicatorLifetime += DeltaTime;
	if (IndicatorLifetime >= SpawnDelay)
	{
		HideIndicator();
		bMoving = true;
	}
	
}

void ARocket::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IDamageableInterface* damageableInterface = Cast<IDamageableInterface>(OtherActor))
	{
		damageableInterface->TakeDamage(Damage);
		//explode
		//clean up
		RocketManager->RemoveRocketFromSet(this);
	}
	// do expolsion
}

void ARocket::Move(float DeltaTime) {
	SetActorLocation(GetActorLocation() + FVector(SpeedBase * SpeedFactor, 0.0f, 0.0f) * DeltaTime);
}

void ARocket::HideIndicator() {
	IndicatorMesh->SetHiddenInGame(true, true);
}

//ICleanableInterface::Clean() doesn't have access to Destroy();
void ARocket::Clean() {
	RocketManager->RemoveRocketFromSet(this);
	if(rand() % 100 < DisappearChance) {
		if(ARocket* randomRocket = RocketManager->GetRandomRocketFromSet()) {
			RocketManager->RemoveRocketFromSet(randomRocket);
		}

	}
	//temporary solution destroy improve to object pooling
}

void ARocket::Disable() {
	Destroy();
}