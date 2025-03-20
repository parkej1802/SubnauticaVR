// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BoidManager.generated.h"

UCLASS()
class SUBNAUTICA_VR_API ABoidManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABoidManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

//-------------------------------------------------
public:
	UPROPERTY(EditAnywhere)
	float MinSpeed;

	UPROPERTY(EditAnywhere)
	float MaxSpeed;

	UPROPERTY(EditAnywhere)
	float LocalFlockRadius;

	UPROPERTY(EditAnywhere)
	float SeparationRadius;

	UPROPERTY(EditAnywhere)
	float SeparationStrength;

	UPROPERTY(EditAnywhere)
	float AlignmentRadius;

	UPROPERTY(EditAnywhere)
	float AlignmentStrength;

	UPROPERTY(EditAnywhere)
	float CohesionRadius;

	UPROPERTY(EditAnywhere)
	float CohesionStrength;

	UPROPERTY(EditAnywhere)
	float Boid_Boundary;

public:
	float GetMinSpeed();
	float GetMaxSpeed();
	float GetLocalFlockRadius();

	float GetSeparationRadius();
	float GetSeparationStrength();

	float GetAlignmentRadius();
	float GetAlignmentStrength();

	float GetCohesionRadius();
	float GetCohesionStrength();

	float GetBoidBoundary();
};
