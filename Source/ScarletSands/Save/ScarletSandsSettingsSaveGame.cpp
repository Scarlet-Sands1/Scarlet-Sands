// Copyright Epic Games, Inc. All Rights Reserved.

#include "ScarletSandsSettingsSaveGame.h"
#include "Kismet/GameplayStatics.h"

const FString UScarletSandsSettingsSaveGame::SettingsSaveSlot = TEXT("SS_Settings");

UScarletSandsSettingsSaveGame::UScarletSandsSettingsSaveGame()
{
	ApplyDefaults();
}

void UScarletSandsSettingsSaveGame::ApplyDefaults()
{
	MasterVolume = 1.0f;
	MusicVolume = 0.7f;
	SFXVolume = 0.8f;
	MouseSensitivity = 1.0f;
	bInvertYAxis = false;
}

void UScarletSandsSettingsSaveGame::SaveSettings()
{
	UGameplayStatics::SaveGameToSlot(this, SettingsSaveSlot, 0);
}

bool UScarletSandsSettingsSaveGame::LoadSettings()
{
	if (UGameplayStatics::DoesSaveGameExist(SettingsSaveSlot, 0))
	{
		UScarletSandsSettingsSaveGame* LoadedSettings = Cast<UScarletSandsSettingsSaveGame>(
			UGameplayStatics::LoadGameFromSlot(SettingsSaveSlot, 0)
		);

		if (LoadedSettings)
		{
			MasterVolume = LoadedSettings->MasterVolume;
			MusicVolume = LoadedSettings->MusicVolume;
			SFXVolume = LoadedSettings->SFXVolume;
			MouseSensitivity = LoadedSettings->MouseSensitivity;
			bInvertYAxis = LoadedSettings->bInvertYAxis;
			return true;
		}
	}

	return false;
}
