// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankAimingComponent.h"
// Depends on movement component via pathfinding system

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	
	ControlledTank = GetPawn();

	if (!ControlledTank)
	{
		return;
	}
	AIAimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AIAimingComponent))
	{
		return;
	}
	PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
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
	AIAimingComponent->Fire();
}
