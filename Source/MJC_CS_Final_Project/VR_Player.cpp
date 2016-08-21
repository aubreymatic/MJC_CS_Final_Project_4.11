// Fill out your copyright notice in the Description page of Project Settings.

#include "MJC_CS_Final_Project.h"
#include "VR_Player.h"
#include "VRProjectile.h"

// Sets default values
AVR_Player::AVR_Player()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AVR_Player::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AVR_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AVR_Player::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);
	// set up gameplay key bindings

	InputComponent->BindAction("Jump", IE_Pressed, this, &AVR_Player::Jump);
	InputComponent->BindAction("Jump", IE_Released, this, &AVR_Player::StopJumping);

	InputComponent->BindAxis("MoveForward", this, &AVR_Player::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AVR_Player::MoveRight);

	InputComponent->BindAxis("Turn", this, &AVR_Player::AddControllerYawInput);
	InputComponent->BindAxis("LookUp", this, &AVR_Player::AddControllerPitchInput);

	InputComponent->BindAction("Fire", IE_Pressed, this, &AVR_Player::OnFire);
}

void AVR_Player::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		FRotator Rotation = Controller->GetControlRotation();
		// Limit pitch when walking or falling
		if (GetCharacterMovement()->IsMovingOnGround() || GetCharacterMovement()->IsFalling())
		{
			Rotation.Pitch = 0.0f;
		}
		// add movement in that direction
		const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AVR_Player::MoveRight(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void AVR_Player::OnStartJump()
{
	bPressedJump = true;
}
void AVR_Player::OnStopJump()
{
	bPressedJump = false;
}

void AVR_Player::OnFire()
{
	// try and fire a projectile
	if (ProjectileClass != NULL)
	{
		// Get the camera transform
		FVector CameraLoc;
		FRotator CameraRot;
		GetActorEyesViewPoint(CameraLoc, CameraRot);
		// MuzzleOffset is in camera space, so transform it to world space before offsetting from the camera to find the final muzzle position
		FVector const MuzzleLocation = CameraLoc + FTransform(CameraRot).TransformVector(MuzzleOffset);
		FRotator MuzzleRotation = CameraRot;
		//MuzzleRotation.Pitch += 10.0f;          // skew the aim upwards a bit
		UWorld* const World = GetWorld();
		if (World)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = Instigator;
			// spawn the projectile at the muzzle
			AVRProjectile* const Projectile = World->SpawnActor<AVRProjectile>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);
			if (Projectile)
			{
				// find launch direction
				FVector const LaunchDir = MuzzleRotation.Vector();
				Projectile->InitVelocity(LaunchDir);
			}
		}
	}
}