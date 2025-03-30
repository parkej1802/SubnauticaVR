// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Border.h"
#include "ItemData.h"
#include "Layout/Geometry.h"
#include "Input/Events.h"
#include "Blueprint/DragDropOperation.h"
#include "DragDropImage.h"
#include "InventoryWidget.h"
#include "InventoryTile.generated.h"

/**
 * 
 */
UCLASS()
class SUBNAUTICA_VR_API UInventoryTile : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"))
	class UAC_InventoryComponent* InventoryComp;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* Text_Quantity;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* Text_Name;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UBorder* ImageBorder;

	UPROPERTY(EditAnywhere)
	int32 Index = 0;

	UPROPERTY(EditAnywhere)
	class APlayerCharacter* PlayerCharacter;

	FItemData Item;

	UPROPERTY(EditAnywhere, Category = MainWidget)
	TSubclassOf<UUserWidget> InventoryTileDDWidget;

	class UDragDropImage* InventoryTileDD;


	void SetTile();

	bool bIsDragging = false;

	//virtual FReply OnMouseMove(FGeometry MyGeometry, const FPointerEvent& MouseEvent);

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	//virtual FReply OnMouseButtonUp(FGeometry MyGeometry, const FPointerEvent& MouseEvent);

	// virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
};
