// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Building_Interface.generated.h"

UINTERFACE(Blueprintable)
class UBuilding_Interface : public UInterface
{
    GENERATED_BODY()
};

class IBuilding_Interface
{
    GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Build")
	TArray<UBoxComponent*> GetBoxCollision();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Build")
	void SetMesh(UStaticMesh* Mesh);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Build")
	void InteractWithBuild();
};