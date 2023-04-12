// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputActionValue.h"
#include "MyPawn.generated.h"

class UCapsuleComponent;
class UStaticMeshComponent;
class UInputMappingContext;
class UInputAction;
//class UActor;

UCLASS()
class ENDLESSRUNNER_API AMyPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyPawn();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* JumpAction;

	virtual void Jump(const FInputActionValue& Value);
private:
	UPROPERTY(VisibleAnywhere)
	UCapsuleComponent* Capsule;

	UPROPERTY(EditAnywhere, Category = "MyPawnCategory")
	UStaticMeshComponent* Mesh;

	//UPROPERTY(EditAnywhere, Category = "MyPawnCategory")
	//UActor* Camera;

	int counter = 0;

	UPROPERTY(EditAnywhere)
	float JumpHeight;

	FVector JumpVector;

	UPROPERTY(EditAnywhere, Category = "MyPawnCategory")
	bool JumpBool;

	UPROPERTY(EditAnywhere)
	AActor* CameraActor;

	APlayerController* PlayerController;


};
