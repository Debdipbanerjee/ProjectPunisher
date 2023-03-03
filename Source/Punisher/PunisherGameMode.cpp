// Copyright Epic Games, Inc. All Rights Reserved.

#include "PunisherGameMode.h"
#include "PunisherCharacter.h"
#include "UObject/ConstructorHelpers.h"

APunisherGameMode::APunisherGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
