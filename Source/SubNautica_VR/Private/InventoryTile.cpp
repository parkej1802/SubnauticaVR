// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryTile.h"
#include "PlayerCharacter.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "InventoryWidget.h"
#include "InventoryDD.h"

void UInventoryTile::NativeConstruct()
{
	Super::NativeConstruct();


	this->SetIsFocusable(true);
	this->SetVisibility(ESlateVisibility::Visible);
    SetTile();
	
}

FReply UInventoryTile::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
    FEventReply reply;

    reply.NativeReply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

    if (InMouseEvent.IsMouseButtonDown(FKey("LeftMouseButton")))
    {
        reply = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);
    }

    return reply.NativeReply;
}

//FReply UInventoryTile::OnMouseButtonDown(FGeometry MyGeometry, const FPointerEvent& MouseEvent)
//{
//    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("MouseButtonDown")));
//    FEventReply EventReply = UWidgetBlueprintLibrary::DetectDragIfPressed(MouseEvent, this, EKeys::LeftMouseButton);
//    return EventReply.NativeReply;
//}


void UInventoryTile::NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragCancelled(InDragDropEvent, InOperation);

	UWorld* World = GetWorld();
	if (!World)
	{
		return;
	}

	TArray<UUserWidget*> FoundWidgets;

	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(this, FoundWidgets, UInventoryWidget::StaticClass(), false);

	if (FoundWidgets.Num() > 0)
	{
		if (UInventoryWidget* InventoryWidget = Cast<UInventoryWidget>(FoundWidgets[0]))
		{
			InventoryWidget->SetGrid();
		}
	}
}


void UInventoryTile::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
    Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

    if (InventoryTileDDWidget) {
        InventoryTileDD = CreateWidget<UDragDropImage>(this, InventoryTileDDWidget);
        InventoryTileDD->Item = this->Item;
        InventoryTileDD->Index = this->Index;
    }
            
    if (Item.Quantity > 0) {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("MouseButtonDown ItemQuantity FOund")));
		Text_Name->SetText(FText::GetEmpty());
		ImageBorder->SetBrushFromTexture(nullptr);
		Text_Quantity->SetText(FText::GetEmpty());
        UInventoryDD* InventoryDD = NewObject<UInventoryDD>(this);
        if (InventoryDD)
        {
            // GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("iNVENTORYdd")));
            InventoryDD->Index = this->Index;
            InventoryDD->Item = this->Item;

            InventoryDD->DefaultDragVisual = InventoryTileDD;

            OutOperation = InventoryDD;
        }
    }
}


bool UInventoryTile::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
    Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

    UInventoryDD* InventoryDD = Cast<UInventoryDD>(InOperation);

    PlayerCharacter = Cast<APlayerCharacter>(GetOwningPlayerPawn());

    InventoryComp = PlayerCharacter->InventoryComp;

    if (this->Item.Quantity == 0)
    {
        InventoryComp->ItemStruct[InventoryDD->Index] = FItemData();

        InventoryComp->ItemStruct[this->Index] = InventoryDD->Item;
    }

    else if (InventoryDD->Item.Quantity > 0)
    {
        FItemData TempItem = this->Item;

        InventoryComp->ItemStruct[this->Index] = InventoryDD->Item;
        InventoryComp->ItemStruct[InventoryDD->Index] = TempItem;
    }

    if (UInventoryWidget* InventoryWidget = InventoryComp->InventoryMainUI)
    {
        InventoryWidget->SetGrid();
    }

    return true;
}

void UInventoryTile::SetTile()
{
    if (Item.Quantity == 0)
    {
        Text_Name->SetText(FText::GetEmpty());
        ImageBorder->SetBrushFromTexture(nullptr);
        Text_Quantity->SetText(FText::GetEmpty());
    }
    else
    {
        Text_Name->SetText(FText::FromName(Item.Name));
        ImageBorder->SetBrushFromTexture(Item.Thumbnail);
        Text_Quantity->SetText(FText::AsNumber(Item.Quantity));
    }
}

