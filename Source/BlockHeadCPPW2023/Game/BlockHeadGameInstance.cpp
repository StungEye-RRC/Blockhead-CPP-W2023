// Fill out your copyright notice in the Description page of Project Settings.


#include "BlockHeadGameInstance.h"
#include "../DebugHelper.h"
#include "Kismet/GameplayStatics.h"

void UBlockHeadGameInstance::Init() {
	Super::Init();
}

bool UBlockHeadGameInstance::LoadNextLevel() {
	if (CurrentLevel >= Levels.Num()) {
		GLUTTON_LOG(PREP("No More Levels Left. Current: %d", CurrentLevel));
		return false;
	}

	GLUTTON_LOG(PREP("Loading Level %d", CurrentLevel));
	UGameplayStatics::OpenLevelBySoftObjectPtr(this, Levels[CurrentLevel]);
	CurrentLevel++;
	return true;
}

bool UBlockHeadGameInstance::LoadFirstLevel() {
	CurrentLevel = 0;
	return LoadNextLevel();
}

void UBlockHeadGameInstance::SetInputMode(bool GameOnly) const {
	const UWorld* World = GetWorld();
	if (!World) {
		return;
	}

	if (APlayerController* Controller = World->GetFirstPlayerController()) {
		if (GameOnly) {
			const FInputModeGameOnly InputMode;
			Controller->SetInputMode(InputMode);
			Controller->bShowMouseCursor = false;
		} else {
			const FInputModeUIOnly InputMode;
			Controller->SetInputMode(InputMode);
			Controller->bShowMouseCursor = true;
		}
	}
}
