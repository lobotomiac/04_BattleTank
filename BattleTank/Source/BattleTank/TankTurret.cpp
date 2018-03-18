// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"


/// Rotating the turret's yaw rotation
void UTankTurret::RotateTurret(float RelativeChangeSpeed)
{
	auto YawChange = FMath::Clamp<float>(RelativeChangeSpeed, 1.0, -1.0) * MaxTurretYawRotationSpeed * GetWorld()->DeltaTimeSeconds;

	auto NewYawRotation = RelativeRotation.Yaw - YawChange;

	SetRelativeRotation(FRotator(0.0, NewYawRotation, 0.0));
}

