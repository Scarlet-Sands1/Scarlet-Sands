// Copyright Epic Games, Inc. All Rights Reserved.

#include "SettingsWidget.h"
#include "Components/Button.h"
#include "Components/Slider.h"
#include "Components/CheckBox.h"
#include "Components/ComboBoxString.h"
#include "GameFramework/GameUserSettings.h"
#include "Sound/SoundClass.h"
#include "Kismet/GameplayStatics.h"
#include "../Save/ScarletSandsSettingsSaveGame.h"
#include "../ScarletSandsGameUserSettings.h"
#include "MenuManagerSubsystem.h"

void USettingsWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ScreenType = EMenuScreen::Settings;

	// Load sound classes
	MasterSoundClass = LoadObject<USoundClass>(nullptr, TEXT("/Game/ScarletSands/UI/Audio/SC_Master.SC_Master"));
	MusicSoundClass = LoadObject<USoundClass>(nullptr, TEXT("/Game/ScarletSands/UI/Audio/SC_Music.SC_Music"));
	SFXSoundClass = LoadObject<USoundClass>(nullptr, TEXT("/Game/ScarletSands/UI/Audio/SC_SFX.SC_SFX"));

	InitializeGraphicsOptions();
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

	// Graphics controls
	if (WindowModeComboBox)
	{
		WindowModeComboBox->OnSelectionChanged.AddDynamic(this, &USettingsWidget::OnWindowModeChanged);
	}

	if (ResolutionComboBox)
	{
		ResolutionComboBox->OnSelectionChanged.AddDynamic(this, &USettingsWidget::OnResolutionChanged);
	}

	if (VSyncCheckBox)
	{
		VSyncCheckBox->OnCheckStateChanged.AddDynamic(this, &USettingsWidget::OnVSyncChanged);
	}

	if (QualityPresetComboBox)
	{
		QualityPresetComboBox->OnSelectionChanged.AddDynamic(this, &USettingsWidget::OnQualityPresetChanged);
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
	// Load audio/control settings from save game
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

		// Set audio slider values
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

		// Cache current audio/control values
		CurrentMasterVolume = Settings->MasterVolume;
		CurrentMusicVolume = Settings->MusicVolume;
		CurrentSFXVolume = Settings->SFXVolume;
		CurrentMouseSensitivity = Settings->MouseSensitivity;
		bCurrentInvertY = Settings->bInvertYAxis;
	}

	// Load graphics settings from GameUserSettings
	UScarletSandsGameUserSettings* GameSettings = UScarletSandsGameUserSettings::GetScarletSandsGameUserSettings();
	if (GameSettings)
	{
		GameSettings->LoadSettings();

		CurrentWindowMode = GameSettings->GetWindowModePreference();
		CurrentResolution = GameSettings->GetScreenResolution();
		bCurrentVSync = GameSettings->IsVSyncEnabled();
		CurrentQualityPreset = GameSettings->GetQualityPreset();

		// Set graphics UI values
		if (WindowModeComboBox)
		{
			WindowModeComboBox->SetSelectedIndex(CurrentWindowMode);
		}

		if (ResolutionComboBox)
		{
			FString ResString = FString::Printf(TEXT("%dx%d"), CurrentResolution.X, CurrentResolution.Y);
			ResolutionComboBox->SetSelectedOption(ResString);
		}

		if (VSyncCheckBox)
		{
			VSyncCheckBox->SetIsChecked(bCurrentVSync);
		}

		if (QualityPresetComboBox)
		{
			QualityPresetComboBox->SetSelectedIndex(CurrentQualityPreset);
		}
	}

	// Save initial values for dirty checking
	SavedMasterVolume = CurrentMasterVolume;
	SavedMusicVolume = CurrentMusicVolume;
	SavedSFXVolume = CurrentSFXVolume;
	SavedWindowMode = CurrentWindowMode;
	SavedResolution = CurrentResolution;
	bSavedVSync = bCurrentVSync;
	SavedQualityPreset = CurrentQualityPreset;
	SavedMouseSensitivity = CurrentMouseSensitivity;
	bSavedInvertY = bCurrentInvertY;

	// Apply audio settings immediately
	ApplySettings();
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

	// Apply graphics settings using GameUserSettings
	UScarletSandsGameUserSettings* GameSettings = UScarletSandsGameUserSettings::GetScarletSandsGameUserSettings();
	if (GameSettings)
	{
		GameSettings->SetWindowModePreference(CurrentWindowMode);
		GameSettings->SetScreenResolution(CurrentResolution);
		GameSettings->SetVSyncEnabled(bCurrentVSync);
		GameSettings->SetQualityPreset(CurrentQualityPreset);
		GameSettings->ApplySettings(false);
	}

	// Control settings are stored and used by player controller
}

