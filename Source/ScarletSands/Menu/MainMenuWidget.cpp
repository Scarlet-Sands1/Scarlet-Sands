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
	BindButtonEvents();
	UpdateContinueButtonState();
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
	}

	if (ContinueButton)
	{
		ContinueButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnContinueClicked);
	}

	if (SettingsButton)
	{
		SettingsButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnSettingsClicked);
	}

	if (CreditsButton)
	{
		CreditsButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnCreditsClicked);
	}

	if (QuitButton)
	{
		QuitButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnQuitClicked);
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
