// Fill out your copyright notice in the Description page of Project Settings.


#include "BlockHeadGameMode.h"
#include "BlockHeadGameInstance.h"
#include "BlockHeadCPPW2023/DebugHelper.h"

#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

void ABlockHeadGameMode::BeginPlay() {
	Super::BeginPlay();

	GameInstance = Cast<UBlockHeadGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	GameInstance->SetInputMode(true);

	if (DefaultHUDWidget) {
		HUDWidget = CreateWidget<UUserWidget>(GetWorld(), DefaultHUDWidget);
		HUDWidget->AddToViewport();
	} else {
		GLUTTON_LOG("No HUD specified in Game Mode Blueprint.");
	}
}

void ABlockHeadGameMode::LevelCompleted() {
	if (DefaultLevelCompleteWidget) {
		LevelCompleteWidget = CreateWidget<UUserWidget>(GetWorld(), DefaultLevelCompleteWidget);
		LevelCompleteWidget->AddToViewport();
	} else {
		UE_LOG(LogTemp, Warning, TEXT("No Default Level Complete Widget Selected!"));
	}

	// Wait two seconds before loading the next level after showing the level compete widget.
	GetWorldTimerManager().SetTimer(LevelSwapTimer, this, &ABlockHeadGameMode::NextLevel, 2.0f, false);
}

void ABlockHeadGameMode::NextLevel() {
	if (GameInstance->IsPlayerOnFinalLevel()) {
		if (LevelCompleteWidget) {
			LevelCompleteWidget->RemoveFromParent();
		}
		GameCompleted(true);
	} else {
		GameInstance->LoadNextLevel();
	}
}

void ABlockHeadGameMode::GameCompleted(bool PlayerWon) {
	if (DefaultGameCompleteWidget) {
		GameCompleteWidget = CreateWidget<UUserWidget>(GetWorld(), DefaultGameCompleteWidget);
		GameCompleteWidget->AddToViewport();

		UTextBlock* LostOrComplete = Cast<UTextBlock>(
			GameCompleteWidget->GetWidgetFromName(TEXT("LostOrComplete")));
		const FText WidgetText = PlayerWon ? FText::FromString("You Win!") : FText::FromString("You Lose!");
		LostOrComplete->SetText(WidgetText);

		GameInstance->SetInputMode(false);
	} else {
		UE_LOG(LogTemp, Warning, TEXT("No Default Game Complete Widget Selected!"));
	}
}
