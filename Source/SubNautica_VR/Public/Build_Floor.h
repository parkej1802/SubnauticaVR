// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Building_Interface.h"
#include "DT_BuildingComponent.h"
#include "Build_Floor.generated.h"

UCLASS()
class SUBNAUTICA_VR_API ABuild_Floor : public AActor, public IBuilding_Interface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABuild_Floor();
	
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	class UBoxComponent* BoxComp1;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	class UBoxComponent* BoxComp2;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	class UBoxComponent* BoxComp3;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	class UBoxComponent* BoxComp4;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* Wall1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* Wall2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* Wall3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* Wall4;

	TArray<UBoxComponent*> BoxCompArray;

	virtual TArray<UBoxComponent*> GetBoxCollision_Implementation() override;
};
