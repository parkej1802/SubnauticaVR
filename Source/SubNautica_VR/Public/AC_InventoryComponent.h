// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ItemData.h"
#include "AC_InventoryComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SUBNAUTICA_VR_API UAC_InventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAC_InventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void SetupInputBinding(class UEnhancedInputComponent* Input);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class APlayerCharacter* PlayerCharacter;
	class APlayerController* pc;

// Widget
public:
	UPROPERTY(EditAnywhere, Category = MainWidget)
	TSubclassOf<UUserWidget> InventoryWidget;

	class UInventoryWidget* InventoryMainUI;

// Input
public:
	bool bIsInventoryMode = false;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	class UInputAction* IA_InventoryMode;

	void ShowInventory();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Columns = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Rows = 0.f;

	TMap<int32, FItemData> ItemStruct;
};
