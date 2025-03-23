
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

// PlayerAction
public:
	UPROPERTY(EditDefaultsOnly, Category = PlayerAction)
	class UAC_PlayerAction* PlayerActionComp;

	
// BuildingSystem
public:
	UPROPERTY(EditDefaultsOnly, Category = BuildingSystem)
	class UAC_BuildingComponent* BuildComp;
};

