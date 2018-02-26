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

 }

 void ATankPlayerController::AimTowardsCrosshair()
 {
	 if (!GetControlledTank()) { return; }
	// Get World Location with linetrace (raycast) through crosshair 
	// If it hits the landscape
		// Tell controlled tank to aim at this point
 }

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}


