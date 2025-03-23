// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DirectionalLight.h"
#include "DayAndNightSystem.generated.h"

UCLASS()
class SUBNAUTICA_VR_API ADayAndNightSystem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADayAndNightSystem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
    UPROPERTY(EditAnywhere, Category = "Day Night Cycle")
    float DaySpeed = 0.5f; 

    UPROPERTY(EditAnywhere, Category = "Day Night Cycle")
    float NightSpeed = 1.0f; 

    UPROPERTY(EditAnywhere, Category = "Day Night Cycle")
    ADirectionalLight* DirectionalLight;

    float CurrentTimeOfDay = 0.0f; 
    bool bIsDayTime = true; // ³·°ú ¹ã ±¸ºÐ º¯¼ö

};
