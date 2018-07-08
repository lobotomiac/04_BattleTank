 // Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Engine/World.h"
#include "Tank.generated.h"

class UTankBarrel; 
class AProjectile;


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDestructionBroadcast);

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	// called by the engine when damage is dealt (detects projectiles close enough automatically
	virtual float TakeDamage(float DamageAmount,struct FDamageEvent const & DamageEvent,class AController * EventInstigator,AActor * DamageCauser) override;

	// Returns a percentage of current health 
	UFUNCTION(BlueprintPure, Category = Health)
	float GetHealthPercentage() const;

	UPROPERTY(BlueprintAssignable, Category = Death)
	FDestructionBroadcast OnDeath;

private:

	UPROPERTY(VisibleAnywhere, Category = Health)
	int32 CurrentHealth;

	UPROPERTY(EditDefaultsOnly, Category = Health)
	int32 FullHealth = 100;
};
