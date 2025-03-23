// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Building_Interface.h"
#include "DT_BuildingComponent.h"
#include "Build_Wall.generated.h"

UCLASS()
class SUBNAUTICA_VR_API ABuild_Wall : public AActor, public IBuilding_Interface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABuild_Wall();

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	class UBoxComponent* BoxComp1;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	class UBoxComponent* BoxComp2;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	class UBoxComponent* BoxComp3;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	class UBoxComponent* BoxComp4;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	TArray<UBoxComponent*> BoxCompArray;

	virtual TArray<UBoxComponent*> GetBoxCollision_Implementation() override;
};
