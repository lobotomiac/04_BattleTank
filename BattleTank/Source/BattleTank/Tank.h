 // Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Engine/World.h"
#include "Tank.generated.h"

class UTankBarrel; 
class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	virtual void BeginPlay() override;

	// called by the engine when damage is dealt (detects projectiles close enough automatically
	virtual float TakeDamage(float DamageAmount,struct FDamageEvent const & DamageEvent,class AController * EventInstigator,AActor * DamageCauser) override;

private:
	UPROPERTY(EditDefaultsOnly, Category = Health)
	int32 FullHealth = 100.0f;

	UPROPERTY(VisibleAnywhere, Category = Health)
	int32 CurrentHealth = FullHealth;

};
