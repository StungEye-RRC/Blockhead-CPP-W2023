// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "VoxelGameMode.generated.h"

/**
 * 
 */
UCLASS()
class BLOCKHEADCPPW2023_API AVoxelGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	// Constructor
	AVoxelGameMode();

	virtual void BeginPlay() override;
	// Event tick function
	virtual void Tick(float DeltaSeconds) override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Voxel")
	TSubclassOf<AActor> VoxelBPClass;

	UPROPERTY()
	TArray<AActor*> SpawnedActors;
	
};
