// Fill out your copyright notice in the Description page of Project Settings.

#include "SprungWheel.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"

// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Mass = CreateDefaultSubobject<UStaticMeshComponent>("Mass");
	SetRootComponent(Mass);
	Mass->SetSimulatePhysics(true);

	Wheel = CreateDefaultSubobject<UStaticMeshComponent>("Wheel");
	Wheel->SetupAttachment(Mass);
	Wheel->SetSimulatePhysics(true);

	PhysicsConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>("Physics Constraint");
	PhysicsConstraint->SetupAttachment(Mass);

}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

