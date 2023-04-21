// Fill out your copyright notice in the Description page of Project Settings.


#include "ScrollingActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "LevelFragment.h"

// Sets default values
AScrollingActor::AScrollingActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;


}

// Called when the game starts or when spawned
void AScrollingActor::BeginPlay()
{
	Super::BeginPlay();

	FragmentJump = FragmentNumber * FragmentLength;

	for (int i = 0; i < FragmentNumber; i++)
	{
		FTransform SpawnTransform = GetActorTransform();
		SpawnTransform.SetLocation(SpawnTransform.GetLocation() + FVector(FragmentLength * i,0.0f,0.0f));
		ALevelFragment* Fragment = GetWorld()->SpawnActor<ALevelFragment>(FragmentClass, SpawnTransform);
		//do some stuff to the fragment
		Fragment->SetSpeed(FragmentSpeed);
		Fragment->SetMoveBackLength(FragmentJump);
	}
}

// Called every frame
void AScrollingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}