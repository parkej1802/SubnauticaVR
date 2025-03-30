// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Item.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EItemRarityType : uint8
{
    Common     UMETA(DisplayName = "Common"),
    Rare       UMETA(DisplayName = "Rare"),
    VeryRare   UMETA(DisplayName = "Very Rare")
};

UCLASS()
class SUBNAUTICA_VR_API UItem : public UObject
{
	GENERATED_BODY()

public:
    UItem();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    int32 ItemID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    FName ItemName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    FText ItemDescription;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    EItemRarityType Rarity;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    TArray<FName> CraftingMaterials;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    FName Effect;
	
  
   
};
