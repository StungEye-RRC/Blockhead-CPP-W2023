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
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 CurrentLevel = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FName> Levels;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<TSoftObjectPtr<UWorld>> ProperLevels;

public:
	void TestMethod();
};
