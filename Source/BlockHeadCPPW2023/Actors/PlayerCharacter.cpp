// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "../GluttonTools.h"

using UEILPS = UEnhancedInputLocalPlayerSubsystem;
using UEIC = UEnhancedInputComponent;

// Sets default values
APlayerCharacter::APlayerCharacter() {
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	UE_LOG(LogTemp, Warning, TEXT("Hello from C++ Player Character Constructor."));
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay() {
	Super::BeginPlay();

	if (const APlayerController* PlayerController = Cast<APlayerController>(GetController())) {
		const ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer();
	UE_LOG(LogTemp, Warning, TEXT("Got Player Controller"));
		if (UEILPS* SubSystem = ULocalPlayer::GetSubsystem<UEILPS>(LocalPlayer)) {
	UE_LOG(LogTemp, Warning, TEXT("Got Local Player and SubSystem"));
			SubSystem->AddMappingContext(InputMappingContext, 0);
		}
	}

	float Pi = 3.14;

	GLUTTON_LOG("Hello from C++ Player Character Begin Play.");
	GLUTTON_LOG(PRINTF("Hello Logging float: %f", Pi));
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	UEIC* EnhancedInputComponent = CastChecked<UEIC>(PlayerInputComponent);
	if (EnhancedInputComponent) {
	UE_LOG(LogTemp, Warning, TEXT("Got Enhanced Input Compontent Binding..."));
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::MoveRightLeft);
	}
}

void APlayerCharacter::MoveRightLeft(const FInputActionValue& Value) {
	UE_LOG(LogTemp, Warning, TEXT("Hello Logging float: %f"), Value.Get<float>());
}
