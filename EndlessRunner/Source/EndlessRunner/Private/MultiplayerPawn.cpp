// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiplayerPawn.h"

#include "EndlessRunnerGameModeBase.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMultiplayerPawn::AMultiplayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = root;
	root->SetMobility(EComponentMobility::Movable);

	Player1Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Player1 Capsule Collider"));
	Player1Capsule->SetupAttachment(root);

	Player1Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Player1 Mesh"));
	Player1Mesh->SetupAttachment(Player1Capsule);

	Player2Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Player2 Capsule Collider"));
	Player2Capsule->SetupAttachment(root);

	Player2Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Player2 Mesh"));
	Player2Mesh->SetupAttachment(Player2Capsule);
}

// Called when the game starts or when spawned
void AMultiplayerPawn::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = Cast<APlayerController>(GetController());
	if(!PlayerController)
		return;
	if(UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem< UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer())) {
		Subsystem->AddMappingContext(MultiPlayerMappingContext, 0);	
	}

	Player1JumpVector = FVector(0.0f, 0.0f, Player1JumpHeight);
	Player2JumpVector = FVector(0.0f, 0.0f, Player2JumpHeight);

	CurrentHealth = StartingHealth;
}

// Called every frame
void AMultiplayerPawn::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AMultiplayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if(UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		EnhancedInputComponent->BindAction(Player1JumpAction, ETriggerEvent::Triggered, this, &AMultiplayerPawn::Player1Jump);
		EnhancedInputComponent->BindAction(Player2JumpAction, ETriggerEvent::Triggered, this, &AMultiplayerPawn::Player2Jump);
	}
}

void AMultiplayerPawn::Player1Jump(const FInputActionValue& Value) {
	if(GetController()) {
		Player1Capsule->AddForce(Player1JumpVector);
	}
}

void AMultiplayerPawn::Player2Jump(const FInputActionValue& Value) {
	if(GetController()) {
		Player2Capsule->AddForce(Player2JumpVector);
	}
}

void AMultiplayerPawn::TakeDamage(int32 amount) {
	CurrentHealth -= amount;
	UE_LOG(LogTemp, Warning, TEXT("PLAYERS Took Damage player"));
	if(CurrentHealth <= 0) {
		Death();
	}

}

void AMultiplayerPawn::Death() {
	UE_LOG(LogTemp, Warning, TEXT("PLAYERS DIED"));
	AEndlessRunnerGameModeBase* GameMode = Cast<AEndlessRunnerGameModeBase>( UGameplayStatics::GetGameMode(GetWorld()));
	GameMode->SaveScore();
	//FGenericPlatformMisc::RequestExit(false);
	Destroy();
}