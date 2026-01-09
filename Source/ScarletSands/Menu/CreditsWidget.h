// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "MenuWidgetBase.h"
#include "CreditsWidget.generated.h"

class UButton;
class UTextBlock;

/**
 * Credits Widget - displays game credits
 */
UCLASS()
class SCARLETSANDS_API UCreditsWidget : public UMenuWidgetBase
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

protected:
	// Credits text
	UPROPERTY(meta = (BindWidget))
	UTextBlock* CreditsText;

	// Back button
	UPROPERTY(meta = (BindWidget))
	UButton* BackButton;

	// Button callback
	UFUNCTION()
	void OnBackClicked();

private:
	void InitializeCreditsText();
};
