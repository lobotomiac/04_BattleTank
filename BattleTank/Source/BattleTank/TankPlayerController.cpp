// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include "Tank.h"


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
	 if (!GetPawn())
	 {
		 return;
	 }
	 AimTowardsCrosshair();
 }

 void ATankPlayerController::AimTowardsCrosshair()
 {
	 bool bGotHitLocation = GetSightRayHitLocation(OutHitLocation);
	 if (bGotHitLocation)
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
		return GotLookVectorHitLocation(LookDirection, OutHitLocation);
	}	
	return false;
 }

 bool ATankPlayerController::GotLookVectorHitLocation(FVector LookDirection, FVector &OutHitLocation) const
 {
	 FHitResult HitResult;
	 FVector Start = PlayerCameraManager->GetCameraLocation();
	 FVector End = Start + (LookDirection * LineTraceRange);
	 FCollisionQueryParams Params;
	 Params.AddIgnoredActor(GetPawn());
	 if (GetWorld()->LineTraceSingleByChannel (HitResult, Start, End, ECC_Camera, Params))
	 {
		 OutHitLocation = HitResult.Location;
		 return true;
	 }
	 OutHitLocation = FVector(0);
	 return false;
}

 void ATankPlayerController::SetPawn(APawn* InPawn)
 {
	 Super::SetPawn(InPawn);
	 if (InPawn)
	 {
		 auto PossesedTank = Cast<ATank>(InPawn);

		 if (!ensure(PossesedTank))
		 {
			 return;
		 }
		 // Subscribe our local method to the tank's death event 
		 PossesedTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnPossessedTankDeath);
	 }
 }

 void ATankPlayerController::OnPossessedTankDeath()
 {
	UE_LOG(LogTemp, Warning, TEXT("Player Tank Destroyed"))
	APlayerController::StartSpectatingOnly();
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
