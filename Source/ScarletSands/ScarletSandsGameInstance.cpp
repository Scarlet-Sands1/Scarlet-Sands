// Copyright Epic Games, Inc. All Rights Reserved.

#include "ScarletSandsGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Save/ScarletSandsSaveGame.h"

UScarletSandsGameInstance::UScarletSandsGameInstance()
{
	DefaultSaveSlot = TEXT("SS_MainSlot");
}

void UScarletSandsGameInstance::Init()
{
	Super::Init();
	InitializeDefaultSaveSlot();
}

void UScarletSandsGameInstance::InitializeDefaultSaveSlot()
{
	// Initialize default save slot configuration if needed
}

bool UScarletSandsGameInstance::DoesSaveGameExist(const FString& SlotName) const
{
	return UGameplayStatics::DoesSaveGameExist(SlotName, 0);
}

void UScarletSandsGameInstance::CreateNewGame()
{
	// Create a new save game object
	UScarletSandsSaveGame* NewSaveGame = Cast<UScarletSandsSaveGame>(
		UGameplayStatics::CreateSaveGameObject(UScarletSandsSaveGame::StaticClass())
	);

	if (NewSaveGame)
	{
		// Initialize new game state
		NewSaveGame->InitializeNewGame();

		// Save to slot
		UGameplayStatics::SaveGameToSlot(NewSaveGame, DefaultSaveSlot, 0);

		// Load game world
		LoadGameWorld();
	}
}

void UScarletSandsGameInstance::ContinueGame()
{
	if (DoesSaveGameExist(DefaultSaveSlot))
	{
		// Load existing save game
		UScarletSandsSaveGame* LoadedGame = Cast<UScarletSandsSaveGame>(
			UGameplayStatics::LoadGameFromSlot(DefaultSaveSlot, 0)
		);

		if (LoadedGame)
		{
			// Restore game state and load world
			LoadGameWorld();
		}
	}
}

void UScarletSandsGameInstance::DeleteSaveGame(const FString& SlotName)
{
	if (DoesSaveGameExist(SlotName))
	{
		UGameplayStatics::DeleteGameInSlot(SlotName, 0);
	}
}

void UScarletSandsGameInstance::LoadTitleScreen()
{
	UGameplayStatics::OpenLevel(this, FName(TEXT("L_TitleBackdrop")));
}

void UScarletSandsGameInstance::LoadGameWorld()
{
	UGameplayStatics::OpenLevel(this, FName(TEXT("L_World_Persistent")));
}
