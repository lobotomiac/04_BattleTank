// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankAimingComponent.h"
// Depends on movement component via pathfinding system

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	auto ControlledTank = GetPawn();
	if (!ControlledTank)
	{
		return;
	}
	AIAimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
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
	//TODO fix firing && fire if ready
	// ControlledTank->Fire();
}
