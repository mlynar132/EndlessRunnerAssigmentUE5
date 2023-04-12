// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelFragment.h"

// Sets default values
ALevelFragment::ALevelFragment() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	Ceiling = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ceiling"));
	Ceiling->SetupAttachment(Root);

	Background = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Background"));
	Background->SetupAttachment(Root);

	Roof = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Roof"));
	Roof->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void ALevelFragment::BeginPlay() {
	Super::BeginPlay();

}

// Called every frame
void ALevelFragment::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	SetActorLocation(GetActorLocation() + Speed * DeltaTime);	
}

void ALevelFragment::MoveBack() {

	SetActorLocation(GetActorLocation() + MoveBackLength);
}

void ALevelFragment::SetSpeed(float value) {
	Speed = FVector (value,0.0f,0.0f);
}

void ALevelFragment::SetMoveBackLength(float value) {
	MoveBackLength = FVector(value, 0.0f, 0.0f);
}