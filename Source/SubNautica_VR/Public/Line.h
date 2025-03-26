// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Line.generated.h"

USTRUCT(BlueprintType)

struct FInventoryLineStruct : public FTableRowBase {

	GENERATED_BODY();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Line")
	FVector2D Start;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Line")
	FVector2D End;

};
