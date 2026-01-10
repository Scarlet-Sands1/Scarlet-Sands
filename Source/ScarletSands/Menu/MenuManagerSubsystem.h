// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "MenuManagerSubsystem.generated.h"

class UMenuWidgetBase;
class UUserWidget;

UENUM(BlueprintType)
enum class EMenuScreen : uint8
{
	None,
	TitleRoot,
	MainMenu,
	LoadGame,
	Settings,
	Credits,
	ConfirmDialog
};

/**
 * Menu Manager Subsystem - manages menu navigation stack and screen transitions
 */
UCLASS()
class SCARLETSANDS_API UMenuManagerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	// Navigation
	UFUNCTION(BlueprintCallable, Category = "Menu Manager")
	void PushScreen(EMenuScreen Screen);

	UFUNCTION(BlueprintCallable, Category = "Menu Manager")
	void PopScreen();

	UFUNCTION(BlueprintCallable, Category = "Menu Manager")
	void ClearStack();

	UFUNCTION(BlueprintCallable, Category = "Menu Manager")
	EMenuScreen GetCurrentScreen() const;

	// Widget management
	UFUNCTION(BlueprintCallable, Category = "Menu Manager")
	void ShowTitleScreen();

	UFUNCTION(BlueprintCallable, Category = "Menu Manager")
	void ShowMainMenu();

	UFUNCTION(BlueprintCallable, Category = "Menu Manager")
	void ShowSettings();

	UFUNCTION(BlueprintCallable, Category = "Menu Manager")
	void ShowCredits();

	UFUNCTION(BlueprintCallable, Category = "Menu Manager")
	void ShowConfirmDialog(const FText& Title, const FText& Message, const FSimpleDelegate& OnConfirm, const FSimpleDelegate& OnCancel);

	// Back navigation (called by widgets on Escape/B/Back)
	UFUNCTION(BlueprintCallable, Category = "Menu Manager")
	void HandleBackNavigation();

	// Widget registration (called by widgets on construct)
	void RegisterWidget(EMenuScreen ScreenType, UMenuWidgetBase* Widget);
	void UnregisterWidget(EMenuScreen ScreenType);

	// Audio playback
	UFUNCTION(BlueprintCallable, Category = "Menu Manager")
	void PlayUISound(class USoundBase* Sound);

protected:
	// Navigation stack
	UPROPERTY()
	TArray<EMenuScreen> NavigationStack;

	// Active widgets
	UPROPERTY()
	TMap<EMenuScreen, UMenuWidgetBase*> ActiveWidgets;

	// Widget classes
	UPROPERTY(EditDefaultsOnly, Category = "Menu Manager")
	TMap<EMenuScreen, TSubclassOf<UUserWidget>> WidgetClasses;

	// Confirm dialog delegates
	FSimpleDelegate ConfirmDelegate;
	FSimpleDelegate CancelDelegate;

private:
	void TransitionToScreen(EMenuScreen Screen);
	void HideCurrentScreen();
	void ShowScreen(EMenuScreen Screen);
	UMenuWidgetBase* GetOrCreateWidget(EMenuScreen Screen);
};
