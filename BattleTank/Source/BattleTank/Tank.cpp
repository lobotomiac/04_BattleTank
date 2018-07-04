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
// TODO fix camera in general


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	CurrentHealth = FullHealth;
}

void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

float ATank::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser)
{
	int32 DamagePoints = FGenericPlatformMath::RoundToInt(DamageAmount);
	auto DamageToApply = FMath::Clamp(DamagePoints, 0, CurrentHealth);

	//UE_LOG(LogTemp, Warning, TEXT("DamageAmount: %f || DamageToApply: %i"), DamageAmount, DamageToApply)
	CurrentHealth -= DamageToApply;
	if (CurrentHealth <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Tank destroyed"))
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Tank Health: %i"), CurrentHealth)
	}
	return DamageToApply;
}


