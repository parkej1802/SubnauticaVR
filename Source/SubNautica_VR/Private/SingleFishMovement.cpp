// Fill out your copyright notice in the Description page of Project Settings.


#include "SingleFishMovement.h"
#include "Components/SplineComponent.h"

// Sets default values
ASingleFishMovement::ASingleFishMovement()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 스플라인 컴포넌트 생성
	SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("SplineComponent"));
	RootComponent = SplineComponent;

	// 물고기 위치 초기화
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

    // 물고기 위치를 스플라인을 따라 이동
    if (SplineComponent)
    {
        // 스플라인을 따라 이동할 위치 계산
        SplineDistance += MovementSpeed * DeltaTime;

        // 스플라인을 넘지 않도록 제한
        if (SplineDistance >= SplineComponent->GetSplineLength())
        {
            SplineDistance = 0.f;  // 처음으로 돌아가는 경우
        }

        // 스플라인을 따라 물고기 위치 업데이트
        FVector NewLocation = SplineComponent->GetLocationAtDistanceAlongSpline(SplineDistance, ESplineCoordinateSpace::World);
        SetActorLocation(NewLocation);
    }

}

