// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "MenuWidgetBase.h"
#include "SettingsWidget.generated.h"

class UButton;
class USlider;
class UCheckBox;

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

	// Cached sound classes
	UPROPERTY()
	class USoundClass* MasterSoundClass;

	UPROPERTY()
	class USoundClass* MusicSoundClass;

	UPROPERTY()
	class USoundClass* SFXSoundClass;

	// Current settings values
	float CurrentMasterVolume;
	float CurrentMusicVolume;
	float CurrentSFXVolume;
	float CurrentMouseSensitivity;
	bool bCurrentInvertY;
};
