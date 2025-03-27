// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SplineComponent.h"
#include "BasicSplineController.generated.h"

UCLASS()
class SUBNAUTICA_VR_API ABasicSplineController : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABasicSplineController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

//------------------------------------------------------
    // 이동할 물고기들
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Fish Movement")
    TArray<AActor*> FishArray;

    // 따라갈 Spline
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Fish Movement")
    USplineComponent* Spline;

    // 이동 속도 (각 물고기마다 다르게 가능)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Fish Movement")
    float MoveSpeed = 300.0f;

    // 물고기별 진행 거리
    TMap<AActor*, float> FishProgressMap;



};
