// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicSplineController.h"
#include "Components/SplineComponent.h"

// Sets default values
ABasicSplineController::ABasicSplineController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 스플라인 컴포넌트 추가
	Spline = CreateDefaultSubobject<USplineComponent>(TEXT("Spline"));
	RootComponent = Spline;

}

// Called when the game starts or when spawned
void ABasicSplineController::BeginPlay()
{
	Super::BeginPlay();
	
	for (AActor* Fish : FishArray)
	{
		if (Fish)
		{
			// 각 물고기의 초기 위치를 0으로 설정
			FishProgressMap.Add(Fish, 0.0f);
		}
	}

}

// Called every frame
void ABasicSplineController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if (!Spline || FishArray.Num() == 0) return;

    for (AActor* Fish : FishArray)
    {
        if (!Fish) continue;

        // 현재 진행 거리 업데이트
        float& DistanceAlongSpline = FishProgressMap[Fish];
        DistanceAlongSpline += MoveSpeed * DeltaTime;

        float SplineLength = Spline->GetSplineLength();
        if (DistanceAlongSpline > SplineLength)
        {
            DistanceAlongSpline = 0.0f; // 처음으로 리셋
        }

        // 새로운 위치 & 회전 가져오기
        FVector NewLocation = Spline->GetLocationAtDistanceAlongSpline(DistanceAlongSpline, ESplineCoordinateSpace::World);
        FRotator NewRotation = Spline->GetRotationAtDistanceAlongSpline(DistanceAlongSpline, ESplineCoordinateSpace::World);

        // 물고기 위치 & 회전 업데이트
        Fish->SetActorLocationAndRotation(NewLocation, NewRotation);
    }

}

