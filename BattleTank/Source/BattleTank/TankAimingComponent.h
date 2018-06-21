// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringStatus : uint8
{
	Reloading,
	Locked,
	Aiming
};

// forward declaration
class UTankBarrel; 
class UTankTurret;

// holds barrel, turret reference 
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

public:	
	
	UFUNCTION(BlueprintCallable, Category = Setup)
	void Initialise(UTankTurret *TurretToSet, UTankBarrel *BarrelToSet);

	void AimAt(FVector OutHitLocation) const;

private:
	// starting value, overridable in blueprint / find reasonable value
	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float LaunchSpeed = 100000;
	UTankTurret * Turret = nullptr;
	UTankBarrel* Barrel = nullptr;
	void MoveBarrel(FVector AimDirection) const;

protected:
	UPROPERTY(BlueprintReadOnly, Category = State)
	EFiringStatus FiringState = EFiringStatus::Locked;

};
