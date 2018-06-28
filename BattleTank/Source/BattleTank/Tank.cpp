// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "Engine/World.h"
#include "Projectile.h"
#include "TankBarrel.h"


// TODO fix AI tanks driving backwards
// TODO fix driving feel properly
// TODO clip movement input values
// TODO debug the barrel shaking & clip values when not moving crosshair
// TODO fix camera not pointing in tank direction at start
// TODO fix camera able to go below floor


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void ATank::BeginPlay()
{
	Super::BeginPlay();
}