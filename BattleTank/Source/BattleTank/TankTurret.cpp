// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"


/// Rotating the turret's yaw rotation
void UTankTurret::RotateTurret(float RelativeChangeSpeed)
{
	//
	if (FMath::Abs(RelativeChangeSpeed) > 180)
	{
		RelativeChangeSpeed *= -1;
	}
	else if (RelativeChangeSpeed < -180)
	{
		RelativeChangeSpeed *= -1;
	}
	
	// clamping the speed of rotation
	auto YawChange = FMath::Clamp<float>(RelativeChangeSpeed, 1.0, -1.0) * MaxTurretRotation * GetWorld()->DeltaTimeSeconds;
	
	auto NewRotation = RelativeRotation.Yaw - YawChange;
	SetRelativeRotation(FRotator(0.0, NewRotation, 0.0));

}

