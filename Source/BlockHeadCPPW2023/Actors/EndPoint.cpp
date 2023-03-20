// Fill out your copyright notice in the Description page of Project Settings.


#include "EndPoint.h"
#include "Components/BoxComponent.h"

// Sets default values
AEndPoint::AEndPoint() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	RootComponent = CollisionBox;

	Plane = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Plane"));
	Plane->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	Plane->SetupAttachment(CollisionBox);
}

// Called when the game starts or when spawned
void AEndPoint::BeginPlay() {
	Super::BeginPlay();
}
