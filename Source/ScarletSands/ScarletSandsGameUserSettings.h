// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameUserSettings.h"
#include "ScarletSandsGameUserSettings.generated.h"

/**
 * Custom Game User Settings for Scarlet Sands - manages graphics and game settings persistence
 */
UCLASS()
class SCARLETSANDS_API UScarletSandsGameUserSettings : public UGameUserSettings
{
	GENERATED_BODY()

public:
	UScarletSandsGameUserSettings();

	// Get singleton instance
	UFUNCTION(BlueprintCallable, Category = "Settings")
	static UScarletSandsGameUserSettings* GetScarletSandsGameUserSettings();

	// Graphics settings
	UFUNCTION(BlueprintCallable, Category = "Settings|Graphics")
	int32 GetWindowModePreference() const;

	UFUNCTION(BlueprintCallable, Category = "Settings|Graphics")
	void SetWindowModePreference(int32 InWindowMode);

	UFUNCTION(BlueprintCallable, Category = "Settings|Graphics")
	int32 GetQualityPreset() const;

	UFUNCTION(BlueprintCallable, Category = "Settings|Graphics")
	void SetQualityPreset(int32 InQualityPreset);

	// Override Apply to ensure our custom settings are applied
	virtual void ApplySettings(bool bCheckForCommandLineOverrides) override;

protected:
	// Window mode: 0=Fullscreen, 1=Windowed, 2=Borderless
	UPROPERTY(Config)
	int32 WindowModePreference;

	// Quality preset: 0=Low, 1=Medium, 2=High, 3=Epic
	UPROPERTY(Config)
	int32 QualityPreset;
};
