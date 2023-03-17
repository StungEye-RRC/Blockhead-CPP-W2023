// Fill out your copyright notice in the Description page of Project Settings.


#include "Obstacle.h"

// Sets default values
AObstacle::AObstacle() {
	PrimaryActorTick.bCanEverTick = false;

	Cube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cube"));
	RootComponent = Cube;
}

// Called when the game starts or when spawned
void AObstacle::BeginPlay() {
	Super::BeginPlay();
}
