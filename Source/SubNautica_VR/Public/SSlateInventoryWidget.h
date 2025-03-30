// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "UObject/WeakObjectPtrTemplates.h"

/**
 * 
 */
class SUBNAUTICA_VR_API SSlateInventoryWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SSlateInventoryWidget)
	{}
	SLATE_ARGUMENT(TWeakObjectPtr<class AInventoryHUD>, OwningHUD)
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	TWeakObjectPtr<class AInventoryHUD> OwningHUD;

	virtual bool SupportsKeyboardFocus() const override { return true; }
};

