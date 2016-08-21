// Fill out your copyright notice in the Description page of Project Settings.

#include "MJC_CS_Final_Project.h"
#include "VRProjectile.h"


// Sets default values
AVRProjectile::AVRProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

AVRProjectile::AVRProjectile(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Use a sphere as a simple collision representation
	CollisionComp = ObjectInitializer.CreateDefaultSubobject<USphereComponent>(this, TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(15.0f);
	RootComponent = CollisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = ObjectInitializer.CreateDefaultSubobject<UProjectileMovementComponent>(this, TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;
	ProjectileMovement->Bounciness = 0.3f;

	CollisionComp->BodyInstance.SetCollisionProfileName("VRProjectile");
}

// Called when the game starts or when spawned
void AVRProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AVRProjectile::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AVRProjectile::InitVelocity(const FVector& ShootDirection)
{
	if (ProjectileMovement)
	{
		// set the projectile's velocity to the desired direction
		ProjectileMovement->Velocity = ShootDirection * ProjectileMovement->InitialSpeed;
	}
}