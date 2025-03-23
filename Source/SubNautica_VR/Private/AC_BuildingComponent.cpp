// Fill out your copyright notice in the Description page of Project Settings.


#include "AC_BuildingComponent.h"
#include "Engine/DataTable.h"
#include "../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/InputAction.h"
#include "../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h"
#include "../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedPlayerInput.h"
#include "Camera/CameraComponent.h"
#include "PlayerCharacter.h"

// Sets default values for this component's properties
UAC_BuildingComponent::UAC_BuildingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	ConstructorHelpers::FObjectFinder<UInputAction>TempIA_BuildMode(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/IA_BuildMode.IA_BuildMode'"));
	if (TempIA_BuildMode.Succeeded()) 
	{
		IA_BuildMode = TempIA_BuildMode.Object;
	}

	ConstructorHelpers::FObjectFinder<UInputAction>TempIA_SpawnBuilding(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/IA_SpawnBuilding.IA_SpawnBuilding'"));
	if (TempIA_SpawnBuilding.Succeeded())
	{
		IA_SpawnBuilding = TempIA_SpawnBuilding.Object;
	}

	FString DataTablePath = TEXT("/Script/Engine.DataTable'/Game/UP/BuildingComponent/DT_Building.DT_Building'");
	BuildableDT = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, *DataTablePath));
}

// Called when the game starts
void UAC_BuildingComponent::BeginPlay()
{
	Super::BeginPlay();

	AActor* OwnerActor = GetOwner();

	if (APlayerController* PlayerController = GetOwner()->GetInstigatorController<APlayerController>())
	{
		UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent);
		if (EnhancedInputComponent)
		{
			SetupInputBinding(EnhancedInputComponent);
		}
	}


	if (OwnerActor)
	{
		PlayerCharacter = Cast<APlayerCharacter>(OwnerActor);
	}

	GetDataTableRowNames();
	
}

// Called every frame
void UAC_BuildingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

}

void UAC_BuildingComponent::SetupInputBinding(class UEnhancedInputComponent* Input)
{
	Input->BindAction(IA_BuildMode, ETriggerEvent::Started, this, &UAC_BuildingComponent::LaunchBuildMode);
	Input->BindAction(IA_SpawnBuilding, ETriggerEvent::Started, this, &UAC_BuildingComponent::SpawnBuild);
}

void UAC_BuildingComponent::SetBuildTransform(FTransform* BT)
{
	BuildTransform = *BT;
}

void UAC_BuildingComponent::BuildDelay(/*FName BuildingName*/)
{
	if (IsBuildMode)
	{
		FTimerHandle TH_DelayManager;
		FTimerDelegate TimerDelegate;
		TimerDelegate.BindLambda([this]() {
			OnBuildCycle.ExecuteIfBound();
			});

		GetWorld()->GetTimerManager().SetTimer(TH_DelayManager, TimerDelegate, 0.01f, false);
	}
}

void UAC_BuildingComponent::SpawnBuildGhost(/*FName BuildingName*/)
{
	if (PlayerCharacter)
	{
		UStaticMeshComponent* NewBuildGhost = Cast<UStaticMeshComponent>(
			PlayerCharacter->AddComponentByClass(UStaticMeshComponent::StaticClass(), false, BuildTransform, false));

		if (NewBuildGhost)
		{
			BuildGhost = NewBuildGhost;

			FBuildingStruct& BuildingData = BuildableDataArray[0];

			UStaticMesh* MeshAsset = BuildingData.Mesh;

			if (MeshAsset)
			{
				BuildGhost->SetStaticMesh(MeshAsset);
				BuildGhost->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			}
			else
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Failed BuildGhost"));
			}
		}
	}
}

void UAC_BuildingComponent::BuildCycle(/*FName BuildingName*/)
{
	FVector CameraLocation = PlayerCharacter->VRCamera->GetComponentLocation();
	FVector CameraForwardVector = PlayerCharacter->VRCamera->GetForwardVector();

	FVector StartLocation = CameraForwardVector * 350 + CameraLocation;
	FVector EndLocation = CameraForwardVector * 1000 + CameraLocation;

	FHitResult HitResult;

	FCollisionQueryParams CollisionParams;

	AActor* OwnerActor = GetOwner();
	if (OwnerActor)
	{
		CollisionParams.AddIgnoredActor(OwnerActor);
	}

	FBuildingStruct& BuildingData = BuildableDataArray[0];
	TEnumAsByte<ETraceTypeQuery> TraceInfo = BuildingData.TraceType;

	ECollisionChannel CollisionChannel = UEngineTypes::ConvertToCollisionChannel(BuildingData.TraceType);

	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, CollisionChannel, CollisionParams);

	FRotator Rotation = BuildTransform.GetRotation().Rotator();
	FVector Scale = BuildTransform.GetScale3D();

	if (bHit)
	{
		FVector ImpactLocation = HitResult.ImpactPoint;
		FTransform SetTransform = FTransform(Rotation, ImpactLocation, Scale);
		HitActor = HitResult.GetActor();
		HitComponent = HitResult.GetComponent();

		/*
		if (HitComponent)
		{
			FString ComponentName = HitComponent->GetName();
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("HitComponent Name: %s"), *ComponentName));
			}
		}
		*/

		SetBuildTransform(&SetTransform);

		if (BuildGhost != nullptr) {
			FBuildDetectResult DetectResult = DetectBuildBox();
			if (DetectResult.Found) {
				FTransform bTransform = DetectResult.BuildTransform;
				BuildTransform = bTransform;
				//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Snapping Success!!"));
			}

			GiveBuildColor(true);
			//BuildDelay();
		}
	}
	else {
		FVector TraceEnd = HitResult.TraceEnd;
		FTransform SetTransform = FTransform(Rotation, TraceEnd, Scale);
		SetBuildTransform(&SetTransform);

		if (BuildGhost != nullptr) {
			GiveBuildColor(false);
		}
	}

	BuildDelay(/*BuildingName*/);
}

