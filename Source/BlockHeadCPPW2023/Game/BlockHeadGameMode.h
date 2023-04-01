// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BlockHeadGameMode.generated.h"

// Forward Declarations:
class UBlockHeadGameInstance;

UCLASS()
class BLOCKHEADCPPW2023_API ABlockHeadGameMode : public AGameModeBase {
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly)
	UBlockHeadGameInstance* GameInstance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG")
	TSubclassOf<UUserWidget> DefaultLevelCompleteWidget;
	UPROPERTY() // Prevents the widget from being garbage collected.
	UUserWidget* LevelCompleteWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG")
	TSubclassOf<UUserWidget> DefaultGameCompleteWidget;
	UPROPERTY()
	UUserWidget* GameCompleteWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG")
	TSubclassOf<UUserWidget> DefaultHUDWidget;
	UPROPERTY()
	UUserWidget* HUDWidget;

	FTimerHandle LevelSwapTimer;

public:
	void LevelCompleted();
	void NextLevel();
	void GameCompleted(bool PlayerWon);
};
