// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TitleScreenPlayerController.generated.h"

/**
 * Player Controller for Title Screen - handles UI input and menu navigation
 */
UCLASS()
class SCARLETSANDS_API ATitleScreenPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ATitleScreenPlayerController();

	virtual void BeginPlay() override;

protected:
	// Show the title screen on begin play
	UFUNCTION(BlueprintCallable, Category = "Title Screen")
	void ShowTitleScreen();

	// Widget class for title root
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<class UUserWidget> TitleRootWidgetClass;

private:
	UPROPERTY()
	class UUserWidget* TitleRootWidget;
};
