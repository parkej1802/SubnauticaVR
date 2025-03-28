// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "Components/BoxComponent.h"
#include "PlayerCharacter.h"
#include "Components/SphereComponent.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    //-----------------------------------------------------------------------
    // 1. 스켈레탈 메쉬 로드
    ConstructorHelpers::FObjectFinder<USkeletalMesh> TempMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Underwater/Meshes/Shark/SM_Shark_00.SM_Shark_00'"));

    if (TempMesh.Succeeded()) {
        GetMesh()->SetSkeletalMesh(TempMesh.Object);
    }

    //-----------------------------------------------------------------------
    // 2. 범위 감지
    CheckPlayerRange = CreateDefaultSubobject<USphereComponent>(TEXT("CheckPlayerRange"));
    CheckPlayerRange->SetupAttachment(RootComponent);
    CheckPlayerRange->SetSphereRadius(3000.0f); // 반지름 증가

    CheckPlayerRange->SetCollisionProfileName("EnemyRangeCheck");


}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
    Super::BeginPlay();

    APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
    if (PlayerController)
    {
        APawn* PlayerPawn = PlayerController->GetPawn();
        if (PlayerPawn)
        {
            PlayerCharacter = Cast<APlayerCharacter>(PlayerPawn);
        }
    }

    // 중력 비활성화
    GetCharacterMovement()->GravityScale = 0.0f;

    // 범위 감지 이벤트 바인딩
    CheckPlayerRange->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::OnPlayerEnterRange);
    CheckPlayerRange->OnComponentEndOverlap.AddDynamic(this, &AEnemy::OnPlayerExitRange);
}



// Called every frame
void AEnemy::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // 이동
    EnemyMovetoPlayer(DeltaTime);
}


// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

//----------------------------------------------------------------------------------------
// 이동
void AEnemy::EnemyMovetoPlayer(float DeltaTime)
{
    
    if (!bChasePlayer || PlayerCharacter == nullptr)
    {
        return; // 플레이어를 쫓지 않을 때 동작하지 않도록 함
    }
    

    FVector PlayerLocation = PlayerCharacter->GetActorLocation();
    FVector EnemyLocation = GetActorLocation();

    // 플레이어를 향한 방향 벡터 (X, Y, Z 모두 반영)
    FVector Direction = PlayerLocation - EnemyLocation;
    Direction.Normalize();

    // 회전 적용 (플레이어를 바라보게)
    FRotator LookAtRotation = Direction.Rotation();
    SetActorRotation(LookAtRotation);

    // 이동
    SetActorLocation(EnemyLocation + Speed * Direction * DeltaTime);
}


//----------------------------------------------------------------------------------------
// 범위 감지
void AEnemy::OnPlayerEnterRange(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Player Chase is true."));
    if (OtherActor == PlayerCharacter)
    {
        bChasePlayer = true;
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Player Chase is true."));

    }
}

void AEnemy::OnPlayerExitRange(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Player Chase is true."));

    if (OtherActor == PlayerCharacter)
    {
        bChasePlayer = false;
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Player Chase is false."));
    }
}

//----------------------------------------------------------------------------------------
