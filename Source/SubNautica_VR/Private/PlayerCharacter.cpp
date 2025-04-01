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
#include "MotionControllerComponent.h"
#include "../../../../Plugins/Runtime/XRBase/Source/XRBase/Public/HeadMountedDisplayFunctionLibrary.h"
#include "../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputSubsystems.h"
#include "../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h"
#include "../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/InputMappingContext.h"
#include "../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/InputAction.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"
#include "Blueprint/UserWidget.h"
#include "Components/WidgetComponent.h"
#include "InventoryWidget.h"

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

	LeftHandMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("LeftHandMesh"));
	LeftHandMesh->SetupAttachment(LeftHand);

	// 스켈레탈 메쉬 로드
	ConstructorHelpers::FObjectFinder<USkeletalMesh> TempLeftHandMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Characters/MannequinsXR/Meshes/SKM_MannyXR_left.SKM_MannyXR_left'"));

	if (TempLeftHandMesh.Succeeded()) {
		LeftHandMesh->SetSkeletalMesh(TempLeftHandMesh.Object);
	}
	
	//---------------------------------------------------------------------------------------
	RightHand = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("RightHand"));
	RightHand->SetupAttachment(RootComponent);
	RightHand->SetTrackingMotionSource(TEXT("Right"));

	RightHandMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("RightHandMesh"));
	RightHandMesh->SetupAttachment(RightHand);

	// 스켈레탈 메쉬 로드
	ConstructorHelpers::FObjectFinder<USkeletalMesh> TempRightHandMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Characters/MannequinsXR/Meshes/SKM_MannyXR_right.SKM_MannyXR_right'"));

	if (TempRightHandMesh.Succeeded()) {
		RightHandMesh->SetSkeletalMesh(TempRightHandMesh.Object);
	}

	//-----------------------------------------------------------
	//3. 도구 추가
	Scanner = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Scanner"));
	Scanner->SetupAttachment(RightHandMesh, TEXT("palm_r"));
	Scanner->SetRelativeScale3D(FVector(0.05));

	ConstructorHelpers::FObjectFinder<UStaticMesh> Temp_ScannerMesh(TEXT("/Script/Engine.StaticMesh'/Game/AHS/Assets/Models/Tools/sci-fi-scanner__2_/source/scannerf.scannerf'"));

	if (Temp_ScannerMesh.Succeeded()) {
		Scanner->SetStaticMesh(Temp_ScannerMesh.Object);
	}

	TempScanner = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TempScanner"));
	TempScanner->SetupAttachment(Scanner);
	//ScannerCollision->SetCollisionProfileName("");

	//-----------------------------------------------------------------------------------------
	// 무기
	CrowBar = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CrowBar"));
	CrowBar->SetupAttachment(RightHandMesh, TEXT("palm_r"));

	ConstructorHelpers::FObjectFinder<UStaticMesh> Temp_CrowbarMesh(TEXT("/Script/Engine.StaticMesh'/Game/AHS/Assets/Models/Tools/crowbar/source/crowbar1.crowbar1'"));

	if (Temp_CrowbarMesh.Succeeded()) {
		CrowBar->SetStaticMesh(Temp_CrowbarMesh.Object);
	}

	CrowBarCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("CrowBarCollision"));
	CrowBarCollision->SetupAttachment(CrowBar);
	CrowBarCollision->SetCollisionProfileName("PlayerAttack");
	CrowBarCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	//-----------------------------------------------------------------------------------------
	// 엔진 복구 % UI 표현
	// 위젯 컴포넌트 생성
	RestorePercentWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("RestorePercentWidget"));
	RestorePercentWidget->SetupAttachment(RootComponent); // 플레이어 캐릭터에 부착

	// 위젯 클래스 설정 (Blueprint에서 설정 가능)
	/*
	static ConstructorHelpers::FClassFinder<UUserWidget> WidgetClass(TEXT("/Game/UI/WBP_RestorePercent"));
	if (WidgetClass.Succeeded()) {
		RestorePercentWidget->SetWidgetClass(WidgetClass.Class);
	}
	*/

	InventoryUI = CreateDefaultSubobject<UWidgetComponent>(TEXT("InventoryWidgetComponent"));
	InventoryUI->SetupAttachment(RootComponent);


	//-----------------------------------------------------------
	BuildComp = CreateDefaultSubobject<UAC_BuildingComponent>(TEXT("BuildingComp"));
	PlayerActionComp = CreateDefaultSubobject<UAC_PlayerAction>(TEXT("PlayerActionComp"));

	InventoryComp = CreateDefaultSubobject<UAC_InventoryComponent>(TEXT("InventoryComp"));

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
	
	//-------------------------------------------------------------------
	// 1. 도구 설정
	Scanner->SetVisibility(false);
	CrowBar->SetVisibility(false);
	InventoryUI->SetVisibility(false);
	
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Depth: %d"), CalculateDepth(DeltaTime)));

	if (engineRestorePercent >= 100) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("100%!"));

		UGameplayStatics::OpenLevel(GetWorld(), FName("EndingMap"));
	}
	
	// ShowPlayerUI();
}

//-----------------------------------------------------------------------
// Input 연결
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


}


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

//-----------------------------------------------------------------------
// 플레이어 체력 구현
int APlayerCharacter::GetPlayerHP()
{
	return hp;
}

void APlayerCharacter::SetPlayerHP(int amount)
{
	hp += amount;
}

//-----------------------------------------------------------------------
// 플레이어 공격 구현
void APlayerCharacter::AttackCollisionCheck()
{
	if (bAttackCollsion == false) {
		CrowBar->SetVisibility(false);
		CrowBarCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	else {
		CrowBar->SetVisibility(true);
		CrowBarCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	}
}



//-----------------------------------------------------------------------

