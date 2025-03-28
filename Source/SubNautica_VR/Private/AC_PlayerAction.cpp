// Fill out your copyright notice in the Description page of Project Settings.


#include "AC_PlayerAction.h"
#include "GameFramework/PlayerController.h"
#include "../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h"
#include "PlayerCharacter.h"
#include "../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputSubsystems.h"
#include "../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/InputMappingContext.h"
#include "../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/InputAction.h"
#include "InputActionValue.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "../../../../Plugins/FX/Niagara/Source/Niagara/Public/NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"

// Sets default values for this component's properties
UAC_PlayerAction::UAC_PlayerAction()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	ConstructorHelpers::FObjectFinder<UInputMappingContext>TempIMC(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Input/IMC_VRInput.IMC_VRInput'"));

	if (TempIMC.Succeeded()) {
		IMC_VRInput = TempIMC.Object;
	}

	ConstructorHelpers::FObjectFinder<UInputAction>TempIA_Move(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/IA_VRMove.IA_VRMove'"));
	if (TempIA_Move.Succeeded()) {
		IA_PlayerMove = TempIA_Move.Object;
	}

	ConstructorHelpers::FObjectFinder<UInputAction>TempIA_Turn(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/IA_VRTurn.IA_VRTurn'"));
	if (TempIA_Turn.Succeeded()) {
		IA_PlayerTurn = TempIA_Turn.Object;
	}

	ConstructorHelpers::FObjectFinder<UInputAction>TempIA_Jump(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/IA_VRJump.IA_VRJump'"));
	if (TempIA_Jump.Succeeded()) {
		IA_PlayerJump = TempIA_Jump.Object;
	}

	ConstructorHelpers::FObjectFinder<UInputAction>TempIA_Swim(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/IA_Swim.IA_Swim'"));
	if (TempIA_Swim.Succeeded()) {
		IA_Swim = TempIA_Swim.Object;
	}

	ConstructorHelpers::FObjectFinder<UInputAction>TempIA_Catch(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/IA_Catch.IA_Catch'"));
	if (TempIA_Catch.Succeeded()) {
		IA_Catch = TempIA_Catch.Object;
	}

	//-------------------------------------------------------------
	ConstructorHelpers::FObjectFinder<UInputAction>TempIA_SnapTurn(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/IA_SnapTurn.IA_SnapTurn'"));
	if (TempIA_SnapTurn.Succeeded()) {
		IA_SnapTurn = TempIA_SnapTurn.Object;
	}

	ConstructorHelpers::FObjectFinder<UInputAction>TempIA_ShowTool(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/IA_UseTool.IA_UseTool'"));
	if (TempIA_ShowTool.Succeeded()) {
		IA_ShowTool = TempIA_ShowTool.Object;
	}
	//-------------------------------------------------------------
}

// Called when the game starts
void UAC_PlayerAction::BeginPlay()
{
	Super::BeginPlay();

	AActor* OwnerActor = GetOwner();

	if (APlayerController* PlayerController = GetOwner()->GetInstigatorController<APlayerController>())
	{
		UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent);
		if (EnhancedInputComponent)
		{
			SetupInputBinding(EnhancedInputComponent);
		}
	}

	if (OwnerActor)
	{
		PlayerCharacter = Cast<APlayerCharacter>(OwnerActor);
	}
	
}

// Called every frame
void UAC_PlayerAction::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bIsCatch) {
		PlayerCatchTrace();
	}

}

void UAC_PlayerAction::SetupInputBinding(class UEnhancedInputComponent* Input)
{
	auto pc = GetWorld()->GetFirstPlayerController();

	if (pc) {
		auto localPlayer = pc->GetLocalPlayer();
		auto SS = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(localPlayer);

		if (SS) {
			SS->AddMappingContext(IMC_VRInput, 1);
		}
	}

	auto InputSystem = Cast<UEnhancedInputComponent>(Input);

	if (InputSystem) {
		InputSystem->BindAction(IA_PlayerMove, ETriggerEvent::Triggered, this, &UAC_PlayerAction::PlayerMove);


		InputSystem->BindAction(IA_PlayerTurn, ETriggerEvent::Triggered, this, &UAC_PlayerAction::Turn);
		InputSystem->BindAction(IA_PlayerJump, ETriggerEvent::Started, this, &UAC_PlayerAction::PlayerJump);
		InputSystem->BindAction(IA_Swim, ETriggerEvent::Triggered, this, &UAC_PlayerAction::PlayerSwimming);
		InputSystem->BindAction(IA_Catch, ETriggerEvent::Started, this, &UAC_PlayerAction::PlayerCatchStart);
		InputSystem->BindAction(IA_Catch, ETriggerEvent::Completed, this, &UAC_PlayerAction::PlayerCatchEnd);


		InputSystem->BindAction(IA_SnapTurn, ETriggerEvent::Triggered, this, &UAC_PlayerAction::SnapTurn);

		InputSystem->BindAction(IA_ShowTool, ETriggerEvent::Started, this, &UAC_PlayerAction::ToolUse);
		InputSystem->BindAction(IA_ShowTool, ETriggerEvent::Completed, this, &UAC_PlayerAction::HideTool);

	}
}


void UAC_PlayerAction::PlayerMove(const struct FInputActionValue& InputValue)
{
	FVector2D Scale = InputValue.Get<FVector2D>();


	//1. 물속에서 이동
	if (PlayerCharacter->bIsSwimming)
	{
		PlayerCharacter->GetCharacterMovement()->MaxFlySpeed = PlayerCharacter->SwimSpeed;

		// 물속에서 이동 감속 반영
		FVector Forward = PlayerCharacter->VRCamera->GetForwardVector();
		FVector Right = PlayerCharacter->VRCamera->GetRightVector();
		FVector Up = FVector::UpVector; // 수직 이동 (물속에서 뜨거나 가라앉는 경우)

		// 속도를 점진적으로 줄이기 위한 감쇠 적용
		float DragFactor = 0.8f; // 항력 계수 (조절 가능)
		PlayerCharacter->Velocity *= DragFactor;

		// 플레이어가 물속에서 입력에 따라 움직이도록 적용
		FVector SwimDirection = (Forward * Scale.X + Right * Scale.Y).GetSafeNormal();
		PlayerCharacter->Velocity += SwimDirection * PlayerCharacter->SwimSpeed * GetWorld()->GetDeltaSeconds();

		// 최종 이동 적용
		PlayerCharacter->AddMovementInput(PlayerCharacter->Velocity.GetSafeNormal());
	}
	//2. 기존 지상 이동
	else
	{
		// 기존 지상 이동
		PlayerCharacter->AddMovementInput(PlayerCharacter->VRCamera->GetForwardVector(), Scale.X);
		PlayerCharacter->AddMovementInput(PlayerCharacter->VRCamera->GetRightVector(), Scale.Y);
	}
}

//기존 코드
//FVector Direction = PlayerCharacter->VRCamera->GetForwardVector() * Scale.X + PlayerCharacter->VRCamera->GetRightVector() * Scale.Y;
//PlayerCharacter->AddMovementInput(Direction);



//===============================================================================================
void UAC_PlayerAction::Turn(const struct FInputActionValue& Values)
{
	FVector2d Scale = Values.Get<FVector2d>();
	PlayerCharacter->AddControllerPitchInput(Scale.Y);
	PlayerCharacter->AddControllerYawInput(Scale.X);
}

void UAC_PlayerAction::PlayerJump(const struct FInputActionValue& Values)
{
	if (!PlayerCharacter->bIsSwimming)
	{
		PlayerCharacter->Jump();
	}
}

void UAC_PlayerAction::InWater()
{
	/*
	UCharacterMovementComponent* CharacterMovement = PlayerCharacter->GetCharacterMovement();
	if (CharacterMovement)
	{
		CharacterMovement->SetMovementMode(MOVE_Swimming);
	}
	*/
}	

void UAC_PlayerAction::OutWater()
{
	/*
	UCharacterMovementComponent* CharacterMovement = PlayerCharacter->GetCharacterMovement();
	if (CharacterMovement)
	{
		CharacterMovement->SetMovementMode(MOVE_Walking);
	}
	*/
}

void UAC_PlayerAction::PlayerSwimming(const struct FInputActionValue& InputValue)
{
	/*
	if (!PlayerCharacter->bIsSwimming) return;

	FVector2d Scale = InputValue.Get<FVector2d>();

	FVector Direction = PlayerCharacter->VRCamera->GetForwardVector() * Scale.X + PlayerCharacter->VRCamera->GetRightVector() * Scale.Y;

	PlayerCharacter->AddMovementInput(Direction);
	*/
}

//---------------------------------------------------------------------------------------------
void UAC_PlayerAction::PlayerCatchTrace()
{
	FVector StartLocation = PlayerCharacter->VRCamera->GetComponentLocation();
	FVector ForwardVector = PlayerCharacter->VRCamera->GetForwardVector();


	float TraceDistance = 150.0f;
	float SphereRadius = 40.0f;

	TArray<FHitResult> HitResults;
	FCollisionQueryParams QueryParams;

	QueryParams.AddIgnoredActor(PlayerCharacter);

	TMap<AActor*, float> HitActorTimeMap;

	for (int32 i = 0; i < 5; i++) {
		TraceDistance -= 25;
		SphereRadius -= 5;
	
		FVector TraceStart = StartLocation;
		FVector TraceEnd = StartLocation + ForwardVector * TraceDistance;

		FHitResult HitResult;
		bool bHit = GetWorld()->SweepSingleByChannel(
			HitResult,
			TraceStart,
			TraceEnd,
			FQuat::Identity,
			ECC_Visibility,
			FCollisionShape::MakeSphere(SphereRadius),
			QueryParams
		);

		if (bHit)
		{
			DrawDebugSphere(GetWorld(), HitResult.Location, SphereRadius, 12, FColor::Green, false, 0.1f);

			AActor* HitActor = HitResult.GetActor();
			if (HitActor)
			{
				if (HitActors.Contains(HitActor))
				{
					HitActors[HitActor] += GetWorld()->GetDeltaSeconds();
				}
				else
				{
					HitActors.Add(HitActor, 0.0f);
				}

				if (HitActors[HitActor] >= 3.0f)
				{
					HitActor->Destroy();
					HitActors.Remove(HitActor);
				}
			}
		}
		else
		{
			DrawDebugSphere(GetWorld(), TraceEnd, SphereRadius, 12, FColor::Red, false, 0.1f);
		}
	}


}

void UAC_PlayerAction::PlayerCatchStart(const struct FInputActionValue& InputValue)
{	
	bIsCatch = true;
}

void UAC_PlayerAction::PlayerCatchEnd(const struct FInputActionValue& InputValue)
{
	bIsCatch = false;
}

//---------------------------------------------------------------------------------------------
// 컨트롤러를 활용한 회전
void UAC_PlayerAction::SnapTurn(const struct FInputActionValue& InputValue)
{
	FVector2D Scale = InputValue.Get<FVector2D>();

	// X축 입력값 → 좌우 회전 (Yaw)
	PlayerCharacter->AddControllerYawInput(Scale.X * RotationSpeed);

	// Y축 입력값 → 위아래 회전 (Pitch)
	PlayerCharacter->AddControllerPitchInput(Scale.Y * RotationSpeed);
}

// 도구 사용
void UAC_PlayerAction::ToolUse(const struct FInputActionValue& InputValue)
{
	// 도구 보이게 하기
	PlayerCharacter->bAttackCollsion = true;
	PlayerCharacter->AttackCollisionCheck();
}

void UAC_PlayerAction::HideTool(const struct FInputActionValue& InputValue)
{
	PlayerCharacter->bAttackCollsion = false;
	PlayerCharacter->AttackCollisionCheck();
}

//---------------------------------------------------------------------------------------------


