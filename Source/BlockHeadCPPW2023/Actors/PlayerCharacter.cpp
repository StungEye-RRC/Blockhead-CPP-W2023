// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"

#include "EndPoint.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Obstacle.h"
#include "../DebugHelper.h"

using UEILPS = UEnhancedInputLocalPlayerSubsystem;
using UEIC = UEnhancedInputComponent;

// Sets default values
APlayerCharacter::APlayerCharacter() {
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Cube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cube"));
	RootComponent = Cube;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(Cube);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay() {
	Super::BeginPlay();

	if (!InputMappingContext) {
		GLUTTON_LOG("Mapping Context missing. Please set one in root node details");
		return;
	}

	if (const APlayerController* PlayerController = Cast<APlayerController>(GetController())) {
		const ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer();
		if (UEILPS* SubSystem = ULocalPlayer::GetSubsystem<UEILPS>(LocalPlayer)) {
			SubSystem->AddMappingContext(InputMappingContext, 0);
		}
	}

	if (Cube) {
		Cube->OnComponentHit.AddDynamic(this, &APlayerCharacter::OnHit);
		Cube->OnComponentBeginOverlap.AddDynamic(this, &APlayerCharacter::OnBeginOverlap);
	}
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if (!bLevelEnded) {
		const FVector CubeForce{ForwardForce, 0.0f, 0.0f};
		Cube->AddForce(CubeForce, NAME_None, true);
	}
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (!MoveAction) {
		GLUTTON_LOG("Move Action input action missing. Please set one in root node details");
		return;
	}

	if (UEIC* EnhancedInputComponent = CastChecked<UEIC>(PlayerInputComponent)) {
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this,
		                                   &APlayerCharacter::MoveRightLeft);
	}
}

void APlayerCharacter::MoveRightLeft(const FInputActionValue& Value) {
	const float MovementAxis = Value.Get<float>();

	if (!bLevelEnded) {
		const FVector CubeForce = FVector(0.0f, SideForce * MovementAxis, 0.0f);
		Cube->AddForce(CubeForce, NAME_None, true);
	}
}

void APlayerCharacter::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
                             FVector NormalImpulse, const FHitResult& Hit) {
	if (OtherActor->IsA(AObstacle::StaticClass()) && !bLevelEnded) {
		GLUTTON_LOG("Hit an obstacle!");
		bLevelEnded = true;
	}
}

void APlayerCharacter::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                      UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                      const FHitResult& SweepResult) {
	if (OtherActor->IsA(AEndPoint::StaticClass()) && !bLevelEnded) {
		GLUTTON_LOG("Reached the end!");
		bLevelEnded = true;
	}
}
