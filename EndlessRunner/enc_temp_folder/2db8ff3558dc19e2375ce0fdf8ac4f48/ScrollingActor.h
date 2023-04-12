// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ScrollingActor.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
class UMaterial;

UCLASS()
class ENDLESSRUNNER_API AScrollingActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AScrollingActor();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:	

	UPROPERTY(EditAnywhere, Category = "MyPawnCategory")
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
	float FragmentSpeed;

	UPROPERTY(EditAnywhere)
	float FragmentNumber;

	UPROPERTY(EditAnywhere)
	float FragmentLength;

	float FragmentJump;

	UPROPERTY(EditAnywhere)
	TArray<AActor*> ZoneFragments;

	UPROPERTY(EditAnywhere)
	TArray<float> ZoneStart;



	UPROPERTY(EditAnywhere)
	TSubclassOf<class ALevelFragment> FragmentClass;
};
