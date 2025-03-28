// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "GameFramework/CharacterMovementComponent.h"

#include "Enemy.generated.h"

UENUM(BlueprintType) 
enum class EEnemyState : uint8{
	Idle,
	Move,
	Attack,
	Damage,
	Die,
};

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
// Collision 판정
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UBoxComponent* EnemyCollision;

//-----------------------------------------------------------------------
// 상태 구현
	// 상태 변수
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	EEnemyState mState = EEnemyState::Idle;

	void IdleState();

//-----------------------------------------------------------------------
// 에너미 -> 타겟 이동
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class APlayerCharacter* target;

	// 일반 이동
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Speed = 500.0f;

	void MoveState(float DeltaTime);

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
// 공격 구현
public:
	// 공격 범위
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	float AttackRange = 400.0f; // 공격 범위

	// 공격 상태
	void AttackState();

	void EndAttack();

	// 공격 상태로 전환되었는지 여부
	bool bIsAttacking = false;

	// 공격 상태 후 대기 시간 (딜레이 시간)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	float AttackDelayTime = 2.0f;  // 예시로 2초 대기시간 설정

	// 공격 애니메이션 또는 효과에 사용할 타이머
	FTimerHandle AttackDelayTimerHandle;

//-----------------------------------------------------------------------
// 피격 구현
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 MaxHP = 1;

	// 체력
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 hp = MaxHP;

//-----------------------------------------------------------------------

};
