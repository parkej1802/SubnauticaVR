// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Line.h"
#include "InventoryGridWidget.generated.h"

/**
 * 
 */
UCLASS()
class SUBNAUTICA_VR_API UInventoryGridWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	// virtual int32 NativePaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;

public:

	/*UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class APlayerCharacter* PlayerCharacter;

	UPROPERTY(EditDefaultsOnly, Category = InventorySystem)
	class UAC_InventoryComponent* InventoryComp;

	void InitializeInventory(class UAC_InventoryComponent* Inventory, float InventoryTileSize);
	void CreateLineSegments();

	float TileSize = 50.f;

	UPROPERTY(meta = (BindWidget))
	class UBorder* GridBorder;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UCanvasPanel* GridCanvasPanel;

	float X = 0.f;
	float Y = 0.f;

	TArray<FInventoryLineStruct> LineData;*/

};
