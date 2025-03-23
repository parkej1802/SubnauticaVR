// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Building_Interface.h"
#include "DT_BuildingComponent.h"
#include "Build_Door.generated.h"

UCLASS()
class SUBNAUTICA_VR_API ABuild_Door : public AActor, public IBuilding_Interface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABuild_Door();

};
