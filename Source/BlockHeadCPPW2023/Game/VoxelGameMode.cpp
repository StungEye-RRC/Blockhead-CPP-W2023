// Fill out your copyright notice in the Description page of Project Settings.


#include "VoxelGameMode.h"

#include "Kismet/GameplayStatics.h"

AVoxelGameMode::AVoxelGameMode() {
    PrimaryActorTick.bCanEverTick = true;
}

void AVoxelGameMode::BeginPlay() {
	Super::BeginPlay();

    // Spawn an instance of the selected Blueprint actor at world space (0,0,0)
    const FVector SpawnLocation = FVector(0.0f, 0.0f, 0.0f);
    const FRotator SpawnRotation = FRotator(0.0f, 0.0f, 0.0f);
    AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(VoxelBPClass, SpawnLocation, SpawnRotation);

    // Check if the actor was successfully spawned
    if (SpawnedActor)
    {
        UE_LOG(LogTemp, Log, TEXT("Successfully spawned actor of class %s"), *VoxelBPClass->GetName());
		SpawnedActors.Add(SpawnedActor);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to spawn actor of class %s"), *VoxelBPClass->GetName());
    }
}

void AVoxelGameMode::Tick(float DeltaSeconds) {
	Super::Tick(DeltaSeconds);
    // Get all actors of type VoxelBPClass
    TArray<AActor*> FoundActors;
    
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), VoxelBPClass.Get(), FoundActors);

    int32 NumVoxels = FoundActors.Num();
    UE_LOG(LogTemp, Warning, TEXT("Number of Voxels in level: %d"), NumVoxels);

}
