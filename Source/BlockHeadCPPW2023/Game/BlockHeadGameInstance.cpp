// Fill out your copyright notice in the Description page of Project Settings.


#include "BlockHeadGameInstance.h"
#include "Engine/LevelStreaming.h"
#include "Engine/AssetManager.h"
#include "../DebugHelper.h"

void UBlockHeadGameInstance::Init() {
	Super::Init();
	GLUTTON_LOG("In UBlockHeadGameInstance::Init()");
	// Initialize the LevelArray
	InitializeLevelArray();
}

void UBlockHeadGameInstance::InitializeLevelArray() {
	// Get a reference to the current world

	TArray<FAssetData> AssetData;
	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<
		FAssetRegistryModule>("AssetRegistry");
	AssetRegistryModule.Get().GetAssetsByPackageName(FName("/All/Game/BlockHead/Maps/"), AssetData);

	GLUTTON_LOG(PREP("Size of Asset Data: %d", AssetData.Num()));
	for (auto& Asset : AssetData) {
		FString AssetName = Asset.AssetName.ToString();
		GLUTTON_LOG(AssetName);

		// Check if the asset is a level
		if (AssetName.StartsWith("/All/Game/BlockHead/Maps/") && AssetName.EndsWith(".umap")) {
			// Load the level
			ULevel* Level = LoadObject<ULevel>(nullptr, *AssetName);

			if (Level) {
				// Add the level to the array
				Levels.Add(Level);
			}
		}
	}

	// Use GLUTTON_LOG and PREP to print the number of levels in the array
	GLUTTON_LOG(PREP("Levels has %d elements", Levels.Num()));
}
