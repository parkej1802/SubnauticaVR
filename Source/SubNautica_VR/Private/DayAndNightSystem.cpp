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

    // ���� �ִ� Directional Light ã��
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
        // ���� ���� DaySpeed �ӵ���, ���� ���� NightSpeed �ӵ��� �ð� �帧�� ����
        if (bIsDayTime)
        {
            CurrentTimeOfDay += DeltaTime * DaySpeed;  // �� �ð� �ӵ�
            if (CurrentTimeOfDay >= 12.0f)  // 12�ð����� ������ ���� (12�ð� �̻� �Ǹ� ������ ����)
            {
                bIsDayTime = false;  // ������ ������ ����
            }
        }
        else
        {
            CurrentTimeOfDay += DeltaTime * NightSpeed;  // �� �ð� �ӵ�
            if (CurrentTimeOfDay >= 24.0f)  // 24�ð��� �Ѿ�� �ٽ� ������ ����
            {
                CurrentTimeOfDay = 0.0f;
                bIsDayTime = true;  // �㿡�� ������ ����
            }
        }

        // Directional Light�� ȸ�� �� ����
        float SunRotation = (CurrentTimeOfDay / 24.0f) * 360.0f;
        FRotator NewRotation(SunRotation, 0.0f, 0.0f);
        DirectionalLight->SetActorRotation(NewRotation);
    }
}

