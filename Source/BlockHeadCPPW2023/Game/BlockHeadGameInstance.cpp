// Fill out your copyright notice in the Description page of Project Settings.


#include "BlockHeadGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "../GluttonTools.h"

void UBlockHeadGameInstance::LoadNextLevel() {
	if (CurrentLevel >= Levels.Num()) {
		GLUTTON_LOG(PRINTF("No more levels to load. Current Level: %d", CurrentLevel));
		return;
	}

	GLUTTON_LOG(PRINTF("Loading Level %d", CurrentLevel));

	UGameplayStatics::OpenLevelBySoftObjectPtr(this, Levels[CurrentLevel]);
	CurrentLevel++;
}

bool UBlockHeadGameInstance::IsPlayerOnFinalLevel() const {
	return CurrentLevel == Levels.Num();
}

void UBlockHeadGameInstance::SetInputMode(bool GameOnly) const {
	const UWorld* World = GetWorld();
	if (!World) {
		GLUTTON_LOG("Cannot Access World!");
		return;
	}

	if (APlayerController* const Controller = World->GetFirstPlayerController()) {
		if (GameOnly) {
			const FInputModeGameOnly InputMode;
			Controller->SetInputMode(InputMode);
		} else {
			const FInputModeUIOnly InputMode;
			Controller->SetInputMode(InputMode);
		}

		Controller->bShowMouseCursor = !GameOnly;
	}
}

void UBlockHeadGameInstance::LoadFirstLevel() {
	CurrentLevel = 0;
	LoadNextLevel();
}
