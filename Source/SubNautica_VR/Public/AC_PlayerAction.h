// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
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
};
