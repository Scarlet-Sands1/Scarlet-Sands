// Copyright Epic Games, Inc. All Rights Reserved.

#include "ConfirmDialogWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "MenuManagerSubsystem.h"

void UConfirmDialogWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ScreenType = EMenuScreen::ConfirmDialog;

	if (ConfirmButton)
	{
		ConfirmButton->OnClicked.AddDynamic(this, &UConfirmDialogWidget::OnConfirmClicked);
	}

	if (CancelButton)
	{
		CancelButton->OnClicked.AddDynamic(this, &UConfirmDialogWidget::OnCancelClicked);
	}
}

void UConfirmDialogWidget::SetDialogContent(const FText& Title, const FText& Message)
{
	if (TitleText)
	{
		TitleText->SetText(Title);
	}

	if (MessageText)
	{
		MessageText->SetText(Message);
	}
}

void UConfirmDialogWidget::SetCallbacks(const FSimpleDelegate& OnConfirm, const FSimpleDelegate& OnCancel)
{
	ConfirmDelegate = OnConfirm;
	CancelDelegate = OnCancel;
}

void UConfirmDialogWidget::OnConfirmClicked()
{
	PlaySelectSound();

	// Execute confirm callback
	if (ConfirmDelegate.IsBound())
	{
		ConfirmDelegate.Execute();
	}

	// Close dialog
	UMenuManagerSubsystem* MenuManager = GetMenuManager();
	if (MenuManager)
	{
		MenuManager->PopScreen();
	}
}

void UConfirmDialogWidget::OnCancelClicked()
{
	PlayBackSound();

	// Execute cancel callback
	if (CancelDelegate.IsBound())
	{
		CancelDelegate.Execute();
	}

	// Close dialog
	UMenuManagerSubsystem* MenuManager = GetMenuManager();
	if (MenuManager)
	{
		MenuManager->PopScreen();
	}
}
