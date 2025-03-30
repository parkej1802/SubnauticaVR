#include "ItemSpawner.h"
#include "Kismet/GameplayStatics.h"
#include "ItemActor.h"
#include "ItemSpawnPoint.h"

// Sets default values
AItemSpawner::AItemSpawner()
{
    PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AItemSpawner::BeginPlay()
{
    Super::BeginPlay();

    // 스폰 포인트 찾기
    FindSpawnPoints();

    // 랜덤 시간 후 아이템 스폰 시작
    float CreateTime = FMath::RandRange(MinTime, MaxTime);
    GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &AItemSpawner::CreateItem, CreateTime);
}

void AItemSpawner::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // 아이템 스폰 주기를 관리하는 코드 추가
    if (AllItemsInLevel < 5)  // 예: 5개 이하로 아이템이 있을 때만 스폰
    {
        // 랜덤 타이머로 아이템 스폰
        float SpawnTime = FMath::RandRange(MinTime, MaxTime);
        GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &AItemSpawner::CreateItem, SpawnTime, false);
    }
}

void AItemSpawner::FindSpawnPoints()
{
    // 검색된 스폰 포인트를 저장할 배열
    TArray<AActor*> allActors;

    // AItemSpawnPoint 타입의 액터만 찾기
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AItemSpawnPoint::StaticClass(), allActors);

    // 찾은 액터들을 배열에 추가
    for (auto spawn : allActors)
    {
        SpawnPoints.Add(Cast<AItemSpawnPoint>(spawn));
    }
}

void AItemSpawner::CreateItem()
{
    if (AllItemsInLevel >= 5)
    {
        float CreateTime = FMath::RandRange(MinTime, MaxTime);
        GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &AItemSpawner::CreateItem, CreateTime);
        return;
    }

    if (SpawnPoints.Num() == 0 || SpawnableItemClasses.Num() == 0)
    {
        return;
    }

    int32 Index;
    do
    {
        Index = FMath::RandRange(0, SpawnPoints.Num() - 1);
    } while (UsedIndices.Contains(Index) && UsedIndices.Num() < SpawnPoints.Num());

    UsedIndices.Add(Index);
    SpawnItemAtLocation(Index);

    AllItemsInLevel++;

    float CreateTime = FMath::RandRange(MinTime, MaxTime);
    GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &AItemSpawner::CreateItem, CreateTime);
}

void AItemSpawner::SpawnItemAtLocation(int32 Index)
{
    if (!SpawnPoints.IsValidIndex(Index) || SpawnableItemClasses.Num() == 0)
    {
        return;
    }

    FVector SpawnLocation = SpawnPoints[Index]->GetActorLocation();
    TSubclassOf<AItemActor> ItemClass = SpawnableItemClasses[FMath::RandRange(0, SpawnableItemClasses.Num() - 1)];

    AItemActor* NewItem = GetWorld()->SpawnActor<AItemActor>(ItemClass, SpawnLocation, FRotator::ZeroRotator);
    if (NewItem)
    {
        NewItem->SetSpawnIndex(Index);
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Spawned Item: %s at Index: %d"), *NewItem->GetName(), Index));
    }
}

void AItemSpawner::FreeSpawnPoint(int32 Index)
{
    UsedIndices.Remove(Index);
    AllItemsInLevel--;
}
