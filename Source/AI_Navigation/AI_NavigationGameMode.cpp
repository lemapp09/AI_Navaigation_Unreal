// Copyright Epic Games, Inc. All Rights Reserved.

#include "AI_NavigationGameMode.h"
#include "AI_NavigationCharacter.h"
#include "UObject/ConstructorHelpers.h"

AAI_NavigationGameMode::AAI_NavigationGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
