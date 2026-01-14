// Copyright Epic Games, Inc. All Rights Reserved.

#include "CreditsWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

void UCreditsWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ScreenType = EMenuScreen::Credits;

	InitializeCreditsText();

	if (BackButton)
	{
		BackButton->OnClicked.AddDynamic(this, &UCreditsWidget::OnBackClicked);
	}
}

void UCreditsWidget::InitializeCreditsText()
{
	if (CreditsText)
	{
		FString Credits = TEXT(
			"SCARLET SANDS\n\n"
			"A survival adventure on a mysterious island\n\n\n"
			"DEVELOPMENT\n"
			"Game Design & Programming\n"
			"Art & Animation\n"
			"Audio & Music\n\n\n"
			"SPECIAL THANKS\n"
			"Epic Games - Unreal Engine 5\n"
			"Community Contributors\n\n\n"
			"© 2024 Scarlet Sands\n"
			"All Rights Reserved"
		);

		CreditsText->SetText(FText::FromString(Credits));
	}
}

void UCreditsWidget::OnBackClicked()
{
	PlayBackSound();
	HandleBackPressed();
}
