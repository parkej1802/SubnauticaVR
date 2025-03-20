// Fill out your copyright notice in the Description page of Project Settings.


#include "AHS/BoidSpawner.h"

// Sets default values
ABoidSpawner::ABoidSpawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABoidSpawner::BeginPlay()
{
	Super::BeginPlay();

	for (int i = 0; i < SpawnCount; i++) {

		FVector SpawnPosition;

		if (EnableCenterSpawn){
			SpawnPosition = FVector(0, 0, 0);
		}
		else {
			SpawnPosition = GetRandomVector(-SpawnArea, SpawnArea);
		}

		FRotator SpawnRotation(0, FMath::RandRange(-180, 180), 0);

		ABoid* Boid = GetWorld()->SpawnActor<ABoid>(ActorToSpawn, SpawnPosition, SpawnRotation);
	}
	
}

// Called every frame
void ABoidSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FVector ABoidSpawner::GetRandomVector(double Min, double Max)
{
	FVector RandomVector(FMath::RandRange(Min, Max), FMath::RandRange(Min, Max), 0);

	return RandomVector;
}

