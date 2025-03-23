// Fill out your copyright notice in the Description page of Project Settings.


#include "Build_WallDoor.h"

// Sets default values
ABuild_WallDoor::ABuild_WallDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABuild_WallDoor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABuild_WallDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

