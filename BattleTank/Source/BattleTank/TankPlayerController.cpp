// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "TankAimingComponent.h"



 void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent))
	{
		return;
	}
		FoundAimingComponent(AimingComponent);
}

 void ATankPlayerController::Tick(float DeltaTime)
 {
	 Super::Tick(DeltaTime);

	 AimTowardsCrosshair();
 }

 void ATankPlayerController::AimTowardsCrosshair()
 {
	 if (GetSightRayHitLocation(OutHitLocation))
	 {
		 if (!AimingComponent)
		 {
			 return;
		 }
		 AimingComponent->AimAt(OutHitLocation);
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
	FVector LookDirection; 
	if (CrosshairLookDirection(ScreenLocation, LookDirection))
	{
		// Line-Trace along that look direction, and see what we hit(up to max range)
		GetLookVectorHitLocation(LookDirection, OutHitLocation);
	}
		
	return true;
 }

 bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector &OutHitLocation) const
 {
	 FHitResult HitResult;
	 FVector Start = PlayerCameraManager->GetCameraLocation();
	 FVector End = Start + (LookDirection * LineTraceRange);
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

 bool ATankPlayerController::CrosshairLookDirection(FVector2D ScreenLocation, FVector &LookDirection) const
 {
	FVector CameraWorldDirection; // To be discarded
	if (DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldDirection, LookDirection))
	{
		return true;
	}
	else
	{
		return false;
	}
 }
