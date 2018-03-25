// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"


class ATank;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public: 
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	ATank * GetControlledTank() const;
	
	FVector OutHitLocation;	// Out Parameter

	void AimTowardsCrosshair();

	bool GetSightRayHitLocation(FVector &OutHitLocation) const;
	
	float ViewportSizeXLocation;

	float ViewportSizeYLocation;
	
	// Find aiming coordinates in 3D space
	bool CrosshairAimDirection(FVector2D ScreenLocation, FVector &AimDirection) const;

	// Line tracing to where the aim is, false if hitting sky, else true &  coordinates of hit collision with object
	bool GetLookVectorHitLocation(FVector AimDirectionn, FVector &OutHitLocation) const;

	UPROPERTY(EditDefaultsOnly)
	float LineTraceRange = 1000000;
};
