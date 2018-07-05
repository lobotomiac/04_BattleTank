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

protected: 
	// how close can the AI tank get before stopping movement
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float AcceptanceRadius = 3000.0f;

private:
	virtual void BeginPlay() override;
	virtual void Tick(float) override;
	virtual void SetPawn(APawn* InPawn) override;

	UFUNCTION()
	void OnPossessedTankDeath();

public:
	UTankAimingComponent* AIAimingComponent = nullptr;
	
	
};
