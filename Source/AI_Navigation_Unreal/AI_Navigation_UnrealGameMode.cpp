// Copyright Epic Games, Inc. All Rights Reserved.

#include "AI_Navigation_UnrealGameMode.h"
#include "AI_Navigation_UnrealCharacter.h"
#include "UObject/ConstructorHelpers.h"

AAI_Navigation_UnrealGameMode::AAI_Navigation_UnrealGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
