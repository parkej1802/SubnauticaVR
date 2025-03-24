// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerStatUI.h"
#include "PlayerCharacter.h"

void UPlayerStatUI::NativeConstruct()
{
	Super::NativeConstruct();

	APlayerController* PlayerController = GetOwningPlayer();
	if (PlayerController)
	{
		APawn* PlayerPawn = PlayerController->GetPawn();

		PlayerCharacter = Cast<APlayerCharacter>(PlayerPawn);
	}
}

void UPlayerStatUI::NativeTick(const FGeometry& MyGeometry, float DeltaTime)
{
	Super::NativeTick(MyGeometry, DeltaTime);
	UpdatePlayerOxygen();
}

void UPlayerStatUI::UpdatePlayerOxygen()
{
	PlayerOxygen_ProgressBar->SetPercent((float)PlayerCharacter->CurrentOxygen / (float)PlayerCharacter->MaxOxygen);
	PlayerOxygen_TextNum->SetText(FText::AsNumber(PlayerCharacter->CurrentOxygen));
}
