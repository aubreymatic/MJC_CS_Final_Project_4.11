// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "VRGameMode.generated.h"

/**
*
*/
UCLASS()
class MJC_CS_FINAL_PROJECT_API AVRGameMode : public AGameMode
{
	GENERATED_BODY()

		virtual void StartPlay() override; // Note that engine version 4.3 changed this method's name to StartPlay(), because of this engine versions before 4.3, or older tutorials, use BeginPlay()

	AVRGameMode(const FObjectInitializer& ObjectInitializer);
};