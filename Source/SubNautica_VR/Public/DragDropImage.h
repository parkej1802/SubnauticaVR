// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Border.h"
#include "ItemData.h"
#include "Layout/Geometry.h"
#include "Input/Events.h"
#include "DragDropImage.generated.h"

/**
 * 
 */
UCLASS()
class SUBNAUTICA_VR_API UDragDropImage : public UUserWidget
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

	void SetTile();
};
