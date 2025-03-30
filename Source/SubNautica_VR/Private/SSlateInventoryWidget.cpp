// Fill out your copyright notice in the Description page of Project Settings.


#include "SSlateInventoryWidget.h"
#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

#define LOCTEXT_NAMESPACE "MySlateInventoryWidget"

void SSlateInventoryWidget::Construct(const FArguments& InArgs)
{
	const FMargin ContentPadding = FMargin(500.f, 300.f);

	const FText TitleText = LOCTEXT("GameTitle", "My Super Greate Game");

	ChildSlot
		[
			SNew(SOverlay)
			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
				[
					SNew(SImage)
						.ColorAndOpacity(FColor::Black)
				]
			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(ContentPadding)
			[
				SNew(SVerticalBox)
				+ SVerticalBox::Slot()
				[
					SNew(STextBlock)
					.Text(TitleText)
				]
			]
		];
}

#undef LOCTEXT_NAMESPACE
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

