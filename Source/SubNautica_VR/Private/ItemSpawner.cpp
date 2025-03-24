#include "ItemSpawner.h"
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "ItemActor.h"
#include "ItemData.h" // ItemData 구조체가 정의된 헤더 파일

AItemSpawner::AItemSpawner()
{
    PrimaryActorTick.bCanEverTick = false;

    // 기본 값 설정
    SpawnAreaMin = FVector(-500.f, -500.f, 0.f);
    SpawnAreaMax = FVector(500.f, 500.f, 0.f);
}

void AItemSpawner::BeginPlay()
{
    Super::BeginPlay();

    // 아이템 스폰을 시작
    SpawnItemAtRandomLocation();
}

void AItemSpawner::SpawnItemAtRandomLocation()
{
    // 랜덤 위치 생성
    FVector RandomLocation = FMath::RandPointInBox(FBox(SpawnAreaMin, SpawnAreaMax));

    // 아이템 ID 목록을 순회하여 아이템을 소환
    for (int32 ItemID : ItemIDs)
    {
        SpawnItem(ItemID, RandomLocation);
    }
}

void AItemSpawner::SpawnItem(int32 ItemID, const FVector& SpawnLocation)
{
    if (ItemDataTable == nullptr)
    {
        UE_LOG(LogTemp, Warning, TEXT("ItemDataTable이 설정되지 않음"));
        return;
    }

    // DataTable에서 해당 ID의 아이템 정보를 찾음
    FItemData* ItemData = ItemDataTable->FindRow<FItemData>(FName(*FString::FromInt(ItemID)), TEXT(""));
    if (ItemData)
    {
        // 아이템 정보 출력 (GEngine을 사용하여 화면에 출력)
        FString ItemInfo = FString::Printf(TEXT("아이템 이름: %s, 희귀도: %d"), *ItemData->Name, (int32)ItemData->Rarity);
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, ItemInfo);

        // 아이템 Actor를 생성
        AItemActor* NewItem = GetWorld()->SpawnActor<AItemActor>(AItemActor::StaticClass(), SpawnLocation, FRotator::ZeroRotator);
        if (NewItem)
        {
            // 아이템 데이터 설정
            NewItem->ItemID = ItemID;
            NewItem->ItemName = ItemData->Name;
            NewItem->Rarity = ItemData->Rarity;

            // 아이템 초기화 함수 호출 (필요한 경우)
            NewItem->InitializeItem(ItemData);

            UE_LOG(LogTemp, Log, TEXT("아이템 생성: %s, 희귀도: %d"), *ItemData->Name, (int32)ItemData->Rarity);
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("ID %d에 해당하는 아이템을 찾을 수 없음"), ItemID);
    }
}
