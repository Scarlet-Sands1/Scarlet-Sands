// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "ScarletSandsSaveGame.generated.h"

/**
 * Main save game object for Scarlet Sands - stores player progress and game state
 */
UCLASS()
class SCARLETSANDS_API UScarletSandsSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UScarletSandsSaveGame();

	// Initialize a new game save
	void InitializeNewGame();

	// Player progress data
	UPROPERTY(VisibleAnywhere, Category = "Save Data")
	FString PlayerName;

	UPROPERTY(VisibleAnywhere, Category = "Save Data")
	FVector PlayerLocation;

	UPROPERTY(VisibleAnywhere, Category = "Save Data")
	FRotator PlayerRotation;

	UPROPERTY(VisibleAnywhere, Category = "Save Data")
	FString CurrentLevelName;

	UPROPERTY(VisibleAnywhere, Category = "Save Data")
	float PlayTime;

	UPROPERTY(VisibleAnywhere, Category = "Save Data")
	FDateTime SaveTimestamp;

	// Game progress flags
	UPROPERTY(VisibleAnywhere, Category = "Save Data")
	TArray<FString> CompletedObjectives;

	UPROPERTY(VisibleAnywhere, Category = "Save Data")
	TMap<FString, bool> GameFlags;
};
