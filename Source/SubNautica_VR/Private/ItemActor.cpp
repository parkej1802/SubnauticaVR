#include "ItemActor.h"
#include "ItemData.h"
#include "Engine/Engine.h"

AItemActor::AItemActor()
{
    PrimaryActorTick.bCanEverTick = false;
}

void AItemActor::BeginPlay()
{
    Super::BeginPlay();
    LoadItemData();
}

void AItemActor::LoadItemData()
{
    if (ItemDataTable == nullptr)
    {
        UE_LOG(LogTemp, Warning, TEXT("ItemDataTable이 설정되지 않음"));
        return;
    }

    // DataTable에서 해당 ID의 행을 찾음
    FItemData* ItemData = ItemDataTable->FindRow<FItemData>(FName(*FString::FromInt(ItemID)), TEXT(""));
    if (ItemData)
    {
        ItemName = ItemData->Name;
        Rarity = ItemData->Rarity;
        UE_LOG(LogTemp, Log, TEXT("아이템 로드: %s, 희귀도: %d"), *ItemName, (int32)Rarity);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("ID %d에 해당하는 아이템을 찾을 수 없음"), ItemID);
    }
}

#if WITH_EDITOR
void AItemActor::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
    Super::PostEditChangeProperty(PropertyChangedEvent);

    // 에디터에서 ID 변경 시 자동으로 LoadItemData 실행
    LoadItemData();
}
#endif

void AItemActor::InitializeItem(FItemData* ItemData)
{
    if (ItemData)
    {
        // 아이템 데이터로 Actor 초기화 (예: 아이템 이름, 희귀도, 모델 등 설정)
        this->ItemName = ItemData->Name;
        this->Rarity = ItemData->Rarity;

        // 아이템에 대한 추가 설정을 할 수 있습니다.
        // 예: 모델 설정, 특성 등
    }
}