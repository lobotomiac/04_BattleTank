// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * TankTrack is used to move & apply forces to tank, as well as controlling the max throttle of the tank movement
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public: 
	// Sets the throttle for the track with values between -1 and +1
	UFUNCTION(BlueprintCallable, Category = Input)
	void SetThrottle(float Throttle);
	
	// Max driving force in Newtons
	UPROPERTY(EditDefaultsOnly)
	float MaxDrivingForce = 107290;		// TODO fix a realistic value /learn more about acceleration

private:
	UTankTrack();

	virtual void BeginPlay() override;

	void DriveTrack(float CurrentThrottle);

	TArray<class ASprungWheel*> GetWheels() const;
};
