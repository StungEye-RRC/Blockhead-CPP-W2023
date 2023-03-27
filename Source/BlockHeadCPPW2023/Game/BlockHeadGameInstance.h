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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Levels")
	TArray<TSoftObjectPtr<UWorld>> Levels;

public:
	bool LoadNextLevel();
	bool LoadFirstLevel();
	void SetInputMode(bool GameOnly) const;
};
