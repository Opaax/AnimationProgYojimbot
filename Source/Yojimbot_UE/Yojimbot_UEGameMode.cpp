// Copyright Epic Games, Inc. All Rights Reserved.

#include "Yojimbot_UEGameMode.h"
#include "Yojimbot_UECharacter.h"
#include "UObject/ConstructorHelpers.h"

AYojimbot_UEGameMode::AYojimbot_UEGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
