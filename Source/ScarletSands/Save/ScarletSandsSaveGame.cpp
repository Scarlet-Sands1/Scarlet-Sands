// Copyright Epic Games, Inc. All Rights Reserved.

#include "ScarletSandsSaveGame.h"

UScarletSandsSaveGame::UScarletSandsSaveGame()
{
	PlayerName = TEXT("Kai");
	PlayerLocation = FVector::ZeroVector;
	PlayerRotation = FRotator::ZeroRotator;
	CurrentLevelName = TEXT("L_World_Persistent");
	PlayTime = 0.0f;
	SaveTimestamp = FDateTime::Now();
}

void UScarletSandsSaveGame::InitializeNewGame()
{
	// Reset to default new game state
	PlayerName = TEXT("Kai");
	PlayerLocation = FVector::ZeroVector;
	PlayerRotation = FRotator::ZeroRotator;
	CurrentLevelName = TEXT("L_World_Persistent");
	PlayTime = 0.0f;
	SaveTimestamp = FDateTime::Now();
	CompletedObjectives.Empty();
	GameFlags.Empty();
}
