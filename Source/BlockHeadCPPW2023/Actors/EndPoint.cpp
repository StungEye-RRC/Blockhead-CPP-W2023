// Fill out your copyright notice in the Description page of Project Settings.


#include "EndPoint.h"
#include "Components/BoxComponent.h"

// Sets default values
AEndPoint::AEndPoint() {
	PrimaryActorTick.bCanEverTick = false;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Box"));
	Plane = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Plane"));
	Plane->SetupAttachment(Box);
	Plane->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	RootComponent = Box;
}

// Called when the game starts or when spawned
void AEndPoint::BeginPlay() {
	Super::BeginPlay();
}