void UAC_BuildingComponent::GiveBuildColor(bool isGreen)
{
	CanBuild = isGreen;

	int32 NumMaterial = BuildGhost->GetNumMaterials();

	for (int32 i = 0; i < NumMaterial; i++) {
		if (isGreen) {
			UMaterial* GreenMaterial = LoadObject<UMaterial>(nullptr, TEXT("/Script/Engine.Material'/Game/UP/BuildingComponent/BuildAsset/Material/GreenColor.GreenColor'"));
			if (GreenMaterial)
			{
				BuildGhost->SetMaterial(i, GreenMaterial);
			}
		}
		else {
			UMaterial* RedMaterial = LoadObject<UMaterial>(nullptr, TEXT("/Script/Engine.Material'/Game/UP/BuildingComponent/BuildAsset/Material/RedColor.RedColor'"));
			if (RedMaterial)
			{
				BuildGhost->SetMaterial(i, RedMaterial);
			}
		}
	}
	BuildGhost->SetWorldTransform(BuildTransform);
}

void UAC_BuildingComponent::LaunchBuildMode(/*FName BuildingName*/)
{
	if (!IsBuildMode) {
		IsBuildMode = true;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("B Pressed"));
		SpawnBuildGhost();
		OnBuildCycle.BindUObject(this, &UAC_BuildingComponent::BuildCycle);
		BuildCycle();
	}
	else {
		IsBuildMode = false;
		StopBuildMode();
	}
}

void UAC_BuildingComponent::StopBuildMode()
{
	CanBuild = false;
	IsBuildMode = false;

	if (BuildGhost != nullptr) {
		BuildGhost->DestroyComponent();
		BuildGhost = nullptr;
	}
}

void UAC_BuildingComponent::GetDataTableRowNames()
{
	if (BuildableDT)
	{
		TArray<FName> RowNames = BuildableDT->GetRowNames();

		for (FName& RowName : RowNames)
		{
			FBuildingStruct* RowData = BuildableDT->FindRow<FBuildingStruct>(RowName, TEXT("Context"));
			if (RowData)
			{
				BuildableDataArray.Add(*RowData);
				BuildableDataMap.Add(RowName, *RowData);
			}
		}
	}
}

void UAC_BuildingComponent::ChangeMesh()
{

}

void UAC_BuildingComponent::SpawnBuild(/*FName BuildingName*/)
{
	if (IsBuildMode && CanBuild) {

		FBuildingStruct& BuildingData = BuildableDataArray[0];

		TSubclassOf<AActor> BuildingActor = BuildingData.Actor;

		AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(BuildingActor, BuildTransform);
	}
}

void UAC_BuildingComponent::DestroyBuild()
{

}

void UAC_BuildingComponent::RotateRight()
{
	FQuat NewRotation = FQuat(FRotator(0.0f, 90.0f * GetWorld()->GetDeltaSeconds(), 0.0f));

	BuildTransform.SetRotation(BuildTransform.GetRotation() * NewRotation);

	BuildGhost->SetWorldTransform(BuildTransform);
}

void UAC_BuildingComponent::RotateLeft()
{
	FQuat NewRotation = FQuat(FRotator(0.0f, -90.0f * GetWorld()->GetDeltaSeconds(), 0.0f));

	BuildTransform.SetRotation(BuildTransform.GetRotation() * NewRotation);

	BuildGhost->SetWorldTransform(BuildTransform);
}

FBuildDetectResult UAC_BuildingComponent::DetectBuildBox()
{
	FBuildDetectResult Result;
	Result.Found = false;

	if (HitActor && HitActor->Implements<UBuilding_Interface>())
	{
		IBuilding_Interface* BuildActor = Cast<IBuilding_Interface>(HitActor);

		if (BuildActor)
		{

			//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("BuildActor Valid!!!"));

			TArray<UBoxComponent*> TraceCollision = IBuilding_Interface::Execute_GetBoxCollision(HitActor);

			for (UBoxComponent* Box : TraceCollision)
			{
				//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("UBoxComponent Valid!!!"));
				/*if (Box)
				{
					FString BoxName = Box->GetName();
					GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, *BoxName);
				}*/

				if (Box == HitComponent)
				{
					Result.Found = true;
					Result.BuildTransform = HitComponent->GetComponentTransform();
					//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("BoxCollisionFound"));
					break;
				}
			}
		}
		else {
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("No BuildActor"));
		}
	}

	return Result;
}

