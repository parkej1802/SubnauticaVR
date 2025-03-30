
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
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
	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* VRCamera;

	bool bIsSwimming = true;

	int32 WaterDepth = 0.0f;

	int CalculateDepth(float DeltaSecond);

	int32 MaxOxygen = 100;

	int32 CurrentOxygen = MaxOxygen;

	float currentOxygenTime = 0.f;
	float OxygenTime = 0.25f;

	void ShowPlayerUI();

	UPROPERTY(EditAnywhere, Category = MainWidget)
	TSubclassOf<UUserWidget> PlayerMainWidget;

	class UPlayerStatUI* PlayerMainUI;

// PlayerAction
public:
	UPROPERTY(EditDefaultsOnly, Category = PlayerAction)
	class UAC_PlayerAction* PlayerActionComp;

	
// BuildingSystem
public:
	UPROPERTY(EditDefaultsOnly, Category = BuildingSystem)
	class UAC_BuildingComponent* BuildComp;

// InventorySystem;
	UPROPERTY(EditDefaultsOnly, Category = InventorySystem)
	class UAC_InventoryComponent* InventoryComp;

	UPROPERTY(EditAnywhere, Category = MainWidget)
	TSubclassOf<UUserWidget> InventoryWidget;

	class UInventoryWidget* InventoryMainUI;
};

