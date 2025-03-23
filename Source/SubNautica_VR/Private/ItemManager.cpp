#include "ItemManager.h"
#include "Engine/DataTable.h"

const FItemData* UItemManager::GetItemDataByID(int32 ItemID)
{
    if (!ItemDataTable) return nullptr;

    // 데이터 테이블의 모든 Row 가져오기
    static const FString ContextString(TEXT("Item Lookup"));
    TArray<FItemData*> AllRows;
    ItemDataTable->GetAllRows<FItemData>(ContextString, AllRows);

    // ID와 일치하는 데이터 찾기
    for (FItemData* Row : AllRows)
    {
        if (Row->ID == ItemID)
        {
            return Row;
        }
    }

    return nullptr; // 해당 ID가 없으면 nullptr 반환
}
