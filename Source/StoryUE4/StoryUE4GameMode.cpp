// Copyright Epic Games, Inc. All Rights Reserved.

#include "StoryUE4GameMode.h"
#include "StoryUE4Character.h"
#include "UObject/ConstructorHelpers.h"

AStoryUE4GameMode::AStoryUE4GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
