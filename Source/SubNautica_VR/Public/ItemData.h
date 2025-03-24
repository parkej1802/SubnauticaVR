#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ItemData.generated.h"

UENUM(BlueprintType)
enum class EItemType : uint8
{
    Resource UMETA(DisplayName = "Resource"),
    Tool UMETA(DisplayName = "Tool")
};

UENUM(BlueprintType)
enum class EItemRarity : uint8
{
    Common UMETA(DisplayName = "Common"),
    Rare UMETA(DisplayName = "Rare"),
    VeryRare UMETA(DisplayName = "Very Rare")
};

USTRUCT(BlueprintType)
struct FItemData : public FTableRowBase
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    int32 ID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    FString Name;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    EItemType Type;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    FString Area;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    EItemRarity Rarity;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    FString RequiredEquipment;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    FString CraftingMaterials;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    FString Effects;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    FString Description;

    FItemData()
        : ID(0), Name(TEXT("")), Type(EItemType::Resource), Area(TEXT("")),
          Rarity(EItemRarity::Common), RequiredEquipment(TEXT("")),
          CraftingMaterials(TEXT("")), Effects(TEXT("")), Description(TEXT("")) {}
};
