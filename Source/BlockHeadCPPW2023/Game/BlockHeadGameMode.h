// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BlockHeadGameMode.generated.h"

class UBlockHeadGameInstance;
/**
 * 
 */
UCLASS()
class BLOCKHEADCPPW2023_API ABlockHeadGameMode : public AGameModeBase {
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	void NextLevel();

	UPROPERTY(BlueprintReadOnly)
	UBlockHeadGameInstance* GameInstance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG")
	TSubclassOf<UUserWidget> DefaultLevelCompleteWidget;
	UPROPERTY()
	UUserWidget* LevelCompleteWidget;

	// Step 1: In the Game Mode Header File:
	// Set up the required variable and pointers for another UMG widget,
	// specifically the Game Complete widget.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG")
	TSubclassOf<UUserWidget> DefaultGameCompleteWidget;
	UPROPERTY()
	UUserWidget* GameCompleteWidget;

	FTimerHandle LevelSwapTimer;

public:
	void LevelCompleted();
	void GameCompleted(bool PlayerWon);
};
