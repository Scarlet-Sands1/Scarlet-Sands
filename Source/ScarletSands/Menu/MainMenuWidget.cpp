// Copyright Epic Games, Inc. All Rights Reserved.

#include "MainMenuWidget.h"
#include "MenuManagerSubsystem.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "../ScarletSandsGameInstance.h"

void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ScreenType = EMenuScreen::MainMenu;
	CurrentFocusIndex = 0;

	// Build navigation order (matches button order spec: New Game, Continue, Load Game, Settings, Credits, Quit)
	NavigationOrder.Empty();
	NavigationOrder.Add(NewGameButton);
	NavigationOrder.Add(ContinueButton);
	NavigationOrder.Add(LoadGameButton);
	NavigationOrder.Add(SettingsButton);
	NavigationOrder.Add(CreditsButton);
	NavigationOrder.Add(QuitButton);

	BindButtonEvents();
	UpdateContinueButtonState();
	UpdateLoadGameButtonState();
	SetInitialFocus();
}

void UMainMenuWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	// Update continue button state in case save was created/deleted
	UpdateContinueButtonState();
}

void UMainMenuWidget::BindButtonEvents()
{
	if (NewGameButton)
	{
		NewGameButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnNewGameClicked);
		NewGameButton->OnHovered.AddDynamic(this, &UMainMenuWidget::OnNewGameHovered);
	}

	if (ContinueButton)
	{
		ContinueButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnContinueClicked);
		ContinueButton->OnHovered.AddDynamic(this, &UMainMenuWidget::OnContinueHovered);
	}

	if (LoadGameButton)
	{
		LoadGameButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnLoadGameClicked);
		LoadGameButton->OnHovered.AddDynamic(this, &UMainMenuWidget::OnLoadGameHovered);
	}

	if (SettingsButton)
	{
		SettingsButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnSettingsClicked);
		SettingsButton->OnHovered.AddDynamic(this, &UMainMenuWidget::OnSettingsHovered);
	}

	if (CreditsButton)
	{
		CreditsButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnCreditsClicked);
		CreditsButton->OnHovered.AddDynamic(this, &UMainMenuWidget::OnCreditsHovered);
	}

	if (QuitButton)
	{
		QuitButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnQuitClicked);
		QuitButton->OnHovered.AddDynamic(this, &UMainMenuWidget::OnQuitHovered);
	}
}

void UMainMenuWidget::UpdateContinueButtonState()
{
	if (ContinueButton)
	{
		bool bSaveExists = DoesSaveExist();
		ContinueButton->SetIsEnabled(bSaveExists);
	}
}

bool UMainMenuWidget::DoesSaveExist() const
{
	UScarletSandsGameInstance* GameInstance = Cast<UScarletSandsGameInstance>(GetGameInstance());
	if (GameInstance)
	{
		return GameInstance->DoesSaveGameExist(TEXT("SS_MainSlot"));
	}
	return false;
}

void UMainMenuWidget::OnNewGameClicked()
{
	PlaySelectSound();

	// Check if save exists - if so, show overwrite confirmation
	if (DoesSaveExist())
	{
		UMenuManagerSubsystem* MenuManager = GetMenuManager();
		if (MenuManager)
		{
			MenuManager->ShowConfirmDialog(
				FText::FromString(TEXT("Overwrite Save?")),
				FText::FromString(TEXT("Starting a new game will overwrite your existing save. Continue?")),
				FSimpleDelegate::CreateLambda([this]() {
					// Confirmed - start new game
					UScarletSandsGameInstance* GameInstance = Cast<UScarletSandsGameInstance>(GetGameInstance());
					if (GameInstance)
					{
						GameInstance->CreateNewGame();
					}
				}),
				FSimpleDelegate() // Cancel does nothing
			);
		}
	}
	else
	{
		// No save exists - start new game directly
		UScarletSandsGameInstance* GameInstance = Cast<UScarletSandsGameInstance>(GetGameInstance());
		if (GameInstance)
		{
			GameInstance->CreateNewGame();
		}
	}
}

void UMainMenuWidget::OnContinueClicked()
{
	PlaySelectSound();

	UScarletSandsGameInstance* GameInstance = Cast<UScarletSandsGameInstance>(GetGameInstance());
	if (GameInstance)
	{
		GameInstance->ContinueGame();
	}
}

void UMainMenuWidget::OnSettingsClicked()
{
	PlaySelectSound();

	UMenuManagerSubsystem* MenuManager = GetMenuManager();
	if (MenuManager)
	{
		MenuManager->ShowSettings();
	}
}

void UMainMenuWidget::OnCreditsClicked()
{
	PlaySelectSound();

	UMenuManagerSubsystem* MenuManager = GetMenuManager();
	if (MenuManager)
	{
		MenuManager->ShowCredits();
	}
}

void UMainMenuWidget::OnQuitClicked()
{
	PlaySelectSound();

	UMenuManagerSubsystem* MenuManager = GetMenuManager();
	if (MenuManager)
	{
		MenuManager->ShowConfirmDialog(
			FText::FromString(TEXT("Quit Game")),
			FText::FromString(TEXT("Are you sure you want to quit?")),
			FSimpleDelegate::CreateLambda([this]() {
				UKismetSystemLibrary::QuitGame(
					this,
					UGameplayStatics::GetPlayerController(this, 0),
					EQuitPreference::Quit,
					false
				);
			}),
			FSimpleDelegate() // Cancel does nothing
		);
	}
}

