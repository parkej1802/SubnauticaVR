// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DT_BuildingComponent.h"
#include "Building_Interface.h"
#include "AC_BuildingComponent.generated.h"

DECLARE_DELEGATE(FOnBuildCycleDelegate)

USTRUCT(BlueprintType)
struct FBuildDetectResult
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "SnapDetect")
	bool Found;

	UPROPERTY(BlueprintReadWrite, Category = "SnapDetect")
	FTransform BuildTransform;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SUBNAUTICA_VR_API UAC_BuildingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAC_BuildingComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetupInputBinding(class UEnhancedInputComponent* Input);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BuildingSystem)
	class UCameraComponent* CameraBS;

	void SetCameraBS(UCameraComponent* NewCamera);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BuildingSystem)
	class UStaticMeshComponent* BuildGhost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BuildingSystem)
	bool IsBuildMode = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BuildingSystem)
	bool CanBuild = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BuildingSystem)
	int BuildID = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BuildingSystem)
	FTransform BuildTransform;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	class UDataTable* BuildableDT;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Data)
    TArray<FBuildingStruct> BuildableDataArray;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Data)
	TMap<FName, FBuildingStruct> BuildableDataMap;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Data)
	AActor* HitActor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Data)

	class UPrimitiveComponent* HitComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class APlayerCharacter* PlayerCharacter;

// Input
public:
	UPROPERTY(EditDefaultsOnly, Category = Input)
	class UInputAction* IA_BuildMode;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	class UInputAction* IA_SpawnBuilding;



// Delegate
public:
	FOnBuildCycleDelegate OnBuildCycle;
	
public:
	void SetBuildTransform(FTransform* BT);
	void BuildDelay(/*FName BuildingName*/);
	void SpawnBuildGhost(/*FName BuildingName*/);
	void BuildCycle(/*FName BuildingName*/);
	void GiveBuildColor(bool isGreen);
	void LaunchBuildMode(/*FName BuildingName*/);
	void StopBuildMode();
	void GetDataTableRowNames();
	void ChangeMesh();
	void SpawnBuild(/*FName BuildingName*/);
	void DestroyBuild();
	void RotateRight();
	void RotateLeft();
	bool IsIngredientsEnough(/*FName BuildingName*/);
	FBuildDetectResult DetectBuildBox();

};
