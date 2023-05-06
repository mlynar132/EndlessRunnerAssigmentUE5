// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/PlayerController.h"

// Sets default values
AMyPawn::AMyPawn() {
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = Capsule;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Capsule);
}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay() {
	Super::BeginPlay();
	PlayerController = Cast<APlayerController>(GetController());

	if(!PlayerController)
		return;

	if(UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer())) {
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
	JumpVector = FVector(0.0f, 0.0f, JumpHeight);

	CurrentHealth = StartingHealth;
}

// Called every frame
void AMyPawn::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if(UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AMyPawn::Jump);
	}
}

void AMyPawn::Jump(const FInputActionValue& Value) {
	if(GetController()) {
		Capsule->AddForce(JumpVector);
	}
}

void AMyPawn::TakeDamage(int32 amount) {
	CurrentHealth -= amount;
	UE_LOG(LogTemp, Warning, TEXT("PLAYER Took Damage player"));
	if(CurrentHealth <= 0) {
		Death();
	}

}

void AMyPawn::Death() {
	UE_LOG(LogTemp, Warning, TEXT("PLAYER DIED"));
	Destroy();
}