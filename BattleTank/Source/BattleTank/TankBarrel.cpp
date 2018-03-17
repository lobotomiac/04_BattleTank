// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"


/// change barrel elevation per frame up to max elevation speed and the frame time 
void UTankBarrel::ElevateBarrel(float RelativeSpeed)
{
	//  elevatino speed change
	auto ElevationChange = FMath::Clamp<float>(RelativeSpeed, -1.0, 1.0) * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;

	auto NewElevation = RelativeRotation.Pitch + ElevationChange;

	SetRelativeRotation(FRotator(FMath::Clamp(NewElevation, MinElevation, MaxElevation), 0.0, 0.0));
}
