// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "AHS/BoidManager.h"
#include "Boid.generated.h"

UCLASS()
class SUBNAUTICA_VR_API ABoid : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABoid();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

//----------------------------------------------
public:
	FVector Velocity;

	// �̵� ������ �ӵ�
	float BoidSpeed;

protected:
	// �̵�
	void Steer(float DeltaTime);
	void StayInBoundary(float DeltaTime);

	// ��ġ ����
	ABoidManager* BoidManager;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USphereComponent* LocalFlockArea;

	FVector Separate(TArray<AActor*> LocalFlock);
	FVector Align(TArray<AActor*> LocalFlock);
	FVector Cohesion(TArray<AActor*> LocalFlock);

};
