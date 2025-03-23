#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"  // DataTable 사용
#include "ItemData.h"          // FItemData 포함
#include "ItemActor.generated.h"


UCLASS()
class SUBNAUTICA_VR_API AItemActor : public AActor
{
    GENERATED_BODY()
    
public:    
    AItemActor();

protected:
    virtual void BeginPlay() override;

#if WITH_EDITOR
    virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif


public:
    /** 아이템 ID (에디터에서 입력) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    int32 ItemID;

    /** 데이터 테이블 레퍼런스 */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    UDataTable* ItemDataTable;

    /** 아이템 이름 */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item")
    FString ItemName;

    /** 아이템 희귀도 */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item")
    EItemRarity Rarity;

    /** 데이터 테이블에서 아이템 정보를 불러오는 함수 */
    void LoadItemData();

    void InitializeItem(FItemData* ItemData);
};
