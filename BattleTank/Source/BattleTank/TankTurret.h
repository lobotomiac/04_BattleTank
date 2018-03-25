// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent), hidecategories = (Cooking, ComponentReplication, Lighting, Rendering, Physics, HLOD, Mobile))
class BATTLETANK_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()
	

public: 
	// turret rotation function
	void RotateTurret(float AimDirection);

private:
	//  Max speed of turret rotation duh? :P
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float MaxTurretRotation = 25.0;
	
};
