// Copyright Epic Games, Inc. All Rights Reserved.

#include "ScarletSandsGameUserSettings.h"

UScarletSandsGameUserSettings::UScarletSandsGameUserSettings()
{
	// Default to borderless fullscreen (most modern approach)
	WindowModePreference = 2;

	// Default to High quality
	QualityPreset = 2;
}

UScarletSandsGameUserSettings* UScarletSandsGameUserSettings::GetScarletSandsGameUserSettings()
{
	return Cast<UScarletSandsGameUserSettings>(UGameUserSettings::GetGameUserSettings());
}

int32 UScarletSandsGameUserSettings::GetWindowModePreference() const
{
	return WindowModePreference;
}

void UScarletSandsGameUserSettings::SetWindowModePreference(int32 InWindowMode)
{
	if (WindowModePreference != InWindowMode)
	{
		WindowModePreference = InWindowMode;

		// Convert to Unreal's EWindowMode
		EWindowMode::Type WindowMode = EWindowMode::Windowed;
		switch (InWindowMode)
		{
		case 0:
			WindowMode = EWindowMode::Fullscreen;
			break;
		case 1:
			WindowMode = EWindowMode::Windowed;
			break;
		case 2:
			WindowMode = EWindowMode::WindowedFullscreen;
			break;
		}

		SetFullscreenMode(WindowMode);
	}
}

int32 UScarletSandsGameUserSettings::GetQualityPreset() const
{
	return QualityPreset;
}

void UScarletSandsGameUserSettings::SetQualityPreset(int32 InQualityPreset)
{
	if (QualityPreset != InQualityPreset)
	{
		QualityPreset = InQualityPreset;
		SetOverallScalabilityLevel(InQualityPreset);
	}
}

void UScarletSandsGameUserSettings::ApplySettings(bool bCheckForCommandLineOverrides)
{
	// Apply window mode
	SetWindowModePreference(WindowModePreference);

	// Apply quality preset
	SetQualityPreset(QualityPreset);

	// Call parent to apply all Unreal settings
	Super::ApplySettings(bCheckForCommandLineOverrides);
}
