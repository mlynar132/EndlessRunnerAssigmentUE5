// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CleanableInterface.h"
#include "Rocket.generated.h"

class UCapsuleComponent;
class UStaticMeshComponent;

UCLASS()
class ENDLESSRUNNER_API ARocket : public AActor, public ICleanableInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARocket();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Initialize(float Delay, float SpeedFactorArg);

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void Move(float DeltaTime);

	void HideIndicator();

	virtual void ICleanableInterface::Clean() override; //not sure about the ICleanableInterface::

	//virtual void UCleanableInterface::Clean() override;

private:
	UPROPERTY(EditAnywhere)
	int32 Damage;

	float SpawnDelay;

	float IndicatorLifetime = 0;

	UPROPERTY(EditAnywhere)
	float SpeedBase;

	float SpeedFactor;

	float SpeedTotal;

	bool bMoving = false;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* IndicatorMesh;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* RocketMesh;

	UPROPERTY(EditAnywhere)
	UCapsuleComponent* TriggerCapsule;

};