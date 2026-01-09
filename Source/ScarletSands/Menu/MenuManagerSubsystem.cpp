// Copyright Epic Games, Inc. All Rights Reserved.

#include "MenuManagerSubsystem.h"
#include "MenuWidgetBase.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Sound/SoundBase.h"

void UMenuManagerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	NavigationStack.Empty();
	ActiveWidgets.Empty();
}

void UMenuManagerSubsystem::Deinitialize()
{
	ClearStack();
	ActiveWidgets.Empty();
	Super::Deinitialize();
}

void UMenuManagerSubsystem::PushScreen(EMenuScreen Screen)
{
	if (Screen == EMenuScreen::None)
	{
		return;
	}

	// Hide current screen
	if (NavigationStack.Num() > 0)
	{
		HideCurrentScreen();
	}

	// Push new screen to stack
	NavigationStack.Add(Screen);

	// Show new screen
	ShowScreen(Screen);
}

void UMenuManagerSubsystem::PopScreen()
{
	if (NavigationStack.Num() <= 1)
	{
		// Can't pop the root screen
		return;
	}

	// Hide and remove current screen
	HideCurrentScreen();
	NavigationStack.Pop();

	// Show previous screen
	if (NavigationStack.Num() > 0)
	{
		ShowScreen(NavigationStack.Last());
	}
}

void UMenuManagerSubsystem::ClearStack()
{
	// Hide all screens
	for (auto& Pair : ActiveWidgets)
	{
		if (Pair.Value)
		{
			Pair.Value->RemoveFromParent();
		}
	}

	NavigationStack.Empty();
}

EMenuScreen UMenuManagerSubsystem::GetCurrentScreen() const
{
	if (NavigationStack.Num() > 0)
	{
		return NavigationStack.Last();
	}
	return EMenuScreen::None;
}

void UMenuManagerSubsystem::ShowTitleScreen()
{
	ClearStack();
	PushScreen(EMenuScreen::TitleRoot);
}

void UMenuManagerSubsystem::ShowMainMenu()
{
	PushScreen(EMenuScreen::MainMenu);
}

void UMenuManagerSubsystem::ShowSettings()
{
	PushScreen(EMenuScreen::Settings);
}

void UMenuManagerSubsystem::ShowCredits()
{
	PushScreen(EMenuScreen::Credits);
}

void UMenuManagerSubsystem::ShowConfirmDialog(const FText& Title, const FText& Message,
	const FSimpleDelegate& OnConfirm, const FSimpleDelegate& OnCancel)
{
	ConfirmDelegate = OnConfirm;
	CancelDelegate = OnCancel;
	PushScreen(EMenuScreen::ConfirmDialog);

	// Set dialog text if widget exists
	// This would be implemented in the widget itself through an interface or direct call
}

void UMenuManagerSubsystem::HandleBackNavigation()
{
	if (NavigationStack.Num() > 1)
	{
		PopScreen();
	}
	else if (GetCurrentScreen() == EMenuScreen::MainMenu)
	{
		// Show quit confirmation from main menu
		ShowConfirmDialog(
			FText::FromString(TEXT("Quit Game")),
			FText::FromString(TEXT("Are you sure you want to quit?")),
			FSimpleDelegate::CreateLambda([]() {
				UKismetSystemLibrary::QuitGame(
					GEngine->GetWorld(),
					nullptr,
					EQuitPreference::Quit,
					false
				);
			}),
			FSimpleDelegate()
		);
	}
}

void UMenuManagerSubsystem::RegisterWidget(EMenuScreen ScreenType, UMenuWidgetBase* Widget)
{
	if (Widget)
	{
		ActiveWidgets.Add(ScreenType, Widget);
	}
}

void UMenuManagerSubsystem::UnregisterWidget(EMenuScreen ScreenType)
{
	ActiveWidgets.Remove(ScreenType);
}

void UMenuManagerSubsystem::PlayUISound(USoundBase* Sound)
{
	if (Sound)
	{
		UGameplayStatics::PlaySound2D(this, Sound);
	}
}

void UMenuManagerSubsystem::TransitionToScreen(EMenuScreen Screen)
{
	HideCurrentScreen();
	ShowScreen(Screen);
}

void UMenuManagerSubsystem::HideCurrentScreen()
{
	EMenuScreen CurrentScreen = GetCurrentScreen();
	if (CurrentScreen != EMenuScreen::None)
	{
		UMenuWidgetBase* Widget = ActiveWidgets.FindRef(CurrentScreen);
		if (Widget)
		{
			Widget->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void UMenuManagerSubsystem::ShowScreen(EMenuScreen Screen)
{
	UMenuWidgetBase* Widget = GetOrCreateWidget(Screen);
	if (Widget)
	{
		Widget->SetVisibility(ESlateVisibility::Visible);
		Widget->AddToViewport(0);
	}
}

UMenuWidgetBase* UMenuManagerSubsystem::GetOrCreateWidget(EMenuScreen Screen)
{
	// Check if widget already exists
	UMenuWidgetBase* Widget = ActiveWidgets.FindRef(Screen);
	if (Widget)
	{
		return Widget;
	}

	// Create new widget from class if available
	TSubclassOf<UUserWidget>* WidgetClass = WidgetClasses.Find(Screen);
	if (WidgetClass && *WidgetClass)
	{
		UUserWidget* NewWidget = CreateWidget<UUserWidget>(GetWorld(), *WidgetClass);
		Widget = Cast<UMenuWidgetBase>(NewWidget);
		if (Widget)
		{
			RegisterWidget(Screen, Widget);
		}
	}

	return Widget;
}
