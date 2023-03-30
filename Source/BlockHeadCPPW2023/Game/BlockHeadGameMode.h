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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UBlockHeadGameInstance* GameInstance;

	FTimerHandle LevelSwapTimer;

public:
	void LevelCompleted();
	void GameCompleted(bool PlayerWon);

};
