// Copyright Epic Games, Inc. All Rights Reserved.

#include "YojimbotGameMode.h"
#include "YojimbotCharacter.h"
#include "UObject/ConstructorHelpers.h"

AYojimbotGameMode::AYojimbotGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
