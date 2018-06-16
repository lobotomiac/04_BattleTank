// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;		// should it tick? 
	
	// ...
}



void UTankAimingComponent::Initialise(UTankTurret * TurretToSet, UTankBarrel * BarrelToSet)
{
	TurretToSet = Turret;
	BarrelToSet = Barrel;
}

void UTankAimingComponent::AimAt(FVector OutHitLocation, float LaunchSpeed) const
{
	if (!ensure(Barrel)) { return; }

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("LaunchPoint"));

	bool ProjectileAimSolution = UGameplayStatics::SuggestProjectileVelocity (
		this,
		OutLaunchVelocity,
		StartLocation,
		OutHitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
		//FCollisionObjectQueryParams::DefaultObjectQueryParam,	//enable to trace path
		//TArray<AActor*>(),										//enable to trace path
		//true													//enable to trace path
	);
	if (ProjectileAimSolution)
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrel(AimDirection);
	}
	else 
	{
		return;
	}
}

void UTankAimingComponent::MoveBarrel(FVector AimDirection) const
{
	if (!ensure (Barrel && Turret)) { return; }
	auto BarrelRotation = Barrel->GetComponentRotation();
	auto AimRotation = AimDirection.Rotation();
	auto DeltaRotation = AimRotation - BarrelRotation;
		
	/// rotate barrel and turret towards crosshair
	Barrel->ElevateBarrel(DeltaRotation.Pitch);
	//  Makes sure the turret rotation takes the shortest route to turn
	Turret->RotateTurret(DeltaRotation.GetNormalized().Yaw);
}
