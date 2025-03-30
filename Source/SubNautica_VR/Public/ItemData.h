#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Engine/Texture2D.h"
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
    FName Name;

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

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    class UStaticMesh* Mesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    int32 Quantity;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    bool Stackable;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    UTexture2D* Thumbnail;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    int32 Index;

    FItemData()
        : ID(0)
        , Name(FName(TEXT("None")))
        , Type(EItemType::Resource)
        , Area(TEXT(""))
        , Rarity(EItemRarity::Common)
        , RequiredEquipment(TEXT(""))
        , CraftingMaterials(TEXT(""))
        , Effects(TEXT(""))
        , Description(TEXT(""))
        , Mesh(nullptr)
        , Quantity(0)
        , Stackable(false)
        , Thumbnail(nullptr)
        , Index(-1)
    {
    }
	/* FItemData()
		 : ID(0), Name(TEXT("")), Type(EItemType::Resource), Area(TEXT("")),
		   Rarity(EItemRarity::Common), RequiredEquipment(TEXT("")),
		   CraftingMaterials(TEXT("")), Effects(TEXT("")), Description(TEXT("")) {}*/
};
