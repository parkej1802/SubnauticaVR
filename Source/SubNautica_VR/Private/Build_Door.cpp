// Fill out your copyright notice in the Description page of Project Settings.


#include "Build_Door.h"

// Sets default values
ABuild_Door::ABuild_Door()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABuild_Door::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABuild_Door::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

