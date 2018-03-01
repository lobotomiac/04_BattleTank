// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"




 void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Error, TEXT("PLayerController does not possess a tank."))
		return;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%s possesses a tank"),*GetName())
	}
}

 void ATankPlayerController::Tick(float DeltaTime)
 {
	 Super::Tick(DeltaTime);

	 AimTowardsCrosshair();
 }

 void ATankPlayerController::AimTowardsCrosshair()
 {
	 if (!GetControlledTank()) { return; }

	 FVector OutHitLocation;	// Out Parameter

	 if (GetSightRayHitLocation(OutHitLocation))
	 {
		 UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *OutHitLocation.ToString())
			 // If it hits the landscape
			 // Tell controlled tank to aim at this point
	 } 
 }

 /// Getting location of crosshair in world (location of where its pointing) and returning true if hitting terrain, objects || false for aiming at sky
 bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
 {
	 OutHitLocation = FVector(12.0);
	 // ray cast from turret to crosshair
		// check hit
		// update HitLocation
	 return true;
 }

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}


