// Fill out your copyright notice in the Description page of Project Settings.


#include "SingleFishMovement.h"
#include "Components/SplineComponent.h"

// Sets default values
ASingleFishMovement::ASingleFishMovement()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// ���ö��� ������Ʈ ����
	SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("SplineComponent"));
	RootComponent = SplineComponent;

	// ����� ��ġ �ʱ�ȭ
	SplineDistance = 0.f;
}

// Called when the game starts or when spawned
void ASingleFishMovement::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASingleFishMovement::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    // ����� ��ġ�� ���ö����� ���� �̵�
    if (SplineComponent)
    {
        // ���ö����� ���� �̵��� ��ġ ���
        SplineDistance += MovementSpeed * DeltaTime;

        // ���ö����� ���� �ʵ��� ����
        if (SplineDistance >= SplineComponent->GetSplineLength())
        {
            SplineDistance = 0.f;  // ó������ ���ư��� ���
        }

        // ���ö����� ���� ����� ��ġ ������Ʈ
        FVector NewLocation = SplineComponent->GetLocationAtDistanceAlongSpline(SplineDistance, ESplineCoordinateSpace::World);
        SetActorLocation(NewLocation);
    }

}

