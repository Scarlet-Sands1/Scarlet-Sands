// Copyright Epic Games, Inc. All Rights Reserved.

#include "MenuWidgetBase.h"
#include "MenuManagerSubsystem.h"
#include "Kismet/GameplayStatics.h"

void UMenuWidgetBase::NativeConstruct()
{
	Super::NativeConstruct();

	// Cache menu manager reference
	CachedMenuManager = GetMenuManager();

	// Register with menu manager
	if (CachedMenuManager)
	{
		CachedMenuManager->RegisterWidget(ScreenType, this);
	}

	// Set input mode to UI only
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0))
	{
		FInputModeUIOnly InputMode;
		InputMode.SetWidgetToFocus(TakeWidget());
		PC->SetInputMode(InputMode);
		PC->bShowMouseCursor = true;
	}
}

void UMenuWidgetBase::NativeDestruct()
{
	// Unregister from menu manager
	if (CachedMenuManager)
	{
		CachedMenuManager->UnregisterWidget(ScreenType);
	}

	Super::NativeDestruct();
}

FReply UMenuWidgetBase::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	// Handle back/escape key
	FKey Key = InKeyEvent.GetKey();
	if (Key == EKeys::Escape || Key == EKeys::Gamepad_FaceButton_Right) // B button
	{
		HandleBackPressed();
		return FReply::Handled();
	}

	return Super::NativeOnKeyDown(InGeometry, InKeyEvent);
}

void UMenuWidgetBase::HandleBackPressed()
{
	PlayBackSound();

	if (CachedMenuManager)
	{
		CachedMenuManager->HandleBackNavigation();
	}
}

UMenuManagerSubsystem* UMenuWidgetBase::GetMenuManager() const
{
	if (CachedMenuManager)
	{
		return CachedMenuManager;
	}

	UGameInstance* GameInstance = GetGameInstance();
	if (GameInstance)
	{
		return GameInstance->GetSubsystem<UMenuManagerSubsystem>();
	}

	return nullptr;
}

void UMenuWidgetBase::PlayHoverSound()
{
	if (HoverSound && CachedMenuManager)
	{
		CachedMenuManager->PlayUISound(HoverSound);
	}
}

void UMenuWidgetBase::PlaySelectSound()
{
	if (SelectSound && CachedMenuManager)
	{
		CachedMenuManager->PlayUISound(SelectSound);
	}
}

void UMenuWidgetBase::PlayBackSound()
{
	if (BackSound && CachedMenuManager)
	{
		CachedMenuManager->PlayUISound(BackSound);
	}
}
