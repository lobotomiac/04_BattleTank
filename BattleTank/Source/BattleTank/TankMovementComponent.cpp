// Fill out your copyright notice in the Description page of Project Settings.


#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	// No need to call Super as we're replacing the functionality completely
	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();
	// UE_LOG(LogTemp, Warning, TEXT("Time: %f |  velocity: %s"), GetWorld()->GetTimeSeconds(),  *AIForwardIntention.ToString());
	// how fast we would like to go (how far and in what direction the controller has been pressed/pushed)
	auto ForwardThrow = FVector::DotProduct(TankForward, AIForwardIntention);
	IntendMoveForward(ForwardThrow);
	// how fast we would like to turn (how far and in what direction the controller has been pressed/pushed)
	auto RightThrow = FVector::CrossProduct(AIForwardIntention, TankForward).Z;
	IntendTurnRight(RightThrow);
}


void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!ensure (LeftTrack && RightTrack))
	{
		return;
	}
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	if (!LeftTrack || !RightTrack) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}