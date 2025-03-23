// Fill out your copyright notice in the Description page of Project Settings.


#include "Build_Floor.h"

// Sets default values
ABuild_Floor::ABuild_Floor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABuild_Floor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABuild_Floor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

