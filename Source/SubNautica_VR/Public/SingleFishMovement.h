// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SingleFishMovement.generated.h"

UCLASS()
class SUBNAUTICA_VR_API ASingleFishMovement : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASingleFishMovement();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// ���ö��� ������Ʈ
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spline")
    class USplineComponent* SplineComponent;

    // ����� �̵� �ӵ�
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    float MovementSpeed = 100.f;

    // ����� ��ġ�� ���󰡰� �ִ� ����
    float SplineDistance;

};
