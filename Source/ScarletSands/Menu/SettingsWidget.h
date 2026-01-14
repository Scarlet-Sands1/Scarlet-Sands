// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "MenuWidgetBase.h"
#include "SettingsWidget.generated.h"

class UButton;
class USlider;
class UCheckBox;
class UComboBoxString;

/**
 * Settings Widget - handles Graphics, Audio, and Controls settings
 */
UCLASS()
class SCARLETSANDS_API USettingsWidget : public UMenuWidgetBase
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

protected:
	// Audio sliders
	UPROPERTY(meta = (BindWidget))
	USlider* MasterVolumeSlider;

	UPROPERTY(meta = (BindWidget))
	USlider* MusicVolumeSlider;

	UPROPERTY(meta = (BindWidget))
	USlider* SFXVolumeSlider;

	// Graphics settings
	UPROPERTY(meta = (BindWidget))
	UComboBoxString* WindowModeComboBox;

	UPROPERTY(meta = (BindWidget))
	UComboBoxString* ResolutionComboBox;

	UPROPERTY(meta = (BindWidget))
	UCheckBox* VSyncCheckBox;

	UPROPERTY(meta = (BindWidget))
	UComboBoxString* QualityPresetComboBox;

	// Control settings
	UPROPERTY(meta = (BindWidget))
	USlider* MouseSensitivitySlider;

	UPROPERTY(meta = (BindWidget))
	UCheckBox* InvertYCheckBox;

	// Buttons
	UPROPERTY(meta = (BindWidget))
	UButton* ApplyButton;

	UPROPERTY(meta = (BindWidget))
	UButton* BackButton;

	// Audio callbacks
	UFUNCTION()
	void OnMasterVolumeChanged(float Value);

	UFUNCTION()
	void OnMusicVolumeChanged(float Value);

	UFUNCTION()
	void OnSFXVolumeChanged(float Value);

	// Graphics callbacks
	UFUNCTION()
	void OnWindowModeChanged(FString SelectedItem, ESelectInfo::Type SelectionType);

	UFUNCTION()
	void OnResolutionChanged(FString SelectedItem, ESelectInfo::Type SelectionType);

	UFUNCTION()
	void OnVSyncChanged(bool bIsChecked);

	UFUNCTION()
	void OnQualityPresetChanged(FString SelectedItem, ESelectInfo::Type SelectionType);

	// Control callbacks
	UFUNCTION()
	void OnMouseSensitivityChanged(float Value);

	UFUNCTION()
	void OnInvertYChanged(bool bIsChecked);

	// Button callbacks
	UFUNCTION()
	void OnApplyClicked();

	UFUNCTION()
	void OnBackClicked();

private:
	void BindEvents();
	void LoadSettings();
	void ApplySettings();
	void SaveSettings();
	void InitializeGraphicsOptions();
	bool HasUnsavedChanges() const;
	void ShowDiscardConfirmation();

	// Cached sound classes
	UPROPERTY()
	class USoundClass* MasterSoundClass;

	UPROPERTY()
	class USoundClass* MusicSoundClass;

	UPROPERTY()
	class USoundClass* SFXSoundClass;

	// Current settings values (Audio)
	float CurrentMasterVolume;
	float CurrentMusicVolume;
	float CurrentSFXVolume;

	// Current settings values (Graphics)
	int32 CurrentWindowMode;
	FIntPoint CurrentResolution;
	bool bCurrentVSync;
	int32 CurrentQualityPreset;

	// Current settings values (Controls)
	float CurrentMouseSensitivity;
	bool bCurrentInvertY;

	// Saved settings values for dirty checking
	float SavedMasterVolume;
	float SavedMusicVolume;
	float SavedSFXVolume;
	int32 SavedWindowMode;
	FIntPoint SavedResolution;
	bool bSavedVSync;
	int32 SavedQualityPreset;
	float SavedMouseSensitivity;
	bool bSavedInvertY;
};
