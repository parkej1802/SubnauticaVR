
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class SUBNAUTICA_VR_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	// 카메라
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	class UCameraComponent* VRCamera;

	//--------------------------------------------------------
	// 모션 컨트롤러 연결
	UPROPERTY(VisibleAnywhere, Category = "MotionController")
	class UMotionControllerComponent* LeftHand;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hand")
	class USkeletalMeshComponent* LeftHandMesh;

	UPROPERTY(VisibleAnywhere, Category = "MotionController")
	class UMotionControllerComponent* RightHand;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hand")
	class USkeletalMeshComponent* RightHandMesh;

	//---------------------------------------------------------	
	// 현재 속도 (초기값: 정지 상태)
	UPROPERTY(EditAnywhere, Category = "Player Settings")
	FVector Velocity = FVector::ZeroVector;

	// 수영 속도 (초기값: 300.0f)
	UPROPERTY(EditAnywhere, Category = "Player Settings")
	float SwimSpeed = 300.0f;

	// 수영 상태 판별
	UPROPERTY(EditAnywhere)
	bool bIsSwimming = true;
	//---------------------------------------------------------

	// 수심
	int32 WaterDepth = 0.0f;

	// 수심 계산
	int CalculateDepth(float DeltaSecond);

	//--------------------------------------------------------
public:
	// 산소 최대치
	int32 MaxOxygen = 100;

	// 현재 산소
	int32 CurrentOxygen = MaxOxygen;

	float currentOxygenTime = 0.f;

	//산소 소모 속도(시간 비례)
	UPROPERTY(EditAnywhere)
	float OxygenTime = 0.25f;


	//--------------------------------------------------------
	// 임시 UI
	void ShowPlayerUI();

	UPROPERTY(EditAnywhere, Category = MainWidget)
	TSubclassOf<UUserWidget> PlayerMainWidget;

	class UPlayerStatUI* PlayerMainUI;


//----------------------------------------------------------------
// PlayerAction
public:
	UPROPERTY(EditDefaultsOnly, Category = PlayerAction)
	class UAC_PlayerAction* PlayerActionComp;


// BuildingSystem
public:
	UPROPERTY(EditDefaultsOnly, Category = BuildingSystem)
	class UAC_BuildingComponent* BuildComp;

//----------------------------------------------------------------
// 플레이어 HP (에너미 상호작용 관련)
	int32 MaxHP = 3;

	// 체력
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 hp = MaxHP;

	int GetPlayerHP();
	void SetPlayerHP(int amount);

//----------------------------------------------------------------
// 플레이어 공격
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tools")
	class UStaticMeshComponent* Scanner;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tools")
	class UStaticMeshComponent* TempScanner;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tools")
	class UStaticMeshComponent* CrowBar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tools")
	class UBoxComponent* CrowBarCollision;

	bool bAttackCollsion = false;

	void AttackCollisionCheck();

//----------------------------------------------------------------
// 플레이어 스캔 액션





// InventorySystem;
	UPROPERTY(EditDefaultsOnly, Category = InventorySystem)
	class UAC_InventoryComponent* InventoryComp;

	UPROPERTY(EditAnywhere, Category = MainWidget)
	TSubclassOf<UUserWidget> InventoryWidget;

	class UInventoryWidget* InventoryMainUI;
};


