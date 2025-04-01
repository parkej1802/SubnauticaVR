// Fill out your copyright notice in the Description page of Project Settings.


#include "AC_InventoryComponent.h"
#include "../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/InputAction.h"
#include "../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h"
#include "../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedPlayerInput.h"
#include "InventoryWidget.h"
#include "PlayerCharacter.h"
#include "GameFramework/PlayerController.h"
#include "Components/WidgetComponent.h"

// Sets default values for this component's properties
UAC_InventoryComponent::UAC_InventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	ConstructorHelpers::FObjectFinder<UInputAction>TempIA_InventoryMode(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/IA_InventoryMode.IA_InventoryMode'"));
	if (TempIA_InventoryMode.Succeeded())
	{
		IA_InventoryMode = TempIA_InventoryMode.Object;
	}
}


// Called when the game starts
void UAC_InventoryComponent::BeginPlay()
{
	Super::BeginPlay();
		
	AActor* OwnerActor = GetOwner();

	if ((pc = OwnerActor->GetInstigatorController<APlayerController>()) != nullptr)
	{
		UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(pc->InputComponent);
		if (EnhancedInputComponent)
		{
			SetupInputBinding(EnhancedInputComponent);
		}
	}

	if (OwnerActor)
	{
		PlayerCharacter = Cast<APlayerCharacter>(OwnerActor);
	}
	
	for (int32 i = 0; i < 16; i++)
	{
		ItemStruct.Add(i, FItemData());
	}
}

// Called every frame
void UAC_InventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


void UAC_InventoryComponent::SetupInputBinding(class UEnhancedInputComponent* Input)
{
	Input->BindAction(IA_InventoryMode, ETriggerEvent::Started, this, &UAC_InventoryComponent::ShowInventory);
}


void UAC_InventoryComponent::ShowInventory()
{

	if (!bIsInventoryMode) {
		bIsInventoryMode = true;
		if (InventoryWidget)
		{
			InventoryMainUI = CreateWidget<UInventoryWidget>(GetWorld(), InventoryWidget);
			InventoryMainUI->SetGrid();
			PlayerCharacter->InventoryUI->SetWidget(InventoryMainUI);
			PlayerCharacter->InventoryUI->SetVisibility(true);
			PlayerCharacter->RestorePercentWidget->SetVisibility(false);
		}
		if (InventoryMainUI)
		{
			//InventoryMainUI->AddToViewport();
		}
		FInputModeGameAndUI UIInputMode;
		pc->SetInputMode(UIInputMode);
		pc->bShowMouseCursor = true;
	}
	else {
		bIsInventoryMode = false;
		if (InventoryMainUI)
		{
			InventoryMainUI->RemoveFromParent();
			PlayerCharacter->InventoryUI->SetVisibility(false);
			PlayerCharacter->RestorePercentWidget->SetVisibility(true);
		}
		FInputModeGameOnly GameInputMode;
		pc->SetInputMode(GameInputMode);
		pc->bShowMouseCursor = false;
	}
}

