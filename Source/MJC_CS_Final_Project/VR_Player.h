// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "VR_Player.generated.h"

UCLASS()
class MJC_CS_FINAL_PROJECT_API AVR_Player : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AVR_Player();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Parameterized Constructor
	AVR_Player(const FObjectInitializer& ObjectInitializer);

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	/** Gun muzzle's offset from the camera location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		FVector MuzzleOffset;

	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		TSubclassOf<class AVRProjectile> ProjectileClass;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	UFUNCTION()
		/** Handles moving forward/backward */
		void MoveForward(float Val);

	/** Handles stafing movement, left and right */
	void MoveRight(float Val);

	//sets jump flag when key is pressed
	UFUNCTION()
		void OnStartJump();
	//clears jump flag when key is released
	UFUNCTION()
		void OnStopJump();

	//handles firing
	UFUNCTION()
		void OnFire();
};