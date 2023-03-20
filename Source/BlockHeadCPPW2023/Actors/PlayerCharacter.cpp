// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "../GluttonTools.h"

using UEILPS = UEnhancedInputLocalPlayerSubsystem;
using UEIC = UEnhancedInputComponent;

// Sets default values
APlayerCharacter::APlayerCharacter() {
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Cube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cube"));
	Cube->SetSimulatePhysics(true);
	RootComponent = Cube;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(Cube);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay() {
	Super::BeginPlay();

	if (const APlayerController* PlayerController = Cast<APlayerController>(GetController())) {
		const ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer();
		if (UEILPS* SubSystem = ULocalPlayer::GetSubsystem<UEILPS>(LocalPlayer)) {
			if (InputMappingContext) {
				SubSystem->AddMappingContext(InputMappingContext, 0);
			} else {
				GLUTTON_LOG("No Mapping Context Selected in Blueprint.");
			}
		}
	}
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if (!bLevelEnded) {
		const FVector CubeForce = FVector(ForwardForce, 0.0f, 0.0f);
		Cube->AddForce(CubeForce, NAME_None, true);
	}
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEIC* EnhancedInputComponent = CastChecked<UEIC>(PlayerInputComponent)) {
		if (MoveAction) {
			EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this,
			                                   &APlayerCharacter::MoveRightLeft);
		} else {
			GLUTTON_LOG("No Move Action Selected in Blueprint.");
		}
	}
}

void APlayerCharacter::MoveRightLeft(const FInputActionValue& Value) {
	const float MovementAxis = Value.Get<float>();
	GLUTTON_LOG(PRINTF("Movement Axis: %f", MovementAxis));

	if (!bLevelEnded) {
		const FVector CubeForce = FVector(0.0f, MovementAxis * SideForce, 0.0f);
		Cube->AddForce(CubeForce, NAME_None, true);
	}
}
