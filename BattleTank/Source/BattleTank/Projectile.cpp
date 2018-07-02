// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "Particles/ParticleSystemComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"



// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// creating default sub-object to allow projectile movement
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
	ProjectileMovementComponent->bAutoActivate = false;
	
	// creating default sub-object
	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>("Collision Mesh");
	// setting the root component and its properties
	SetRootComponent(CollisionMesh);
	CollisionMesh->SetNotifyRigidBodyCollision(true);
	CollisionMesh->SetVisibility(false);


	// creating default sub-object
	LaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>("Launch Blast");
	LaunchBlast->SetupAttachment(CollisionMesh);

	// creating default sub-object
	ImpactBlast = CreateDefaultSubobject<UParticleSystemComponent>("Impact Blast");
	ImpactBlast->bAutoActivate = false;
	ImpactBlast->SetupAttachment(CollisionMesh);

	ExplosionBlast = CreateDefaultSubobject<URadialForceComponent>("Explosion Blast");
	ExplosionBlast->SetupAttachment(CollisionMesh);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	CollisionMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}


void AProjectile::LaunchProjectile(float LaunchSpeed)
{
	ProjectileMovementComponent->SetVelocityInLocalSpace(FVector::ForwardVector * LaunchSpeed);
	ProjectileMovementComponent->Activate();
}

void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	LaunchBlast->Deactivate();
	ImpactBlast->Activate();
	ExplosionBlast->FireImpulse();
}