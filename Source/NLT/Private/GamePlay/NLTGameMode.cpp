// Copyright Epic Games, Inc. All Rights Reserved.


#include "GamePlay/NLTGameMode.h"

#include "GamePlay/NLTCharacter.h"
#include "UObject/ConstructorHelpers.h"

ANLTGameMode::ANLTGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
