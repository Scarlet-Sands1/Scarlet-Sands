// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "ScarletSandsSettingsSaveGame.generated.h"

/**
 * Settings save game - persists user preferences for audio and controls
 */
UCLASS()
class SCARLETSANDS_API UScarletSandsSettingsSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UScarletSandsSettingsSaveGame();

	// Audio settings
	UPROPERTY(VisibleAnywhere, Category = "Audio Settings")
	float MasterVolume;

	UPROPERTY(VisibleAnywhere, Category = "Audio Settings")
	float MusicVolume;

	UPROPERTY(VisibleAnywhere, Category = "Audio Settings")
	float SFXVolume;

	// Control settings
	UPROPERTY(VisibleAnywhere, Category = "Control Settings")
	float MouseSensitivity;

	UPROPERTY(VisibleAnywhere, Category = "Control Settings")
	bool bInvertYAxis;

	// Helper methods
	void ApplyDefaults();
	void SaveSettings();
	bool LoadSettings();

	static const FString SettingsSaveSlot;
};
