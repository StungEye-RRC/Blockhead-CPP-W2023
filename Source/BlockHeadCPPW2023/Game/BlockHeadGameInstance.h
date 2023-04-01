// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "BlockHeadGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class BLOCKHEADCPPW2023_API UBlockHeadGameInstance : public UGameInstance {
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Game Levels")
	int32 CurrentLevel = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Game Levels")
	TArray<TSoftObjectPtr<UWorld>> Levels;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Score")
	int32 Score = 0;

public:
	void LoadNextLevel();
	bool IsPlayerOnFinalLevel() const;

	UFUNCTION(BlueprintCallable, Category = "Input Mode")
	void SetInputMode(bool GameOnly) const;

	UFUNCTION(BlueprintCallable, Category = "Game Levels")
	void LoadFirstLevel();

	UFUNCTION(BlueprintCallable, Category = "Score")
	int32 UpdateScore(int32 ScoreDelta);
};
