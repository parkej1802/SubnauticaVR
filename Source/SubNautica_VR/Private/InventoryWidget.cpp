// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryWidget.h"
#include "PlayerCharacter.h"
#include "AC_InventoryComponent.h"
#include "Components/GridPanel.h"
#include "InventoryGridWidget.h"
#include "InventoryTile.h"

//void UInventoryWidget::NativeOnInitialized()
//{
//	Super::NativeOnInitialized();
//
//	APlayerController* PlayerController = GetOwningPlayer();
//	if (PlayerController)
//	{
//		APawn* PlayerPawn = PlayerController->GetPawn();
//
//		PlayerCharacter = Cast<APlayerCharacter>(PlayerPawn);
//		InventoryComp = PlayerCharacter->InventoryComp;
//	}
//
//	if (!InventoryGridUI)
//	{
//		UE_LOG(LogTemp, Warning, TEXT("InventoryGridUI is null!"));
//		return;
//	}
//
//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("NativeOnInitialized Working"));
//	InventoryGridUI->InitializeInventory(InventoryComp, TileSize);
//}

void UInventoryWidget::SetGrid()
{
	APlayerController* PlayerController = GetOwningPlayer();
	if (PlayerController)
	{
		APawn* PlayerPawn = PlayerController->GetPawn();

		PlayerCharacter = Cast<APlayerCharacter>(PlayerPawn);
		InventoryComp = PlayerCharacter->InventoryComp;
		ItemStruct = InventoryComp->ItemStruct;
	}

	GridPanel->ClearChildren();

	for (int32 i = 0; i <= 15; i++) {
		if (InventoryTileWidget)
		{
			InventoryTileUI = CreateWidget<UInventoryTile>(GetWorld(), InventoryTileWidget);
			InventoryTileUI->Item = ItemStruct[i];
			InventoryTileUI->Index = i; //ItemStruct[i].Index;
			GridPanel->AddChildToGrid(InventoryTileUI, i / 4, i % 4);
		}
	}
}
