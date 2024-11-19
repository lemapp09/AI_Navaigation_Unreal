// Copyright Epic Games, Inc. All Rights Reserved.

#include "AI_Navagation_UnRealGameMode.h"
#include "AI_Navagation_UnRealCharacter.h"
#include "UObject/ConstructorHelpers.h"

AAI_Navagation_UnRealGameMode::AAI_Navagation_UnRealGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
