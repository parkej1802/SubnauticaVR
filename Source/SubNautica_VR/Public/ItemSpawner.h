#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemSpawner.generated.h"

class AItemActor; // 전방 선언

UCLASS()
class SUBNAUTICA_VR_API AItemSpawner : public AActor
{
    GENERATED_BODY()
    
public:    
    AItemSpawner();

protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

    /** 스폰할 수 있는 아이템 클래스 목록 */
    UPROPERTY(EditAnywhere, Category = "Item Spawner")
    TArray<TSubclassOf<AItemActor>> SpawnableItemClasses;

    /** 스폰할 수 있는 위치 목록 */
    UPROPERTY(VisibleAnywhere, Category = "Item Spawner")
    TArray<AActor*> SpawnPoints;

    /** 현재 사용 중인 스폰 위치 */
    TSet<int32> UsedIndices;

    /** 현재 맵에 존재하는 아이템 개수 */
    int32 AllItemsInLevel = 0;

    /** 스폰 타이머 핸들 */
    FTimerHandle SpawnTimerHandle;

    /** 아이템을 스폰할 최소, 최대 시간 */
    UPROPERTY(EditAnywhere, Category = "Item Spawner")
    float MinTime = 5.0f;

    UPROPERTY(EditAnywhere, Category = "Item Spawner")
    float MaxTime = 10.0f;

    /** 아이템 스폰 포인트 찾기 */
    void FindSpawnPoints();

    /** 아이템을 스폰 */
    void CreateItem();

    /** 특정 위치에서 아이템을 스폰 */
    void SpawnItemAtLocation(int32 Index);

    /** 특정 위치를 비활성화 */
    void FreeSpawnPoint(int32 Index);
};
