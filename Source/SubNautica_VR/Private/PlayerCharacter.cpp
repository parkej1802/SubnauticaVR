// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "AC_BuildingComponent.h"
#include "AC_PlayerAction.h"
#include "PlayerStatUI.h"
#include "GameFramework/CharacterMovementComponent.h" 
#include "MotionControllerComponent.h"
#include "../../../../Plugins/Runtime/XRBase/Source/XRBase/Public/HeadMountedDisplayFunctionLibrary.h"
#include "../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputSubsystems.h"
#include "../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h"
#include "../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/InputMappingContext.h"
#include "../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/InputAction.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 0. Collision 설정
	GetCapsuleComponent()->SetCollisionProfileName("Player");

	// 1. 카메라 붙이기
	VRCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("VRCamera"));
	VRCamera->SetupAttachment(RootComponent);

	// 2. 손 붙이기
	LeftHand = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("LeftHand"));
	LeftHand->SetupAttachment(RootComponent);
	LeftHand->SetTrackingMotionSource(TEXT("Left"));

	RightHand = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("RightHand"));
	RightHand->SetupAttachment(RootComponent);
	RightHand->SetTrackingMotionSource(TEXT("Right"));


	//-----------------------------------------------------------
	BuildComp = CreateDefaultSubobject<UAC_BuildingComponent>(TEXT("BuildingComp"));
	PlayerActionComp = CreateDefaultSubobject<UAC_PlayerAction>(TEXT("PlayerActionComp"));
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	// HMD가 연결되어 있으면, HMD의 Tracking 위치를 조절해보자
	if (UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayEnabled()) {
		UHeadMountedDisplayFunctionLibrary::SetTrackingOrigin(EHMDTrackingOrigin::View);
		UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition(0);
		//UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition(90);
	}

	// 컨트롤러 연결
	if (PlayerActionComp)
	{
		UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(InputComponent);
		if (EnhancedInput)
		{
			PlayerActionComp->SetupInputBinding(EnhancedInput);
		}
	}


	
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Depth: %d"), CalculateDepth(DeltaTime)));
	//ShowPlayerUI();
}

//-----------------------------------------------------------------------
// Input 연결
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


}


//-----------------------------------------------------------------------


//-----------------------------------------------------------------------
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

