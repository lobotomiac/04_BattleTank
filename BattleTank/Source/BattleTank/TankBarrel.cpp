// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"



void UTankBarrel::ElevateBarrel(float DegreesPerSecond)
{
	// change barrel elevation per frame up to max elevatin speed and the frame time (deltatime?)
	UE_LOG(LogTemp, Warning, TEXT("Barrel-Elevate() called at speed %f"), DegreesPerSecond)
}
