// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"
// Depends on movement component via pathfinding system

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	AIControlledTank = Cast<ATank>(GetPawn());
	PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
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
		if (!ensure(AIControlledTank))
		{
			return;
		}
		AIControlledTank->AimAt(PlayerTank->GetActorLocation());
		// fire if ready
		AIControlledTank->Fire();
}







