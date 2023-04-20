// Fill out your copyright notice in the Description page of Project Settings.


#include "VoxelPawn.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
AVoxelPawn::AVoxelPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

// Called when the game starts or when spawned
void AVoxelPawn::BeginPlay()
{
	Super::BeginPlay();
    
	
}

void AVoxelPawn::Zoom(float axisValue) {
    // get delta time
    float DeltaTime = GetWorld()->GetDeltaSeconds();
	// Update the camera boom length based on the zoom input
	SpringArm->TargetArmLength += axisValue * ZoomSpeed * DeltaTime;
}

// Called every frame
void AVoxelPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    // Get a reference to the player controller
    APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
    if (PlayerController)
    {
        float MouseX, MouseY;
        PlayerController->GetInputMouseDelta(MouseX, MouseY);

        // Calculate the new camera rotation
        FQuat DeltaRot = FQuat(FVector::UpVector, MouseX * RotationSpeed * DeltaTime) * FQuat(FVector::RightVector, MouseY * RotationSpeed * DeltaTime);
        FQuat NewRotation = DeltaRot * Camera->GetRelativeRotation().Quaternion();
        SpringArm->SetWorldRotation(NewRotation.Rotator());
     }
}

// Called to bind functionality to input
void AVoxelPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
    PlayerInputComponent->BindAxis("Zoom", this, &AVoxelPawn::Zoom);

    // Capture the mouse
    APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
    if (PlayerController)
    {
        PlayerController->bShowMouseCursor = false;
        FInputModeGameOnly InputMode;
        PlayerController->SetInputMode(InputMode);
    }
}

