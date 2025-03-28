// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "GameFramework/CharacterMovementComponent.h"

#include "Enemy.generated.h"

UCLASS()
class SUBNAUTICA_VR_API AEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

//------------------------------------------------------------------------
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* BoxComp;


//-----------------------------------------------------------------------
// 에너미 -> 타겟 이동
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class APlayerCharacter* PlayerCharacter;

	// 일반 이동
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Speed = 500.0f;

	void EnemyMovetoPlayer(float DeltaTime);

	// 범위 감지
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USphereComponent* CheckPlayerRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bChasePlayer = false;

	void OnPlayerEnterRange(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void OnPlayerExitRange(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

//-----------------------------------------------------------------------


};
