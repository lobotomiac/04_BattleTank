// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringStatus : uint8
{
	Reloading,
	Locked,
	Aiming
};

// forward declaration
class UTankBarrel; 
class UTankTurret;

// holds barrel, turret reference 
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

public:	
	
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelReference(UTankBarrel* BarrelToSet);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTurretReference(UTankTurret* TurretToSet);

	void AimAt(FVector OutHitLocation, float LaunchSpeed) const;

private:
	UTankBarrel* Barrel = nullptr;
	void MoveBarrel(FVector AimDirection) const;

	UTankTurret* Turret = nullptr;

protected:
	UPROPERTY(BlueprintReadOnly, Category = State)
	EFiringStatus FiringState = EFiringStatus::Locked;

};
