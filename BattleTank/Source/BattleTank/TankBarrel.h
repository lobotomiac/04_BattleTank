 // Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent), hidecategories = (Cooking, ComponentReplication, Lighting, Rendering, Physics, HLOD, Mobile))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	// elevates the barrel by % of MaxBarrelElevationChangeSpeed 
	void ElevateBarrel(float RelativeChangeSpeed);

private:
	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxBarrelElevationChangeSpeed = 10;	
	
	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxElevation	= 30.0;

	UPROPERTY(EditAnywhere, Category = Setup)
	float MinElevation = 0;

};
