// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "AC_BuildingComponent.h"
#include "AC_PlayerAction.h"
#include "PlayerStatUI.h"
#include "GameFramework/CharacterMovementComponent.h" 
#include "AC_InventoryComponent.h"
#include "InventoryGridWidget.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	VRCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("VRCamera"));
	VRCamera->SetupAttachment(RootComponent);

	BuildComp = CreateDefaultSubobject<UAC_BuildingComponent>(TEXT("BuildingComp"));
	PlayerActionComp = CreateDefaultSubobject<UAC_PlayerAction>(TEXT("PlayerActionComp"));

	InventoryComp = CreateDefaultSubobject<UAC_InventoryComponent>(TEXT("InventoryComp"));

}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Depth: %d"), CalculateDepth(DeltaTime)));

	ShowPlayerUI();
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

int APlayerCharacter::CalculateDepth(float DeltaSecond)
{
	float calculateZ = 0.0f - GetActorLocation().Z;

	int meter = static_cast<int>(calculateZ) / 100;

	currentOxygenTime += DeltaSecond;
	if (meter > 0 && currentOxygenTime >= OxygenTime && CurrentOxygen > 0) {
		
		CurrentOxygen -= 1;
		currentOxygenTime = 0.0f;
	}
	else if (meter < 0 && currentOxygenTime >= OxygenTime && CurrentOxygen < 100) {
		CurrentOxygen += 1;
		currentOxygenTime = 0.0f;
	}

	return meter;
}

void APlayerCharacter::ShowPlayerUI()
{
	if (PlayerMainWidget)
	{
		PlayerMainUI = CreateWidget<UPlayerStatUI>(GetWorld(), PlayerMainWidget);
	}
	if (PlayerMainUI)
	{
		PlayerMainUI->AddToViewport();
	}
}

