// Fill out your copyright notice in the Description page of Project Settings.


#include "FragmentCleaner.h"
#include "Components/BoxComponent.h"
#include "LevelFragment.h"

// Sets default values
AFragmentCleaner::AFragmentCleaner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Box"));
	RootComponent = TriggerBox;

	TriggerBox->SetGenerateOverlapEvents(true);
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AFragmentCleaner::OnOverlapBegin);
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AFragmentCleaner::BOB);
}

void AFragmentCleaner::BOB(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("BOOOOOOOB"));

}


// Called when the game starts or when spawned
void AFragmentCleaner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFragmentCleaner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFragmentCleaner::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ALevelFragment* frag = Cast<ALevelFragment>(OtherActor))
	{
		frag->MoveBack();
	}
}

