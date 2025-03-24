// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "PlayerStatUI.generated.h"

/**
 * 
 */
UCLASS()
class SUBNAUTICA_VR_API UPlayerStatUI : public UUserWidget
{
	GENERATED_BODY()
	
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float DeltaTime) override;

	UPROPERTY()
	class APlayerCharacter* PlayerCharacter;

	UPROPERTY(EditAnywhere, meta = (BindWidget))

	class UProgressBar* PlayerOxygen_ProgressBar;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* PlayerOxygen_TextNum;

	void UpdatePlayerOxygen();
};

