#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"  // DataTable 사용
#include "ItemData.h"          // FItemData 포함
#include "ItemActor.h"         // AItemActor 포함
#include "ItemSpawner.generated.h"

UCLASS()
class SUBNAUTICA_VR_API AItemSpawner : public AActor
{
    GENERATED_BODY()

public:    
    AItemSpawner();

protected:
    virtual void BeginPlay() override;

public:
    //아이템 스폰할 범위
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
    FVector SpawnAreaMin;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
    FVector SpawnAreaMax;

    //스폰할 아이템 데이터 테이블
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
    UDataTable* ItemDataTable;

    //스폰할 아이템 ID 목록
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
    TArray<int32> ItemIDs;

    //아이템 소환 함수
    void SpawnItemAtRandomLocation();

private:
    //아이템을 생성하는 함수
    void SpawnItem(int32 ItemID, const FVector& SpawnLocation);
};
