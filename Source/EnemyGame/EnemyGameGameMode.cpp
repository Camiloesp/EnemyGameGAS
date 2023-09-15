// Copyright Epic Games, Inc. All Rights Reserved.

#include "EnemyGameGameMode.h"
#include "EnemyGameCharacter.h"
#include "UObject/ConstructorHelpers.h"

AEnemyGameGameMode::AEnemyGameGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