void USettingsWidget::SaveSettings()
{
	// Save audio/control settings
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

	// Save graphics settings
	UScarletSandsGameUserSettings* GameSettings = UScarletSandsGameUserSettings::GetScarletSandsGameUserSettings();
	if (GameSettings)
	{
		GameSettings->SaveSettings();
	}

	// Update saved values for dirty checking
	SavedMasterVolume = CurrentMasterVolume;
	SavedMusicVolume = CurrentMusicVolume;
	SavedSFXVolume = CurrentSFXVolume;
	SavedWindowMode = CurrentWindowMode;
	SavedResolution = CurrentResolution;
	bSavedVSync = bCurrentVSync;
	SavedQualityPreset = CurrentQualityPreset;
	SavedMouseSensitivity = CurrentMouseSensitivity;
	bSavedInvertY = bCurrentInvertY;
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

	// Check for unsaved changes
	if (HasUnsavedChanges())
	{
		ShowDiscardConfirmation();
	}
	else
	{
		HandleBackPressed();
	}
}

void USettingsWidget::InitializeGraphicsOptions()
{
	// Initialize Window Mode options
	if (WindowModeComboBox)
	{
		WindowModeComboBox->ClearOptions();
		WindowModeComboBox->AddOption(TEXT("Fullscreen"));
		WindowModeComboBox->AddOption(TEXT("Windowed"));
		WindowModeComboBox->AddOption(TEXT("Borderless Fullscreen"));
	}

	// Initialize Resolution options (common 16:9 resolutions)
	if (ResolutionComboBox)
	{
		ResolutionComboBox->ClearOptions();
		ResolutionComboBox->AddOption(TEXT("1280x720"));
		ResolutionComboBox->AddOption(TEXT("1600x900"));
		ResolutionComboBox->AddOption(TEXT("1920x1080"));
		ResolutionComboBox->AddOption(TEXT("2560x1440"));
		ResolutionComboBox->AddOption(TEXT("3840x2160"));
	}

	// Initialize Quality Preset options
	if (QualityPresetComboBox)
	{
		QualityPresetComboBox->ClearOptions();
		QualityPresetComboBox->AddOption(TEXT("Low"));
		QualityPresetComboBox->AddOption(TEXT("Medium"));
		QualityPresetComboBox->AddOption(TEXT("High"));
		QualityPresetComboBox->AddOption(TEXT("Epic"));
	}
}

void USettingsWidget::OnWindowModeChanged(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	if (WindowModeComboBox)
	{
		CurrentWindowMode = WindowModeComboBox->GetSelectedIndex();
	}
}

void USettingsWidget::OnResolutionChanged(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	// Parse resolution string "WIDTHxHEIGHT"
	FString LeftString, RightString;
	if (SelectedItem.Split(TEXT("x"), &LeftString, &RightString))
	{
		int32 Width = FCString::Atoi(*LeftString);
		int32 Height = FCString::Atoi(*RightString);
		CurrentResolution = FIntPoint(Width, Height);
	}
}

void USettingsWidget::OnVSyncChanged(bool bIsChecked)
{
	bCurrentVSync = bIsChecked;
}

void USettingsWidget::OnQualityPresetChanged(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	if (QualityPresetComboBox)
	{
		CurrentQualityPreset = QualityPresetComboBox->GetSelectedIndex();
	}
}

bool USettingsWidget::HasUnsavedChanges() const
{
	return (CurrentMasterVolume != SavedMasterVolume) ||
		   (CurrentMusicVolume != SavedMusicVolume) ||
		   (CurrentSFXVolume != SavedSFXVolume) ||
		   (CurrentWindowMode != SavedWindowMode) ||
		   (CurrentResolution != SavedResolution) ||
		   (bCurrentVSync != bSavedVSync) ||
		   (CurrentQualityPreset != SavedQualityPreset) ||
		   (CurrentMouseSensitivity != SavedMouseSensitivity) ||
		   (bCurrentInvertY != bSavedInvertY);
}

void USettingsWidget::ShowDiscardConfirmation()
{
	UMenuManagerSubsystem* MenuManager = GetMenuManager();
	if (MenuManager)
	{
		FSimpleDelegate OnConfirm;
		OnConfirm.BindUObject(this, &USettingsWidget::HandleBackPressed);

		FSimpleDelegate OnCancel;
		// Do nothing on cancel - stay in settings

		MenuManager->ShowConfirmDialog(
			FText::FromString(TEXT("Discard Changes?")),
			FText::FromString(TEXT("You have unsaved changes. Are you sure you want to discard them?")),
			OnConfirm,
			OnCancel
		);
	}
}
