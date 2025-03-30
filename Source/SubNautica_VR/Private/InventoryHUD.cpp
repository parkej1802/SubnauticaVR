// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryHUD.h"
#include "SSlateInventoryWidget.h"
#include "Widgets/SWeakWidget.h"
#include "Engine/Engine.h"

void AInventoryHUD::BeginPlay()
{
	Super::BeginPlay();

	if (GEngine && GEngine->GameViewport)
	{
		InventoryWidget = SNew(SSlateInventoryWidget).OwningHUD(this);
		GEngine->GameViewport->AddViewportWidgetContent(SAssignNew(InventoryWidgetContainer, SWeakWidget).PossiblyNullContent(InventoryWidget.ToSharedRef()));
	}
}
