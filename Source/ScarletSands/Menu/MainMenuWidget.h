// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "MenuWidgetBase.h"
#include "MainMenuWidget.generated.h"

class UButton;

/**
 * Main Menu Widget - handles New Game, Continue, Settings, Credits, and Quit
 */
UCLASS()
class SCARLETSANDS_API UMainMenuWidget : public UMenuWidgetBase
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

protected:
	// Button references (bound in UMG)
	UPROPERTY(meta = (BindWidget))
	UButton* NewGameButton;

	UPROPERTY(meta = (BindWidget))
	UButton* ContinueButton;

	UPROPERTY(meta = (BindWidget))
	UButton* LoadGameButton;

	UPROPERTY(meta = (BindWidget))
	UButton* SettingsButton;

	UPROPERTY(meta = (BindWidget))
	UButton* CreditsButton;

	UPROPERTY(meta = (BindWidget))
	UButton* QuitButton;

	// Button callbacks
	UFUNCTION()
	void OnNewGameClicked();

	UFUNCTION()
	void OnContinueClicked();

	UFUNCTION()
	void OnLoadGameClicked();

	UFUNCTION()
	void OnSettingsClicked();

	UFUNCTION()
	void OnCreditsClicked();

	UFUNCTION()
	void OnQuitClicked();

	// Hover callbacks for mouse focus update
	UFUNCTION()
	void OnNewGameHovered();

	UFUNCTION()
	void OnContinueHovered();

	UFUNCTION()
	void OnLoadGameHovered();

	UFUNCTION()
	void OnSettingsHovered();

	UFUNCTION()
	void OnCreditsHovered();

	UFUNCTION()
	void OnQuitHovered();

private:
	void UpdateContinueButtonState();
	void BindButtonEvents();
	bool DoesSaveExist() const;
	void SetInitialFocus();
	void UpdateLoadGameButtonState();

	// Navigation order for buttons (top to bottom)
	TArray<UButton*> NavigationOrder;
	int32 CurrentFocusIndex;
};
