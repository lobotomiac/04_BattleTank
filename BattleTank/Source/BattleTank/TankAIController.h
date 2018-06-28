// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class UTankAimingComponent;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
private:
	virtual void BeginPlay() override;

	virtual void Tick(float) override;
	// how close can the AI tank get before stopping movement
	float AcceptanceRadius = 30.0f;

	APawn* PlayerTank = nullptr;
	APawn* ControlledTank = nullptr;

public:
	UTankAimingComponent* AIAimingComponent = nullptr;

};
