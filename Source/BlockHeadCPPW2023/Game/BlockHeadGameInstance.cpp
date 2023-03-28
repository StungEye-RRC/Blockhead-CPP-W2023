// Fill out your copyright notice in the Description page of Project Settings.


#include "BlockHeadGameInstance.h"
#include "../DebugHelper.h"
#include "Kismet/GameplayStatics.h"

void UBlockHeadGameInstance::LoadNextLevel() {
	if (CurrentLevel >= Levels.Num()) {
		GLUTTON_LOG(PREP("No More Levels Left. Current: %d", CurrentLevel));
		return;
	}

	GLUTTON_LOG(PREP("Loading Level %d", CurrentLevel));
	UGameplayStatics::OpenLevelBySoftObjectPtr(this, Levels[CurrentLevel]);
	CurrentLevel++;
}

bool UBlockHeadGameInstance::IsPlayerOnFinalLevel() const {
	return CurrentLevel >= Levels.Num();
}

void UBlockHeadGameInstance::LoadFirstLevel() {
	CurrentLevel = 0;
	LoadNextLevel();
}

void UBlockHeadGameInstance::SetInputMode(bool GameOnly) const {
	const UWorld* World = GetWorld();
	if (!World) {
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
