// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuManagerSubsystem.h"
#include "MenuWidgetBase.generated.h"

/**
 * Base class for all menu widgets - handles common functionality and back navigation
 */
UCLASS()
class SCARLETSANDS_API UMenuWidgetBase : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

	// Screen type for this widget
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Menu")
	EMenuScreen ScreenType;

protected:
	// Called when back/escape is pressed
	UFUNCTION(BlueprintCallable, Category = "Menu")
	virtual void HandleBackPressed();

	// Get menu manager subsystem
	UFUNCTION(BlueprintPure, Category = "Menu")
	UMenuManagerSubsystem* GetMenuManager() const;

	// Play UI sounds
	UFUNCTION(BlueprintCallable, Category = "Menu")
	void PlayHoverSound();

	UFUNCTION(BlueprintCallable, Category = "Menu")
	void PlaySelectSound();

	UFUNCTION(BlueprintCallable, Category = "Menu")
	void PlayBackSound();

	// UI sounds
	UPROPERTY(EditDefaultsOnly, Category = "Audio")
	class USoundBase* HoverSound;

	UPROPERTY(EditDefaultsOnly, Category = "Audio")
	class USoundBase* SelectSound;

	UPROPERTY(EditDefaultsOnly, Category = "Audio")
	class USoundBase* BackSound;

private:
	UPROPERTY()
	UMenuManagerSubsystem* CachedMenuManager;
};
