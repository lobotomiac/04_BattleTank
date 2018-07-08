// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"



class UTankAimingComponent;

/**
 *	Responsible for helping player aim 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public: 
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UTankAimingComponent* AimingComponent = nullptr;

	UFUNCTION(BlueprintImplementableEvent, Category = Setup)
	void FoundAimingComponent(UTankAimingComponent* AimComponentReference);

private:
	FVector OutHitLocation;	// Out Parameter

	void AimTowardsCrosshair();

	bool GetSightRayHitLocation(FVector &OutHitLocation) const;

	float ViewportSizeXLocation = 0.5;
	float ViewportSizeYLocation = 0.33333333;
	
	// Find aiming coordinates in 3D space
	bool CrosshairLookDirection(FVector2D ScreenLocation, FVector &LookDirection) const;

	// Line tracing to where the aim is, false if hitting sky, else true &  coordinates of hit collision with object
	bool GotLookVectorHitLocation(FVector LookDirectionn, FVector &OutHitLocation) const;

	UPROPERTY(EditDefaultsOnly)
	float LineTraceRange = 1000000;

	virtual void SetPawn(APawn* InPawn) override;

	UFUNCTION()
	void OnPossessedTankDeath();
};
