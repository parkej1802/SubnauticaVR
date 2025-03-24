// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "ItemData.h"
#include "ItemManager.generated.h"

UCLASS()
class SUBNAUTICA_VR_API UItemManager : public UObject
{
    GENERATED_BODY()

public:
    // 아이템 데이터 테이블
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
    UDataTable* ItemDataTable;

    // 특정 ID로 아이템 데이터 가져오기
    const FItemData* GetItemDataByID(int32 ItemID);
};
