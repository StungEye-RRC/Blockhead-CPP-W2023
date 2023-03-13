// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

// Sets default values
APlayerCharacter::APlayerCharacter() {
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	UE_LOG(LogTemp, Warning, TEXT("Hello from C++ Player Character Constructor."));
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay() {
	Super::BeginPlay();

	int32 Answer = 42;
	float Pi = 3.14;
	FString Msg{"This is message."};

	UE_LOG(LogTemp, Warning, TEXT("Hello from C++ Player Character Begin Play."));
	UE_LOG(LogTemp, Warning, TEXT("Hello Logging int: %d"), Answer);
	UE_LOG(LogTemp, Warning, TEXT("Hello Logging float: %f"), Pi);
	UE_LOG(LogTemp, Warning, TEXT("Hello Loggin Fstring: %s"), *Msg);
	GEngine->AddOnScreenDebugMessage(0, 5.0f, FColor::Red,
	                                 FString::Printf(
		                                 TEXT("On Screen Hello Hello from C++ Player Character Begin Play: %d"),
		                                 Answer));
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
