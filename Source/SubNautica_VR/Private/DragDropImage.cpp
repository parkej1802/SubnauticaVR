// Fill out your copyright notice in the Description page of Project Settings.


#include "DragDropImage.h"

void UDragDropImage::NativeConstruct()
{
    Super::NativeConstruct();

    SetTile();
}

void UDragDropImage::SetTile()
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
