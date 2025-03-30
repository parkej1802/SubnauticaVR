// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemData.h"
#include "AC_InventoryComponent.h"
#include "InventoryWidget.generated.h"

/**
 * 
 */
UCLASS()
class SUBNAUTICA_VR_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	// virtual void NativeOnInitialized() override;

public:

	/*UPROPERTY()
	class APlayerCharacter* PlayerCharacter;

	UPROPERTY(EditDefaultsOnly, Category = InventorySystem)
	class UAC_InventoryComponent* InventoryComp;

	UPROPERTY(EditDefaultsOnly) 
	float TileSize = 50.f;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> InventoryGridWidget;

	UPROPERTY(meta = (BindWidget))
	class UInventoryGridWidget* InventoryGridUI;*/

	UPROPERTY()
	class APlayerCharacter* PlayerCharacter;

	UPROPERTY(EditDefaultsOnly, Category = InventorySystem)
	class UAC_InventoryComponent* InventoryComp;

	TMap<int32, FItemData> ItemStruct;

	void SetGrid();

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UGridPanel* GridPanel;

	UPROPERTY(EditAnywhere, Category = MainWidget)
	TSubclassOf<UUserWidget> InventoryTileWidget;

	class UInventoryTile* InventoryTileUI;
};
