// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()

public:
	// amount of movement depending on the throw of the analog/mushroom key on controllers 
	UFUNCTION(BlueprintCallable, Category = Movement)
	void IntendMoveForward(float Throw);
	
	
};
