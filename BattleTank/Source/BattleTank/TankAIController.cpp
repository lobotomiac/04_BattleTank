// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "Tank.h"
// Depends on movement component via pathfinding system

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	auto ControlledTank = GetPawn();
	if (!ControlledTank)
	{
		return;
	}
	AIAimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AIAimingComponent))
	{
		return;
	}
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!ensure(PlayerTank))
	{
		return;
	}
	//  move towards the player
	MoveToActor(PlayerTank, AcceptanceRadius);
	// AI aims towards the player
	if (!ensure(ControlledTank))
	{
		return;
	}
	AIAimingComponent->AimAt(PlayerTank->GetActorLocation());
	// fire if ready
	if (AIAimingComponent->GetFiringState() == EFiringState::Locked)
	{
		AIAimingComponent->Fire();
	}
}

void ATankAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto PossesedTank = Cast<ATank>(InPawn);

		if (!ensure(PossesedTank))
		{
			return;
		}
			// Subscribe our local method to the tank's death event 
			PossesedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossessedTankDeath);
	}
}


void ATankAIController::OnPossessedTankDeath()
{
	// deposes the tank or turn off its controlls 
	UE_LOG(LogTemp, Warning, TEXT("AI tank is destroyed"))
}