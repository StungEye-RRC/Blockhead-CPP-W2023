// Fill out your copyright notice in the Description page of Project Settings.


#include "BlockHeadGameMode.h"
#include "BlockHeadGameInstance.h"
#include "../GluttonTools.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

void ABlockHeadGameMode::BeginPlay() {
	Super::BeginPlay();
	GameInstance = CastChecked<UBlockHeadGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (GameInstance) {
		GameInstance->SetInputMode(true);
	}
}

void ABlockHeadGameMode::LevelCompleted() {
	if (DefaultLevelCompleteWidget) {
		LevelCompleteWidget = CreateWidget<UUserWidget>(GetWorld(), DefaultLevelCompleteWidget);
		if (LevelCompleteWidget) {
			LevelCompleteWidget->AddToViewport();
		} else {
			GLUTTON_LOG("Failed to Create Level Complete Widget!");
		}
	} else {
		GLUTTON_LOG("No Level Complete Widget Specified!");
	}
	GetWorldTimerManager().SetTimer(LevelSwapTimer, this, &ABlockHeadGameMode::NextLevel, 2.0f);
}

void ABlockHeadGameMode::NextLevel() {
	// Step 2) From within NextLevel():
	// Check if player is on the final level.
	// If so, remove the level complete widget from the viewport (Remove From Parent)
	// and call GameCompleted() with a true parameter.
	// If we are not on the final level, just load the next level via the game instance.
	if (LevelCompleteWidget) {
		LevelCompleteWidget->RemoveFromParent();
	} else {
		GLUTTON_LOG("No Level Complete Widget to Remove!");
	}

	if (GameInstance->IsPlayerOnFinalLevel()) {
		GameCompleted(true);
	} else {
		GameInstance->LoadNextLevel();
	}
}

void ABlockHeadGameMode::GameCompleted(bool PlayerWon) {
	// Step 3) From within GameCompleted():
	// Set the input mode to UI only.
	// Call the game instance's SetInputMode() function with a false parameter.
	// Create the Game Complete widget and add it to the viewport.
	// If the default game complete widget is null, log that.
	if (DefaultGameCompleteWidget) {
		GameInstance->SetInputMode(false);

		GameCompleteWidget = CreateWidget<UUserWidget>(GetWorld(), DefaultGameCompleteWidget);
		if (GameCompleteWidget) {
			GameCompleteWidget->AddToViewport();
			UTextBlock* LostOrComplete = Cast<UTextBlock>(
				GameCompleteWidget->GetWidgetFromName(FName{"LostOrComplete"}));
			const FText WinLossMessage = PlayerWon ? FText::FromString("You Won!") : FText::FromString("You Lost!");
			LostOrComplete->SetText(WinLossMessage);
		} else {
			GLUTTON_LOG("Failed to Create Game Complete Widget!");
		}
	} else {
		GLUTTON_LOG("No Default Game Complete Widget Specified!");
	}
}

// Step 4) In the Game Complete Widget.
// Write some blueprint code to :
// - Restart the game (via the game instance) when the "replay" button is clicked.
// - Exit the game (quit node) when the "quit" button is clicked.
