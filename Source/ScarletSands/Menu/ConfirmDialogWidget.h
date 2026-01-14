// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "MenuWidgetBase.h"
#include "ConfirmDialogWidget.generated.h"

class UButton;
class UTextBlock;

/**
 * Confirm Dialog Widget - displays confirmation dialogs with Yes/No options
 */
UCLASS()
class SCARLETSANDS_API UConfirmDialogWidget : public UMenuWidgetBase
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	// Set dialog content
	UFUNCTION(BlueprintCallable, Category = "Confirm Dialog")
	void SetDialogContent(const FText& Title, const FText& Message);

	// Set callbacks
	void SetCallbacks(const FSimpleDelegate& OnConfirm, const FSimpleDelegate& OnCancel);

protected:
	// UI elements
	UPROPERTY(meta = (BindWidget))
	UTextBlock* TitleText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* MessageText;

	UPROPERTY(meta = (BindWidget))
	UButton* ConfirmButton;

	UPROPERTY(meta = (BindWidget))
	UButton* CancelButton;

	// Button callbacks
	UFUNCTION()
	void OnConfirmClicked();

	UFUNCTION()
	void OnCancelClicked();

private:
	FSimpleDelegate ConfirmDelegate;
	FSimpleDelegate CancelDelegate;
};
