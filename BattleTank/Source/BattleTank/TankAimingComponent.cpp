// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;		// should it tick? 
	
	// ...
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	Barrel = BarrelToSet;
}


void UTankAimingComponent::AimAt(FVector OutHitLocation, float LaunchSpeed) const
{
	if (!Barrel) { return; }

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("LaunchPoint"));

	bool ProjectileAimSolution = UGameplayStatics::SuggestProjectileVelocity
	(
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
		auto RunningTime = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("%f : Aim \"Solve\" whatever that is found"), RunningTime)
	}
	else 
	{
		auto RunningTime = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("%f : Aim \"Solve\" whatever that is, not found"), RunningTime)
		return;
	}
}

void UTankAimingComponent::MoveBarrel(FVector AimDirection) const
{
	auto BarrelRotation = Barrel->GetComponentRotation();
	auto AimRotation = AimDirection.Rotation();
	auto DeltaRotation = AimRotation - BarrelRotation;
	// UE_LOG(LogTemp, Warning, TEXT("BarrelRotatino: %s  AimRotation : %s"), *BarrelRotation.ToString(), *AimRotation.ToString())
		//	setTurretRotationSpeed
		//	SetTurretElevationSpeed
		//	Take mouse input from user 
		//	Change rotation towards to where user points mouse at previously set speed
		Barrel->ElevateBarrel(DeltaRotation.Pitch); //TODO remove magic number
}	




