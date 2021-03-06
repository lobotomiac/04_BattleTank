// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;		// should it tick? 
}

void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
}


void UTankAimingComponent::Initialise(UTankTurret * TurretToSet, UTankBarrel * BarrelToSet)
{
	Turret = TurretToSet;
	Barrel = BarrelToSet;
}


void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	if (Ammunition > 0)
	{
		if ((GetWorld()->GetTimeSeconds() - LastFireTime) < ReloadTime)
		{
			FiringState = EFiringState::Reloading;
		}
		else if (IsBarrelMoving())
		{
			FiringState = EFiringState::Aiming;
		}
		else if (!IsBarrelMoving())
		{
			FiringState = EFiringState::Locked;
		}
	}
	else
	{
		FiringState = EFiringState::Empty;
	}
}


void UTankAimingComponent::AimAt(FVector OutHitLocation)
{
	if (!ensure(Barrel)) { return; }

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("LaunchPoint"));

	bool bProjectileAimSolution = UGameplayStatics::SuggestProjectileVelocity (
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
	if (bProjectileAimSolution)
	{
		AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrel(AimDirection);
	}
	else 
	{
		return;
	}
}

void UTankAimingComponent::MoveBarrel(FVector AimDirection)
{
	if (!ensure(Barrel) || !ensure(Turret)) { return; }
	auto BarrelRotation = Barrel->GetComponentRotation();
	auto AimRotation = AimDirection.Rotation();
	auto DeltaRotation = AimRotation - BarrelRotation;
		
	/// rotate barrel and turret towards crosshair
	Barrel->ElevateBarrel(DeltaRotation.Pitch);
	//  Makes sure the turret rotation takes the shortest route to turn
	Turret->RotateTurret(DeltaRotation.GetNormalized().Yaw);
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel))
	{
		return false;
	}
	auto BarrelForwardVector = Barrel->GetForwardVector();
	// TODO Fix the difference between The barrel and Aim direction
	return !AimDirection.Equals(BarrelForwardVector, 0.02);
}


void UTankAimingComponent::Fire()
{
	if (!ensure(Barrel && ProjectileBlueprint))
	{
		return;
	}
	if (FiringState != EFiringState::Reloading && FiringState != EFiringState::Empty)
	{
		// spawn a projectile at the socket location on the barrel
		AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Barrel->GetSocketLocation("LaunchPoint"), Barrel->GetSocketRotation("LaunchPoint"));
		Projectile->LaunchProjectile(LaunchSpeed);

		LastFireTime = GetWorld()->GetTimeSeconds();
		AmmunitionCount();
	}
}

void UTankAimingComponent::AmmunitionCount()
{
	--Ammunition;
}

EFiringState UTankAimingComponent::GetFiringState() const
{
	return FiringState;
}
