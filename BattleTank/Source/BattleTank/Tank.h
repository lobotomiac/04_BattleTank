// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel; 
class UTankTurret; 
class UTankAimingComponent;	

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UTankAimingComponent* TankAimingComponent = nullptr;

public:	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//	Called to aim at either crosshair(player) or player(AI)
	virtual void AimAt(FVector OutHitLocation) const;
	
	// Delegating SetbarrelReference to the aiming component
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelReference(UTankBarrel* BarrelToSet);

	// Delegating SetTurretReference to the aiming component
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTurretReference(UTankTurret* TurretToSet);

	// starting value, overridable in blueprint / find reasonable value
	UPROPERTY(EditAnywhere, Category = Firing)
	float LaunchSpeed = 100000;	

	UFUNCTION(BlueprintCallable, Category = Firing)
	void Fire() const;

};
