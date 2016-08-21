// Fill out your copyright notice in the Description page of Project Settings.

#include "MJC_CS_Final_Project.h"
#include "VRGameMode.h"
#include "VR_Player.h"
#include "Engine.h" //for version 4.4+
// Note that this may no longer be necessary as this file will likely already include [ProjectName].h, which, by default, will include "Engine.h" itself

AVRGameMode::AVRGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// set default pawn class to our Blueprinted character
	// note that if player is not forced to control a character in
	//the level, they will have all of the functions of the default pawn class automatically.
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnObject(TEXT("Pawn'/Game/Blueprints/BP_VR_Player.BP_VR_Player_C'"));
	if (PlayerPawnObject.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnObject.Class;
	}
}

// Note that engine version 4.3 changed the method's name to StartPlay(), because of this engine versions before 4.3, or older tutorials, use BeginPlay()
void AVRGameMode::StartPlay()
{
	Super::StartPlay();

	StartMatch();
}