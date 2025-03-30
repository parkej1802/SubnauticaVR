// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "InventoryHUD.generated.h"

/**
 * 
 */
UCLASS()
class SUBNAUTICA_VR_API AInventoryHUD : public AHUD
{
	GENERATED_BODY()

protected:
	TSharedPtr<class SSlateInventoryWidget> InventoryWidget;
	TSharedPtr<class SWidget> InventoryWidgetContainer;
	
	virtual void BeginPlay() override;

};
