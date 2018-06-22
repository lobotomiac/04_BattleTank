// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"


/// change barrel elevation per frame up to max elevation speed and the frame time 
void UTankBarrel::ElevateBarrel(float RelativeChangeSpeed)
{
	//  elevation speed change
	auto PitchChange = FMath::Clamp<float>(RelativeChangeSpeed, -1.0, 1.0) * MaxBarrelElevationChangeSpeed * GetWorld()->DeltaTimeSeconds;

	auto NewElevation = RelativeRotation.Pitch + PitchChange;
	// TODO fix barrel rotation to be more precise with the aim 
	SetRelativeRotation(FRotator(FMath::Clamp(NewElevation, MinElevation, MaxElevation), 0.0, 0.0));
}
