// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../../../../Plugins/FX/Niagara/Source/Niagara/Classes/NiagaraSystem.h"
#include "Sound/SoundCue.h"
#include "AC_PlayerAction.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SUBNAUTICA_VR_API UAC_PlayerAction : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAC_PlayerAction();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetupInputBinding(class UEnhancedInputComponent* Input);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class APlayerCharacter* PlayerCharacter;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	class UInputMappingContext* IMC_VRInput;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	class UInputAction* IA_PlayerMove;

	void PlayerMove(const struct FInputActionValue& InputValue);

	UPROPERTY(EditDefaultsOnly, Category = Input)
	class UInputAction* IA_PlayerTurn;

	void Turn(const struct FInputActionValue& Values);

	UPROPERTY(EditDefaultsOnly, Category = Input)
	class UInputAction* IA_PlayerJump;

	// 스냅턴 기능 추가
	UPROPERTY(EditDefaultsOnly, Category = Input)
	class UInputAction* IA_SnapTurn;

	//--------------------------------------------------------------
	void PlayerJump(const struct FInputActionValue& Values);

	void InWater();

	void OutWater();
	
	void PlayerSwimming(const struct FInputActionValue& InputValue);

	UPROPERTY(EditDefaultsOnly, Category = Input)
	class UInputAction* IA_Swim;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	class UInputAction* IA_Catch;

	void PlayerCatchStart(const struct FInputActionValue& InputValue);

	void PlayerCatchEnd(const struct FInputActionValue& InputValue);

	void PlayerCatchTrace();

	bool bIsCatch = false;

	TMap<AActor*, float> HitActors;

	//============================================================
	// 스냅 턴 관련 구현
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerTurn")
	float RotationSpeed = 1.0f;

	void SnapTurn(const struct FInputActionValue& InputValue);

	bool bCanSnapTurn = true;

	//------------------------------------------------------------
	// 도구 사용 추가
	UPROPERTY(EditDefaultsOnly, Category = Input)
	class UInputAction* IA_ShowTool;

	void ToolUse(const struct FInputActionValue& InputValue);
	void HideTool(const struct FInputActionValue& InputValue);

};