void UMainMenuWidget::OnLoadGameClicked()
{
	PlaySelectSound();

	// v1: Load Game is disabled/hidden - show placeholder message or navigate to Load screen
	UMenuManagerSubsystem* MenuManager = GetMenuManager();
	if (MenuManager)
	{
		// For v1.1, this would navigate to Load Game screen
		// MenuManager->ShowLoadGame();

		// For v1, just show a "Coming Soon" message via confirm dialog
		MenuManager->ShowConfirmDialog(
			FText::FromString(TEXT("Load Game")),
			FText::FromString(TEXT("Multiple save slots coming in v1.1!")),
			FSimpleDelegate(), // No action
			FSimpleDelegate()  // No action
		);
	}
}

void UMainMenuWidget::SetInitialFocus()
{
	// Focus priority: Continue (if enabled) -> New Game
	// Per spec: "If save exists → Continue, Else → New Game"

	if (ContinueButton && ContinueButton->GetIsEnabled())
	{
		// Save exists - focus Continue
		CurrentFocusIndex = 1; // Continue is second in navigation order (after New Game)
		ContinueButton->SetKeyboardFocus();
	}
	else
	{
		// No save - focus New Game
		CurrentFocusIndex = 0; // New Game is first in navigation order
		if (NewGameButton)
		{
			NewGameButton->SetKeyboardFocus();
		}
	}
}

void UMainMenuWidget::UpdateLoadGameButtonState()
{
	// v1: Load Game is disabled with "(Coming Soon)" label or hidden entirely
	// Per spec: "Hide the button entirely OR Show disabled with label"

	if (LoadGameButton)
	{
		// For v1, we disable it (UMG can show "(Coming Soon)" text in design)
		LoadGameButton->SetIsEnabled(false);

		// Alternative: Hide it entirely
		// LoadGameButton->SetVisibility(ESlateVisibility::Collapsed);
	}
}

FReply UMainMenuWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	FKey Key = InKeyEvent.GetKey();

	// Handle D-pad/arrow navigation
	if (Key == EKeys::Down || Key == EKeys::Gamepad_DPad_Down || Key == EKeys::Gamepad_LeftStick_Down)
	{
		// Move focus down
		int32 NextIndex = CurrentFocusIndex + 1;

		// Skip disabled buttons
		while (NextIndex < NavigationOrder.Num())
		{
			if (NavigationOrder[NextIndex] && NavigationOrder[NextIndex]->GetIsEnabled())
			{
				CurrentFocusIndex = NextIndex;
				NavigationOrder[CurrentFocusIndex]->SetKeyboardFocus();
				PlayHoverSound();
				return FReply::Handled();
			}
			NextIndex++;
		}

		// Wrap to top if needed
		if (NavigationOrder.Num() > 0 && NavigationOrder[0] && NavigationOrder[0]->GetIsEnabled())
		{
			CurrentFocusIndex = 0;
			NavigationOrder[CurrentFocusIndex]->SetKeyboardFocus();
			PlayHoverSound();
			return FReply::Handled();
		}
	}
	else if (Key == EKeys::Up || Key == EKeys::Gamepad_DPad_Up || Key == EKeys::Gamepad_LeftStick_Up)
	{
		// Move focus up
		int32 PrevIndex = CurrentFocusIndex - 1;

		// Skip disabled buttons
		while (PrevIndex >= 0)
		{
			if (NavigationOrder[PrevIndex] && NavigationOrder[PrevIndex]->GetIsEnabled())
			{
				CurrentFocusIndex = PrevIndex;
				NavigationOrder[CurrentFocusIndex]->SetKeyboardFocus();
				PlayHoverSound();
				return FReply::Handled();
			}
			PrevIndex--;
		}

		// Wrap to bottom if needed
		for (int32 i = NavigationOrder.Num() - 1; i >= 0; i--)
		{
			if (NavigationOrder[i] && NavigationOrder[i]->GetIsEnabled())
			{
				CurrentFocusIndex = i;
				NavigationOrder[CurrentFocusIndex]->SetKeyboardFocus();
				PlayHoverSound();
				return FReply::Handled();
			}
		}
	}

	// Let base class handle Escape/B for back navigation
	return Super::NativeOnKeyDown(InGeometry, InKeyEvent);
}

void UMainMenuWidget::OnNewGameHovered()
{
	// Update focus index when mouse hovers (per spec)
	CurrentFocusIndex = NavigationOrder.Find(NewGameButton);
	PlayHoverSound();
}

void UMainMenuWidget::OnContinueHovered()
{
	CurrentFocusIndex = NavigationOrder.Find(ContinueButton);
	PlayHoverSound();
}

void UMainMenuWidget::OnLoadGameHovered()
{
	CurrentFocusIndex = NavigationOrder.Find(LoadGameButton);
	PlayHoverSound();
}

void UMainMenuWidget::OnSettingsHovered()
{
	CurrentFocusIndex = NavigationOrder.Find(SettingsButton);
	PlayHoverSound();
}

void UMainMenuWidget::OnCreditsHovered()
{
	CurrentFocusIndex = NavigationOrder.Find(CreditsButton);
	PlayHoverSound();
}

void UMainMenuWidget::OnQuitHovered()
{
	CurrentFocusIndex = NavigationOrder.Find(QuitButton);
	PlayHoverSound();
}
