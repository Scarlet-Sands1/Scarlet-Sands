// Copyright Epic Games, Inc. All Rights Reserved.

#include "TitleScreenPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "../Menu/MenuManagerSubsystem.h"

ATitleScreenPlayerController::ATitleScreenPlayerController()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
}

void ATitleScreenPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// Set input mode to UI
	FInputModeUIOnly InputMode;
	SetInputMode(InputMode);
	bShowMouseCursor = true;

	// Show title screen through menu manager
	ShowTitleScreen();
}

void ATitleScreenPlayerController::ShowTitleScreen()
{
	// Get menu manager subsystem
	UGameInstance* GameInstance = GetGameInstance();
	if (GameInstance)
	{
		UMenuManagerSubsystem* MenuManager = GameInstance->GetSubsystem<UMenuManagerSubsystem>();
		if (MenuManager)
		{
			MenuManager->ShowTitleScreen();
		}
	}

	// Alternatively, create title root widget directly if set
	if (TitleRootWidgetClass && !TitleRootWidget)
	{
		TitleRootWidget = CreateWidget<UUserWidget>(this, TitleRootWidgetClass);
		if (TitleRootWidget)
		{
			TitleRootWidget->AddToViewport(0);
		}
	}
}
