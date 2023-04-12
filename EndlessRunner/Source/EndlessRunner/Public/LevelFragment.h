// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelFragment.generated.h"

UCLASS()
class ENDLESSRUNNER_API ALevelFragment : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ALevelFragment();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void MoveBack();

	void SetSpeed(float value);

	void SetMoveBackLength( float value);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Ceiling;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Background;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Roof;

	FVector Speed;

	FVector MoveBackLength;

};
