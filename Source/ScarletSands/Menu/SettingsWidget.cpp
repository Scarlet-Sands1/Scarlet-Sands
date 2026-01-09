// Copyright Epic Games, Inc. All Rights Reserved.

#include "SettingsWidget.h"
#include "Components/Button.h"
#include "Components/Slider.h"
#include "Components/CheckBox.h"
#include "GameFramework/GameUserSettings.h"
#include "Sound/SoundClass.h"
#include "Kismet/GameplayStatics.h"
#include "../Save/ScarletSandsSettingsSaveGame.h"

void USettingsWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ScreenType = EMenuScreen::Settings;

	// Load sound classes
	MasterSoundClass = LoadObject<USoundClass>(nullptr, TEXT("/Game/ScarletSands/UI/Audio/SC_Master.SC_Master"));
	MusicSoundClass = LoadObject<USoundClass>(nullptr, TEXT("/Game/ScarletSands/UI/Audio/SC_Music.SC_Music"));
	SFXSoundClass = LoadObject<USoundClass>(nullptr, TEXT("/Game/ScarletSands/UI/Audio/SC_SFX.SC_SFX"));

	BindEvents();
	LoadSettings();
}

void USettingsWidget::BindEvents()
{
	// Audio sliders
	if (MasterVolumeSlider)
	{
		MasterVolumeSlider->OnValueChanged.AddDynamic(this, &USettingsWidget::OnMasterVolumeChanged);
	}

	if (MusicVolumeSlider)
	{
		MusicVolumeSlider->OnValueChanged.AddDynamic(this, &USettingsWidget::OnMusicVolumeChanged);
	}

	if (SFXVolumeSlider)
	{
		SFXVolumeSlider->OnValueChanged.AddDynamic(this, &USettingsWidget::OnSFXVolumeChanged);
	}

	// Control sliders
	if (MouseSensitivitySlider)
	{
		MouseSensitivitySlider->OnValueChanged.AddDynamic(this, &USettingsWidget::OnMouseSensitivityChanged);
	}

	if (InvertYCheckBox)
	{
		InvertYCheckBox->OnCheckStateChanged.AddDynamic(this, &USettingsWidget::OnInvertYChanged);
	}

	// Buttons
	if (ApplyButton)
	{
		ApplyButton->OnClicked.AddDynamic(this, &USettingsWidget::OnApplyClicked);
	}

	if (BackButton)
	{
		BackButton->OnClicked.AddDynamic(this, &USettingsWidget::OnBackClicked);
	}
}

void USettingsWidget::LoadSettings()
{
	// Load or create settings save game
	UScarletSandsSettingsSaveGame* Settings = Cast<UScarletSandsSettingsSaveGame>(
		UGameplayStatics::CreateSaveGameObject(UScarletSandsSettingsSaveGame::StaticClass())
	);

	if (Settings)
	{
		// Try to load existing settings
		if (!Settings->LoadSettings())
		{
			// No settings exist, use defaults
			Settings->ApplyDefaults();
		}

		// Set slider values
		if (MasterVolumeSlider)
		{
			MasterVolumeSlider->SetValue(Settings->MasterVolume);
		}

		if (MusicVolumeSlider)
		{
			MusicVolumeSlider->SetValue(Settings->MusicVolume);
		}

		if (SFXVolumeSlider)
		{
			SFXVolumeSlider->SetValue(Settings->SFXVolume);
		}

		if (MouseSensitivitySlider)
		{
			MouseSensitivitySlider->SetValue(Settings->MouseSensitivity);
		}

		if (InvertYCheckBox)
		{
			InvertYCheckBox->SetIsChecked(Settings->bInvertYAxis);
		}

		// Cache current values
		CurrentMasterVolume = Settings->MasterVolume;
		CurrentMusicVolume = Settings->MusicVolume;
		CurrentSFXVolume = Settings->SFXVolume;
		CurrentMouseSensitivity = Settings->MouseSensitivity;
		bCurrentInvertY = Settings->bInvertYAxis;

		// Apply audio settings immediately
		ApplySettings();
	}
}

void USettingsWidget::ApplySettings()
{
	// Apply audio settings to sound classes
	if (MasterSoundClass)
	{
		MasterSoundClass->Properties.Volume = CurrentMasterVolume;
	}

	if (MusicSoundClass)
	{
		MusicSoundClass->Properties.Volume = CurrentMusicVolume;
	}

	if (SFXSoundClass)
	{
		SFXSoundClass->Properties.Volume = CurrentSFXVolume;
	}

	// Graphics settings would be applied here using UGameUserSettings
	UGameUserSettings* GameSettings = UGameUserSettings::GetGameUserSettings();
	if (GameSettings)
	{
		GameSettings->ApplySettings(false);
	}

	// Control settings are stored and used by player controller
}

void USettingsWidget::SaveSettings()
{
	// Create and save settings
	UScarletSandsSettingsSaveGame* Settings = Cast<UScarletSandsSettingsSaveGame>(
		UGameplayStatics::CreateSaveGameObject(UScarletSandsSettingsSaveGame::StaticClass())
	);

	if (Settings)
	{
		Settings->MasterVolume = CurrentMasterVolume;
		Settings->MusicVolume = CurrentMusicVolume;
		Settings->SFXVolume = CurrentSFXVolume;
		Settings->MouseSensitivity = CurrentMouseSensitivity;
		Settings->bInvertYAxis = bCurrentInvertY;

		Settings->SaveSettings();
	}
}

void USettingsWidget::OnMasterVolumeChanged(float Value)
{
	CurrentMasterVolume = Value;
	if (MasterSoundClass)
	{
		MasterSoundClass->Properties.Volume = Value;
	}
}

void USettingsWidget::OnMusicVolumeChanged(float Value)
{
	CurrentMusicVolume = Value;
	if (MusicSoundClass)
	{
		MusicSoundClass->Properties.Volume = Value;
	}
}

void USettingsWidget::OnSFXVolumeChanged(float Value)
{
	CurrentSFXVolume = Value;
	if (SFXSoundClass)
	{
		SFXSoundClass->Properties.Volume = Value;
	}
}

void USettingsWidget::OnMouseSensitivityChanged(float Value)
{
	CurrentMouseSensitivity = Value;
}

void USettingsWidget::OnInvertYChanged(bool bIsChecked)
{
	bCurrentInvertY = bIsChecked;
}

void USettingsWidget::OnApplyClicked()
{
	PlaySelectSound();
	ApplySettings();
	SaveSettings();
}

void USettingsWidget::OnBackClicked()
{
	PlayBackSound();
	HandleBackPressed();
}
