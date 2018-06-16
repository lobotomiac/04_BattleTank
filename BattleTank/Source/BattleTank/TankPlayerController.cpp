// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include "Tank.h"


 void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto AimingComponent = GetControlledTank()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent))
	{
		UE_LOG(LogTemp, Warning, TEXT("AimingComponent reference not found on Begin Play."))
		return;
	}
	else
	{
		FoundAimingComponent(AimingComponent);
	}
}

 void ATankPlayerController::Tick(float DeltaTime)
 {
	 Super::Tick(DeltaTime);

	 AimTowardsCrosshair();
 }

 void ATankPlayerController::AimTowardsCrosshair()
 {
	 if (!ensure (GetControlledTank())) { return; }

	 if (GetSightRayHitLocation(OutHitLocation))
	 {
		 GetControlledTank()->AimAt(OutHitLocation);
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
	}
		
	return true;
 }

 bool ATankPlayerController::GetLookVectorHitLocation(FVector AimDirection, FVector &OutHitLocation) const
 {
	 FHitResult HitResult;
	 FVector Start = PlayerCameraManager->GetCameraLocation();
	 FVector End = Start + (AimDirection * LineTraceRange);
	 FCollisionQueryParams Params;
	 Params.AddIgnoredActor(GetPawn());
	 if (GetWorld()->LineTraceSingleByChannel (HitResult, Start, End, ECC_Visibility, Params))
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
	else
	{
		return false;
	}
 }



ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}


