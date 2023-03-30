// Fill out your copyright notice in the Description page of Project Settings.


#include "BlockHeadGameMode.h"
#include "BlockHeadGameInstance.h"
#include "../GluttonTools.h"

#include "Kismet/GameplayStatics.h"

void ABlockHeadGameMode::BeginPlay() {
	Super::BeginPlay();
	GameInstance = CastChecked<UBlockHeadGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (GameInstance) {
		GameInstance->SetInputMode(true);
	}
}

void ABlockHeadGameMode::LevelCompleted() {
	GetWorldTimerManager().SetTimer(LevelSwapTimer, this, &ABlockHeadGameMode::NextLevel, 2.0f);
}

void ABlockHeadGameMode::NextLevel() {
	GameInstance->LoadNextLevel();
}

void ABlockHeadGameMode::GameCompleted(bool PlayerWon) {
}

