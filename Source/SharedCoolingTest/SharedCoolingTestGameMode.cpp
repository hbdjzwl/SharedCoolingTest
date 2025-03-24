// Copyright Epic Games, Inc. All Rights Reserved.

#include "SharedCoolingTestGameMode.h"
#include "SharedCoolingTestCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASharedCoolingTestGameMode::ASharedCoolingTestGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
