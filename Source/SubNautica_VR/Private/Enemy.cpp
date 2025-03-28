// AEnemy.cpp 파일
#include "Enemy.h"
#include "Components/BoxComponent.h"
#include "PlayerCharacter.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

// 기본 생성자
AEnemy::AEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	// 스켈레탈 메쉬 로드
	ConstructorHelpers::FObjectFinder<USkeletalMesh> TempMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Underwater/Meshes/Shark/SM_Shark_00.SM_Shark_00'"));

	if (TempMesh.Succeeded()) {
		GetMesh()->SetSkeletalMesh(TempMesh.Object);
		GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
	}

	//-------------------------------------------------------------------------------------
	//Enemy Character Collision Check

	EnemyCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("EnemyCollision"));
	EnemyCollision->SetupAttachment(RootComponent);
	EnemyCollision->SetBoxExtent(FVector(100, 100, 100));
	EnemyCollision->SetCollisionProfileName("Enemy");


	//-------------------------------------------------------------------------------------
	// 범위 감지
	CheckPlayerRange = CreateDefaultSubobject<USphereComponent>(TEXT("CheckPlayerRange"));
	CheckPlayerRange->SetupAttachment(RootComponent);
	CheckPlayerRange->SetSphereRadius(1500.0f); // 반지름 증가
	CheckPlayerRange->SetCollisionProfileName("EnemyRangeCheck");
}

// 게임 시작 시 호출
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController)
	{
		APawn* PlayerPawn = PlayerController->GetPawn();
		if (PlayerPawn)
		{
			target = Cast<APlayerCharacter>(PlayerPawn);
		}
	}

	// 중력 비활성화
	GetCharacterMovement()->GravityScale = 0.0f;

	// 범위 감지 이벤트 바인딩
	CheckPlayerRange->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::OnPlayerEnterRange);
	CheckPlayerRange->OnComponentEndOverlap.AddDynamic(this, &AEnemy::OnPlayerExitRange);

	//---------------------------------------------------------------------------------------------
	// Spline 찾기
	// Spline 찾기
	TArray<AActor*> FoundSplines;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASplinePath::StaticClass(), FoundSplines);
	if (FoundSplines.Num() > 0)
	{
		PatrolPath = Cast<ASplinePath>(FoundSplines[0]); // 첫 번째 Spline 사용

		if (PatrolPath)
		{
			USplineComponent* Spline = PatrolPath->SplineComponent;
			if (Spline)
			{
				// 적을 Spline의 첫 번째 위치에 배치
				FVector StartLocation = Spline->GetLocationAtSplinePoint(0, ESplineCoordinateSpace::World);
				SetActorLocation(StartLocation);

				// 방향도 첫 번째 구간을 향하도록 설정
				FVector NextLocation = Spline->GetLocationAtSplinePoint(1, ESplineCoordinateSpace::World);
				FVector ForwardDirection = (NextLocation - StartLocation).GetSafeNormal();
				SetActorRotation(ForwardDirection.Rotation());

				// Spline 시작 위치로 초기화
				DistanceAlongSpline = 0.0f;
			}
		}
	}


}






// 매 프레임 호출
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// HP가 0보다 작다면 죽는다.
	if (hp <= 0) {
		mState = EEnemyState::Die;
	}


	// 실행창에 상태 메세지 출력하기
	switch (mState) {
		case EEnemyState::Idle: {	IdleState(DeltaTime);	} break;
		case EEnemyState::Move: {  MoveState(DeltaTime); } break;
		case EEnemyState::Attack: { AttackState(); } break;
		case EEnemyState::Die: { DieState(); } break;
	}
}

// 입력 설정
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

//-----------------------------------------------------------------------------------------------
// 일반 상태
void AEnemy::IdleState(float DeltaTime)
{
	if (bChasePlayer) {
		mState = EEnemyState::Move;
		return;
	}

	if (PatrolPath)
	{
		// Spline을 따라 순찰하는 상태
		if (!PatrolPath) return;
		USplineComponent* Spline = PatrolPath->SplineComponent;
		if (!Spline) return;

		// Spline을 따라 이동
		DistanceAlongSpline += Speed * DeltaTime;
		float SplineLength = Spline->GetSplineLength();

		if (DistanceAlongSpline >= SplineLength)
		{
			DistanceAlongSpline = 0.0f; // 순환 이동
		}

		FVector NewLocation = Spline->GetLocationAtDistanceAlongSpline(DistanceAlongSpline, ESplineCoordinateSpace::World);
		FRotator NewRotation = Spline->GetRotationAtDistanceAlongSpline(DistanceAlongSpline, ESplineCoordinateSpace::World);

		SetActorLocation(NewLocation);
		SetActorRotation(NewRotation);
	}
}



