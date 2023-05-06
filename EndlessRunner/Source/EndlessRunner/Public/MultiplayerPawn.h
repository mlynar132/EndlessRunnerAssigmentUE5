// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputActionValue.h"
#include "DamageableInterface.h"
#include "MultiplayerPawn.generated.h"

class UCapsuleComponent;
class UStaticMeshComponent;
class UInputMappingContext;
class UInputAction;

UCLASS()
class ENDLESSRUNNER_API AMultiplayerPawn : public APawn, public IDamageableInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMultiplayerPawn();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void TakeDamage(int32 amount) override;

	virtual void Death() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* MultiPlayerMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* Player1JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* Player2JumpAction;

	virtual void Player1Jump(const FInputActionValue& Value);

	virtual void Player2Jump(const FInputActionValue& Value);

private:	
#pragma region Player1	
	UPROPERTY(VisibleAnywhere)
	UCapsuleComponent* Player1Capsule;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Player1Mesh;

	UPROPERTY(EditAnywhere)
	float Player1JumpHeight;

	FVector Player1JumpVector;

	UPROPERTY(EditAnywhere)
	bool Player1JumpBool;

#pragma endregion Player1	

#pragma region Player2	

	UPROPERTY(VisibleAnywhere)
	UCapsuleComponent* Player2Capsule;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Player2Mesh;

	UPROPERTY(EditAnywhere)
	float Player2JumpHeight;

	FVector Player2JumpVector;

	UPROPERTY(EditAnywhere)
	bool Player2JumpBool;

#pragma endregion Player2

#pragma region Shared

	UPROPERTY(EditAnywhere)
	int32 StartingHealth;

	UPROPERTY(EditAnywhere)
	int32 CurrentHealth;

	APlayerController* PlayerController;

#pragma endregion Shared
};