// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tile.generated.h"

USTRUCT(BlueprintType)

struct FInventoryTileStruct : public FTableRowBase {

	GENERATED_BODY();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile")
	int32 X;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile")
	int32 Y;

};
