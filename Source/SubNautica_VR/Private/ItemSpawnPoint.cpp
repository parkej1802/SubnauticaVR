#include "ItemSpawnPoint.h"

// Sets default values
AItemSpawnPoint::AItemSpawnPoint()
{
	// Tick() 호출 비활성화 (필요하지 않음)
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AItemSpawnPoint::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame (사용하지 않음)
void AItemSpawnPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
