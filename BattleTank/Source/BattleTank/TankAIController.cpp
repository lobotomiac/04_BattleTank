// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	AIControlledTank();

	auto PlayerTank = GetPlayerTank();
	if (!PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("No PlayerTank detected."))
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerTank possesses %s"), *(PlayerTank->GetName()))
	}


}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsPlayer();
}

ATank * ATankAIController::GetAIControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank * ATankAIController::GetPlayerTank() const
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	// return Cast<ATank>(PlayerPawn);
	if (!PlayerPawn)
	{
		return nullptr;
	}
	else
	{
		return Cast<ATank>(PlayerPawn);
	}
}

void ATankAIController::AIControlledTank()
{
	auto AIControlledTank = GetAIControlledTank();

	if (!AIControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s is not possesed by AI!"), *(AIControlledTank->GetName()))
		return;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController posseses %s."), *(AIControlledTank->GetName()))
	}
}

void ATankAIController::AimTowardsPlayer()
{
	if (GetPlayerTank())
	{
		GetAIControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
	}
}

