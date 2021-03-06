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
// TODO fix PIE: Warning: Constraint


void ATank::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = FullHealth;
}

float ATank::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser)
{
	// getting int DamagePoints from DamageAmount
	int32 DamagePoints = FGenericPlatformMath::RoundToInt(DamageAmount);
	// clamp damage value to a reasonable amount && to prevent it from going below 0
	auto DamageToApply = FMath::Clamp(DamagePoints, 0, CurrentHealth);

	CurrentHealth -= DamageToApply;
	if (CurrentHealth <= 0)
	{
		OnDeath.Broadcast(); // broadcast death of tank for appropriate response by the delegate function
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Tank Health: %i"), CurrentHealth)
	}
	return DamageToApply;
}

float ATank::GetHealthPercentage() const
{
	return (float)CurrentHealth / (float)FullHealth;
}

