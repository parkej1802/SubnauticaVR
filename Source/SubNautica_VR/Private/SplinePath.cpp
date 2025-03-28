#include "SplinePath.h"
#include "Components/SplineComponent.h"

ASplinePath::ASplinePath()
{
	PrimaryActorTick.bCanEverTick = false;

	SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("SplineComponent"));
	RootComponent = SplineComponent;
}
