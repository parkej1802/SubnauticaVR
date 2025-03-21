// Fill out your copyright notice in the Description page of Project Settings.


#include "DayAndNightSystem.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/DirectionalLight.h"

// Sets default values
ADayAndNightSystem::ADayAndNightSystem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADayAndNightSystem::BeginPlay()
{
	Super::BeginPlay();

    // 씬에 있는 Directional Light 찾기
    TArray<AActor*> FoundLights;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ADirectionalLight::StaticClass(), FoundLights);

    if (FoundLights.Num() > 0)
    {
        DirectionalLight = Cast<ADirectionalLight>(FoundLights[0]);
    }
	
}

// Called every frame
void ADayAndNightSystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if (DirectionalLight)
    {
        // 낮일 때는 DaySpeed 속도로, 밤일 때는 NightSpeed 속도로 시간 흐름을 조정
        if (bIsDayTime)
        {
            CurrentTimeOfDay += DeltaTime * DaySpeed;  // 낮 시간 속도
            if (CurrentTimeOfDay >= 12.0f)  // 12시간까지 낮으로 설정 (12시간 이상 되면 밤으로 변경)
            {
                bIsDayTime = false;  // 낮에서 밤으로 변경
            }
        }
        else
        {
            CurrentTimeOfDay += DeltaTime * NightSpeed;  // 밤 시간 속도
            if (CurrentTimeOfDay >= 24.0f)  // 24시간을 넘어가면 다시 낮으로 설정
            {
                CurrentTimeOfDay = 0.0f;
                bIsDayTime = true;  // 밤에서 낮으로 변경
            }
        }

        // Directional Light의 회전 값 설정
        float SunRotation = (CurrentTimeOfDay / 24.0f) * 360.0f;
        FRotator NewRotation(SunRotation, 0.0f, 0.0f);
        DirectionalLight->SetActorRotation(NewRotation);
    }
}

