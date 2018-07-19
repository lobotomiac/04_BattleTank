// Fill out your copyright notice in the Description page of Project Settings.

#include "SprungWheel.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TankAxleConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>("TankAxleConstraint");
	SetRootComponent(TankAxleConstraint);

	Axle = CreateDefaultSubobject<USphereComponent>("Axle");
	Axle->SetupAttachment(TankAxleConstraint);

	Wheel = CreateDefaultSubobject<UStaticMeshComponent>("Wheel");
	Wheel->SetupAttachment(Axle);

	AxleWheelConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>("AxleWheelConstraint");
	AxleWheelConstraint->SetupAttachment(Axle);
}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();
	
	SetupConstraint();
}

// Sets up a constraint between Tank and wheel
void ASprungWheel::SetupConstraint()
{
	if (!GetAttachParentActor())
	{
		return;
	}
	UPrimitiveComponent* BodyRoot = Cast<UPrimitiveComponent>(GetAttachParentActor()->GetRootComponent());
	if (!BodyRoot)
	{
		return;
	}
	TankAxleConstraint->SetConstrainedComponents(BodyRoot, NAME_None, Axle, NAME_None);

	AxleWheelConstraint->SetConstrainedComponents(Axle, NAME_None, Wheel, NAME_None);
}


// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

