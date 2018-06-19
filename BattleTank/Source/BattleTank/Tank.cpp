// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "Engine/World.h"
#include "Projectile.h"
#include "TankBarrel.h"
#include "TankAimingComponent.h"


// TODO fix AI tanks driving backwards
// TODO fix driving feel properly
// TODO clip movement input values
// TODO debug the barrel shaking & clip values when not moving crosshair
// TODO fix camera not pointing in tank direction at start


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void ATank::BeginPlay()
{
	Super::BeginPlay();
	TankAimingComponent = FindComponentByClass<UTankAimingComponent>();
	Barrel = FindComponentByClass<UTankBarrel>();
}


void ATank::Fire()
{
	if (!ensure (Barrel))
	{
		return;
	}
	
	bool IsReloaded = (GetWorld()->GetTimeSeconds() - LastFireTime) > ReloadTime;
	if (IsReloaded)
	{
		// spawn a projectile at the socket location on the barrel
		AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Barrel->GetSocketLocation("LaunchPoint"), Barrel->GetSocketRotation("LaunchPoint"));

		Projectile->LaunchProjectile(LaunchSpeed);

		LastFireTime = GetWorld()->GetTimeSeconds();
	}

	
}

void ATank::AimAt(FVector OutHitLocation) const
{
	if (!ensure (TankAimingComponent))	{  return;	}
	TankAimingComponent->AimAt(OutHitLocation, LaunchSpeed);
}


