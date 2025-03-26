// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AC_InventorySystem.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SUBNAUTICA_VR_API UAC_InventorySystem : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAC_InventorySystem();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	

	UPROPERTY(EditAnywhere)
	class APlayerCharacter* PlayerCharacter;

	void DetectPlayer();
	void TryAddItem(AActor* Actor);
	
	// FInventoryStruct ItemData;

	void IsItemAlreadyInInventory();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Inventory)
	// TArray<FInventoryStruct> ItemsInInventory;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Inventory)
	//TSubclassOf<UUserWidget> InventoryWidget;

	//class UInventoryUI* InventoryUI;

	void PickUpItem();
};
