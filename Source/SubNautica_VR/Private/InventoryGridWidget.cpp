// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryGridWidget.h"
#include "PlayerCharacter.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Border.h"
#include "Components/CanvasPanel.h"
#include "AC_InventoryComponent.h"
#include "CanvasTypes.h"
#include "Layout/Geometry.h"
#include "Engine/Canvas.h"


//int32 UInventoryGridWidget::NativePaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
//{
//    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Native Paint"));
//
//    int32 NewLayerId = Super::NativePaint(Args, AllottedGeometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle, bParentEnabled);
//    for (const FInventoryLineStruct& Line : LineData)
//    {
//        // GridBorder의 캐시된 Geometry 가져오기
//        const FGeometry& GridBorderGeometry = GridBorder->GetCachedGeometry();
//        //FVector2D LocalTopLeft = GridBorderGeometry.GetLocalTopLeft();
//
//        // 시작점(A)와 끝점(B) 계산
//        FVector2D TempStart = /*LocalTopLeft +*/ Line.Start; // POSITION A
//        FVector2D TempEnd = /*LocalTopLeft +*/ Line.End;     // POSITION B
//
//        // 선을 그리기 위한 점 배열 생성
//        TArray<FVector2D> Points;
//        Points.Add(TempStart); // 시작점
//        Points.Add(TempEnd);   // 끝점
//
//        // Slate로 선 그리기
//        FSlateDrawElement::MakeLines(
//            OutDrawElements,
//            NewLayerId + 1,
//            GridBorderGeometry.ToPaintGeometry(), // GridBorder 기준으로 변경
//            Points,
//            ESlateDrawEffect::None,
//            FLinearColor::White,
//            true,
//            2.0f
//        );
//    }
//
//    return NewLayerId + 1; // 사용된 최고 레이어 ID 반환
//}
//
//void UInventoryGridWidget::InitializeInventory(UAC_InventoryComponent* Inventory, float InventoryTileSize)
//{
//    InventoryComp = Inventory;
//    TileSize = InventoryTileSize;
//
//    if (!GridBorder)
//    {
//        UE_LOG(LogTemp, Warning, TEXT("GridBorder is not set in UInventoryGridWidget"));
//        return;
//    }
//
//    if (UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(GridBorder->Slot))
//    {
//        CanvasSlot->SetPosition(FVector2D(100.f, 100.f));
//        CanvasSlot->SetSize(FVector2D(Inventory->Columns * TileSize, Inventory->Rows * TileSize));
//        CanvasSlot->SetAnchors(FAnchors(0.0f, 0.0f));
//        CanvasSlot->SetAutoSize(false);
//        CreateLineSegments();
//    }
//    else
//    {
//        UE_LOG(LogTemp, Warning, TEXT("GridBorder is not inside a CanvasPanel!"));
//    }
//}
//
//void UInventoryGridWidget::CreateLineSegments()
//{
//    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("CreateLineSegment"));
//    for (int32 i = 0; i < static_cast<int>(InventoryComp->Columns); i++) {
//        X = TileSize * i; 
//        FInventoryLineStruct NewLine;
//
//        NewLine.Start = FVector2D(X, 0);
//        NewLine.End = FVector2D(X, InventoryComp->Rows * TileSize); 
//
//        LineData.Add(NewLine);
//    }
//
//    for (int32 i = 0; i < static_cast<int>(InventoryComp->Rows); i++) {
//        Y = TileSize * i;
//        FInventoryLineStruct NewLine;
//
//        NewLine.Start = FVector2D(0, Y);
//        NewLine.End = FVector2D(InventoryComp->Columns * TileSize, Y);
//
//        LineData.Add(NewLine);
//    }
//}
//
