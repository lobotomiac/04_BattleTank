// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	PlayerControlledTank();

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

ATank * ATankAIController::GetPlayerControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank * ATankAIController::GetPlayerTank() const
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	return Cast<ATank>(PlayerPawn);
	if (!PlayerPawn)
	{
		return nullptr;
	}
	else
	{
		return Cast<ATank>(PlayerPawn);
	}
}

void ATankAIController::PlayerControlledTank()
{
	auto PlayerControlledTank = GetPlayerControlledTank();

	if (!PlayerControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s is not possesed by AI!"), *(PlayerControlledTank->GetName()))
		return;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController posseses %s."), *(PlayerControlledTank->GetName()))
	}
}

