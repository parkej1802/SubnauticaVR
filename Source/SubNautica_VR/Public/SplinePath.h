#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SplineComponent.h"
#include "SplinePath.generated.h"

UCLASS()
class SUBNAUTICA_VR_API ASplinePath : public AActor
{
	GENERATED_BODY()

public:
	ASplinePath();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USplineComponent* SplineComponent;
};
