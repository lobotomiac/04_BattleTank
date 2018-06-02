// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Engine/World.h"
#include "Tank.generated.h"

class UTankTurret;
class UTankBarrel; 
class AProjectile;
class UTankAimingComponent;	
class UTankMovementComponent;


UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

protected:
	// Called when the game starts or when spawned
	UPROPERTY(BlueprintReadOnly)
	UTankAimingComponent* TankAimingComponent = nullptr;
	
	UPROPERTY(BlueprintReadOnly)
	UTankMovementComponent* TankMovementComponent = nullptr;

public:	
	//	Called to aim at either crosshair(player) or player(AI)
	virtual void AimAt(FVector OutHitLocation) const;
	
	// starting value, overridable in blueprint / find reasonable value
	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float LaunchSpeed = 100000;	

	UFUNCTION(BlueprintCallable, Category = Firing)
	void Fire();

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY(BlueprintReadOnly)
	UTankBarrel* Barrel = nullptr;

	float ReloadTime = 3.0f;
	double LastFireTime = 0.0;
};
