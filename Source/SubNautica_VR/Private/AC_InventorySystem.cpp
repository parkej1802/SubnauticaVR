// Fill out your copyright notice in the Description page of Project Settings.


#include "AC_InventorySystem.h"

// Sets default values for this component's properties
UAC_InventorySystem::UAC_InventorySystem()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAC_InventorySystem::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UAC_InventorySystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

