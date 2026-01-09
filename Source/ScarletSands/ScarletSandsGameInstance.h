// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ScarletSandsGameInstance.generated.h"

/**
 * Game Instance for Scarlet Sands - manages persistent state across level transitions
 */
UCLASS()
class SCARLETSANDS_API UScarletSandsGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UScarletSandsGameInstance();

	virtual void Init() override;

	// Save slot management
	UFUNCTION(BlueprintCallable, Category = "Save System")
	bool DoesSaveGameExist(const FString& SlotName) const;

	UFUNCTION(BlueprintCallable, Category = "Save System")
	void CreateNewGame();

	UFUNCTION(BlueprintCallable, Category = "Save System")
	void ContinueGame();

	UFUNCTION(BlueprintCallable, Category = "Save System")
	void DeleteSaveGame(const FString& SlotName);

	// Level transitions
	UFUNCTION(BlueprintCallable, Category = "Level Management")
	void LoadTitleScreen();

	UFUNCTION(BlueprintCallable, Category = "Level Management")
	void LoadGameWorld();

protected:
	// Default save slot name
	UPROPERTY(EditDefaultsOnly, Category = "Save System")
	FString DefaultSaveSlot;

private:
	void InitializeDefaultSaveSlot();
};
