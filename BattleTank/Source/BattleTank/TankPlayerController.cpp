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

	ViewportSizeXLocation = 0.5;
	ViewportSizeYLocation = 0.33333;

}

 void ATankPlayerController::Tick(float DeltaTime)
 {
	 Super::Tick(DeltaTime);

	 AimTowardsCrosshair();
 }

 void ATankPlayerController::AimTowardsCrosshair()
 {
	 if (!GetControlledTank()) { return; }

	 if (GetSightRayHitLocation(OutHitLocation))
	 {
		// UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *OutHitLocation.ToString())
			 // If it hits the landscape
			 // Tell controlled tank to aim at this point
	 } 
 }

 /// Getting location of crosshair in world (location of where its pointing) and returning true if hitting terrain, objects || false for aiming at sky
 bool ATankPlayerController::GetSightRayHitLocation(FVector &OutHitLocation) const
 {
	// Find the crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX * ViewportSizeXLocation, ViewportSizeY * ViewportSizeYLocation);

	// "De-project" the screen position of the crosshair to a world direction
	FVector AimDirection; 
	if (CrosshairAimDirection(ScreenLocation, AimDirection))
	{
		// Line-Trace along that look direction, and see what we hit(up to max range)
		GetLookVectorHitLocation(AimDirection, OutHitLocation);
		UE_LOG(LogTemp, Warning, TEXT("Crosshair aimed at: %s"), *OutHitLocation.ToString())
	}
		
	return true;
 }

 bool ATankPlayerController::GetLookVectorHitLocation(FVector AimDirection, FVector &OutHitLocation) const
 {
	 FHitResult HitResult;
	 FVector Start = PlayerCameraManager->GetCameraLocation();
	 FVector End = Start + (AimDirection * LineTraceRange);

	 if (GetWorld()->LineTraceSingleByChannel(
		 HitResult,
		 Start,
		 End,
		 ECC_Visibility)
		 )
	 {
	 OutHitLocation = HitResult.Location;
	 return true;
	 }
	 OutHitLocation = FVector(0);
	 return false;
	 }

 bool ATankPlayerController::CrosshairAimDirection(FVector2D ScreenLocation, FVector &AimDirection) const
 {
	FVector CameraWorldDirection; // To be discarded
	if (DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldDirection, AimDirection))
	{
		return true;
	}
	else { return false; }
 }



ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}


