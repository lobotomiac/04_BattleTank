// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SprungWheel.generated.h"

class UPhysicsConstraintComponent;


UCLASS()
class BATTLETANK_API ASprungWheel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASprungWheel();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	 
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mass = nullptr;
	
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Wheel = nullptr;

	UPROPERTY(VisibleAnywhere)
	UPhysicsConstraintComponent* PhysicsConstraint = nullptr;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