//-----------------------------------------------------------------------------------------------
// 이동
/*
void AEnemy::MoveState(float DeltaTime)
{
	if (!bChasePlayer || target == nullptr || bIsAttacking)
	{
		return; // 플레이어를 쫓지 않거나 공격 중일 때 동작하지 않도록 함
	}

	FVector PlayerLocation = target->GetActorLocation();
	FVector EnemyLocation = GetActorLocation();

	// 플레이어와의 거리 계산
	float Distance = FVector::Dist(PlayerLocation, EnemyLocation);

	// 공격 범위 이내일 경우 공격 상태로 전환
	if (Distance <= AttackRange)
	{
		mState = EEnemyState::Attack;
		return; // 공격 상태로 전환되면 더 이상 이동하지 않음
	}

	// 플레이어를 향한 방향 벡터 (X, Y, Z 모두 반영)
	FVector Direction = PlayerLocation - EnemyLocation;
	Direction.Normalize();

	// 회전 적용 (플레이어를 바라보게)
	FRotator LookAtRotation = Direction.Rotation();
	SetActorRotation(LookAtRotation);

	// 이동
	SetActorLocation(EnemyLocation + Speed * Direction * DeltaTime);
}
*/


void AEnemy::MoveState(float DeltaTime)
{
	if (bIsAttacking) return; // 공격 중이면 이동 X

	FVector EnemyLocation = GetActorLocation();

	if (bChasePlayer && target)
	{
		// 플레이어를 쫓는 상태
		FVector PlayerLocation = target->GetActorLocation();
		float Distance = FVector::Dist(PlayerLocation, EnemyLocation);

		if (Distance <= AttackRange)
		{
			mState = EEnemyState::Attack;
			return;
		}

		// 플레이어를 향한 방향으로 이동
		FVector Direction = PlayerLocation - EnemyLocation;
		Direction.Normalize();

		FRotator LookAtRotation = Direction.Rotation();
		SetActorRotation(LookAtRotation);

		SetActorLocation(EnemyLocation + Speed * Direction * DeltaTime);
	}
	else
	{
		// Spline을 따라 순찰하는 상태
		if (!PatrolPath) return;
		USplineComponent* Spline = PatrolPath->SplineComponent;
		if (!Spline) return;

		// Spline을 따라 이동
		DistanceAlongSpline += Speed * DeltaTime;
		float SplineLength = Spline->GetSplineLength();

		if (DistanceAlongSpline >= SplineLength)
		{
			DistanceAlongSpline = 0.0f; // 순환 이동
		}

		FVector NewLocation = Spline->GetLocationAtDistanceAlongSpline(DistanceAlongSpline, ESplineCoordinateSpace::World);
		FRotator NewRotation = Spline->GetRotationAtDistanceAlongSpline(DistanceAlongSpline, ESplineCoordinateSpace::World);

		SetActorLocation(NewLocation);
		SetActorRotation(NewRotation);
	}
}




// 플레이어가 범위에 들어왔을 때
void AEnemy::OnPlayerEnterRange(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == target)
	{
		bChasePlayer = true;
	}
}

// 플레이어가 범위에서 나갔을 때
void AEnemy::OnPlayerExitRange(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor == target)
	{
		bChasePlayer = false;
	}
}

//--------------------------------------------------------------------------------------------
// 공격 상태로 전환
void AEnemy::AttackState()
{
	if (bIsAttacking)
	{
		return; // 이미 공격 중이라면 다시 공격하지 않음
	}

	int playerHP = target->GetPlayerHP();
	if (playerHP <= 0) {
		return;
	}
	else {
		target->SetPlayerHP(-1);

		// 공격 상태 시작
		bIsAttacking = true;

		// 공격 애니메이션 또는 효과를 여기에 추가 (예: 공격 애니메이션 실행)
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, FString::Printf(TEXT("Player HP is %d"), target->GetPlayerHP()));


		// 공격 후 일정 시간 대기하도록 타이머 설정
		GetWorld()->GetTimerManager().SetTimer(AttackDelayTimerHandle, this, &AEnemy::EndAttack, AttackDelayTime, false);
	}



}

// 공격 상태 종료
void AEnemy::EndAttack()
{
	// 공격 상태 종료
	bIsAttacking = false;

	// 상태를 Idle로 변경
	mState = EEnemyState::Idle;
}

void AEnemy::DieState()
{
	this->Destroy();
}

//--------------------------------------------------------------------------------------------




