#include "AHS/Boid.h"
#include "Math/UnrealMathUtility.h"

// 기본 생성자
ABoid::ABoid()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ABoid::BeginPlay()
{
	Super::BeginPlay();

	BoidManager = Cast<ABoidManager>(UGameplayStatics::GetActorOfClass(GetWorld(), ABoidManager::StaticClass()));

	LocalFlockArea = NewObject<USphereComponent>(this, USphereComponent::StaticClass(), TEXT("Sphere"));

	if (LocalFlockArea) {
		LocalFlockArea->SetupAttachment(RootComponent);
		LocalFlockArea->RegisterComponent();
		LocalFlockArea->CreationMethod = EComponentCreationMethod::Instance;
		LocalFlockArea->SetSphereRadius(BoidManager->GetLocalFlockRadius());
	}

	BoidSpeed = FMath::RandRange(BoidManager->GetMinSpeed(), BoidManager->GetMaxSpeed());

	//z축 방향의 변경을 위한 시도.
	//Velocity = GetActorForwardVector().GetSafeNormal() * BoidSpeed;
	FVector RandomDirection = FMath::VRand(); // 랜덤한 단위 벡터
	Velocity = RandomDirection * BoidSpeed;

}

void ABoid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Steer(DeltaTime);
	StayInBoundary(DeltaTime);
}

void ABoid::Steer(float DeltaTime)
{
	FVector Acceleration = FVector::ZeroVector;

	TArray<AActor*> LocalFlock;
	LocalFlockArea->GetOverlappingActors(LocalFlock, ABoid::StaticClass());

	Acceleration += Separate(LocalFlock);
	Acceleration += Align(LocalFlock);
	Acceleration += Cohesion(LocalFlock);

	Velocity += Acceleration * DeltaTime;
	Velocity = Velocity.GetClampedToSize(BoidManager->GetMinSpeed(), BoidManager->GetMaxSpeed());
	SetActorLocation(GetActorLocation() + (Velocity * DeltaTime));
	SetActorRotation(Velocity.ToOrientationQuat());
}

void ABoid::StayInBoundary(float DeltaTime)
{
	FVector CurrentLocation = GetActorLocation();
	float Boundary = BoidManager->GetBoidBoundary();

	// X 좌표 경계 체크
	if (CurrentLocation.X < -Boundary)
		CurrentLocation.X = Boundary;
	else if (CurrentLocation.X > Boundary)
		CurrentLocation.X = -Boundary;

	// Y 좌표 경계 체크
	if (CurrentLocation.Y < -Boundary)
		CurrentLocation.Y = Boundary;
	else if (CurrentLocation.Y > Boundary)
		CurrentLocation.Y = -Boundary;

	// Z 좌표 경계 체크
	if (CurrentLocation.Z < -Boundary)
		CurrentLocation.Z = Boundary;
	else if (CurrentLocation.Z > Boundary)
		CurrentLocation.Z = -Boundary;

	SetActorLocation(CurrentLocation);
}

FVector ABoid::Separate(TArray<AActor*> LocalFlock)
{
	FVector Steering = FVector::ZeroVector;
	int FlockCount = 0;

	for (AActor* OtherBoid : LocalFlock) {
		if (OtherBoid && OtherBoid != this) {
			float Distance = FVector::Distance(GetActorLocation(), OtherBoid->GetActorLocation());
			if (Distance > BoidManager->GetSeparationRadius()) continue;

			Steering += (GetActorLocation() - OtherBoid->GetActorLocation()).GetSafeNormal();
			FlockCount++;
		}
	}

	if (FlockCount > 0) {
		Steering /= FlockCount;
		Steering = Steering.GetSafeNormal() * BoidManager->GetSeparationStrength();
	}

	return Steering;
}

FVector ABoid::Align(TArray<AActor*> LocalFlock)
{
	FVector Steering = FVector::ZeroVector;
	int FlockCount = 0;

	for (AActor* OtherActor : LocalFlock) {
		if (OtherActor && OtherActor != this) {
			ABoid* OtherBoid = Cast<ABoid>(OtherActor);
			if (!OtherBoid) continue;

			float Distance = FVector::Distance(GetActorLocation(), OtherActor->GetActorLocation());
			if (Distance > BoidManager->GetAlignmentRadius()) continue;

			Steering += OtherBoid->Velocity.GetSafeNormal();
			FlockCount++;
		}
	}

	if (FlockCount > 0) {
		Steering /= FlockCount;
		Steering = Steering.GetSafeNormal() * BoidManager->GetAlignmentStrength();
	}

	return Steering;
}

FVector ABoid::Cohesion(TArray<AActor*> LocalFlock)
{
	FVector Steering = FVector::ZeroVector;
	FVector AveragePosition = FVector::ZeroVector;
	int FlockCount = 0;

	for (AActor* OtherActor : LocalFlock) {
		if (OtherActor && OtherActor != this) {
			float Distance = FVector::Distance(GetActorLocation(), OtherActor->GetActorLocation());
			if (Distance > BoidManager->GetCohesionRadius()) continue;

			AveragePosition += OtherActor->GetActorLocation();
			FlockCount++;
		}
	}

	if (FlockCount > 0) {
		AveragePosition /= FlockCount;
		Steering = (AveragePosition - GetActorLocation()).GetSafeNormal() * BoidManager->GetCohesionStrength();
	}

	return Steering;
}
